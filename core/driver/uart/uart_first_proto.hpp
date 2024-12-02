/**
 * \file uart_first_proto.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>
#include <hardware/irq.h>
#include <hardware/uart.h>

namespace core
{
    namespace driver
    {
        namespace uart
        {
            namespace first
            {
                struct Proto
                {
                    static const unsigned int USART_SPACE_SIZE = (1 << 8);
                    static const int BAUD_RATE = 115200;
                    static const int DATA_BITS = 8;
                    static const int STOP_BITS = 1;
                    static const uart_parity_t PARITY = UART_PARITY_NONE;
                    static const int UART_TX_PIN = 0;
                    static const int UART_RX_PIN = 1;
                    static const int UART_IRQ = UART0_IRQ;
                    static constexpr uint32_t UART_BASE = UART0_BASE;
                };
            }
        }
    }
}
