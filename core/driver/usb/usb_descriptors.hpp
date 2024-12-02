/**
 * \file usb_descriptors.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "event_bus.hpp"

#include <stdint.h>

/* A combination of interfaces must have a unique product id, since PC will save device driver after the first plug.
 * Same VID/PID with different interface e.g MSC (first), then CDC (later) will possibly cause system error on PC.
 *
 * Auto ProductID layout's Bitmap:
 * [MSB]             [LSB]
 * +-----------+-+-+-+-+-+
 *            |  | | | | +---- CDC
 *            |  | | | +------ MSC
 *            |  | | +-------- HID
 *            |  | +---------- MIDI
 *            |  +------------ VENDOR
 *            +--------------- PID
 */
#define _PID_MAP(itf, n) ((CFG_TUD_##itf) << (n))
#define USB_PID                                                                                                                                                \
    ((core::defines::usb::PID & core::defines::usb::PID_MASK) | _PID_MAP(CDC, 0) | _PID_MAP(MSC, 1) | _PID_MAP(HID, 2) | _PID_MAP(MIDI, 3)                     \
     | _PID_MAP(VENDOR, 4))

#define USB_VID (core::defines::usb::VID)

#define USB_BCD 0x0200 /* SB Spec Release Number (BCD) */

namespace core
{
    namespace usb
    {
        extern void set_event_bus(pulp::event::Bus &);
        
        namespace hid
        {

            enum class COMMAND : uint8_t
            {
                KEYBOARD = 1,
                MOUSE = 2,
                CONSUMER = 3,
                CUSTOM = 0xE0,
            };

            extern void sent_keycode(const uint8_t _modifier, const uint8_t _code);
            extern void sent_keycode();
        }
        namespace cdc
        {

        }
    }
}
