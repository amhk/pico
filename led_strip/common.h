#ifndef _COMMON_H_
#define _COMMON_H_

#define TCP_PORT 4242

#ifndef NDEBUG
#define INFO(fmt, ...)                               \
    _INFO("%s:%d:%s: " fmt "\n", __FILE__, __LINE__, \
          __FUNCTION__ __VA_OPT__(, ) __VA_ARGS__)

#define _INFO(fmt, ...)           \
    do {                          \
        printf(fmt, __VA_ARGS__); \
    } while (0)
#else
#define INFO
#endif

#define PANIC(fmt, ...)                                      \
    _PANIC("%s:%d:%s: ERROR: " fmt "\n", __FILE__, __LINE__, \
           __FUNCTION__ __VA_OPT__(, ) __VA_ARGS__)

#define _PANIC(fmt, ...)                   \
    do {                                   \
        fprintf(stderr, fmt, __VA_ARGS__); \
        fflush(stderr);                    \
        abort();                           \
    } while (0)

// implemented in net.c
[[noreturn]] void tcp_server();

#endif
