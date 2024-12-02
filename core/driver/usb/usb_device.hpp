/**
 * \file usb_device.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "active_component_interface.hpp"

namespace core
{
    namespace driver
    {
        struct UsbDevice : public pulp::ActiveComponentInterface
        {
            virtual void initialize() override;
            virtual void shutdown() override;
            virtual void perform() override;
        };
    }
}
