/**
 * \file param_user.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "user register"

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
            namespace user
            {
                struct user_t
                {
                    static const size_t SIZE = 2;
                    uint8_t byte[SIZE];
                };

                /** \brief User register; ignored by firmware. */
                union register_t
                {
                    uint8_t byte[user_t::SIZE];
                    user_t value;

                    void initialize(void);

                    void deserialize(uint8_t const *const);
                    void serialize(uint8_t **) const;
                } __attribute__((packed));

                /** \brief Global user register parameter */
                extern register_t g_register;
            }
        }
    }
}