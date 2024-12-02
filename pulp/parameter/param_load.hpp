/**
 * \file param_load.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "load"

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
            namespace load
            {
                /** \brief Node load calibration details */
                struct calibration_t
                {
                    float value1;
                    float value2;
                    float value3;
                    float value4;
                    float value5;
                } __attribute__((packed));

                static const size_t SIZE = sizeof(calibration_t);

                /**
                    \brief Load calibration parameter
                */
                union register_t
                {
                    uint8_t byte[SIZE];
                    calibration_t value;

                    void initialize(void);

                    void deserialize(uint8_t const *const);
                    void serialize(uint8_t **) const;
                } __attribute__((packed));

                extern register_t g_register;
            }
        }
    }
}