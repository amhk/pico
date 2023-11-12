# This project requires Pico W hardware (cmake -DPICO_BOARD=pico_w ...)
if (PICO_CYW43_SUPPORTED)
    add_executable(led_strip)

    target_sources(
        led_strip
        PRIVATE
        main.c
    )

    target_compile_definitions(
        led_strip
        PRIVATE
        WIFI_SSID=\"${WIFI_SSID}\"
        WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
    )

    target_link_libraries(
        led_strip
        PRIVATE
        pico_cyw43_arch_none
        pico_stdlib
    )

    pico_add_extra_outputs(led_strip)
endif()
