/**
 * \file visual_serie.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "neopixel_interface.hpp"
#include "visual_executor.hpp"
#include "visual_prog_identifier.hpp"

namespace core::driver::visual
{
    struct VisualSerie : public Executor
    {
        VisualSerie(driver::neopixel::Interface &_neopixel) :
            Executor(_neopixel)
        {
        }

        static const unsigned int VISUAL_PIN = 20;

        static const size_t NUMBER_OF_BEACONS = 5;
        static constexpr size_t BEACON_POSITION[NUMBER_OF_BEACONS] = {0, 1, 2, 3, 4};

        static const uint8_t DEFAULT_MODE = 0;
        static const uint8_t DEFAULT_VERBOSITY = 0;

        static constexpr float MIN_TEMPERATURE = 18.5;
        static constexpr float MAX_TEMPERATURE = 22.5;
        static const uint16_t TEMPERATURE_TIMEOUT = 500;

        static const uint16_t BLINK_UPDATE_TIMEOUT = 400;
        static const uint16_t FLASH_UPDATE_TIMEOUT = 10;

        static const uint16_t BLINK_ALERT_TIMEOUT = 120;
        static const uint16_t FLASH_ALERT_TIMEOUT = 10;

        static const uint16_t PROGRAM_FREEZE_TIMEOUT = 120;
        static const uint16_t PROGRAM_OFF_TIMEOUT = 100;

        static const uint16_t BLINK_ACTIVE_TIMEOUT = 2000;
        static const uint16_t FLASH_ACTIVE_TIMEOUT = 20;
        static constexpr Color ACTIVE_BACKLIGHT_LEFT = {
            .rgbw = {.r = 0x00, .g = 0x0f, .b = 0x00, .w = 0x03}
        };
        static constexpr Color ACTIVE_BACKLIGHT_RIGHT = {
            .rgbw = {.r = 0x00, .g = 0x0e, .b = 0x00, .w = 0x03}
        };

        static const uint16_t BLINK_READY_DOWN_TIMEOUT = 1000;
        static const uint16_t BLINK_READY_UP_TIMEOUT = 250;
        static const uint16_t FLASH_READY_TIMEOUT = 10;
    };
}
