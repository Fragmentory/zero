/**
 * \file i2c_master.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "i2c_master.hpp"

#include "component_state.hpp"
#include "i2c_master_variant.hpp"
#include "i2c_slave_variant.hpp"

#include <cassert>
#include <cstring>
#include <hardware/i2c.h>
#include <pico/stdlib.h>

namespace core
{
    namespace driver
    {
        namespace i2c
        {

            void Master::set_address(const uint8_t _address)
            {
                /* Attention: Set the address before initialization! */
                assert(state == pulp::COMPONENT_STATE::UNDEFINED);

                address = _address;
            }

            void Master::initialize(void)
            {
                assert(state == pulp::COMPONENT_STATE::UNDEFINED);
                state = pulp::COMPONENT_STATE::IDLE;

                gpio_init(master::Variant::SDA_PIN);
                gpio_set_function(master::Variant::SDA_PIN, GPIO_FUNC_I2C);
                // pull-ups are already active on slave side, this is just a fail-safe in case the wiring is faulty
                gpio_pull_up(master::Variant::SDA_PIN);

                gpio_init(master::Variant::SCL_PIN);
                gpio_set_function(master::Variant::SCL_PIN, GPIO_FUNC_I2C);
                gpio_pull_up(master::Variant::SCL_PIN);

                i2c_init(master::Variant::INSTANCE, master::Variant::BAUDRATE);
            }

            void Master::shutdown(void)
            {
                assert(state != pulp::COMPONENT_STATE::UNDEFINED);
                state = pulp::COMPONENT_STATE::UNDEFINED;

                i2c_deinit(master::Variant::INSTANCE);
            }

            /**
             * \brief
             *
             * \param _byte The memory address/register for read/write operations.
             *
             * The parameter is not the I2C address of the module; it is the memory address or register
             * where the data should be written or read.
             *
             * When using write_next or read_next, the address/register is automatically incremented by
             * the size of the chunk. This allows large data to be read or written in chunks as needed.
             *
             * \return size_t
             */
            size_t Master::start_from(const uint8_t _byte)
            {
                const uint8_t buffer[] = {_byte};
                const int count = i2c_write_blocking(master::Variant::INSTANCE, address, buffer, 1, true);
                if (count < 0)
                {
                    // communication error
                    return 0;
                }
                return count;
            }

            size_t Master::write_next(const chunk_t &_chunk)
            {
                const int count = i2c_write_blocking(master::Variant::INSTANCE, address, _chunk.space, _chunk.size, true);
                if (count < 0)
                {
                    // communication error
                    return 0;
                }
                return count;
            }

            size_t Master::write_done(const chunk_t &_chunk)
            {
                const int count = i2c_write_blocking(master::Variant::INSTANCE, address, _chunk.space, _chunk.size, false);
                if (count < 0)
                {
                    // communication error
                    return 0;
                }
                return count;
            }

            size_t Master::read_next(const chunk_t &_chunk)
            {
                const int count = i2c_read_blocking(master::Variant::INSTANCE, address, _chunk.space, _chunk.size, true);
                if (count < 0)
                {
                    // communication error
                    return 0;
                }
                return count;
            }

            size_t Master::read_done(const chunk_t &_chunk) const
            {
                const int count = i2c_read_blocking(master::Variant::INSTANCE, address, _chunk.space, _chunk.size, false);
                if (count < 0)
                {
                    // communication error
                    return 0;
                }
                return count;
            }
        }
    }
}