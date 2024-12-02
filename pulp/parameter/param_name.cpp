/**
 * \file param_name.cpp
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

#include "param_name.hpp"

#include "engine.hpp"
#include "macros.hpp"
#include "parameter.hpp"

#include <stdlib.h>
#include <string.h>

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            namespace name
            {

                uint32_t g_unique_key = INVALID_VALUE;
                register_t g_register = {.value = {.byte = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}}};

                /**
                    \brief Initialize with default values
                */
                void register_t::initialize(void) {}

                /**
                    \brief Deserialize parameter value from chunk
                */
                void register_t::deserialize(uint8_t const *const _space)
                {
                    /* ATTENTION: NO CHECKS */
                    memcpy(value.byte, _space, name_t::SIZE);
                }

                /**
                    \brief Serialize parameter value to chunk
                */
                void register_t::serialize(uint8_t **_ptr) const
                {
                    /* ATTENTION: NO CHECKS */
                    memcpy(*_ptr, value.byte, name_t::SIZE);
                    (*_ptr) += name_t::SIZE;
                }
            }
        }
    }
}