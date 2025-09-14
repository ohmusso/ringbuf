#include "ringbuf.h"

RingBuf ringBuf;

void vRingBufInit(void)
{
    size_t i;
    for (i = 0; i < RING_BUF_SIZE; i++)
    {
        ringBuf.buf[i] = 0;
    }
    ringBuf.wPos = 0;
    ringBuf.rPos = 0;
    ringBuf.amount = 0;
}

size_t uxRingBufPush(uint8_t *data, size_t len)
{
    size_t space;
    size_t i;
    size_t wPos = ringBuf.wPos;
    size_t rPos = ringBuf.rPos;

    if (len <= 0)
    {
        return 0;
    }

    if (ringBuf.amount >= RING_BUF_SIZE)
    {
        return 0;
    }

    space = RING_BUF_SIZE - ringBuf.amount;

    if (len > space)
    {
        return 0;
    }

    if ((wPos + len) > RING_BUF_SIZE)
    {
        i = 0;
        while (wPos < RING_BUF_SIZE)
        {
            ringBuf.buf[wPos] = data[i];
            i++;
            wPos++;
        }

        wPos = 0;
        while (i < len)
        {
            ringBuf.buf[wPos] = data[i];
            i++;
            wPos++;
        }
    }
    else
    {
        i = 0;
        while (i < len)
        {
            ringBuf.buf[wPos] = data[i];
            i++;
            wPos++;
        }
    }

    if (wPos >= RING_BUF_SIZE)
    {
        wPos = 0;
    }
    ringBuf.wPos = wPos;

    ringBuf.amount += len;

    return len;
}

size_t uxRingBufPop(uint8_t *data, size_t len)
{
    size_t i;
    size_t wPos = ringBuf.wPos;
    size_t rPos = ringBuf.rPos;

    if (len <= 0)
    {
        return 0;
    }

    if (len > ringBuf.amount)
    {
        return 0;
    }

    if ((rPos + len) > RING_BUF_SIZE)
    {
        i = 0;
        while (rPos < RING_BUF_SIZE)
        {
            data[i] = ringBuf.buf[rPos];
            i++;
            rPos++;
        }

        rPos = 0;
        while (i < len)
        {
            data[i] = ringBuf.buf[rPos];
            i++;
            rPos++;
        }
    }
    else
    {
        i = 0;
        while (i < len)
        {
            data[i] = ringBuf.buf[rPos];
            i++;
            rPos++;
        }
    }

    if (rPos >= RING_BUF_SIZE)
    {
        rPos = 0;
    }
    ringBuf.rPos = rPos;

    ringBuf.amount -= len;

    return len;
}

size_t uxRingBufGetSpace(void)
{
    return RING_BUF_SIZE - ringBuf.amount;
}
