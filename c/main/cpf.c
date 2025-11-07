#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cpf.h"

int main() {
    const ubyte N = 15;
	char cpf[N], cpf_mask[N];
	const char *cpfs[] = { 
		"000.000.000-00",
		"00000000001",
		"111.444.777-35"
	};
	const uint8_t N_CPFS = sizeof(cpfs)/sizeof(uint8_t*);

	for (uint8_t i = 0; i < N_CPFS; ++i) {
		const size_t length = strlen(cpfs[i]);
		printf("CPF: %s\n", cpfs[i]);
		cpf_remove_mask(cpfs[i], cpf, length);
		printf("CPF sem máscara: %s\n", cpf);
		const bool is_valid = cpf_validate(cpf);
		printf("Validate: %s\n", is_valid ? "true" : "false");
		if (!is_valid) {
			printf("\n");
			continue;
		}
		cpf_add_mask(cpf, cpf_mask);
		printf("CPF com máscara: %s\n\n", cpf_mask);
	}

	return 0;
}
