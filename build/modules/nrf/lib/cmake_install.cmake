# Install script for directory: /Users/tadmcallister/Nordic/safecility_thingy/ncs/nrf/lib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Users/tadmcallister/opt/gnuarmemb/gcc-arm-none-eabi-8-2019-q3-update/bin/arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/tadmcallister/Nordic/safecility_thingy/ncs/nrf/samples/nrf9160/mqtt_google_cloud/build/modules/nrf/lib/bin/cmake_install.cmake")
  include("/Users/tadmcallister/Nordic/safecility_thingy/ncs/nrf/samples/nrf9160/mqtt_google_cloud/build/modules/nrf/lib/bsdlib/cmake_install.cmake")
  include("/Users/tadmcallister/Nordic/safecility_thingy/ncs/nrf/samples/nrf9160/mqtt_google_cloud/build/modules/nrf/lib/at_cmd/cmake_install.cmake")
  include("/Users/tadmcallister/Nordic/safecility_thingy/ncs/nrf/samples/nrf9160/mqtt_google_cloud/build/modules/nrf/lib/at_notif/cmake_install.cmake")
  include("/Users/tadmcallister/Nordic/safecility_thingy/ncs/nrf/samples/nrf9160/mqtt_google_cloud/build/modules/nrf/lib/at_cmd_parser/cmake_install.cmake")
  include("/Users/tadmcallister/Nordic/safecility_thingy/ncs/nrf/samples/nrf9160/mqtt_google_cloud/build/modules/nrf/lib/lte_link_control/cmake_install.cmake")
  include("/Users/tadmcallister/Nordic/safecility_thingy/ncs/nrf/samples/nrf9160/mqtt_google_cloud/build/modules/nrf/lib/modem_info/cmake_install.cmake")
  include("/Users/tadmcallister/Nordic/safecility_thingy/ncs/nrf/samples/nrf9160/mqtt_google_cloud/build/modules/nrf/lib/pdn_management/cmake_install.cmake")
  include("/Users/tadmcallister/Nordic/safecility_thingy/ncs/nrf/samples/nrf9160/mqtt_google_cloud/build/modules/nrf/lib/adp536x/cmake_install.cmake")
  include("/Users/tadmcallister/Nordic/safecility_thingy/ncs/nrf/samples/nrf9160/mqtt_google_cloud/build/modules/nrf/lib/flash_patch/cmake_install.cmake")
  include("/Users/tadmcallister/Nordic/safecility_thingy/ncs/nrf/samples/nrf9160/mqtt_google_cloud/build/modules/nrf/lib/fatal_error/cmake_install.cmake")
  include("/Users/tadmcallister/Nordic/safecility_thingy/ncs/nrf/samples/nrf9160/mqtt_google_cloud/build/modules/nrf/lib/modem_key_mgmt/cmake_install.cmake")
  include("/Users/tadmcallister/Nordic/safecility_thingy/ncs/nrf/samples/nrf9160/mqtt_google_cloud/build/modules/nrf/lib/date_time/cmake_install.cmake")

endif()

