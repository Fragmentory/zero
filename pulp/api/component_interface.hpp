/**
 * \file component_interface.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

namespace pulp
{
    struct ComponentInterface
    {
        virtual ~ComponentInterface() {}

        virtual void initialize() = 0;
        virtual void shutdown() = 0;
    };
}
