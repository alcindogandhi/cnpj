#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cnpj.h"

int main() {
    const ubyte N = 19;
	char cnpj[N], cnpj_mask[N];
	const char *cnpjs[] = { 
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
		"83581000172"
	};
	const uint8_t N_CNPJ = sizeof(cnpjs)/sizeof(uint8_t*);

	for (uint8_t i = 0; i < N_CNPJ; ++i) {
		const size_t length = strlen(cnpjs[i]);
		printf("CNPJ: %s\n", cnpjs[i]);
		cnpj_remove_mask(cnpjs[i], cnpj, length);
		printf("CNPJ sem máscara: %s\n", cnpj);
		const bool is_valid = cnpj_validate(cnpj);
		printf("Validate: %s\n", is_valid ? "true" : "false");
		if (!is_valid) {
			printf("\n");
			continue;
		}
		const uint64_t num = cnpj_encode(cnpj);
		printf("CNPJ num: %lu\n", num);		
		cnpj_decode(num, cnpj);
		printf("CNPJ decodificado: %s\n", cnpj);
		cnpj_add_mask(cnpj, cnpj_mask);
		printf("CNPJ com máscara: %s\n\n", cnpj_mask);
	}

	return 0;
}
