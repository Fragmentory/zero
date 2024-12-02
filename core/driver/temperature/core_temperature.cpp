/**
 * \file core_temperature.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "core_temperature.hpp"

#include "board_assembly.hpp"

namespace core
{
    float CoreTemperature::get_value(void) const { return assembly.soc.get_temperature(); }

    uint16_t CoreTemperature::get_raw_value(void) const { return assembly.soc.get_temperature_raw(); }

}
