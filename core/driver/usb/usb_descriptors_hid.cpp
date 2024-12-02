/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (9the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "chunk.h"
#include "core_defines.hpp"
#include "macros.hpp"
#include "pulp_event.hpp"
#include "revision.h"
#include "usb_descriptors.hpp"

#include <tusb.h>

#define _PRINT_EXTENDED_OUTPUT

#if CFG_TUD_HID == 1
#define TUD_HID_REPORT_DESC_CUSTOM(...)                                                                                                                        \
    HID_USAGE_PAGE_N(HID_USAGE_PAGE_VENDOR, 2), HID_USAGE(0xA0), HID_COLLECTION(HID_COLLECTION_APPLICATION), __VA_ARGS__ HID_USAGE(0x01),                      \
        HID_LOGICAL_MIN(0x00), HID_LOGICAL_MAX(0xFF), HID_REPORT_SIZE(8), HID_REPORT_COUNT(3), HID_FEATURE(HID_DATA | HID_VARIABLE | HID_ABSOLUTE),            \
        HID_USAGE(0x02), HID_LOGICAL_MIN(0x00), HID_LOGICAL_MAX(0xFF), HID_REPORT_SIZE(8), HID_REPORT_COUNT(12),                                               \
        HID_FEATURE(HID_DATA | HID_VARIABLE | HID_ABSOLUTE), HID_COLLECTION_END
#endif

static pulp::event::Bus *event_bus = nullptr;

#if CFG_TUD_HID == 1
/**
 * \brief Invoked when received GET DEVICE DESCRIPTOR
 *
 * \return uint8_t const* Application return pointer to descriptor
 */
uint8_t const *tud_descriptor_device_cb(void)
{
    static const tusb_desc_device_t desc_device = {
        .bLength = sizeof(tusb_desc_device_t),
        .bDescriptorType = TUSB_DESC_DEVICE,
        .bcdUSB = USB_BCD,
        .bDeviceClass = 0x00,
        .bDeviceSubClass = 0x00,
        .bDeviceProtocol = 0x00,
        .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,

        .idVendor = USB_VID,
        .idProduct = USB_PID,
        .bcdDevice = 0x0100,

        .iManufacturer = 0x01,
        .iProduct = 0x02,
        .iSerialNumber = 0x03,

        .bNumConfigurations = 0x01,
    };

    return (uint8_t const *)&desc_device;
}
#endif

#if CFG_TUD_HID == 1
/**
 * \brief HID Report Descriptor
 */
uint8_t const desc_hid_report[] = {
    TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(static_cast<uint8_t>(core::usb::COMMAND::KEYBOARD))),
    TUD_HID_REPORT_DESC_MOUSE(HID_REPORT_ID(static_cast<uint8_t>(core::usb::COMMAND::MOUSE))),
    TUD_HID_REPORT_DESC_CONSUMER(HID_REPORT_ID(static_cast<uint8_t>(core::usb::COMMAND::CONSUMER))),
    TUD_HID_REPORT_DESC_CUSTOM(HID_REPORT_ID(static_cast<uint8_t>(core::usb::COMMAND::CUSTOM))),
};
#endif

#if CFG_TUD_HID == 1
/**
 * \brief Invoked when received GET HID REPORT DESCRIPTOR
 *
 * Application return pointer to descriptor
 * Descriptor contents must exist long enough for transfer to complete
 *
 * \param instance
 * \return uint8_t const*
 */
uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance)
{
    (void)instance;
    return desc_hid_report;
}
#endif

/**
 * \brief Configuration Descriptor
 */
enum
{
    ITF_NUM_HID,
    ITF_NUM_TOTAL
};

#define CONFIG_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)

#define EPNUM_HID 0x81

// HID buffer size Should be sufficient to hold ID (if any) + Data
#define CFG_TUD_HID_EP_BUFSIZE 64

