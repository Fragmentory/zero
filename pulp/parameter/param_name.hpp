/**
 * \file param_name.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Configuration parameter device name

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
            namespace name
            {
                static const uint32_t INVALID_VALUE = 0xffffffff;

                struct name_t
                {
                    static const size_t SIZE = 20;
                    uint8_t byte[SIZE];
                } __attribute__((packed));

                /**
                    \brief Serial number parameter

                    Auto generated (read only) parameter with an unique serial number
                */
                union register_t
                {
                    uint8_t byte[name_t::SIZE];
                    name_t value;

                    void initialize(void);

                    void deserialize(uint8_t const *const);
                    void serialize(uint8_t **) const;
                } __attribute__((packed));

                /** \brief Global serial number parameter */
                extern register_t g_register;

                /** \brief Global unique key parameter */
                extern uint32_t g_unique_key;
            }
        }
    }
}
