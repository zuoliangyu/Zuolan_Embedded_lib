/**
 * @file my_usart_pack.h
 * @author 左岚，bilibili空间@https://space.bilibili.com/27619688
 * @brief 串口数据包处理头文件
 */
#ifndef __MY_USART_PACK_H__
#define __MY_USART_PACK_H__
#include "stdint.h"

// 数据包相关定义
#define FRAME_HEADER 0xA5
#define FRAME_TAIL 0x5A
#define MIN_FRAME_SIZE 3
#define MAX_VARIABLES 10
#define MIN_FRAME_LENGTH 3 // 最小帧长度（帧头  + 校验和 + 帧尾）
// 数据类型
typedef enum
{
    TYPE_BYTE,
    TYPE_SHORT,
    TYPE_INT,
    TYPE_FLOAT
} DataType;

// 接口函数声明
void zuolan_SetParseTemplate(DataType *templateArray, void **variableArray, uint16_t count);
void zuolan_ParseFrame(uint8_t *buffer, uint16_t length);
uint16_t zuolan_PrepareFrame(uint8_t *buffer, uint16_t maxLength);
void zuolan_SendFrame(uint8_t *frame, uint16_t length);

#endif // __MY_USART_PACK_H__
