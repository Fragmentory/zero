/**
 * \file rp2040_soc_serie.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "rp2040_soc.hpp"

#include <cstdint>

namespace core
{
    namespace soc
    {
        struct RP2040PlatformSerie : public RP2040
        {
            static constexpr int32_t DEFAULT_TICKER_DELAY_US = -500;
            static constexpr int32_t DEFAULT_HEARTBEAT_COUNTER = 10;

            static constexpr uint16_t DEFAULT_WATCHDOG_PERIODE_MS = 500;
            static constexpr uint16_t DEFAULT_WATCHDOG_REBOOT_DELAY_MS = 100;

            static constexpr uint8_t DEBUG_PIN_NUMBER = 2;
            static constexpr uint8_t DEBUG_PIN[DEBUG_PIN_NUMBER] = {14, 15};

            static constexpr uint8_t HEARTBEAT_PIN = 4;

            static const uint8_t SOUND_PIN = 17;
        };
    }
}
