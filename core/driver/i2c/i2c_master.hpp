/**
 * \file i2c_master.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "chunk.h"
#include "component_interface.hpp"
#include "component_state.hpp"
#include "i2c_master_variant.hpp"

namespace core
{
    namespace driver
    {
        namespace i2c
        {
            struct Master : public pulp::ComponentInterface
            {
                Master() :
                    address(master::Variant::ADDRESS)
                {
                }

                virtual void initialize(void) override;
                virtual void shutdown(void) override;

                void set_address(const uint8_t _address);

                size_t start_from(const uint8_t);
                size_t write_next(const chunk_t &);
                size_t write_done(const chunk_t &);
                size_t read_next(const chunk_t &);
                size_t read_done(const chunk_t &) const;

              private:
                pulp::COMPONENT_STATE state = pulp::COMPONENT_STATE::UNDEFINED;
                uint8_t address;
            };
        }
    }
}