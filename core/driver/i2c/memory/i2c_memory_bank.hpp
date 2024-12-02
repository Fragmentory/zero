/**
 * \file i2c_memory_bank.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "i2c_memory_interface.hpp"
#include "i2c_memory_register.hpp"

#include <cstdint>

namespace core::driver::i2c
{
    namespace memory
    {
        struct Bank : public Interface
        {
            enum class STATE
            {
                ADDRESS,
                DATA,
                UNDEFINED,
            } state{STATE::UNDEFINED};

            virtual bool is_address(void) override { return current_register ? true : false; }

            virtual void reset(void) override
            {
                if (current_register)
                {
                    current_register->reset();
                }
                state = STATE::UNDEFINED;
            }

            virtual bool get_byte(uint8_t &_byte) const override
            {
                if (current_register)
                {
                    current_register->get_byte(_byte);
                    return true;
                }
                return false;
            }

            virtual bool set_byte(const uint8_t _byte) override
            {
                if (current_register)
                {
                    current_register->set_byte(_byte);
                    return true;
                }
                return false;
            }

            virtual void finish(void) override
            {
                if (current_register)
                {
                    if (state == STATE::ADDRESS)
                    {
                        state = STATE::DATA;
                    }
                    else if (state == STATE::DATA)
                    {
                        if (current_register->is_full())
                        {
                            current_register->reset();
                            current_register = nullptr;
                            state = STATE::UNDEFINED;
                        }
                    }
                }
                else
                {
                    reset();
                }
            }

            virtual void handle_byte(const uint8_t _byte) override
            {
                if (!is_address())
                {
                    set_address(_byte);
                    state = STATE::ADDRESS;
                }
                else
                {
                    set_byte(_byte);
                    state = STATE::DATA;
                }
            }

          protected:
            Register *current_register{nullptr};
        };
    }
}
