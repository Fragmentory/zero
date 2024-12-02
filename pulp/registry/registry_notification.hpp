/**
 * \file registry_notification.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Node configuration

    Depends on node parameter.
    Commands should be used with HCI.

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#pragma once

#include "registry_defines.hpp"

namespace pulp
{
    namespace registry
    {
        namespace notification
        {
            enum class CAUSE : uint8_t
            {
                RESET,
                UNDEFINED = 0xff,
            };

            enum class EVENT : uint8_t
            {
                PARAMETER_MISSED,
                BACKUP_CREATED,
                CRITICAL_ERROR,
                UNDEFINED = 0xff,
            };

            struct Event
            {
                CAUSE cause;
                EVENT identifier;
            };

            struct Interface
            {
                virtual void handle(const Event &) = 0;
            };
        }
    }
}