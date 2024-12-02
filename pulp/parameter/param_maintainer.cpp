/**
 * \file param_maintainer.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "maintainer"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "param_maintainer.hpp"

#include "identity_variant.hpp"
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
            namespace maintainer
            {
                register_t g_register = {
                    .byte = {0x00, 0x00}
                };

                /**
                    \brief Initialize field with default values
                */
                void register_t::initialize(void)
                {
                    value.identifier = identity::Variant::IDENTIFIER_DEFAULT;
                    value.hardware = identity::Variant::HW_REVISION_DEFAULT;
                    value.protocol = identity::Variant::FW_REVISION_DEFAULT;
                }

                /**
                    \brief Deserialize parameter value
                */
                void register_t::deserialize(uint8_t const *const _space)
                {
                    /* ATTENTION: NO CHECKS */
                    const uint8_t *ptr = _space;
                    word = deserialize_word(&ptr);
                }

                /**
                    \brief Serialize  parameter value
                */
                void register_t::serialize(uint8_t **_ptr) const
                {
                    /* ATTENTION: NO CHECKS */
                    serialize_word(static_cast<uint16_t>(word), _ptr);
                }
            }
        }
    }
}
