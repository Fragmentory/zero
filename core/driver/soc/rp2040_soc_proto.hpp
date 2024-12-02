/**
 * \file rp2040_soc_proto.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "rp2040_soc.hpp"

namespace core
{
    namespace soc
    {
        struct RP2040PlatformProto : public RP2040
        {
            static constexpr int32_t DEFAULT_TICKER_DELAY_US = -500;
            static constexpr int32_t DEFAULT_HEARTBEAT_COUNTER = 10;

            static constexpr uint16_t DEFAULT_WATCHDOG_PERIODE_MS = 500;
            static constexpr uint16_t DEFAULT_WATCHDOG_REBOOT_DELAY_MS = 500;

            static constexpr uint8_t DEBUG_PIN_NUMBER = 2;
            static constexpr uint8_t DEBUG_PIN[DEBUG_PIN_NUMBER] = {16, 17};

            static constexpr uint8_t HEARTBEAT_PIN = 4;

            static const uint8_t SOUND_PIN = 17;
        };
    }
}
