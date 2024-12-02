/**
 * \file param_user.cpp
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

#include "param_user.hpp"

#include "macros.hpp"
#include "parameter.hpp"

#include <stddef.h>
#include <stdlib.h>

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            namespace user
            {

                /** \brief Global user register parameter */
                register_t g_register = {.value = {.byte = {0xff, 0xff}}};

                /**
                    \brief Initialize with default values
                */
                void register_t::initialize()
                {
                    value.byte[0] = 0xff;
                    value.byte[1] = 0xff;
                }

                /**
                    \brief Deserialize parameter value
                */
                void register_t::deserialize(uint8_t const *const _space)
                {
                    /* ATTENTION: NO CHECKS */
                    value.byte[0] = _space[0];
                    value.byte[1] = _space[1];
                }

                /**
                    \brief Serialize parameter value
                */
                void register_t::serialize(uint8_t **_ptr) const
                {
                    /* ATTENTION: NO CHECKS */
                    *(*_ptr)++ = value.byte[0];
                    *(*_ptr)++ = value.byte[1];
                }
            }
        }
    }
}