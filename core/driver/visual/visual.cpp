/**
 * \file visual.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "visual.hpp"

#include "visual_color_defines.hpp"

#include <cmath>
#include <cstdio>

namespace core
{
    using Program = core::driver::visual::PROGRAM;
    using Color = core::driver::visual::Color;

    void Visual::idle(void) { visual_hardware.set_program(Program::IDLE); }

    void Visual::freeze(void) { visual_hardware.set_program(Program::FREEZE); }

    void Visual::alert(void) { visual_hardware.set_program(Program::ALERT); }

    void Visual::ready(void) { visual_hardware.set_program(Program::READY); }

    void Visual::active(void) { visual_hardware.set_program(Program::ACTIVE); }

    void Visual::off(void) { visual_hardware.set_program(Program::OFF); }

    void Visual::service(void) { visual_hardware.set_program(Program::SERVICE); }

    void Visual::cold(void)
    {
        visual_hardware.set_program(Program::FREEZE);
        visual_hardware.color(driver::visual::COLD_COLOR, driver::visual::COLD_COLOR, driver::visual::Variant::TEMPERATURE_TIMEOUT);
    }

    void Visual::warm(void)
    {
        visual_hardware.set_program(Program::FREEZE);
        visual_hardware.color(driver::visual::COLD_COLOR, driver::visual::HOT_COLOR, driver::visual::Variant::TEMPERATURE_TIMEOUT);
    }

    void Visual::hot(void)
    {
        visual_hardware.set_program(Program::FREEZE);
        visual_hardware.color(driver::visual::HOT_COLOR, driver::visual::HOT_COLOR, Hardware::TEMPERATURE_TIMEOUT);
    }
    
    void Visual::scale(const pulp::temperature::Interface &_temperature)
    {
        float value = _temperature.get_value();

        if (value > max_temperature)
        {
            max_temperature = value;
        }

        if (value < min_temperature)
        {
            min_temperature = value;
        }

        sum -= buffer[index];
        buffer[index] = value;
        sum += buffer[index];
        ++index &= 0x0f;
        value = static_cast<float>(round(sum / 16.0f));

        const float distance = max_temperature - min_temperature;
        const float cold_factor = (max_temperature - value) / distance;
        const float hot_factor = (value - min_temperature) / distance;

        const Color color{
            .rgbw = {
                     .r = static_cast<uint8_t>(driver::visual::COLD_COLOR.rgbw.r * cold_factor + driver::visual::HOT_COLOR.rgbw.r * hot_factor),
                     .g = static_cast<uint8_t>(driver::visual::COLD_COLOR.rgbw.g * cold_factor + driver::visual::HOT_COLOR.rgbw.g * hot_factor),
                     .b = static_cast<uint8_t>(driver::visual::COLD_COLOR.rgbw.b * cold_factor + driver::visual::HOT_COLOR.rgbw.b * hot_factor),
                     .w = 0xff,
                     }
        };

        const Color cold_color{
            .rgbw = {
                     .r = static_cast<uint8_t>(driver::visual::COLD_COLOR.rgbw.r * cold_factor),
                     .g = static_cast<uint8_t>(driver::visual::COLD_COLOR.rgbw.g * cold_factor),
                     .b = static_cast<uint8_t>(driver::visual::COLD_COLOR.rgbw.b * cold_factor),
                     .w = 0xff,
                     }
        };
        const Color hot_color{
            .rgbw = {
                     .r = static_cast<uint8_t>(driver::visual::HOT_COLOR.rgbw.r * hot_factor),
                     .g = static_cast<uint8_t>(driver::visual::HOT_COLOR.rgbw.g * hot_factor),
                     .b = static_cast<uint8_t>(driver::visual::HOT_COLOR.rgbw.b * hot_factor),
                     .w = 0xff,
                     }
        };

        if (hot_factor < (BORDER_1 - DELTA))
        {
            visual_hardware.color(cold_color, cold_color, 1.0);
        }
        else if (hot_factor >= (BORDER_1 + DELTA) && hot_factor < (BORDER_2 - DELTA))
        {
            visual_hardware.color(color, cold_color, 1.0);
        }
        else if (hot_factor >= (BORDER_2 + DELTA) && hot_factor < (BORDER_3 - DELTA))
        {
            visual_hardware.color(color, color, 1.0);
        }
        else if (hot_factor >= (BORDER_3 + DELTA) && hot_factor < (BORDER_4 - DELTA))
        {
            visual_hardware.color(hot_color, color, 1.0);
        }
        else if (hot_factor >= (BORDER_4 + DELTA))
        {
            visual_hardware.color(hot_color, hot_color, 1.0);
        }
    }
}
