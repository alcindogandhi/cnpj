#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "cnpj.h"

static const ubyte BASE = 36;
static const ubyte N = 12;

static const byte PESO1[] = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
static const byte PESO2[] = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};

extern inline byte encode(const byte c) {
	return (c < 'A') ? (c - '0') : (c - 'A' + 10);
}

extern inline byte decode(const byte d) {
	return (d < 10) ? (d + '0') : (d - 10 + 'A');
}

static int16_t dot_product(const byte *v1, const byte *v2) {
	uint16_t sum = 0;
	const byte *end = v1 + N;
	for (; v1 != end; ++v1, ++v2) {
		sum += *v1 * (*v2 - '0');
	}
	return sum;
}

static int8_t calc_dv(const byte *v) {
	int16_t d1 = dot_product(PESO1, v) % 11;
	int16_t d2 = dot_product(PESO2, v);

	d1 = (d1 > 1) ? 11 - d1 : 0;
	d2 += d1*PESO2[N];
	d2 %= 11;
	d2 = (d2 > 1) ? 11 - d2 : 0;

	return (int8_t)(10*d1 + d2);
}

uint64_t encode_cnpj(const byte *in) {
	uint64_t code = 0;
	const byte *end = in + N;
	for (; in != end; ++in) {
		code = BASE*code + encode(*in);
	}
	return code;
}

void decode_cnpj(uint64_t code, byte *out) {
	byte *p = out + N - 1;
	byte *end = out - 1;
	byte dv = 0;
	for (; p != end; --p) {
		*p = decode(code % BASE);
		code /= BASE;
	}
	dv = calc_dv(out);
	out[N] = dv / 10 + '0';
	out[N+1] = dv % 10 + '0';
	out[N+2] = 0;
}

void remove_mask(const byte *in, byte *out) {
	for (; *in; ++in) {
		if (isalnum(*in))
			*(out++) = *in;
	}
	*out = 0;
}

void add_mask(const byte *in, byte *out) {
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

bool validate(const byte* cnpj) {
	size_t len = strlen(cnpj);
	int8_t i, dv = 0;
	
	if (len != (size_t)N+2)
		return false;

	if (!isdigit(cnpj[N]) || !isdigit(cnpj[N+1]))
		return false;

	for (i = 0; i < N; ++i) {
		if (!isalnum(cnpj[i]))
			return false;
	}

	dv = 10*(cnpj[N]-'0') + (cnpj[N+1]-'0');
	return (calc_dv(cnpj) == dv);
}
