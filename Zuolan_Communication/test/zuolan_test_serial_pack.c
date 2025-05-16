#include <stdio.h>
#include "zuolan_serial_pack.h"

int main()
{
    /*** 接收相关变量 ***/
    int zuolan_recvInt1 = 0, zuolan_recvInt2 = 0, zuolan_recvInt3 = 0;
    float zuolan_recvFloat1 = 0.0;
    uint8_t zuolan_recvByte1 = 0;
    int zuolan_recvInts[5] = {0};

    // 定义接收数据的模板数组和变量数组
    DataType zuolan_recvTemplateArray[] = {
        TYPE_INT,   // zuolan_recvInt1
        TYPE_FLOAT, // zuolan_recvFloat1
        TYPE_BYTE,  // zuolan_recvByte1
        TYPE_INT,   // zuolan_recvInt2
        TYPE_INT,   // zuolan_recvInt3
        TYPE_INT,   // zuolan_recvInts[0]
        TYPE_INT,   // zuolan_recvInts[1]
        TYPE_INT,   // zuolan_recvInts[2]
        TYPE_INT,   // zuolan_recvInts[3]
        TYPE_INT    // zuolan_recvInts[4]
    };

    void *zuolan_recvVariableArray[] = {
        &zuolan_recvInt1,    // zuolan_recvInt1
        &zuolan_recvFloat1,  // zuolan_recvFloat1
        &zuolan_recvByte1,   // zuolan_recvByte1
        &zuolan_recvInt2,    // zuolan_recvInt2
        &zuolan_recvInt3,    // zuolan_recvInt3
        &zuolan_recvInts[0], // zuolan_recvInts[0]
        &zuolan_recvInts[1], // zuolan_recvInts[1]
        &zuolan_recvInts[2], // zuolan_recvInts[2]
        &zuolan_recvInts[3], // zuolan_recvInts[3]
        &zuolan_recvInts[4]  // zuolan_recvInts[4]
    };

    /*** 发送相关变量 ***/
    int zuolan_sendInt1 = 500, zuolan_sendInt2 = 1000, zuolan_sendInt3 = 1500;
    float zuolan_sendFloat1 = 25.7;
    uint8_t zuolan_sendByte1 = 250;
    int zuolan_sendInts[5] = {10, 20, 30, 40, 50};

    // 定义发送数据的模板数组和变量数组
    DataType zuolan_sendTemplateArray[] = {
        TYPE_INT,   // zuolan_sendInt1
        TYPE_FLOAT, // zuolan_sendFloat1
        TYPE_BYTE,  // zuolan_sendByte1
        TYPE_INT,   // zuolan_sendInt2
        TYPE_INT,   // zuolan_sendInt3
        TYPE_INT,   // zuolan_sendInts[0]
        TYPE_INT,   // zuolan_sendInts[1]
        TYPE_INT,   // zuolan_sendInts[2]
        TYPE_INT,   // zuolan_sendInts[3]
        TYPE_INT    // zuolan_sendInts[4]
    };

    void *zuolan_sendVariableArray[] = {
        &zuolan_sendInt1,    // zuolan_sendInt1
        &zuolan_sendFloat1,  // zuolan_sendFloat1
        &zuolan_sendByte1,   // zuolan_sendByte1
        &zuolan_sendInt2,    // zuolan_sendInt2
        &zuolan_sendInt3,    // zuolan_sendInt3
        &zuolan_sendInts[0], // zuolan_sendInts[0]
        &zuolan_sendInts[1], // zuolan_sendInts[1]
        &zuolan_sendInts[2], // zuolan_sendInts[2]
        &zuolan_sendInts[3], // zuolan_sendInts[3]
        &zuolan_sendInts[4]  // zuolan_sendInts[4]
    };

    /*** 模拟接收到的数据帧 ***/
    uint8_t zuolan_receivedFrame[] = {
        FRAME_HEADER,           // 帧头
        0x00, 0x00, 0x00, 0x64, // zuolan_recvInt1 = 100
        0x42, 0x48, 0x96, 0x49, // zuolan_recvFloat1 = 50.3 (假设 IEEE754)
        0x7F,                   // zuolan_recvByte1 = 127
        0x00, 0x00, 0x00, 0xC8, // zuolan_recvInt2 = 200
        0x00, 0x00, 0x00, 0x2A, // zuolan_recvInt3 = 42
        0x00, 0x00, 0x00, 0x01, // zuolan_recvInts[0] = 1
        0x00, 0x00, 0x00, 0x02, // zuolan_recvInts[1] = 2
        0x00, 0x00, 0x00, 0x03, // zuolan_recvInts[2] = 3
        0x00, 0x00, 0x00, 0x04, // zuolan_recvInts[3] = 4
        0x00, 0x00, 0x00, 0x05, // zuolan_recvInts[4] = 5
        0xD8,                   // 校验和
        FRAME_TAIL              // 帧尾
    };

    uint16_t zuolan_frameLength = sizeof(zuolan_receivedFrame);

    /*** 解析接收到的数据帧 ***/
    // 设置接收模板
    Zuolan_SetParseTemplate(zuolan_recvTemplateArray, zuolan_recvVariableArray, 10);

    // 解析接收到的数据帧
    Zuolan_ParseFrame(zuolan_receivedFrame, zuolan_frameLength);

    // 打印解析后的变量值
    printf("Parsed Received Data:\n");
    printf("zuolan_recvInt1: %d\n", zuolan_recvInt1);
    printf("zuolan_recvFloat1: %f\n", zuolan_recvFloat1);
    printf("zuolan_recvByte1: %d\n", zuolan_recvByte1);
    printf("zuolan_recvInt2: %d\n", zuolan_recvInt2);
    printf("zuolan_recvInt3: %d\n", zuolan_recvInt3);
    for (int i = 0; i < 5; i++)
    {
        printf("zuolan_recvInts[%d]: %d\n", i, zuolan_recvInts[i]);
    }

    /*** 准备发送序列化后的数据帧 ***/
    // 设置发送模板
    Zuolan_SetParseTemplate(zuolan_sendTemplateArray, zuolan_sendVariableArray, 10);

    // 准备发送数据帧
    uint8_t zuolan_sendBuffer[256];
    uint16_t zuolan_sendFrameLength = Zuolan_PrepareFrame(zuolan_sendBuffer, sizeof(zuolan_sendBuffer));

    if (zuolan_sendFrameLength > 0)
    {
        // 发送数据帧
        printf("\nSerialized and Sending Data:\n");
        Zuolan_SendFrame(zuolan_sendBuffer, zuolan_sendFrameLength);
    }
    else
    {
        printf("Failed to prepare frame for sending!\n");
    }

    return 0;
}
