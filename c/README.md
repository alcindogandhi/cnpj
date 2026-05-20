# CNPJ

## Biblioteca para manipulação de CNPJ alfanumérico.

Esta biblioteca em linguagem C contém funções para geração de hashes reversíveis de 64 bits para manipulação de CNPJ alfanumérico.

Com a mudança do CNPJ do formato numérico para alfanumérico ([link](https://www.gov.br/receitafederal/pt-br/acesso-a-informacao/acoes-e-programas/programas-e-atividades/cnpj-alfanumerico)), não é mais possível representar o CNPJ em campos do tipo inteiro, o que pode gerar problemas de desempenho em bancos de dados que não suportam índices, como é o caso de alguns bancos analíticos distribuídos como o [IBM Netezza](https://www.ibm.com/br-pt/products/netezza).

---
### CNPJ

Para resolver esse problema, foi criada uma função hash reversível que a string do CNPJ em um número de até 63 bits. Ela funciona desprezando os dígitos verificadores e lendo os 12 dígitos significativos como um número na base 36 (10 dígitos e 26 letras) e efetuando a conversão para base 10. O código fonte dessas funções está disponível em [cnpj.c](src/cnpj.c) e um exemplo de utilização pode ser visto [aqui](main/cnpj.c).

---
### CODE

Em alguns casos específicos, por problemas de modelagem de dados, utilizam-se em uma mesmo campo valores de CNPJ, CPF e IE (Inscrição Estadual). Para esses casos, foi criada uma função de hash para CPF e IE e utilizando os dois bits mais significativos para diferenciar a função de hash usada:

- 0X: CNPJ
- 10: CPF
- 11: IE

No caso do CPF, a função de hash usada é a mesma do CNPJ, sem desprezar o dígito verificador, somada com a máscara do CPF (0x8000000000000000). Com isso, ela já está adaptada para um possível CPF alfanumérico, desde que ele não altere a quantidade de dígitos. Já no caso da IE, o hash é calculado somando o número da IE com a máscara da IE (0xC000000000000000)
O código fonte dessas funções está disponível em [code.c](src/code.c) e um exemplo de utilização pode ser visto [aqui](main/code.c).

---
### CPF

Por fim, no arquivo [cpf.c](src/cpf) estão disponíveis funções de validação, remoção e adição de máscara.
