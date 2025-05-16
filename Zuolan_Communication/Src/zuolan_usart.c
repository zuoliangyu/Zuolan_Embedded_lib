/**
 * @file my_usart.c
 * @author 左岚，bilibili空间@https://space.bilibili.com/27619688
 * @brief 串口通信实现文件
 */
#include "zuolan_usart.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include "zuolan_usart_pack.h"
// 全局变量全部由config_usart.h统一管理
#if USART1_ENABLE
// 串口1的缓冲区和状态变量
uint8_t rxBuffer1[RX_BUFFER_SIZE];     ///< 串口1接收缓冲区
uint8_t rxTemp1;                       ///< 串口1中断接收临时变量
uint16_t rxIndex1 = 0;                 ///< 串口1当前接收缓冲区索引
volatile uint8_t commandReceived1 = 0; ///< 串口1接收到命令标志
#if USART1_MODE_PACK
volatile uint8_t frameStarted1 = 0; ///< 串口1帧开始标志
#endif
#endif

#if USART2_ENABLE
// 串口2数据包缓冲区和变量
uint8_t rxBuffer2[RX_BUFFER_SIZE]; ///< 串口2接收缓冲区
uint8_t rxTemp2;                   ///< 串口2中断接收临时变量
uint16_t rxIndex2 = 0;             ///< 串口2当前接收缓冲区索引
#if USART2_MODE_PACK
volatile uint8_t frameStarted2 = 0; ///< 串口2帧开始标志
#endif
#endif

#if USART3_ENABLE
// 串口3的缓冲区和状态变量
uint8_t rxBuffer3[RX_BUFFER_SIZE];     ///< 串口3接收缓冲区
uint8_t rxTemp3;                       ///< 串口3中断接收临时变量
uint16_t rxIndex3 = 0;                 ///< 串口3当前接收缓冲区索引
volatile uint8_t commandReceived3 = 0; ///< 串口3接收到命令标志
#if USART3_MODE_PACK
volatile uint8_t frameStarted3 = 0; ///< 串口3帧开始标志
#endif
#endif

/**
 * @brief 格式化打印并通过指定串口发送
 * @param huart 串口句柄
 * @param format 格式化字符串
 * @param ... 可变参数
 * @return 返回发送的字节数
 */
int zuolan_printf(UART_HandleTypeDef *huart, const char *format, ...)
{
    char buffer[512]; // 临时缓冲区，用于存储格式化后的字符串
    va_list arg;      // 可变参数列表
    int len;

    va_start(arg, format);                                // 初始化可变参数列表
    len = vsnprintf(buffer, sizeof(buffer), format, arg); // 格式化字符串
    va_end(arg);                                          // 清理可变参数列表

    HAL_UART_Transmit(huart, (uint8_t *)buffer, (uint16_t)len, 0xFF); // 发送格式化后的字符串
    return len;
}

