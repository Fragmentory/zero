/**
 * \file usb_device.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "usb_device.hpp"

#include <bsp/board.h>
#include <tusb.h>

namespace core
{
    namespace driver
    {
        void UsbDevice::initialize()
        {
            board_init();
            tusb_init();
            while (!tusb_inited())
                ;
        }

        void UsbDevice::shutdown() {}

        void UsbDevice::perform() { tud_task(); }
    }
}