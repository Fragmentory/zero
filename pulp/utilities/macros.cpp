/**
 * \file macros.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Data types

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "macros.hpp"

#include <stdint.h>

extern void serialize_word(uint16_t const _value, uint8_t **const _ptr)
{
    /* ATTENTION: NO CHECKS */
    *(*_ptr)++ = (uint8_t)common::macro::HIBYTE(_value);
    *(*_ptr)++ = (uint8_t)common::macro::LOBYTE(_value);
}

extern uint16_t deserialize_word(uint8_t const **const _ptr)
{
    /* ATTENTION: NO CHECKS */
    uint8_t byte1 = *(*_ptr)++;
    uint8_t byte2 = *(*_ptr)++;
    return (uint16_t)common::macro::SETWORD(byte1, byte2);
}

extern void serialize_long(uint32_t const _value, uint8_t **const _ptr)
{
    /* ATTENTION: NO CHECKS */
    *(*_ptr)++ = (uint8_t)common::macro::HIBYTE(common::macro::HIWORD(_value));
    *(*_ptr)++ = (uint8_t)common::macro::LOBYTE(common::macro::HIWORD(_value));
    *(*_ptr)++ = (uint8_t)common::macro::HIBYTE(common::macro::LOWORD(_value));
    *(*_ptr)++ = (uint8_t)common::macro::LOBYTE(common::macro::LOWORD(_value));
}

extern uint32_t deserialize_long(uint8_t const **const _ptr)
{
    /* ATTENTION: NO CHECKS */
    uint8_t byte1 = *(*_ptr)++;
    uint8_t byte2 = *(*_ptr)++;
    uint8_t byte3 = *(*_ptr)++;
    uint8_t byte4 = *(*_ptr)++;
    return (uint32_t)common::macro::SETLONG(common::macro::SETWORD(byte1, byte2), common::macro::SETWORD(byte3, byte4));
}

/**
    \brief Serialize float

    \internal

    Some serialized float values:

    -1.0 : 00 00 80 bf
     1.0 : 00 00 80 3f
     0.0 : 00 00 00 00

    Code for https://www.tutorialspoint.com/compile_c99_online.php:

    #include <stdio.h>

    void foo(float x) {
        unsigned char* xx = (unsigned char*)&x;
        for (int i = 0; i < 4; ++i) {
            printf("%02x ", xx[i]);
        }
        printf("\n");
    }

    int main() {
        printf("Hello, World!\n");

        unsigned char bla[] = {0xbf, 0x80 , 0x00, 0x00};

        float blub = *(float*)bla;

        printf("%f\n", blub);


        foo(-1.0);
        foo(1.0);
        foo(0.0);


        return 0;
    }

*/
extern void serialize_float(float const _value, uint8_t **const _ptr)
{
    /* ATTENTION: NO CHECKS */
    uint8_t const *const array = ((uint8_t const *)&_value);
    *(*_ptr)++ = array[0];
    *(*_ptr)++ = array[1];
    *(*_ptr)++ = array[2];
    *(*_ptr)++ = array[3];
}

extern float deserialize_float(uint8_t const **const _ptr)
{
    /* ATTENTION: NO CHECKS */
    uint8_t array[4];
    array[0] = *(*_ptr)++;
    array[1] = *(*_ptr)++;
    array[2] = *(*_ptr)++;
    array[3] = *(*_ptr)++;
    return *(float *)(array);
}
