/**
 * \file param_address.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "address"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#include "param_address.hpp"

#include "i2c_slave_variant.hpp"
#include "macros.hpp"

#include <stdlib.h>
#include <string.h>

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            namespace address
            {
                register_t g_register = {
                    .byte = {0xff, 0xff}
                };

                /**
                    \brief initialize field with default values
                */
                void register_t::initialize(void)
                {
                    value.address_0 = core::driver::i2c::slave::Variant::ADDRESS + 0;
                    value.address_1 = core::driver::i2c::slave::Variant::ADDRESS + 1;
                    value.address_2 = core::driver::i2c::slave::Variant::ADDRESS + 2;
                    value.address_3 = core::driver::i2c::slave::Variant::ADDRESS + 3;
                }

                /**
                    \brief Deserialize parameter value
                */
                void register_t::deserialize(uint8_t const *const _space)
                {
                    /* ATTENTION: NO CHECKS */
                    const uint8_t *ptr = _space;
                    value.address_0 = (static_cast<uint8_t>(*ptr++)) & ADDRESS_MASK;
                    value.address_1 = (static_cast<uint8_t>(*ptr++)) & ADDRESS_MASK;
                    value.address_2 = (static_cast<uint8_t>(*ptr++)) & ADDRESS_MASK;
                    value.address_3 = (static_cast<uint8_t>(*ptr++)) & ADDRESS_MASK;
                }

                /**
                    \brief Serialize parameter value
                */
                void register_t::serialize(uint8_t **_ptr) const
                {
                    /* ATTENTION: NO CHECKS */
                    *(*_ptr)++ = value.address_0;
                    *(*_ptr)++ = value.address_1;
                    *(*_ptr)++ = value.address_2;
                    *(*_ptr)++ = value.address_3;
                }
            }
        }
    }
}