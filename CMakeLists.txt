#
# Copyright (c) 2018 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
#

cmake_minimum_required(VERSION 3.13.1)

set(spm_CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/spm.conf)


set(PM_STATIC_YML_FILE
  ${CMAKE_CURRENT_SOURCE_DIR}/configuration/${BOARD}/pm_static.yml
  )

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(mqtt_google_cloud)

zephyr_compile_definitions(PROJECT_NAME=${PROJECT_NAME})
zephyr_compile_definitions(_POSIX_C_SOURCE=200809L)

if(NOT EXISTS ${APPLICATION_SOURCE_DIR}/src/private_info/key.c)
    message(FATAL_ERROR "!!!!!! Generate key file before continuing !!!!!!")
endif()

# NORDIC SDK APP START
target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/gcloud.c)
target_sources(app PRIVATE src/cJSON.c)
target_sources(app PRIVATE src/private_info/key.c)
# NORDIC SDK APP END
zephyr_include_directories(src)

# Include application events and configuration headers
zephyr_library_include_directories(
  include
  src/env_sensors
  src/watchdog
  )

# Application sources
add_subdirectory(src/env_sensors)
add_subdirectory(src/watchdog)

if (CONFIG_USE_BME680_BSEC)
  target_link_libraries(app PUBLIC bsec_lib)
endif()