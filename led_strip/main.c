#include <stdio.h>

#include "common.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

static void on_command_cb(const char* command) { INFO("hello %d", 42); }

int main() {
    stdio_init_all();
    INFO("WIFI_SSID='%s' WIFI_PASSWORD='%s'", WIFI_SSID, WIFI_PASSWORD);
    if (cyw43_arch_init()) {
        PANIC("cyw43_arch_init failed");
    }
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD,
                                           CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        PANIC("failed to connect");
    }
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    tcp_server();
    return 1;  // won't happen
}
