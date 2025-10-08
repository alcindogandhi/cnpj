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
		"1234567ABCD06",
		"AB.CD1.234/5678-80",
		"zz.zzz.zzz/zzzz-62",
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
