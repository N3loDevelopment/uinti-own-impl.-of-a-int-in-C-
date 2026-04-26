#ifndef UINTI_H
#define UINTI_H

#include "b.h"

#define UINTI_ZERO { {0,0,0,0,0,0,0,0}, 0 }

typedef struct {
    unsigned char bits[8];
    unsigned char overflow;
} uinti;

uinti uinti_from(unsigned long long val);
uinti uinti_inc(uinti ui);
uinti uinti_dec(uinti ui);

b uinti_more(uinti a, uinti b);
b uinti_less(uinti a, uinti b);
b uinti_equals(uinti a, uinti b);

//math
uinti uinti_add(uinti a, uinti b);
void uinti_print(uinti a);

unsigned char* uinti_to_byte(uinti ui);


#endif
