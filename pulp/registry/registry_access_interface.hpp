/**
 * \file registry_access_interface.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "registry_defines.hpp"

#include <cstdint>

namespace pulp::registry::parameter
{
    namespace address
    {
        struct address_t;
    }
    namespace audio
    {
        struct audio_t;
    }
    namespace charger
    {
        struct calibration_t;
    }
    namespace features
    {
        struct features_t;
    }
    namespace load
    {
        struct calibration_t;
    }
    namespace maintainer
    {
        struct maintainer_t;
    }
    namespace name
    {
        struct name_t;
    }
    namespace position
    {
        struct coordinates_t;
    }
    namespace serial_number
    {
        struct serial_t;
    }
    namespace unique_identifier
    {
        struct unique_t;
    }
    namespace user
    {
        struct user_t;
    }
    namespace visual
    {
        struct visual_t;
    }
}

namespace pulp::registry
{
    namespace access
    {
        struct Interface
        {
            virtual result_t address_get(parameter::address::address_t &) const = 0;
            virtual result_t address_set(const parameter::address::address_t &) = 0;

            virtual result_t audio_get(parameter::audio::audio_t &) const = 0;
            virtual result_t audio_set(const parameter::audio::audio_t &) = 0;

            virtual result_t charger_get(parameter::charger::calibration_t &) const = 0;
            virtual result_t charger_set(const parameter::charger::calibration_t &) = 0;

            virtual result_t features_get(parameter::features::features_t &) const = 0;
            virtual result_t features_set(const parameter::features::features_t &) = 0;

            virtual result_t load_get(parameter::load::calibration_t &) const = 0;
            virtual result_t load_set(const parameter::load::calibration_t &) = 0;

            virtual result_t maintainer_get(parameter::maintainer::maintainer_t &) const = 0;
            virtual result_t maintainer_set(const parameter::maintainer::maintainer_t &) = 0;

            virtual result_t name_get(parameter::name::name_t &) const = 0;
            virtual result_t name_set(const parameter::name::name_t &) = 0;

            virtual result_t position_get(parameter::position::coordinates_t &) const = 0;
            virtual result_t position_set(const parameter::position::coordinates_t &) = 0;

            virtual result_t serial_number_get(parameter::serial_number::serial_t &) const = 0;
            virtual result_t serial_number_set(const parameter::serial_number::serial_t &) = 0;

            virtual result_t unique_identifier_get(parameter::unique_identifier::unique_t &) const = 0;
            virtual result_t unique_identifier_set(const parameter::unique_identifier::unique_t &) = 0;

            virtual result_t user_get(parameter::user::user_t &) const = 0;
            virtual result_t user_set(const parameter::user::user_t &) = 0;

            virtual result_t visual_get(parameter::visual::visual_t &) const = 0;
            virtual result_t visual_set(const parameter::visual::visual_t &) = 0;
        };
    }
}
