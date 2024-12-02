/**
 * \file param_features.cpp
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

#include "param_features.hpp"

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
            namespace features
            {

                register_t g_register = {
                    .byte = {0xff, 0xff}
                };

                /**
                    \brief Initialize features field with default values
                */
                void register_t::initialize(void) {}

                /**
                    \brief Set features level parameter value
                */
                void register_t::deserialize(uint8_t const *const _space)
                {
                    /* ATTENTION: NO CHECKS */
                    byte[0] = _space[0];
                    byte[1] = _space[1];
                }

                /**
                    \brief Serialize parameter value
                */
                void register_t::serialize(uint8_t **_ptr) const
                {
                    /* ATTENTION: NO CHECKS */
                    *(*_ptr)++ = byte[0];
                    *(*_ptr)++ = byte[1];
                }
            }
        }
    }
}