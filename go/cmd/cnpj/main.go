package main

import (
	"cnpj/internal/util"
	"fmt"
)

func main() {
	cnpjs := []string{
		"00000000/0000-00",
		"00000000/0000-01",
		"01.234.567/ABCD-06",
		"AB.CD1.234/5678-80",
		"ZZ.ZZZ.ZZZ/ZZZZ-62",
		"12.ABC.345/01DE-35",
	}

	for _, cnpj := range cnpjs {
		fmt.Printf("CNPJ: %s\n", cnpj)
		cnpj := util.RemoveMask(cnpj)
		fmt.Printf("CNPJ sem máscara: %s\n", cnpj)
		isValid := util.Validate(cnpj)
		fmt.Printf("Validate: %t\n", isValid)
		if !isValid {
			fmt.Println()
			continue
		}
		num := util.Encode(cnpj)
		fmt.Printf("CNPJ num: %d\n", num)
		cnpj = util.Decode(num)
		fmt.Printf("CNPJ decodificado: %s\n", cnpj)
		cnpj = util.AddMask(cnpj)
		fmt.Printf("CNPJ com máscara: %s\n\n", cnpj)
	}
}

/*
int main() {
    const ubyte N = 19;
	char cnpj[N], cnpj_mask[N];
	const char *cnpjs[] = {
		"00000000/0000-00",
		"00000000/0000-01",
		"01.234.567/ABCD-06",
		"AB.CD1.234/5678-80",
		"ZZ.ZZZ.ZZZ/ZZZZ-62",
		"12.ABC.345/01DE-35"
	};
	const uint8_t N_CNPJ = sizeof(cnpjs)/sizeof(uint8_t*);
	uint64_t num = 0;
	uint8_t i;
	bool is_valid = false;

	for (i = 0; i < N_CNPJ; ++i) {
		printf("CNPJ: %s\n", cnpjs[i]);
		remove_mask(cnpjs[i], cnpj);
		printf("CNPJ sem máscara: %s\n", cnpj);
		is_valid = validate(cnpj);
		printf("Validate: %s\n", is_valid ? "true" : "false");
		if (!is_valid) {
			printf("\n");
			continue;
		}
		num = encode_cnpj(cnpj);
		printf("CNPJ num: %lu\n", num);
		decode_cnpj(num, cnpj);
		printf("CNPJ decodificado: %s\n", cnpj);
		add_mask(cnpj, cnpj_mask);
		printf("CNPJ com máscara: %s\n\n", cnpj_mask);
	}

	return 0;
}
*/
