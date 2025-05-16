# Zuolan Embedded Library 🚀

[English](README.md) | [中文](README_CN.md)

## English

### Introduction 📖
Zuolan Embedded Library is an open-source embedded component library that provides high-performance, reliable, and easy-to-use components for embedded systems development.

### Features ✨
- Serial Communication Module
  - Support for multiple baud rates
  - Configurable data bits, stop bits, and parity
  - Interrupt-driven and polling modes
  - Buffer management
  - Error handling

### Getting Started 🚀
1. Clone the repository
```bash
git clone https://github.com/yourusername/Zuolan_Embedded_lib.git
```

2. Include the library in your project
```c
#include "Zuolan_Communication/serial.h"
```

### Usage Example 💡
```c
// Initialize serial port
Serial_Init(115200, SERIAL_8N1);

// Send data
Serial_SendString("Hello World!\r\n");

// Receive data
uint8_t data = Serial_ReceiveByte();
```

### Contributing 🤝
We welcome contributions! Please feel free to submit a Pull Request.

### License 📄
This project is licensed under the MIT License - see the LICENSE file for details.

---

## Chinese

### 简介 📖
左蓝嵌入式库是一个开源的嵌入式组件库，为嵌入式系统开发提供高性能、可靠且易用的组件。

### 特性 ✨
- 串口通信模块
  - 支持多种波特率
  - 可配置数据位、停止位和校验位
  - 中断驱动和轮询模式
  - 缓冲区管理
  - 错误处理

### 快速开始 🚀
1. 克隆仓库
```bash
git clone https://github.com/yourusername/Zuolan_Embedded_lib.git
```

2. 在项目中包含库文件
```c
#include "Zuolan_Communication/serial.h"
```

### 使用示例 💡
```c
// 初始化串口
Serial_Init(115200, SERIAL_8N1);

// 发送数据
Serial_SendString("Hello World!\r\n");

// 接收数据
uint8_t data = Serial_ReceiveByte();
```

### 参与贡献 🤝
我们欢迎各种形式的贡献！欢迎提交 Pull Request。

### 开源协议 📄
本项目采用 MIT 协议 - 详见 LICENSE 文件。 