/**
 * @file config_usart.h
 * @author 左岚，bilibili空间@https://space.bilibili.com/27619688
 * @brief 串口通信配置文件
 */
#ifndef __CONFIG_USART_H__
#define __CONFIG_USART_H__

#include "stm32f4xx_hal.h"
#include "usart.h"

// 串口功能配置
#define USART1_MODE_PACK 0   // 串口1使用数据包模式
#define USART1_MODE_HMI 1    // 串口1使用HMI模式
#define USART1_MODE_NORMAL 0 // 串口1使用普通模式
#define USART2_MODE_PACK 0   // 串口2使用数据包模式
#define USART2_MODE_HMI 0    // 串口2使用HMI模式
#define USART2_MODE_NORMAL 0 // 串口2使用普通模式
#define USART3_MODE_PACK 0   // 串口3使用数据包模式
#define USART3_MODE_HMI 0    // 串口3使用HMI模式
#define USART3_MODE_NORMAL 0 // 串口3使用普通模式
// 串口使能配置
#define USART1_ENABLE (USART1_MODE_PACK || USART1_MODE_HMI || USART1_MODE_NORMAL)
#define USART2_ENABLE (USART2_MODE_PACK || USART2_MODE_HMI || USART2_MODE_NORMAL)
#define USART3_ENABLE (USART3_MODE_PACK || USART3_MODE_HMI || USART3_MODE_NORMAL)
// 缓冲区配置
#define RX_BUFFER_SIZE 128 // 每个串口的接收缓冲区大小
// HMI配置
#define HMI_END_CMD "\xff\xff\xff" // HMI命令结束符

#endif // __CONFIG_USART_H__
