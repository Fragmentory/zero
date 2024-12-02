/**
 * \file param_position.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "position"

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
            namespace position
            {
                /** \brief Node position details */
                struct coordinates_t
                {
                    float latitude;
                    float longitude;
                } __attribute__((packed));

                static const size_t SIZE = sizeof(coordinates_t);

                /**
                    \brief Position parameter

                    Parameter with two float values for latitude and longitude.
                */
                union register_t
                {
                    uint8_t byte[SIZE];
                    coordinates_t value;

                    void initialize(void);

                    void deserialize(uint8_t const *const);
                    void serialize(uint8_t **) const;
                } __attribute__((packed));

                extern register_t g_register;
            }
        }
    }
}
