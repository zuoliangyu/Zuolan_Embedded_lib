/**
 * @file my_usart.h
 * @author 左岚，bilibili空间@https://space.bilibili.com/27619688
 * @brief 串口通信基础功能头文件
 */
#ifndef __MY_USART_H__
#define __MY_USART_H__
#include "config_usart.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "stdint.h"
#define RX_BUFFER_SIZE 128 // 每个串口的接收缓冲区大小
// 数据包
#define MIN_FRAME_SIZE 3  // 最小帧大小
extern uint8_t rxTemp1, rxTemp2, rxTemp3;
extern uint8_t rxBuffer1[RX_BUFFER_SIZE], rxBuffer2[RX_BUFFER_SIZE], rxBuffer3[RX_BUFFER_SIZE];
extern uint16_t rxIndex1, rxIndex2, rxIndex3;
extern volatile uint8_t commandReceived1, commandReceived3;
int zuolan_printf(UART_HandleTypeDef *huart, const char *format, ...);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif // __MY_USART_H__
