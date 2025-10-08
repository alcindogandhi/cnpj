package br.com.cnpj;

import br.com.cnpj.util.Cnpj;

public class MainApp {

	public static void main(String[] args) {
		final String cnpjs[] = { 
			"00000000/0000-00", 
			"00000000/0000-01", 
			"01.234.567/ABCD-06",
			"1234567ABCD06",
			"AB.CD1.234/5678-80", 
			"zz.zzz.zzz/zzzz-62", 
			"12.ABC.345/01DE-35" 
		};
		for (String cnpj : cnpjs) {
			System.out.println("CNPJ: " + cnpj);
			cnpj = Cnpj.removeMask(cnpj);
			System.out.println("CNPJ sem máscara: " + cnpj);
			boolean isValid = Cnpj.isValid(cnpj);
			System.out.println("CNPJ válido: " + isValid);
			if (!isValid) {
				System.out.println("");
				continue;
			}
			long code = Cnpj.encode(cnpj);
			System.out.println("CNPJ codificado: " + code);
			cnpj = Cnpj.decode(code);
			System.out.println("CNPJ decodificado: " + cnpj);
			cnpj = Cnpj.addMask(cnpj);
			System.out.println("CNPJ com máscara: " + cnpj);
			System.out.println("");
		}
	}
}
