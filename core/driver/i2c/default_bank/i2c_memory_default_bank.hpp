/**
 * \file i2c_memory_bank.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "component_interface.hpp"
#include "i2c_memory_bank.hpp"
#include "i2c_memory_register_bla.hpp"
#include "i2c_memory_register_blub.hpp"
#include "i2c_memory_register_serial.hpp"

#include <cstdint>

namespace core
{
    namespace driver
    {
        namespace i2c
        {
            namespace memory
            {
                struct DefaultBank : public Bank, public pulp::ComponentInterface
                {
                    bla::register_t bla_register;
                    blub::register_t blub_register;
                    serial::register_t serial_register;

                    virtual void initialize(void) override;
                    virtual void shutdown(void) override {}

                    virtual bool set_address(const uint8_t _address) override;
                };
            }
        }
    }
}
