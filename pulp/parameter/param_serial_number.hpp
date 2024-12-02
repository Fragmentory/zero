/**
 * \file param_serial_number.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Configuration parameter serial number

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#pragma once

#include "parameter.hpp"
#include "random_sequence.hpp"

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            namespace serial_number
            {
                struct serial_t
                {
                    static const size_t SIZE = 12;
                    uint8_t byte[SIZE];
                };

                /**
                    \brief Serial number parameter

                    Auto generated (read only) parameter with an unique serial number
                */
                union register_t
                {
                    uint8_t byte[serial_t::SIZE];
                    serial_t value;

                    void initialize(void);

                    void deserialize(uint8_t const *const);
                    void serialize(uint8_t **) const;
                } __attribute__((packed));

                /** \brief Global serial number parameter */
                extern register_t g_register;
            }
        }
    }
}
