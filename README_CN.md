# 左岚嵌入式库 🚀

[English](README.md) | [中文](README_CN.md)

### 简介 📖
左岚嵌入式库是一个开源的嵌入式组件库，为嵌入式系统开发提供高性能、可靠且易用的组件。

### 特性 ✨
- 串口通信模块
  - 支持多种波特率
  - 可配置数据位、停止位和校验位
  - 中断驱动和轮询模式
  - 缓冲区管理
  - 错误处理
  - 数据帧打包/解包
    - 支持多种数据类型（整型、浮点型、字节型）
    - 帧头/帧尾校验和
    - 基于模板的数据解析
    - 数组支持

### 快速开始 🚀
1. 克隆仓库
```bash
git clone https://github.com/yourusername/Zuolan_Embedded_lib.git
```

2. 在项目中包含库文件
```c
#include "Zuolan_Communication/zuolan_serial.h"
#include "Zuolan_Communication/zuolan_serial_pack.h"
```

### 使用示例 💡
```c
// 基础串口通信
while (1)
{
    if (zuolan_commandReceived1)
    {
        zuolan_commandReceived1 = 0;
        memset(zuolan_rxBuffer1, 0, zuolan_rxIndex1);
    }
    if (zuolan_commandReceived3)
    {
        zuolan_commandReceived3 = 0;
        memset(zuolan_rxBuffer3, 0, zuolan_rxIndex3);
    }
}

// 数据帧打包/解包
// 定义变量
int zuolan_recvInt1 = 0, zuolan_recvInt2 = 0, zuolan_recvInt3 = 0;
float zuolan_recvFloat1 = 0.0;
uint8_t zuolan_recvByte1 = 0;
int zuolan_recvInts[5] = {0};

// 设置模板和变量数组
DataType zuolan_recvTemplateArray[] = {
    TYPE_INT,   // zuolan_recvInt1
    TYPE_FLOAT, // zuolan_recvFloat1
    TYPE_BYTE,  // zuolan_recvByte1
    TYPE_INT,   // zuolan_recvInt2
    TYPE_INT    // zuolan_recvInt3
};

void *zuolan_recvVariableArray[] = {
    &zuolan_recvInt1,    // zuolan_recvInt1
    &zuolan_recvFloat1,  // zuolan_recvFloat1
    &zuolan_recvByte1,   // zuolan_recvByte1
    &zuolan_recvInt2,    // zuolan_recvInt2
    &zuolan_recvInt3     // zuolan_recvInt3
};

// 设置模板并解析数据帧
Zuolan_SetParseTemplate(zuolan_recvTemplateArray, zuolan_recvVariableArray, 5);
Zuolan_ParseFrame(zuolan_receivedFrame, zuolan_frameLength);
```

### 测试文件 📝
- `zuolan_test_serial.c`: 基础串口通信测试
- `zuolan_test_serial_pack.c`: 数据帧打包/解包测试
  - 演示基于模板的数据解析
  - 展示多种数据类型支持
  - 包含数组处理
  - 具有帧校验和验证功能

### 参与贡献 🤝
我们欢迎各种形式的贡献！欢迎提交 Pull Request。

### 开源协议 📄
本项目采用 MIT 协议 - 详见 LICENSE 文件。
