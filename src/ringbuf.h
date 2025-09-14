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

extern void vRingBufInit();
extern size_t uxRingBufPush(uint8_t *data, size_t len);
extern size_t uxRingBufPop(uint8_t *data, size_t len);
extern size_t uxRingBufGetSpace();

#endif /* RINGBUF_H */
