/**
 * \file random.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Random number and sequences generator

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "random_sequence.hpp"

#include "checksum.hpp"
#include "macros.hpp"

#include <cassert>
#include <cstdlib>

namespace core::service
{
    static uint8_t create_random(const uint8_t _value);

    /**
        \brief random generator initialization
    */
    void RandomSequence::initialize(void)
    {
        assert(state == pulp::COMPONENT_STATE::UNDEFINED); // random generator not initialized
        state = pulp::COMPONENT_STATE::IDLE;

        const uint16_t MASK = 0x00ff;

        /* calculate seed (paranoid) */
        const uint8_t value = static_cast<uint8_t>(temperature.get_raw_value() & MASK);
        const uint8_t result = 1 + create_random(value);
        uint16_t seed = result;

        for (uint8_t i = 0; i < result; ++i)
        {
            const uint8_t value = static_cast<uint8_t>(temperature.get_raw_value() & MASK);
            uint8_t byte = create_random(value);
            seed = checksum_crc_byte(byte, seed);
        }

        srand(seed);
    }

    void RandomSequence::shutdown()
    {
        assert(state != pulp::COMPONENT_STATE::UNDEFINED);
        state = pulp::COMPONENT_STATE::UNDEFINED;
    }

    /**
        \brief Create random sequence
    */
    void RandomSequence::create(chunk_t &_sequence) const
    {
        assert(state == pulp::COMPONENT_STATE::IDLE); // random sequence, generator uninitialized

        /* calculate sequence item */
        uint8_t *ptr = _sequence.space;
        size_t len = _sequence.size & ~0x01;

        if (len < 2)
            return;

        for (uint8_t i = 0; i < len; i += 2)
        {
            uint16_t tmp = static_cast<unsigned int>(rand()) & 0xffff;
            *ptr++ = common::macro::HIBYTE(tmp);
            *ptr++ = common::macro::LOBYTE(tmp);
        }

        if (_sequence.size & 0x01)
        {
            uint16_t tmp = static_cast<unsigned int>(rand()) & 0xffff;
            *ptr++ = common::macro::HIBYTE(tmp);
        }
    }

    /**
     * \brief create random byte
     */
    uint8_t create_random(const uint8_t _value)
    {
        uint8_t result = 0x00;
        uint8_t mask = 0x01;

        for (int i = 0; i < 11; ++i)
        {
            uint8_t tmp = _value;

            if (tmp & mask)
            {
                result |= mask;
            }
            else
            {
                result &= static_cast<uint8_t>(~mask);
            }

            if (mask == 0x80)
            {
                mask = 1;
            }
            else
            {
                mask <<= 1;
            }
        }

        return result;
    }
}
