/**
 * \file registry_access.hpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "chunk.h"
#include "param_address.hpp"
#include "param_audio.hpp"
#include "param_charger.hpp"
#include "param_features.hpp"
#include "param_load.hpp"
#include "param_maintainer.hpp"
#include "param_name.hpp"
#include "param_position.hpp"
#include "param_serial_number.hpp"
#include "param_unique_identifier.hpp"
#include "param_user.hpp"
#include "param_visual.hpp"
#include "registry.hpp"
#include "registry_access_interface.hpp"

namespace pulp::registry
{
    struct Access : public pulp::registry::access::Interface
    {
        Access(const pulp::registry::Instance &_registry) :
            registry(_registry)
        {
        }

        virtual result_t address_get(parameter::address::address_t &) const override;
        virtual result_t address_set(const parameter::address::address_t &) override;

        virtual result_t audio_get(parameter::audio::audio_t &) const override;
        virtual result_t audio_set(const parameter::audio::audio_t &) override;

        virtual result_t charger_get(parameter::charger::calibration_t &) const override;
        virtual result_t charger_set(const parameter::charger::calibration_t &) override;

        virtual result_t features_get(parameter::features::features_t &) const override;
        virtual result_t features_set(const parameter::features::features_t &) override;

        virtual result_t load_get(parameter::load::calibration_t &) const override;
        virtual result_t load_set(const parameter::load::calibration_t &) override;

        virtual result_t maintainer_get(parameter::maintainer::maintainer_t &) const override;
        virtual result_t maintainer_set(const parameter::maintainer::maintainer_t &) override;

        virtual result_t name_get(parameter::name::name_t &) const override;
        virtual result_t name_set(const parameter::name::name_t &) override;

        virtual result_t position_get(parameter::position::coordinates_t &) const override;
        virtual result_t position_set(const parameter::position::coordinates_t &) override;

        virtual result_t serial_number_get(parameter::serial_number::serial_t &) const override;
        virtual result_t serial_number_set(const parameter::serial_number::serial_t &) override;

        virtual result_t unique_identifier_get(parameter::unique_identifier::unique_t &) const override;
        virtual result_t unique_identifier_set(const parameter::unique_identifier::unique_t &) override;

        virtual result_t user_get(parameter::user::user_t &) const override;
        virtual result_t user_set(const parameter::user::user_t &) override;

        virtual result_t visual_get(parameter::visual::visual_t &) const override;
        virtual result_t visual_set(const parameter::visual::visual_t &) override;

      private:
        const pulp::registry::Instance &registry;
    };
}
