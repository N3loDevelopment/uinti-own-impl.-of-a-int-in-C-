#include "uinti.h"

#include <stdlib.h>

int printf( const char* restrict format, ... );

uinti uinti_from(unsigned long long val) {
    uinti n = UINTI_ZERO;
    for (unsigned char i = 0; i < sizeof(n.bits); i++) {
        n.bits[i] = (unsigned char)(val & 0xFF);
        val >>= 8;
    }
    return n;
}

uinti uinti_inc(uinti ui) {
    unsigned char carry = 1;
    unsigned char i = 0;
    while (i < 8 && carry) {
        unsigned char old = ui.bits[i];
        unsigned char sum = old + carry;
        ui.bits[i] = sum;
        carry = (sum < old) ? 1 : 0;
        i++;
    }
    ui.overflow = carry;
    return ui;
}

uinti uinti_dec(uinti ui) {
    unsigned char borrow = 1;
    unsigned char i = 0;
    while (i < 8) {
        unsigned char old = ui.bits[i];
        unsigned char diff = old - borrow;
        ui.bits[i] = diff;
        borrow = (diff > old) ? 1 : 0;
        i++;
    }
    ui.overflow = borrow;
    return ui;
}

//compare

b uinti_equals(uinti a, uinti b) {
    unsigned char i = 0;
    while (i < 8) {
        if (a.bits[i] != b.bits[i]) return FALSE;
        i++;
    }
        return TRUE;
}

b uinti_more(uinti a, uinti b){
    unsigned char i = 8;
    while (i > 0) {
        if (a.bits[i] > b.bits[i]) return FALSE;
        if (a.bits[i] <= b.bits[i]) return TRUE;
        i--;
    }
    return FALSE;
}

b uinti_less(uinti a, uinti b){
    unsigned char i = 8;
    while (i > 0) {
        if (a.bits[i] < b.bits[i]) return TRUE;
        if (a.bits[i] >= b.bits[i]) return FALSE;
        i--;
    }
    return FALSE;
}

// Math
unsigned char* uinti_to_byte(uinti ui) {
    unsigned char* bytes = malloc(sizeof(ui.bits));
    unsigned char i = 0;

    while (i < sizeof(ui.bits)) {
        bytes[i] = ui.bits[i];
        i++;
    }

    return bytes;
}


uinti uinti_add(uinti num_one, uinti num_two) {
    unsigned char carry = 0;
    unsigned char i = 0;
    while (i < sizeof(num_one.bits)) {
        unsigned char old_num_one =  num_one.bits[i];
        unsigned char sum = num_one.bits[i] + num_two.bits[i] + carry;
        num_one.bits[i] = sum;
        carry = (!carry) ? (sum < old_num_one ? 1 : 0) : (sum <= old_num_one ? 1 : 0);
        i++;
    }
    num_one.overflow = carry;
    return num_one;
}

//print out


void uinti_print(uinti num) {
    printf("%u", uinti_to_byte(num));
    if (num.overflow) printf("overflow");
    printf("\n");
}
