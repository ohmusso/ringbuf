#ifndef RINGBUF_H
#define RINGBUF_H

#include <stdint.h>

#define RING_BUF_SIZE 10
typedef struct
{
    uint8_t buf[RING_BUF_SIZE];
    size_t wPos;
    size_t rPos;
    size_t amount;
} RingBuf;

extern RingBuf ringBuf;

extern void v_RingBuf_init();
extern size_t v_RingBuf_push(uint8_t *data, size_t len);
extern size_t v_RingBuf_pop(uint8_t *data, size_t len);
extern size_t v_RingBuf_getSpace();

#endif /* RINGBUF_H */
