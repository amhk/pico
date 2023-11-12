cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(pico C CXX ASM)
set(CMAKE_C_STANDARD 17)

# If using Pico W hardware (cmake -DPICO_BOARD=pico_w ...)
if (PICO_CYW43_SUPPORTED)
    if (DEFINED ENV{WIFI_SSID} AND (NOT WIFI_SSID))
        set(WIFI_SSID $ENV{WIFI_SSID})
        message("Using WIFI_SSID from environment ('${WIFI_SSID}')")
    endif()

    if (DEFINED ENV{WIFI_PASSWORD} AND (NOT WIFI_PASSWORD))
        set(WIFI_PASSWORD $ENV{WIFI_PASSWORD})
        message("Using WIFI_PASSWORD from environment")
    endif()

    set(WIFI_SSID "${WIFI_SSID}" CACHE INTERNAL "WiFi SSID")
    set(WIFI_PASSWORD "${WIFI_PASSWORD}" CACHE INTERNAL "WiFi password")
endif()

pico_sdk_init()

add_subdirectory(led_strip)
