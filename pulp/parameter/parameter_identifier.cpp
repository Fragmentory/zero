/**
 * \file parameter_identifier.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "parameter_identifier.hpp"

namespace pulp
{
    namespace registry
    {
        namespace parameter
        {
            /**
             * \brief
             *
             * \param _value
             * \return const IDENTIFIER
             */
            extern IDENTIFIER to_identifier(const uint8_t _value)
            {
                IDENTIFIER tmp = static_cast<IDENTIFIER>(_value);
                if (tmp == IDENTIFIER::AUDIO_FEEDBACK || tmp == IDENTIFIER::CHARGER_CALIB || tmp == IDENTIFIER::DEVICE_NAME || tmp == IDENTIFIER::FEATURES
                    || tmp == IDENTIFIER::LOAD_CALIB || tmp == IDENTIFIER::MAINTAINER || tmp == IDENTIFIER::POSITION || tmp == IDENTIFIER::SERIAL_NUMBER
                    || tmp == IDENTIFIER::UNIQUE_IDENTIFIER || tmp == IDENTIFIER::USER || tmp == IDENTIFIER::VISUAL_FEEDBACK)
                {
                    return tmp;
                }

                return IDENTIFIER::UNDEFINED;
            }

        }
    }
}