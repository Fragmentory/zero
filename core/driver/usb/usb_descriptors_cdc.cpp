/**
 * \file usb_descriptors_cdc.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "event_bus.hpp"
#include "usb_descriptors.hpp"

#include <bsp/board.h>
#include <pico/stdio.h>
#include <pico/stdlib.h>
#include <tusb.h>

enum
{
    ITF_NUM_CDC_0 = 0,
    ITF_NUM_CDC_0_DATA,
    ITF_NUM_CDC_1,
    ITF_NUM_CDC_1_DATA,
    ITF_NUM_TOTAL
};

#define CONFIG_TOTAL_LEN (TUD_CONFIG_DESC_LEN + CFG_TUD_CDC * TUD_CDC_DESC_LEN)
#define EPNUM_CDC_0_NOTIF 0x81
#define EPNUM_CDC_0_OUT 0x02
#define EPNUM_CDC_0_IN 0x82
#define EPNUM_CDC_1_NOTIF 0x83
#define EPNUM_CDC_1_OUT 0x04
#define EPNUM_CDC_1_IN 0x84

static pulp::event::Bus *event_bus = nullptr;

#if CFG_TUD_CDC == 1
/**
 * \brief Device descriptor
 *
 * \return uint8_t const*
 */
uint8_t const *tud_descriptor_device_cb(void)
{
    static const tusb_desc_device_t desc_device = {
        .bLength = sizeof(tusb_desc_device_t),
        .bDescriptorType = TUSB_DESC_DEVICE,
        .bcdUSB = 0x0200,
        .bDeviceClass = TUSB_CLASS_MISC,
        .bDeviceSubClass = MISC_SUBCLASS_COMMON,
        .bDeviceProtocol = MISC_PROTOCOL_IAD,
        .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,

        .idVendor = 0x2e8a,  // 0xCafe,  // Deine Vendor ID
        .idProduct = 0x0003, // 0x4001, // Deine Product ID
        .bcdDevice = 0x0100,

        .iManufacturer = 0x01,
        .iProduct = 0x02,
        .iSerialNumber = 0x03,

        .bNumConfigurations = 0x01,
    };

    return (uint8_t const *)&desc_device;
}
#endif

#if CFG_TUD_CDC == 1
/**
 * \brief Device configuration
 *
 * \param _index
 * \return uint8_t const*
 */
uint8_t const *tud_descriptor_configuration_cb(uint8_t _index)
{
    (void)_index; // Es gibt nur eine Konfiguration
    static const uint8_t desc_configuration[] = {
        // Config number, interface count, string index, total length, attribute, power in mA
        TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, 0x00, 100),

        // 1st CDC: Interface number, string index, EP notification address and size, EP data address (out, in) and size.
        TUD_CDC_DESCRIPTOR(ITF_NUM_CDC_0, 4, EPNUM_CDC_0_NOTIF, 8, EPNUM_CDC_0_OUT, EPNUM_CDC_0_IN, 64),

        // 2nd CDC: Interface number, string index, EP notification address and size, EP data address (out, in) and size.
        TUD_CDC_DESCRIPTOR(ITF_NUM_CDC_1, 4, EPNUM_CDC_1_NOTIF, 8, EPNUM_CDC_1_OUT, EPNUM_CDC_1_IN, 64),
    };
    return desc_configuration;
}
#endif

#if CFG_TUD_CDC == 1
/**
 * \brief
 *
 * \param _index
 * \param _language_id
 * \return uint16_t const*
 */
uint16_t const *tud_descriptor_string_cb(uint8_t _index, uint16_t _language_id)
{
    (void)_language_id;

    static const char *string_desc[] = {
        (const char[]){0x09, 0x04}, // Supported language (English)
        "Romsila", // iManufacturer
        "BabbulaBub", // iProduct
        NULL,
        "123456", // iSerialNumber
    };

    if (_index == 0)
    {
        static uint16_t desc_language = 0x0409; // English
        return &desc_language;
    }

    if (_index >= sizeof(string_desc) / sizeof(string_desc[0]))
        return NULL;

    static uint16_t desc_string[32];
    uint16_t len = static_cast<uint8_t>(strlen(string_desc[_index]) & 0xffff);

    for (uint16_t i = 0; i < len; i++)
    {
        desc_string[1 + i] = string_desc[_index][i];
    }

    desc_string[0] = (static_cast<uint16_t>(TUSB_DESC_STRING) << 8) | static_cast<uint16_t>(2 * len + 2);
    return desc_string;
}
#endif

namespace core::usb
{
    extern void set_event_bus(pulp::event::Bus &_event_bus) { event_bus = &_event_bus; }

}