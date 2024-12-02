/**
 * \file reboot_watcher.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "reboot_watcher.hpp"

#include <hardware/watchdog.h>
#include <pico/bootrom.h>
#include <pico/stdlib.h>
#include <pico/time.h>

namespace core::service
{
    namespace reboot
    {
        defines::Mode Watcher::mode = defines::Mode::RESTART;

        Watcher::Watcher() { Watcher::mode = defines::RESTART; }

        Watcher::~Watcher()
        {
            if (Watcher::mode == defines::Mode::BOOTSEL)
            {
                /* reboot rp2040 in BOOTSEL mode */
                reset_usb_boot((0x00000001 << PICO_DEFAULT_LED_PIN), 0);
            }
            else
            {
                /* (Scratch register value, Scratch mask, Delay in ms) */
                watchdog_reboot(0, 0, 0);
            }
        }
    }
}