/**
 * \file param_maintainer.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
    \brief Parameter "maintainer"

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#pragma once

#include "parameter.hpp"

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            namespace maintainer
            {
                struct maintainer_t
                {
                    uint16_t protocol   : 2;
                    uint16_t hardware   : 4;
                    uint16_t identifier : 10;
                } __attribute__((packed));

                static const size_t SIZE = sizeof(maintainer_t);

                /** \brief Maintainer parameter structure */
                union register_t
                {
                    uint8_t byte[SIZE];
                    uint16_t word; /* dangerous */

                    maintainer_t value;

                    void initialize(void);

                    void deserialize(uint8_t const *const);
                    void serialize(uint8_t **) const;
                } __attribute__((packed));

                extern register_t g_register;
            }
        }
    }
}
