/**
 * \file param_load.cpp
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

#include "param_load.hpp"

#include "macros.hpp"
#include "parameter_variant.hpp"

#include <stdlib.h>
#include <string.h>

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            namespace load
            {
                register_t g_register = {
                    .byte = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}
                };

                /**
                    \brief Initialize field with default values
                */
                void register_t::initialize(void)
                {
                    value.value1 = Defaults::LOAD_CALIBRATION_VALUE_1;
                    value.value2 = Defaults::LOAD_CALIBRATION_VALUE_2;
                    value.value3 = Defaults::LOAD_CALIBRATION_VALUE_3;
                }

                /**
                    \brief Deserialize load parameter value
                */
                void register_t::deserialize(uint8_t const *const _space)
                {
                    /* ATTENTION: NO CHECKS */
                    memcpy(byte, _space, sizeof(register_t));
                }

                /**
                    \brief Serialize load parameter value
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