/**
 * @brief 串口接收中断回调函数
 * @param huart 串口句柄
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#if USART1_ENABLE
    if (huart->Instance == USART1)
    {
#if USART1_MODE_PACK
        if (rxTemp1 == FRAME_HEADER)
        {
            frameStarted1 = 1;
            rxIndex1 = 0;
            rxBuffer1[rxIndex1++] = rxTemp1;
        }
        else if (frameStarted1)
        {
            rxBuffer1[rxIndex1++] = rxTemp1;

            if (rxTemp1 == FRAME_TAIL)
            {
                frameStarted1 = 0;
                zuolan_ParseFrame(rxBuffer1, rxIndex1);
            }

            if (rxIndex1 >= RX_BUFFER_SIZE)
            {
                frameStarted1 = 0;
                rxIndex1 = 0;
                memset(rxBuffer1, 0, RX_BUFFER_SIZE);
            }
        }
#elif USART1_MODE_HMI
        if (rxIndex1 < RX_BUFFER_SIZE - 1)
        {
            if (rxTemp1 == '\n' && rxBuffer1[rxIndex1 - 1] == '\r')
            {
                commandReceived1 = 1;
                rxBuffer1[rxIndex1 - 1] = '\0';
            }
            else
            {
                rxBuffer1[rxIndex1++] = rxTemp1;
            }
        }
        else
        {
            rxIndex1 = 0;
        }
#elif USART1_MODE_NORMAL
        if (rxIndex1 < RX_BUFFER_SIZE - 1)
        {
            rxBuffer1[rxIndex1++] = rxTemp1;
        }
        else
        {
            rxIndex1 = 0;
        }
#endif
        HAL_UART_Receive_IT(&huart1, &rxTemp1, 1);
    }
#endif

#if USART2_ENABLE
    if (huart->Instance == USART2)
    {
#if USART2_MODE_PACK
        if (rxTemp2 == FRAME_HEADER)
        {
            frameStarted2 = 1;
            rxIndex2 = 0;
            rxBuffer2[rxIndex2++] = rxTemp2;
        }
        else if (frameStarted2)
        {
            rxBuffer2[rxIndex2++] = rxTemp2;

            if (rxTemp2 == FRAME_TAIL)
            {
                frameStarted2 = 0;
                zuolan_ParseFrame(rxBuffer2, rxIndex2);
            }

            if (rxIndex2 >= RX_BUFFER_SIZE)
            {
                frameStarted2 = 0;
                rxIndex2 = 0;
                memset(rxBuffer2, 0, RX_BUFFER_SIZE);
            }
        }
#elif USART2_MODE_HMI
        if (rxIndex2 < RX_BUFFER_SIZE - 1)
        {
            if (rxTemp2 == '\n' && rxBuffer2[rxIndex2 - 1] == '\r')
            {
                commandReceived2 = 1;
                rxBuffer2[rxIndex2 - 1] = '\0';
            }
            else
            {
                rxBuffer2[rxIndex2++] = rxTemp2;
            }
        }
        else
        {
            rxIndex2 = 0;
        }
#elif USART2_MODE_NORMAL
        if (rxIndex2 < RX_BUFFER_SIZE - 1)
        {
            rxBuffer2[rxIndex2++] = rxTemp2;
        }
        else
        {
            rxIndex2 = 0;
        }
#endif
        HAL_UART_Receive_IT(&huart2, &rxTemp2, 1);
    }
#endif

#if USART3_ENABLE
    if (huart->Instance == USART3)
    {
#if USART3_MODE_PACK
        if (rxTemp3 == FRAME_HEADER)
        {
            frameStarted3 = 1;
            rxIndex3 = 0;
            rxBuffer3[rxIndex3++] = rxTemp3;
        }
        else if (frameStarted3)
        {
            rxBuffer3[rxIndex3++] = rxTemp3;

            if (rxTemp3 == FRAME_TAIL)
            {
                frameStarted3 = 0;
                zuolan_ParseFrame(rxBuffer3, rxIndex3);
            }

            if (rxIndex3 >= RX_BUFFER_SIZE)
            {
                frameStarted3 = 0;
                rxIndex3 = 0;
                memset(rxBuffer3, 0, RX_BUFFER_SIZE);
            }
        }
#elif USART3_MODE_HMI
        if (rxIndex3 < RX_BUFFER_SIZE - 1)
        {
            if (rxTemp3 == '\n' && rxBuffer3[rxIndex3 - 1] == '\r')
            {
                commandReceived3 = 1;
                rxBuffer3[rxIndex3 - 1] = '\0';
            }
            else
            {
                rxBuffer3[rxIndex3++] = rxTemp3;
            }
        }
        else
        {
            rxIndex3 = 0;
        }
#elif USART3_MODE_NORMAL
        if (rxIndex3 < RX_BUFFER_SIZE - 1)
        {
            rxBuffer3[rxIndex3++] = rxTemp3;
        }
        else
        {
            rxIndex3 = 0;
        }
#endif
        HAL_UART_Receive_IT(&huart3, &rxTemp3, 1);
    }
#endif
}
