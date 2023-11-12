#include <stdio.h>

#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    printf("main.c: hello world\n");
    while (true) {
        tight_loop_contents();
    }
}
