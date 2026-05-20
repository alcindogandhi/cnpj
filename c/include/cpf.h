#ifndef _cpf_h_
#define _cpf_h_

#include <stdint.h>

typedef char byte;
typedef unsigned char ubyte;

void cpf_remove_mask(const byte *in, byte *out, const size_t length);
void cpf_add_mask(const byte *in, byte *out);
bool cpf_validate(const byte* cpf);

#endif // _cpf_h_
