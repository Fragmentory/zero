/**
 * \file registry_access.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#include "registry_access.hpp"

#include "checksum.hpp"
#include "macros.hpp"
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
#include "parameter.hpp"
#include "pulp.hpp"
#include "random_sequence.hpp"
#include "registry.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <pico/assert.h>

namespace pulp::registry
{
    /**
        \brief Get address  parameter
    */
    result_t Access::address_get(parameter::address::address_t &_data) const
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        result_t result = parameter::address_load(parameter::g_param_address);
        _data.address_0 = parameter::address::g_register.value.address_0;
        _data.address_1 = parameter::address::g_register.value.address_1;
        _data.address_2 = parameter::address::g_register.value.address_2;
        _data.address_3 = parameter::address::g_register.value.address_3;
        return result;
    }

    /**
        \brief Save address  parameter
    */
    result_t Access::address_set(const parameter::address::address_t &_data)
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        parameter::address::g_register.value.address_0 = _data.address_0;
        parameter::address::g_register.value.address_1 = _data.address_1;
        parameter::address::g_register.value.address_2 = _data.address_2;
        parameter::address::g_register.value.address_3 = _data.address_3;
        return parameter::param_save();
    }

    /**
        \brief Get audio feedback parameter
    */
    result_t Access::audio_get(parameter::audio::audio_t &_data) const
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        result_t result = parameter::audio_load(parameter::g_param_audio);
        _data.loudness = parameter::audio::g_register.value.loudness;
        _data.verbosity = parameter::audio::g_register.value.verbosity;
        return result;
    }

    /**
        \brief Save audio feedback parameter
    */
    result_t Access::audio_set(const parameter::audio::audio_t &_data)
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        parameter::audio::g_register.value.loudness = _data.loudness;
        parameter::audio::g_register.value.verbosity = _data.verbosity;
        return parameter::param_save();
    }

    /**
        \brief Get charger parameter
    */
    result_t Access::charger_get(parameter::charger::calibration_t &_data) const
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        result_t result = parameter::charger_load(parameter::g_param_charger);
        _data.value1 = parameter::charger::g_register.value.value1;
        _data.value2 = parameter::charger::g_register.value.value2;
        _data.value3 = parameter::charger::g_register.value.value3;
        return result;
    }

    /**
        \brief Save charger parameter
    */
    result_t Access::charger_set(const parameter::charger::calibration_t &_data)
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        parameter::charger::g_register.value.value1 = _data.value1;
        parameter::charger::g_register.value.value2 = _data.value2;
        parameter::charger::g_register.value.value3 = _data.value3;
        return parameter::param_save();
    }

    /**
        \brief Get features parameter
    */
    result_t Access::features_get(parameter::features::features_t &_data) const
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        result_t result = parameter::features_load(parameter::g_param_features);
        _data.reserved = parameter::features::g_register.value.reserved;
        return result;
    }

    /**
        \brief Save features parameter
    */
    result_t Access::features_set(const parameter::features::features_t &_data)
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        parameter::features::g_register.value.reserved = _data.reserved;
        return parameter::param_save();
    }

    /**
        \brief Get load parameter
    */
    result_t Access::load_get(parameter::load::calibration_t &_data) const
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        result_t result = parameter::load_load(parameter::g_param_load);
        _data.value1 = parameter::load::g_register.value.value1;
        _data.value2 = parameter::load::g_register.value.value2;
        _data.value3 = parameter::load::g_register.value.value3;
        _data.value4 = parameter::load::g_register.value.value4;
        _data.value5 = parameter::load::g_register.value.value5;
        return result;
    }

    /**
        \brief Save load parameter
    */
    result_t Access::load_set(const parameter::load::calibration_t &_data)
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        parameter::load::g_register.value.value1 = _data.value1;
        parameter::load::g_register.value.value2 = _data.value2;
        parameter::load::g_register.value.value3 = _data.value3;
        parameter::load::g_register.value.value4 = _data.value4;
        parameter::load::g_register.value.value5 = _data.value5;
        return parameter::param_save();
    }

    /**
        \brief Get maintainer parameter
    */
    result_t Access::maintainer_get(parameter::maintainer::maintainer_t &_data) const
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        result_t result = parameter::maintainer_load(parameter::g_param_maintainer);
        _data.hardware = parameter::maintainer::g_register.value.hardware;
        _data.identifier = parameter::maintainer::g_register.value.identifier;
        _data.protocol = parameter::maintainer::g_register.value.protocol;
        return result;
    }

    /**
        \brief Save maintainer parameter
    */
    result_t Access::maintainer_set(const parameter::maintainer::maintainer_t &_data)
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        parameter::maintainer::g_register.value.hardware = _data.hardware;
        parameter::maintainer::g_register.value.identifier = _data.identifier;
        parameter::maintainer::g_register.value.protocol = _data.protocol;
        return parameter::param_save();
    }

    /**
        \brief Get name parameter
    */
    result_t Access::name_get(parameter::name::name_t &_data) const
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        result_t result = parameter::name_load(parameter::g_param_name);
        memcpy(_data.byte, parameter::name::g_register.value.byte, parameter::name::name_t::SIZE);
        return result;
    }

    /**
        \brief Save name parameter
    */
    result_t Access::name_set(const parameter::name::name_t &_data)
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        memcpy(parameter::name::g_register.value.byte, _data.byte, parameter::name::name_t::SIZE);
        return parameter::param_save();
    }

    /**
        \brief Get node position
        Position combine a two long values: latitude and longitude
    */
    result_t Access::position_get(parameter::position::coordinates_t &_data) const
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        result_t result = parameter::position_load(parameter::g_param_position);
        _data.latitude = parameter::position::g_register.value.latitude;
        _data.longitude = parameter::position::g_register.value.longitude;
        return result;
    }

    /**
        \brief Save node position value
    */
    result_t Access::position_set(const parameter::position::coordinates_t &_data)
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        parameter::position::g_register.value.latitude = _data.latitude;
        parameter::position::g_register.value.longitude = _data.longitude;
        return parameter::param_save();
    }

    /**
        \brief Get serial number value
    */
    result_t Access::serial_number_get(parameter::serial_number::serial_t &_data) const
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        result_t result = parameter::serial_number_load(parameter::g_param_serial_number);
        memcpy(_data.byte, parameter::serial_number::g_register.value.byte, parameter::serial_number::serial_t::SIZE);
        return result;
    }

    /**
        \brief  Save serial number value
        is unsupported
    */
    result_t Access::serial_number_set(const parameter::serial_number::serial_t &_data)
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        memcpy(parameter::serial_number::g_register.value.byte, _data.byte, parameter::serial_number::serial_t::SIZE);
        return parameter::param_save();
    }

    /**
        \brief Get unique_identifier feedback parameter
    */
    result_t Access::unique_identifier_get(parameter::unique_identifier::unique_t &_data) const
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        result_t result = parameter::unique_identifier_load(parameter::g_param_unique_identifier);
        memcpy(_data.byte, parameter::unique_identifier::g_register.value.byte, parameter::unique_identifier::unique_t::SIZE);
        return result;
    }

    /**
        \brief Save unique_identifier feedback parameter value
    */
    result_t Access::unique_identifier_set(const parameter::unique_identifier::unique_t &_data)
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        memcpy(parameter::unique_identifier::g_register.value.byte, _data.byte, parameter::unique_identifier::unique_t::SIZE);
        return parameter::param_save();
    }

    /**
        \brief Get user register value
    */
    result_t Access::user_get(parameter::user::user_t &_data) const
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        result_t result = parameter::user_load(parameter::g_param_user);
        memcpy(_data.byte, parameter::user::g_register.value.byte, parameter::user::user_t::SIZE);
        return result;
    }

    /**
        \brief Save parameter value
    */
    result_t Access::user_set(const parameter::user::user_t &_data)
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        memcpy(parameter::user::g_register.value.byte, _data.byte, parameter::user::user_t::SIZE);
        return parameter::param_save();
    }

    /**
        \brief Get visual feedback parameter
    */
    result_t Access::visual_get(parameter::visual::visual_t &_data) const
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        result_t result = parameter::visual_load(parameter::g_param_visual);
        _data.mode = parameter::visual::g_register.value.mode;
        _data.timeout = parameter::visual::g_register.value.timeout;
        _data.verbosity = parameter::visual::g_register.value.verbosity;
        return result;
    }

    /**
        \brief Save visual feedback parameter value
    */
    result_t Access::visual_set(const parameter::visual::visual_t &_data)
    {
        assert(registry.is_ready() == SUCCESS); /* state should be initialized */
        parameter::visual::g_register.value.mode = _data.mode;
        parameter::visual::g_register.value.timeout = _data.timeout;
        parameter::visual::g_register.value.verbosity = _data.verbosity;
        return parameter::param_save();
    }
}
