#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "cpf.h"

static const ubyte N = 9;

static const byte PESO1[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2 };
static const byte PESO2[] = { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2 };

static inline byte encode(const byte c) {
	return (c - '0');
}

static inline byte decode(const byte d) {
	return (d + '0');
}

static int16_t dot_product(const byte *v1, const byte *v2) {
	uint16_t sum = 0, c = 0;
	const byte *end = v1 + N;
	for (; v1 != end; ++v1, ++v2) {
		c = (*v2 < 'a') ? *v2 : (*v2 - 'a' + 'A');
		sum += *v1 * (c - '0');
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

void cpf_remove_mask(const byte * const in, byte * const out, const size_t length) {
	const ubyte cpf_len = N + 2;
	const byte *p_in = in + length - 1;
	byte *p_out = out + cpf_len - 1;

	out[cpf_len] = 0;
	for (; (p_in >= in) && (p_out >= out); --p_in) {
		if (isalnum(*p_in)) {
			*(p_out--) = *p_in;
		}
	}
	for (; p_out >= out; --p_out) {
		*p_out = '0';
	}
}

void cpf_add_mask(const byte *in, byte *out) {
	byte i;
	for (i = 0; i < 3; ++i) {
		*(out++) = *(in++);
	}
	*(out++) = '.';
	for (i = 3; i < 6; ++i) {
		*(out++) = *(in++);
	}
	*(out++) = '.';
	for (i = 6; i < 9; ++i) {
		*(out++) = *(in++);
	}
	*(out++) = '-';
	for (i = 9; i < 11; ++i) {
		*(out++) = *(in++);
	}
	*out = 0;
}

bool cpf_validate(const byte* cnpj) {
	const size_t len = strlen(cnpj);
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
