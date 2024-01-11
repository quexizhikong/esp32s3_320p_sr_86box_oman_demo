#ifndef _UART_FRAME_H__
#define _UART_FRAME_H__

#include <stdint.h>
#include "driver/uart.h"

#define UART_QUEUE_LENGTH 5
#define RX_BUF_SIZE 256
#define TX_BUF_SIZE 0

#define PACK_FIRST_BYTE 0xAA
#define PACK_SECOND_BYTE 0x55

typedef struct {
    uint16_t cmd;
    uint8_t* buffer;
    uint32_t len;
} al01_frame_t;

void al01_init(uint8_t uart_num, int16_t tx_pin, int16_t rx_pin, uint32_t boudrate);

void al01_write_bytes(uint16_t cmd, uint8_t param, const uint8_t* frame, uint32_t len);

int al01_recv_frame(al01_frame_t* frame, uint32_t timeout_ms);

void al01_free_frame_buffer(al01_frame_t* frame);

#endif
