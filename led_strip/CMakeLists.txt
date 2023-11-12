add_executable(led_strip)

target_sources(
    led_strip
    PRIVATE
    main.c
)

target_link_libraries(
    led_strip
    PRIVATE
    pico_stdlib
)

pico_add_extra_outputs(led_strip)
