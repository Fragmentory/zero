/**
 * \file i2c_slave.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "i2c_slave.hpp"

#include "chunk.h"
#include "i2c_memory_register_identifier.hpp"
#include "i2c_slave_variant.hpp"

#include <cassert>
#include <cstdio>
#include <hardware/i2c.h>
#include <hardware/irq.h>
#include <hardware/sync.h>
#include <pico/i2c_slave.h>
#include <pico/stdlib.h>

namespace core
{
    namespace driver
    {
        namespace i2c
        {
            static bool VERBOSITY_ON = false;

            memory::Interface *Slave::memory_interface = nullptr;

            void Slave::set_address(const uint8_t _address)
            {
                /* Attention: Set the address before initialization! */
                assert(state == pulp::COMPONENT_STATE::UNDEFINED);
                address = _address;
                VERBOSITY_ON &&printf("slave address %d\n", address);
            }

            void Slave::initialize()
            {
                assert(state == pulp::COMPONENT_STATE::UNDEFINED);
                state = pulp::COMPONENT_STATE::IDLE;

                gpio_init(slave::Variant::SDA_PIN);
                gpio_set_function(slave::Variant::SDA_PIN, GPIO_FUNC_I2C);
                gpio_pull_up(slave::Variant::SDA_PIN);

                gpio_init(slave::Variant::SCL_PIN);
                gpio_set_function(slave::Variant::SCL_PIN, GPIO_FUNC_I2C);
                gpio_pull_up(slave::Variant::SCL_PIN);

                i2c_init(slave::Variant::INSTANCE, slave::Variant::BAUDRATE);
                i2c_slave_init(slave::Variant::INSTANCE, address, &Slave::i2c_slave_handler);
            }

            void Slave::shutdown()
            {
                assert(state != pulp::COMPONENT_STATE::UNDEFINED);
                state = pulp::COMPONENT_STATE::UNDEFINED;

                i2c_deinit(slave::Variant::INSTANCE);
            }

            void Slave::i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t _event)
            {
                switch (_event)
                {
                    case I2C_SLAVE_RECEIVE:
                    {
                        const uint8_t byte = i2c_read_byte_raw(i2c);
                        memory_interface->handle_byte(byte);
                        break;
                    }
                    case I2C_SLAVE_REQUEST:
                    {
                        uint8_t byte = 0xff;
                        memory_interface->get_byte(byte);
                        i2c_write_byte_raw(i2c, byte);
                        break;
                    }
                    case I2C_SLAVE_FINISH:
                    {
                        memory_interface->finish();
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }
}