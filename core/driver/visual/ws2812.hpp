/**
 * \file ws2812.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "component_interface.hpp"
#include "component_state.hpp"
#include "neopixel_interface.hpp"

#include <cstdint>
namespace core::driver
{
    namespace ws2812
    {
        struct Instance : public pulp::ComponentInterface, public neopixel::Interface
        {
            virtual void initialize() override;
            virtual void shutdown() override;

            virtual void put_pixel(const visual::rgbw::Color &) override;

          private:
            pulp::COMPONENT_STATE state{pulp::COMPONENT_STATE::UNDEFINED};
        };
    }
}
