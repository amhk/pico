#include <stdio.h>

#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    printf("%s: WIFI_SSID='%s' WIFI_PASSWORD='%s'\n", __FILE__, WIFI_SSID,
           WIFI_PASSWORD);
    if (cyw43_arch_init()) {
        fprintf(stderr, "cyw43_arch_init failed\n");
        return 1;
    }
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(250);
    }
}
