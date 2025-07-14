#ifndef _cnpj_h_
#define _cnpj_h_

#include <stdint.h>

typedef char byte;
typedef unsigned char ubyte;

uint64_t encode_cnpj(const byte *in);
void decode_cnpj(uint64_t code, byte *out);
void remove_mask(const byte *in, byte *out);
void add_mask(const byte *in, byte *out);
bool validate(const byte* cnpj);

#endif // _cnpj_h_
