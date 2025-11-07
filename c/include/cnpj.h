#ifndef _cnpj_h_
#define _cnpj_h_

#include <stdint.h>

typedef char byte;
typedef unsigned char ubyte;

uint64_t cnpj_encode(const byte *in);
void cnpj_decode(uint64_t code, byte *out);
void cnpj_remove_mask(const byte *in, byte *out, const size_t length);
void cnpj_add_mask(const byte *in, byte *out);
bool cnpj_validate(const byte* cnpj);

#endif // _cnpj_h_
