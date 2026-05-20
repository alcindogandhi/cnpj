/**
 * @file code.h
 * @author Alcindo Almeida
 * @brief Declarações de funções para manipulação de códigos de CPF, CNPJ e IE.
 * @date 2024-05-20
 * @description Este arquivo contém as declarações de funções para manipulação de códigos 
 * de CPF, CNPJ e IE, incluindo a remoção de máscaras, adição de máscaras e conversão 
 * entre códigos e hashes.
 */

#ifndef _code_h_
#define _code_h_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef char byte;
typedef unsigned char ubyte;

void cnpj_add_mask(const byte *in, byte *out);
size_t code_remove_mask(const byte * const in, byte * const out, const size_t in_len);
uint64_t code_to_hash(const byte * const in, const size_t len);
size_t hash_to_code(uint64_t hash, byte *out);

#endif // _code_h_
