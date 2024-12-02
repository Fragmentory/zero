/**
 * \file uart_handler.hpp
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
            /** \brief Type for RX/TX handler */
            typedef void (*rx_tx_handler_t)(buffer_t *const _rx, buffer_t *const _tx);
        }
    }
}
