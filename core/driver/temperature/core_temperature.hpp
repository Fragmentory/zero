/**
 * \file core_temperature.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "board_assembly.hpp"
#include "temperature_interface.hpp"

#include <cstdint>

namespace core
{
    struct CoreTemperature : public pulp::temperature::Interface
    {
        CoreTemperature(board::Assembly &_assembly) :
            assembly(_assembly)
        {
        }
        virtual float get_value(void) const;
        virtual uint16_t get_raw_value(void) const;

      private:
        board::Assembly &assembly;
    };
}
