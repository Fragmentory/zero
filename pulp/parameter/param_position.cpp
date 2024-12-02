/**
 * \file param_position.cpp
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

#include "param_position.hpp"

#include "identity_variant.hpp"
#include "macros.hpp"

#include <stdlib.h>
#include <string.h>

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            namespace position
            {
                register_t g_register = {
                    .byte = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}
                };

                /**
                    \brief initialize field with default values

                    magic values ;)
                */
                void register_t::initialize(void)
                {
                    value.latitude = identity::Variant::MAGIC_LATITUDE;
                    value.longitude = identity::Variant::MAGIC_LONGITUDE;
                }

                /**
                    \brief Deserialize position parameter value
                */
                void register_t::deserialize(uint8_t const *const _space)
                {
                    /* ATTENTION: NO CHECKS */
                    memcpy(byte, _space, sizeof(register_t));
                }

                /**
                    \brief Serialize position parameter value
                */
                void register_t::serialize(uint8_t **_ptr) const
                {
                    /* ATTENTION: NO CHECKS */
                    memcpy(*_ptr, byte, sizeof(register_t));
                    (*_ptr) += sizeof(register_t);
                }
            }
        }
    }
}