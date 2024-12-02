# Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

add_library(zero)

pico_generate_pio_header(zero "${CMAKE_CURRENT_LIST_DIR}/core/driver/visual/neopixel.pio")

target_sources(zero PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/core/board/board_assembly.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/core.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/audio/audio_melody.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/audio/audio_pwm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/audio/audio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/i2c/default_bank/i2c_memory_default_bank.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/i2c/i2c_master.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/i2c/i2c_slave.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/i2c/memory/i2c_memory_register.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/soc/rp2040/rp2040_gpio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/soc/rp2040/rp2040_pwm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/soc/rp2040/rp2040_soc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/soc/rp2040/rp2040_stopwatch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/soc/rp2040/rp2040_temperature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/soc/rp2040/rp2040_ticker.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/soc/rp2040/rp2040_watchdog.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/temperature/core_temperature.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/usb/usb_descriptors_cdc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/usb/usb_descriptors_hid.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/usb/usb_device.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/visual/inolux5050.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/visual/program/visual_prog_active.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/visual/program/visual_prog_alert.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/visual/program/visual_prog_freeze.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/visual/program/visual_prog_idle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/visual/program/visual_prog_off.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/visual/program/visual_prog_ready.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/visual/program/visual_prog_service.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/visual/visual_executor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/visual/visual.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/driver/visual/ws2812.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/service/random_sequence.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/service/reboot_watcher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/engine/default_device_validator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/engine/engine_scheduler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/engine/engine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/engine/state_update.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/parameter/param_address.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/parameter/param_audio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/parameter/param_charger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/parameter/param_features.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/parameter/param_load.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/parameter/param_maintainer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/parameter/param_name.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/parameter/param_position.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/parameter/param_serial_number.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/parameter/param_unique_identifier.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/parameter/param_user.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/parameter/param_visual.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/parameter/parameter_identifier.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/pulp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/registry/parameter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/registry/registry_access.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/registry/registry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/utilities/bytering.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/utilities/checksum.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pulp/utilities/macros.cpp
)

include(${CMAKE_SOURCE_DIR}/build/subdirectories.cmake)
get_subdirectories(ZERO_SUBDIRS ${CMAKE_CURRENT_LIST_DIR})

target_include_directories(zero PUBLIC
    ${CMAKE_SOURCE_DIR}/bin
    ${CMAKE_CURRENT_LIST_DIR}
    ${ZERO_SUBDIRS}
)

target_compile_options(tinyusb_board INTERFACE -Wno-switch-enum)
target_compile_options(tinyusb_device INTERFACE -Wno-switch-enum)

target_link_libraries(zero
    hardware_adc
    hardware_clocks
    hardware_exception
    hardware_flash
    hardware_i2c
    hardware_pio
    hardware_pwm
    hardware_spi
    hardware_sync

    pico_stdlib
    pico_i2c_slave

    tinyusb_board
    tinyusb_device
)