#if CFG_TUD_HID == 1
uint8_t const desc_configuration[] = {
    // Config number, interface count, string index, total length, attribute, power in mA
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),

    // Interface number, string index, protocol, report descriptor len, EP In address, size & polling interval
    TUD_HID_DESCRIPTOR(ITF_NUM_HID, 0, HID_ITF_PROTOCOL_NONE, sizeof(desc_hid_report), EPNUM_HID, CFG_TUD_HID_EP_BUFSIZE, 5),
    // TUD_HID_DESCRIPTOR(ITF_NUM_HID, 0, HID_ITF_PROTOCOL_NONE, 4, EPNUM_HID, CFG_TUD_HID_EP_BUFSIZE, 5),
};
#endif

/*
 * ATTENTION:
 * Per USB specs: high speed capable device must report
 * device_qualifier and other_speed_configuration
 */

#if CFG_TUD_HID == 1
/**
 * \brief other speed configuration
 */
uint8_t desc_other_speed_config[CONFIG_TOTAL_LEN];
#endif

#if CFG_TUD_HID == 1
/**
 * \brief Invoked when received GET DEVICE QUALIFIER DESCRIPTOR request
 *
 * Application return pointer to descriptor, whose contents must exist long enough
 * for transfer to complete.
 * device_qualifier descriptor describes information about a high-speed capable
 * device that would change if the device were operating at the other speed.
 * If not highspeed capable stall this request.
 *
 * \return uint8_t const*
 */
uint8_t const *tud_descriptor_device_qualifier_cb(void)
{
    /**
     * \brief device qualifier
     * device qualifier is mostly similar to device descriptor
     * since we don't change configuration based on speed
     */
    static const tusb_desc_device_qualifier_t desc_device_qualifier = {
        .bLength = sizeof(tusb_desc_device_qualifier_t),
        .bDescriptorType = TUSB_DESC_DEVICE_QUALIFIER,
        .bcdUSB = USB_BCD,

        .bDeviceClass = 0x00,
        .bDeviceSubClass = 0x00,
        .bDeviceProtocol = 0x00,

        .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,
        .bNumConfigurations = 0x01,
        .bReserved = 0x00,
    };

    return (uint8_t const *)&desc_device_qualifier;
}
#endif

#if CFG_TUD_HID == 1
/**
 * \brief Invoked when received GET OTHER SEED CONFIGURATION DESCRIPTOR request
 *
 * Application return pointer to descriptor, whose contents must exist long enough
 * for transfer to complete.
 * Configuration descriptor in the other speed e.g if high speed then this is
 * for full speed and vice versa.
 *
 * \param index
 * \return uint8_t const*
 */
uint8_t const *tud_descriptor_other_speed_configuration_cb(uint8_t index)
{
    (void)index; // for multiple configurations

    // other speed config is basically configuration with type = OTHER_SPEED_CONFIG
    memcpy(desc_other_speed_config, desc_configuration, CONFIG_TOTAL_LEN);
    desc_other_speed_config[1] = TUSB_DESC_OTHER_SPEED_CONFIG;

    // this code use the same configuration for both high and full speed mode
    return desc_other_speed_config;
}
#endif

#if CFG_TUD_HID == 1
/**
 * \brief Invoked when received GET CONFIGURATION DESCRIPTOR
 *
 * Descriptor contents must exist long enough for transfer to complete
 *
 * \param index
 * \return uint8_t const* Application return pointer to descriptor
 */
uint8_t const *tud_descriptor_configuration_cb(uint8_t index)
{
    (void)index; // for multiple configurations

    // This example use the same configuration for both high and full speed mode
    return desc_configuration;
}
#endif

#if CFG_TUD_HID == 1
/**
 * \brief Invoked when received GET STRING DESCRIPTOR request
 *
 * Handle string descriptors
 *
 * \param index
 * \param lang_id
 * \return uint16_t const* Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
 */
uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t lang_id)
{
    (void)lang_id;

    static const size_t DESCRIPTOR_SIZE = 32;
    static uint16_t _desc_str[DESCRIPTOR_SIZE];

    auto send_report = [](char const *const str)
    {
        const size_t size = strnlen(str, DESCRIPTOR_SIZE - 1);
        // Convert ASCII string into UTF-16
        for (uint8_t i = 0; i < size; i++)
        {
            _desc_str[1 + i] = str[i];
        }
        // first byte is length (including header), second byte is string type
        _desc_str[0] = (TUSB_DESC_STRING << 8) | uint16_t(2 * size + 2);
    };

    switch (index)
    {
        case 0:
        {
            // supported language is English (0x0409)
            const char language[] = {0x09, 0x04, 0x00};
            send_report(language);
            break;
        }
        case 1:
            // Manufacturer
            send_report(identity::hardware::PLATFORM);
            break;
        case 2:
            // Product
            send_report(identity::firmware::PRODUCT);
            break;
        case 3:
        {
            /*

                TODO

                read proper serial length from registry

            */

            const size_t SERIAL_NUMBER_SIZE = 12;

            // Serials, should use chip ID
            char serial[SERIAL_NUMBER_SIZE * 2 + 1];
            for (size_t i = 0; i < SERIAL_NUMBER_SIZE; ++i)
            {
                /*

                    TODO

                    read serial number byte from registry

                    temporary solution:
                */

                sprintf(&serial[i * 2], "%02x", i);
            }
            serial[SERIAL_NUMBER_SIZE * 2] = 0;
            send_report(serial);
            break;
        }
        default:
            /*
              Note: the 0xEE index string is a Microsoft OS 1.0 Descriptors.
              https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors
            */
            return NULL;
    }

    return _desc_str;
}
#endif

#if CFG_TUD_HID == 1
/**
 * \brief Invoked when device is mounted
 */
void tud_mount_cb(void)
{
    if (event_bus != nullptr)
        event_bus->notify(pulp::event::Connect());
}
#endif

#if CFG_TUD_HID == 1
/**
 * \brief Invoked when device is unmounted
 */
void tud_umount_cb(void)
{
    if (event_bus != nullptr)
        event_bus->notify(pulp::event::Disconnect());
}
#endif

#if CFG_TUD_HID == 1
/**
 * \brief Invoked when usb bus is suspended
 *
 * remote_wakeup_en : if host allow us  to perform remote wakeup
 * Within 7ms, device must draw an average of current less than 2.5 mA from bus
 */
void tud_suspend_cb(bool remote_wakeup_en)
{
    if (event_bus != nullptr)
        event_bus->notify(pulp::event::Suspend(remote_wakeup_en));
}
#endif

#if CFG_TUD_HID == 1
/**
 * \brief Invoked when usb bus is resumed
 */
void tud_resume_cb(void)
{
    if (event_bus != nullptr)
        event_bus->notify(pulp::event::Resume());
}
#endif

#if CFG_TUD_HID == 1
/**
 * \brief Invoked when sent REPORT successfully to host
 *
 * Application can use this to send the next report
 * Note: For composite reports, report[0] is report ID
 */
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint16_t len)
{
    (void)instance;

#if defined(PRINT_EXTENDED_OUTPUT)
    printf("tud_hid_report_complete_cb\n");
    for (int i = 0; i < len; ++i)
    {
        printf("0x%x\n", report[i]);
    }
    printf("\n");
#else
    (void)report;
    (void)len;
#endif
}
#endif

#if CFG_TUD_HID == 1
/**
 * \brief Invoked when received SET_REPORT control request
 *
 * Invoked when received SET_REPORT control request or received data
 * on OUT endpoint ( Report ID = 0, Type = 0 )
 *
 * \param instance
 * \param _report_id
 * \param report_type
 * \param buffer
 * \param bufsize
 */
