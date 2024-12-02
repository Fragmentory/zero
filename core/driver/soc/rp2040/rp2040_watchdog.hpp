/**
 * \file rp2040_watchdog.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "component_interface.hpp"

#include <cstdint>

namespace core
{
    namespace soc
    {
        struct RP2040Watchdog : public pulp::ComponentInterface
        {
            static const uint16_t WATCHDOG_PERIODE_MS;
            static const uint16_t WATCHDOG_REBOOT_DELAY_MS;

            virtual ~RP2040Watchdog() {}

            virtual void initialize(void) override {}
            virtual void shutdown(void) override {}

            void start();
            void update();
            void reboot();
        };
    }
}
