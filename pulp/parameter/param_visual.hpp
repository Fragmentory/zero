/**
 * \file param_visual.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "visual-feedback"

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
            namespace visual
            {

                /** \brief Node visual-feedback details */
                struct visual_t
                {
                    uint8_t mode;
                    uint8_t verbosity;
                    uint16_t timeout;
                } __attribute__((packed));

                static const size_t SIZE = sizeof(visual_t);

                /**
                    \brief Visual-feedback parameter

                    Visual-feedback default configuration.
                */
                union register_t
                {
                    uint8_t byte[SIZE];
                    visual_t value;

                    void initialize(void);

                    void deserialize(uint8_t const *const);
                    void serialize(uint8_t **) const;
                } __attribute__((packed));

                extern register_t g_register;
            }
        }
    }
}
