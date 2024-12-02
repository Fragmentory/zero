/**
 * \file usart_buffer.hpp
 * \author Roman Koch koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "bytering.hpp"

#include <cstdint>

namespace core
{
    namespace driver
    {
        namespace uart
        {
            struct Buffer
            {
                uint8_t *rx_space;
                buffer_t rx_buffer;
                uint8_t *tx_space;
                buffer_t tx_buffer;

                void echo() { bytering_copy(&rx_buffer, &tx_buffer); }
            };
        }
    }
}
