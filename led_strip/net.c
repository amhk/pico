#include <string.h>

#include "common.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "pico/cyw43_arch.h"

static err_t tcp_server_recv_cb(void *arg, struct tcp_pcb *client_pcb,
                                struct pbuf *p, err_t err) {
    INFO("arg=%p client_pcb=%p p=%p err=%d", arg, p, client_pcb, err);
    if (!p) {
        return err;
    }

    char *buf = calloc(sizeof(char), p->len);
    if (!buf) {
        return ERR_MEM;
    }
    memcpy(buf, p->payload, p->len);
    tcp_recved(client_pcb, p->len);
    pbuf_free(p);

    while (strlen(buf) > 0 && isspace(buf[strlen(buf) - 1])) {
        buf[strlen(buf) - 1] = '\0';
    }

    // payload should be returned to main.c via callback for further
    // processing; this will be implemented in a follow-up commit
    if (strcmp(buf, "on") == 0) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    }
    if (strcmp(buf, "off") == 0) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    }

    free(buf);
    return ERR_OK;
}

static err_t tcp_server_sent_cb(void *arg, struct tcp_pcb *client_pcb,
                                u16_t len) {
    INFO("arg=%p client_pcb=%p len=%d", arg, client_pcb, len);
    return ERR_OK;
}

static err_t tcp_server_accept_cb(void *arg, struct tcp_pcb *client_pcb,
                                  err_t err) {
    INFO("arg=%p client_pcb=%p err=%d", arg, client_pcb, err);

    tcp_sent(client_pcb, tcp_server_sent_cb);
    tcp_recv(client_pcb, tcp_server_recv_cb);

    err = tcp_write(client_pcb, "hello\n", 6, TCP_WRITE_FLAG_COPY);
    if (err) {
        PANIC("tcp_write failed: err=%d", err);
    }
    return ERR_OK;
}

[[noreturn]] void tcp_server() {
    struct tcp_pcb *pcb = tcp_new_ip_type(IPADDR_TYPE_ANY);
    if (!pcb) {
        PANIC("failed to create pcb");
        abort();
    }

    err_t err = tcp_bind(pcb, NULL, TCP_PORT);
    if (err) {
        PANIC("failed to bind to port=%d: err=%d", TCP_PORT, err);
    }

    struct tcp_pcb *server_pcb = tcp_listen_with_backlog(pcb, 1);
    if (!server_pcb) {
        PANIC("failed to listen");
    }

    tcp_accept(server_pcb, tcp_server_accept_cb);
    while (true) {
        sleep_ms(1000);
    }
}
