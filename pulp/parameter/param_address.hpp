/**
 * \file param_address.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "backlight"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#pragma once

#include "parameter.hpp"

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            namespace address
            {
                static const uint8_t ADDRESS_MASK = 0x7f;

                /** \brief Node backlight details */
                struct address_t
                {
                    uint8_t address_0;
                    uint8_t address_1;
                    uint8_t address_2;
                    uint8_t address_3;
                } __attribute__((packed));

                static const size_t SIZE = sizeof(address_t);

                /**
                    \brief Address default configuration.
                */
                union register_t
                {
                    uint8_t byte[SIZE];
                    address_t value;

                    void initialize(void);

                    void deserialize(uint8_t const *const);
                    void serialize(uint8_t **) const;
                } __attribute__((packed));

                extern register_t g_register;
            }
        }
    }
}
