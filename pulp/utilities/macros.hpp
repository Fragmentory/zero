/**
 * \file macros.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Data macros

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#pragma once

#include <stdint.h>

namespace common
{
    namespace macro
    {
        constexpr uint8_t HINIBLE(uint8_t x) { return static_cast<uint8_t>((x & 0xf0) >> 4u); }
        constexpr uint8_t LONIBLE(uint8_t x) { return static_cast<uint8_t>(x & 0x0f); }
        constexpr uint8_t HIBYTE(uint16_t x) { return static_cast<uint8_t>((x & 0xff00) >> 8u); }
        constexpr uint8_t LOBYTE(uint16_t x) { return static_cast<uint8_t>(x & 0x00ff); }
        constexpr uint16_t HIWORD(uint32_t x) { return static_cast<uint16_t>((x & 0xffff0000) >> 16u); }
        constexpr uint16_t LOWORD(uint32_t x) { return static_cast<uint16_t>(x & 0x0000ffff); }
        constexpr uint8_t SETBYTE(uint8_t high, uint8_t low) { return static_cast<uint8_t>(((high & 0x0f) << 4u) | (low & 0x0f)); }
        constexpr uint16_t SETWORD(uint8_t high, uint8_t low)
        {
            return static_cast<uint16_t>(((static_cast<uint16_t>(high) << 8u) | static_cast<uint16_t>(low)));
        }
        constexpr uint32_t SETLONG(uint16_t high, uint16_t low)
        {
            return static_cast<uint32_t>(((static_cast<uint32_t>(high) << 16u) | static_cast<uint32_t>(low)));
        }
        constexpr uint64_t SETHUGE(uint32_t high, uint32_t low)
        {
            return static_cast<uint64_t>(((static_cast<uint64_t>(high) << 32u) | static_cast<uint64_t>(low)));
        }
    }
}

typedef uint8_t index_t;

namespace common
{
    namespace result
    {
        /** \brief Anonymous result data type */
        enum VALUE
        {
            ERROR = 0x04,
            FAILURE = 0x01,
            SUCCESS = 0x00,
            UNKNOWN = 0x02,
            UNSUPPORTED = 0x03,

            CUSTOM = 0x80,

            UNDEFINED = 0xFF,
        };
    }

    namespace function
    {
        /** \brief Anonymous function data type */
        enum VALUE
        {
            CLEAN = 0x08,
            DISABLE = 0x03,
            ENABLE = 0x02,
            GET = 0x00,
            OFF = 0x07,
            ON = 0x06,
            SET = 0x01,
            START = 0x04,
            STOP = 0x05,

            CUSTOM = 0x80,

            UNDEFINED = 0xFF,
        };
    }
}

/** \brief Anonymous ability data type  */
typedef enum
{
    DISABLE = 0,
    ENABLE = 1
} ability_t;

/** \brief Anonymous bool data type  */
typedef enum
{
    FALSE = 0,
    TRUE = 1
} bool_t;

extern void serialize_word(uint16_t const _value, uint8_t **const _ptr);
extern uint16_t deserialize_word(uint8_t const **const _ptr);

extern void serialize_long(uint32_t const _value, uint8_t **const _ptr);
extern uint32_t deserialize_long(uint8_t const **const _ptr);

extern void serialize_float(float const _value, uint8_t **const _ptr);
extern float deserialize_float(uint8_t const **const _ptr);
