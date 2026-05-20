
#include "code.h"

static const ubyte CPF_LEN = 11;
static const ubyte CNPJ_LEN = 12;
static const ubyte CNPJ_DV_LEN = CNPJ_LEN + 2;
static const ubyte IE_LEN = 13;
static const ubyte MAX_LEN = CNPJ_DV_LEN + 1;

static const uint64_t INVALID_HASH = 0xFFFFFFFFFFFFFFFF;
static const uint64_t CPF_HASH_MASK = 0x8000000000000000;
static const uint64_t IE_HASH_MASK = 0xC000000000000000;

static const ubyte CPF_BASE = 36;
static const ubyte CNPJ_BASE = 36;
static const ubyte IE_BASE = 10;

static const byte CNPJ_WEIGHT_1[] = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
static const byte CNPJ_WEIGHT_2[] = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};

static inline byte encode(const byte c) {
	return (c < 'A') ? (c - '0') : (c < 'a') ? (c - 'A' + 10) : (c - 'a' + 10);
}

static inline byte decode(const byte d) {
	return (d < 10) ? (d + '0') : (d - 10 + 'A');
}

size_t code_remove_mask(const byte * const in, byte * const out, const size_t in_len) {
    const byte *p_in = in + in_len - 1;
	byte *p_out = out + CNPJ_DV_LEN - 1;
    size_t count = 0;

    out[CNPJ_DV_LEN] = 0;
	for (; (p_in >= in) && (p_out >= out); --p_in) {
		if (isalnum(*p_in)) {
			*(p_out--) = *p_in;
            ++count;
		}
	}
	for (; p_out >= out; --p_out) {
		*p_out = '0';
	}
    for (; (p_in >= in); --p_in) {
		if (isalnum(*p_in)) {
            ++count;
		}
	}
    return count;
}

void cnpj_add_mask(const byte *in, byte *out) {
	byte i;
	for (i = 0; i < 2; ++i) {
		*(out++) = *(in++);
	}
	*(out++) = '.';
	for (i = 2; i < 5; ++i) {
		*(out++) = *(in++);
	}
	*(out++) = '.';
	for (i = 5; i < 8; ++i) {
		*(out++) = *(in++);
	}
	*(out++) = '/';
	for (i = 8; i < 12; ++i) {
		*(out++) = *(in++);
	}
	*(out++) = '-';
	for (i = 12; i < 14; ++i) {
		*(out++) = *(in++);
	}
	*out = 0;
}

static int16_t dot_product(const byte *v1, const byte *v2) {
	uint16_t sum = 0, c = 0;
	const byte *end = v1 + CNPJ_LEN;
	for (; v1 != end; ++v1, ++v2) {
		c = (*v2 < 'a') ? *v2 : (*v2 - 'a' + 'A');
		sum += *v1 * (c - '0');
	}
	return sum;
}

static int8_t calc_dv(const byte *v) {
	int16_t d1 = dot_product(CNPJ_WEIGHT_1, v) % 11;
	int16_t d2 = dot_product(CNPJ_WEIGHT_2, v);

	d1 = (d1 > 1) ? 11 - d1 : 0;
	d2 += d1*CNPJ_WEIGHT_2[CNPJ_DV_LEN-2];
	d2 %= 11;
	d2 = (d2 > 1) ? 11 - d2 : 0;

	return (int8_t)(10*d1 + d2);
}

static bool cnpj_validate(const byte* cnpj) {
	int8_t dv = 0;
	
	if (!isdigit(cnpj[CNPJ_DV_LEN - 2]) || !isdigit(cnpj[CNPJ_DV_LEN - 1])) {
		return false;
	}

	dv = 10*(cnpj[CNPJ_DV_LEN - 2]-'0') + (cnpj[CNPJ_DV_LEN - 1]-'0');
	return (calc_dv(cnpj) == dv);
}

static uint64_t code_encode(const byte *in, const ubyte len, const ubyte base) {
    uint64_t code = 0;
	const byte *end = in + len;
	for (; in != end; ++in) {
		code = base*code + encode(*in);
	}
	return code;
}

static void code_decode(uint64_t value, byte *out, const ubyte len, const ubyte base) {
	byte *p = out + len - 1;
	byte *end = out - 1;
	for (; p != end; --p) {
		*p = decode(value % base);
		value /= base;
	}
	*(out+len) = 0;
}

static void cnpj_add_dv(byte *out) {
	byte dv = calc_dv(out);
	out[CNPJ_DV_LEN - 2] = dv / 10 + '0';
	out[CNPJ_DV_LEN - 1] = dv % 10 + '0';
	out[CNPJ_DV_LEN] = 0;
}

static bool ie_validate(const byte *in) {
    const byte * const end = in + IE_LEN;
    for (; in != end; ++in) {
        if (!isdigit(*in)) {
            return false;
        }
    }
    return true;
}

uint64_t code_to_hash(const byte * const in, const size_t len) {
    byte code[MAX_LEN];
    size_t clean_len = code_remove_mask(in, code, len);
    if (clean_len > CNPJ_DV_LEN) {
        return INVALID_HASH;
    }
    if (cnpj_validate(code)) {
        return code_encode(code, CNPJ_LEN, CNPJ_BASE);
    }
    if (clean_len == CNPJ_DV_LEN) {
        return INVALID_HASH;
    }
    if (clean_len <= CPF_LEN) {
        const byte *cpf_code = code + (CNPJ_DV_LEN - CPF_LEN);
        return CPF_HASH_MASK + code_encode(cpf_code, CPF_LEN, CPF_BASE);
    }
    if (clean_len <= IE_LEN) {
		const byte *ie_code = code + (CNPJ_DV_LEN - IE_LEN);
		if (ie_validate(ie_code)) {
        	return IE_HASH_MASK + code_encode(ie_code, IE_LEN, IE_BASE);
		}
		return INVALID_HASH;
    }
    return INVALID_HASH;
}

size_t hash_to_code(uint64_t hash, byte *out) {
	if (hash == INVALID_HASH) {
		out[0] = 0;
		return 0;
	}
	if ((hash & IE_HASH_MASK) == IE_HASH_MASK) {
		hash -= IE_HASH_MASK;
		code_decode(hash, out, IE_LEN, IE_BASE);
		return IE_LEN;
	}
	if ((hash & CPF_HASH_MASK) == CPF_HASH_MASK) {
		hash -= CPF_HASH_MASK;
		code_decode(hash, out, CPF_LEN, CPF_BASE);
		return CPF_LEN;
	}
	code_decode(hash, out, CNPJ_DV_LEN-2, CNPJ_BASE);
	cnpj_add_dv(out);
	return CNPJ_DV_LEN;
}
