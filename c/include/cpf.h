#ifndef _cnpj_h_
#define _cnpj_h_

#include <stdint.h>

typedef char byte;
typedef unsigned char ubyte;

void cpf_remove_mask(const byte *in, byte *out, const size_t length);
void cpf_add_mask(const byte *in, byte *out);
bool cpf_validate(const byte* cnpj);

#endif // _cnpj_h_
