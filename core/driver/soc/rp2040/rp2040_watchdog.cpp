/**
 * \file rp2040_watchdog.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "rp2040_watchdog.hpp"

#include "soc_variant.hpp"

#include <hardware/watchdog.h>
#include <pico/time.h>

namespace core
{
    namespace soc
    {

        const uint16_t RP2040Watchdog::WATCHDOG_PERIODE_MS = Variant::DEFAULT_WATCHDOG_PERIODE_MS;
        const uint16_t RP2040Watchdog::WATCHDOG_REBOOT_DELAY_MS = Variant::DEFAULT_WATCHDOG_REBOOT_DELAY_MS;

        void RP2040Watchdog::start() { watchdog_enable(WATCHDOG_PERIODE_MS, true); }

        void RP2040Watchdog::update() { watchdog_update(); }

        void RP2040Watchdog::reboot() { watchdog_reboot(0, 0, 0); }
    }
}
