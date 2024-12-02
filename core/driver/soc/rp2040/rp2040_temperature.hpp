/**
 * \file rp2040_temperature.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */

/**
    \brief Handle internal temperature sensor

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#pragma once

#include "component_interface.hpp"

#include <stdint.h>

namespace core
{
    namespace soc
    {
        struct RP2040Temperature : public pulp::ComponentInterface
        {
            virtual ~RP2040Temperature() {}

            virtual void initialize(void) override;
            virtual void shutdown(void) override;

            uint16_t get_raw_value(void) const;
            float get_value(void) const;
        };
    }
}
