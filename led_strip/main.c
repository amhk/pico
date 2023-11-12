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
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    cyw43_arch_enable_sta_mode();
    printf("connecting...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD,
                                           CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        fprintf(stderr, "failed to connect\n");
        return -1;
    } else {
        printf("connected\n");
    }
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    while (true) {
        tight_loop_contents();
    }
}
