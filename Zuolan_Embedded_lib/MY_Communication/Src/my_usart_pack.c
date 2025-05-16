/**
 * @file my_usart_pack.c
 * @author 左岚，bilibili空间@https://space.bilibili.com/27619688
 * @brief 串口数据包实现文件
 */
#include "my_usart_pack.h"
#include "config_usart.h"
#include "stm32f4xx_hal.h"
#include <string.h> // 用于内存操作

// 根据配置选择数据包串口
#if USART1_MODE_PACK
#define huart_pack huart1
#elif USART2_MODE_PACK
#define huart_pack huart2
#elif USART3_MODE_PACK
#define huart_pack huart3
#endif

// 全局变量，用于存储解析模板
static DataType parseTemplate[MAX_VARIABLES]; // 数据类型模板数组
static void *variableMapping[MAX_VARIABLES];  // 变量地址映射数组
static uint16_t variableCount = 0;            // 模板中的变量个数

/**
 * @brief 设置解析模板
 * @param templateArray 数据类型模板数组
 * @param variableArray 变量地址数组
 * @param count 模板中变量的个数
 */
void zuolan_SetParseTemplate(DataType *templateArray, void **variableArray, uint16_t count)
{
    if (count > MAX_VARIABLES) // 防止超出最大变量限制
        return;

    for (uint16_t i = 0; i < count; i++)
    {
        parseTemplate[i] = templateArray[i];   // 设置数据类型
        variableMapping[i] = variableArray[i]; // 设置变量地址映射
    }
    variableCount = count; // 更新变量个数
}

/**
 * @brief 数据帧解析函数，将数据解析到变量中
 * @param my_data 数据帧的指针
 * @param length 数据帧的长度
 */
static void zuolan_ParseDataToVariables(uint8_t *my_data, uint16_t length)
{
    uint16_t index = 0; // 数据区解析索引

    for (uint16_t i = 0; i < variableCount; i++) // 按模板逐个解析变量
    {
        if (index >= length) // 防止索引越界
            return;

        switch (parseTemplate[i])
        {
        case TYPE_BYTE: // 单字节类型
        {
            uint8_t *byteVar = (uint8_t *)variableMapping[i];
            *byteVar = my_data[index]; // 解析为uint8_t
            index++;                   // 单字节占用1字节
            break;
        }
        case TYPE_SHORT: // 短整型类型
        {
            if (index + 1 >= length) // 防止索引越界
                return;
            uint16_t *shortVar = (uint16_t *)variableMapping[i];
            *shortVar = (my_data[index] << 8) | my_data[index + 1]; // 高低字节拼接
            index += 2;                                             // 短整型占用2字节
            break;
        }
        case TYPE_INT: // 整型类型
        {
            if (index + 3 >= length) // 防止索引越界
                return;
            int *intVar = (int *)variableMapping[i];
            *intVar = (my_data[index] << 24) | (my_data[index + 1] << 16) |
                      (my_data[index + 2] << 8) | my_data[index + 3]; // 高低字节拼接
            index += 4;                                               // 整型占用4字节
            break;
        }
        case TYPE_FLOAT: // 浮点型类型
        {
            if (index + 3 >= length) // 防止索引越界
                return;
            float *floatVar = (float *)variableMapping[i];
            *floatVar = *((float *)(my_data + index)); // 假设数据为IEEE754格式
            index += 4;                                // 浮点型占用4字节
            break;
        }
        default:
            return; // 不支持的类型直接返回
        }
    }
}

/**
 * @brief 数据帧解析入口
 * @param buffer 数据帧的指针
 * @param length 数据帧的长度
 */
void zuolan_ParseFrame(uint8_t *buffer, uint16_t length)
{
    // 检查最小帧长度（帧头 + 数据区 + 校验和 + 帧尾）
    if (length < MIN_FRAME_LENGTH)
        return;

    // 检查帧头和帧尾
    if (buffer[0] != FRAME_HEADER || buffer[length - 1] != FRAME_TAIL)
        return;

    // 校验和验证
    uint16_t dataLength = length - 3; // 数据区长度
    uint8_t checksum = 0;
    for (uint16_t i = 1; i <= dataLength; i++)
    {
        checksum += buffer[i];
    }
    if ((checksum & 0xFF) != buffer[length - 2]) // 检查校验和
        return;

    // 调用数据解析函数
    zuolan_ParseDataToVariables(buffer + 1, dataLength);
}

/**
 * @brief 数据帧序列化（准备发送数据帧）
 * @param buffer 缓冲区指针，用于存储序列化后的数据
 * @param maxLength 缓冲区的最大长度
 * @return 返回序列化后的数据帧长度
 */
uint16_t zuolan_PrepareFrame(uint8_t *buffer, uint16_t maxLength)
{
    if (maxLength < MIN_FRAME_LENGTH) // 检查缓冲区是否满足最小帧长度
        return 0;

    uint16_t index = 0;

    // 添加帧头
    buffer[index++] = FRAME_HEADER;

    // 序列化数据
    for (uint16_t i = 0; i < variableCount; i++)
    {
        switch (parseTemplate[i])
        {
        case TYPE_BYTE:
        {
            if (index + 1 > maxLength) // 检查缓冲区是否溢出
                return 0;
            uint8_t *byteVar = (uint8_t *)variableMapping[i];
            buffer[index++] = *byteVar; // 添加单字节数据
            break;
        }
        case TYPE_SHORT:
        {
            if (index + 2 > maxLength)
                return 0;
            uint16_t *shortVar = (uint16_t *)variableMapping[i];
            buffer[index++] = (*shortVar >> 8) & 0xFF; // 高字节
            buffer[index++] = *shortVar & 0xFF;        // 低字节
            break;
        }
        case TYPE_INT:
        {
            if (index + 4 > maxLength)
                return 0;
            int *intVar = (int *)variableMapping[i];
            buffer[index++] = (*intVar >> 24) & 0xFF;
            buffer[index++] = (*intVar >> 16) & 0xFF;
            buffer[index++] = (*intVar >> 8) & 0xFF;
            buffer[index++] = *intVar & 0xFF;
            break;
        }
        case TYPE_FLOAT:
        {
            if (index + 4 > maxLength)
                return 0;
            float *floatVar = (float *)variableMapping[i];
            uint8_t *floatBytes = (uint8_t *)floatVar; // 假设数据为IEEE754格式
            buffer[index++] = floatBytes[0];
            buffer[index++] = floatBytes[1];
            buffer[index++] = floatBytes[2];
            buffer[index++] = floatBytes[3];
            break;
        }
        default:
            return 0; // 不支持的类型直接返回
        }
    }

    // 计算校验和
    uint8_t checksum = 0;
    for (uint16_t i = 1; i < index; i++)
    {
        checksum += buffer[i];
    }
    buffer[index++] = checksum & 0xFF;

    // 添加帧尾
    if (index < maxLength)
    {
        buffer[index++] = FRAME_TAIL;
    }
    else
    {
        return 0; // 超出缓冲区长度
    }

    return index; // 返回帧总长度
}

/**
 * @brief 发送数据帧（通过USART2）
 * @param frame 数据帧指针
 * @param length 数据帧长度
 */
void zuolan_SendFrame(uint8_t *frame, uint16_t length)
{
    HAL_UART_Transmit(&huart_pack, frame, length, HAL_MAX_DELAY);
}
