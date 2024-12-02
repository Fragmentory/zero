/**
 * \file param_features.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "features"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#pragma once

#include "macros.hpp"
#include "parameter.hpp"

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            namespace features
            {
                /** \brief Node features details */
                struct features_t
                {
                    uint16_t reserved : 16;
                } __attribute__((packed));

                static const size_t SIZE = sizeof(features_t);

                /** \brief Features parameter */
                union register_t
                {
                    uint8_t byte[SIZE];
                    features_t value;

                    void initialize(void);

                    void deserialize(uint8_t const *const);
                    void serialize(uint8_t **) const;
                } __attribute__((packed));

                /** \brief Global parameter "features" */
                extern register_t g_register;
            }
        }
    }
}
