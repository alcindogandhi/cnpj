#include <stdio.h>
#include <string.h>
#include "code.h"

static const uint64_t INVALID_HASH = 0xFFFFFFFFFFFFFFFF;
static const ubyte CPF_LEN = 11;
static const ubyte CNPJ_LEN = 14;
static const ubyte IE_LEN = 13;

int main() {
    const ubyte N = 20;
	char value[N], value_mask[N];
	const char *values[] = { 
		// CNPJ
		"00000000/0000-00", 
		"00000000/0000-01", 
		"01.234.567/ABCD-06",
		"1234567ABCD06",
		"AB.CD1.234/5678-80", 
		"zz.zzz.zzz/zzzz-62", 
		"12.ABC.345/01DE-35",
		"193042000196",
		"193039000172",
		"1930390001729",
		"83581000172",
		// CPF
		"01349297640",
		"013.492.976-40",
		"013.492.976-41",
		"013.492.976-AB",
		// IE
		"0017104840060",
		"3245757610016"
	};
	const uint8_t N_VALUES = sizeof(values)/sizeof(uint8_t*);

	for (uint8_t i = 0; i < N_VALUES; ++i) {
		printf("Código: %s\n", values[i]);
		code_remove_mask(values[i], value, strlen(values[i]));
		printf("Código sem máscara: %s\n", value);
		uint64_t hash = code_to_hash(values[i], strlen(values[i]));
		if (hash == INVALID_HASH) {
			printf("Código inválido\n\n");
			continue;
		}
		printf("Hash: %lu\n", hash);
		size_t len = hash_to_code(hash, value);

		if (len == CPF_LEN) {
			printf("CPF decodificado : %s\n\n", value);
		} else if (len == IE_LEN) {
			printf("IE decodificado : %s\n\n", value);
		} else if (len == CNPJ_LEN) {
			printf("CNPJ decodificado: %s\n", value);
			cnpj_add_mask(value, value_mask);
			printf("CNPJ com máscara: %s\n\n", value_mask);
		} else {
			printf("Código inválido\n\n");
		}
	}

	return 0;
}