void tud_hid_set_report_cb(uint8_t instance, uint8_t _report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
{

    (void)instance;
#if !defined(PRINT_EXTENDED_OUTPUT)
    (void)_report_id;
    (void)buffer;
#endif

    if (bufsize < 1)
        return;

    if (report_type == HID_REPORT_TYPE_FEATURE)
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("###### HID_REPORT_TYPE_FEATURE\n");
#endif
        /* do nothing */
    }
    else if (report_type == HID_REPORT_TYPE_OUTPUT)
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("###### HID_REPORT_TYPE_OUTPUT\n");
#endif
        /*
            TODO

            const_chunk_t chunk{.space = buffer, .size = bufsize};
            call set_report_handler(_report_id, chunk);

        */
    }
    else if (HID_REPORT_TYPE_INPUT)
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("###### HID_REPORT_TYPE_INPUT\n");
#endif
    }
    else if (HID_REPORT_TYPE_INVALID)
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("###### HID_REPORT_TYPE_INVALID\n");
#endif
    }
    else
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("###### unknown report type\n");
#endif
    }

#if defined(PRINT_EXTENDED_OUTPUT)
    printf("tud_hid_set_report_cb\n");

    printf("report_id 0x%x\n", _report_id);
    printf("report_type 0x%x\n", report_type);
    for (int i = 0; i < bufsize; ++i)
    {
        printf("0x%x\n", buffer[i]);
    }
    printf("\n");
#endif
}
#endif

#if CFG_TUD_HID == 1
/**
 * \brief Invoked when received GET_REPORT control request
 *
 * Application must fill buffer report's content and return its length.
 *
 * \param instance
 * \param report_id
 * \param report_type
 * \param buffer
 * \param bufsize
 * \return uint16_t Return zero will cause the stack to STALL request
 */
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t bufsize)
{
    (void)instance;
#if !defined(PRINT_EXTENDED_OUTPUT)
    (void)report_id;
    (void)buffer;
#endif

    if (report_type == HID_REPORT_TYPE_FEATURE)
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("##### HID_REPORT_TYPE_FEATURE\n");
#endif
        /*

            TODO

            chunk_t chunk{.space = buffer, .size = bufsize};
            call get_report_handler(report_id, chunk);

        */
    }
    else if (report_type == HID_REPORT_TYPE_INPUT)
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("##### HID_REPORT_TYPE_INPUT\n");
#endif
    }
    else if (report_type == HID_REPORT_TYPE_OUTPUT)
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("##### HID_REPORT_TYPE_OUTPUT\n");
#endif
    }
    else
    {
#if defined(PRINT_EXTENDED_OUTPUT)
        printf("###### unknown report type\n");
#endif
    }

#if defined(PRINT_EXTENDED_OUTPUT)
    printf("tud_hid_get_report_cb\n");

    printf("report_id 0x%x\n", report_id);
    printf("report_type 0x%x\n", report_type);
    for (int i = 0; i < bufsize; ++i)
    {
        printf("0x%x\n", buffer[i]);
    }
    printf("\n");
#endif

    return bufsize;
}
#endif

namespace core::usb
{
    extern void set_event_bus(pulp::event::Bus &_event_bus) { event_bus = &_event_bus; }

    namespace hid
    {
        extern void sent_keycode(const uint8_t _modifier, const uint8_t _code)
        {
#if CFG_TUD_HID == 1
            uint8_t keycode[6] = {0};
            keycode[0] = _code;

            tud_hid_keyboard_report(static_cast<uint8_t>(core::usb::hid::COMMAND::KEYBOARD), _modifier, keycode);
#else
            (void)_modifier;
            (void)_code;
#endif
        }
#if CFG_TUD_HID == 1

        extern void sent_keycode() { tud_hid_keyboard_report(static_cast<uint8_t>(core::usb::hid::COMMAND::KEYBOARD), 0, NULL); }
#endif
    }
}
