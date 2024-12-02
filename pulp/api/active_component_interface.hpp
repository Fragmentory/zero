/**
 * \file active_component_interface.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "component_interface.hpp"

namespace pulp
{
    struct ActiveComponentInterface : public ComponentInterface
    {
        virtual ~ActiveComponentInterface() {}

        virtual void perform() = 0;
    };
}
