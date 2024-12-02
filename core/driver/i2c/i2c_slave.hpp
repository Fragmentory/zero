/**
 * \file i2c_slave.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "bytering.hpp"
#include "component_interface.hpp"
#include "component_state.hpp"
#include "i2c_memory_default_bank.hpp"
#include "i2c_memory_interface.hpp"
#include "i2c_slave_variant.hpp"

#include <cstdint>
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <pico/stdlib.h>

namespace core
{
    namespace driver
    {
        namespace i2c
        {
            struct Slave : public pulp::ComponentInterface
            {
                Slave(memory::Interface &_memory_interface) :
                    address(slave::Variant::ADDRESS)
                {
                    Slave::memory_interface = &_memory_interface;
                }

                void set_address(const uint8_t _address);

                virtual void initialize() override;
                virtual void shutdown() override;

              private:
                pulp::COMPONENT_STATE state = pulp::COMPONENT_STATE::UNDEFINED;
                uint8_t address;

                static memory::Interface *memory_interface;
                static void i2c_slave_handler(i2c_inst_t *, i2c_slave_event_t);
            };
        }
    }
}
