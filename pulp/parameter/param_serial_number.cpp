/**
 * \file param_serial_number.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Configuration parameter serial number

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "param_serial_number.hpp"

#include "macros.hpp"
#include "parameter.hpp"
#include "pulp.hpp"

#include <stdlib.h>
#include <string.h>

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            namespace serial_number
            {
                register_t g_register = {.value = {.byte = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}}};

                /**
                    \brief Initialize with default values
                */
                void register_t::initialize() {}

                /**
                    \brief Deserialize parameter value from chunk
                */
                void register_t::deserialize(uint8_t const *const _space)
                {
                    /* ATTENTION: NO CHECKS */
                    memcpy(value.byte, _space, serial_t::SIZE);
                }

                /**
                    \brief Serialize parameter value to chunk
                */
                void register_t::serialize(uint8_t **_ptr) const
                {
                    /* ATTENTION: NO CHECKS */
                    memcpy(*_ptr, value.byte, serial_t::SIZE);
                    (*_ptr) += serial_t::SIZE;
                }
            }
        }
    }
}
