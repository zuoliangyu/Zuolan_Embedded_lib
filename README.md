# Zuolan Embedded Library 🚀

[English](README.md) | [中文](README_CN.md)

### Introduction 📖
Zuolan Embedded Library is an open-source embedded component library that provides high-performance, reliable, and easy-to-use components for embedded systems development.

### Features ✨
- Serial Communication Module
  - Support for multiple baud rates
  - Configurable data bits, stop bits, and parity
  - Interrupt-driven and polling modes
  - Buffer management
  - Error handling
  - Data frame packing/unpacking
    - Support for multiple data types (int, float, byte)
    - Frame header/tail with checksum
    - Template-based data parsing
    - Array support

### Getting Started 🚀
1. Clone the repository
```bash
git clone https://github.com/yourusername/Zuolan_Embedded_lib.git
```

2. Include the library in your project
```c
#include "Zuolan_Communication/zuolan_serial.h"
#include "Zuolan_Communication/zuolan_serial_pack.h"
```

### Usage Example 💡
```c
// Basic serial communication
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

// Data frame packing/unpacking
// Define variables
int zuolan_recvInt1 = 0, zuolan_recvInt2 = 0, zuolan_recvInt3 = 0;
float zuolan_recvFloat1 = 0.0;
uint8_t zuolan_recvByte1 = 0;
int zuolan_recvInts[5] = {0};

// Set up template and variable arrays
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

// Set template and parse frame
Zuolan_SetParseTemplate(zuolan_recvTemplateArray, zuolan_recvVariableArray, 5);
Zuolan_ParseFrame(zuolan_receivedFrame, zuolan_frameLength);
```

### Test Files 📝
- `zuolan_test_serial.c`: Basic serial communication test
- `zuolan_test_serial_pack.c`: Data frame packing/unpacking test
  - Demonstrates template-based data parsing
  - Shows support for multiple data types
  - Includes array handling
  - Features frame validation with checksum

### Contributing 🤝
We welcome contributions! Please feel free to submit a Pull Request.

### License 📄
This project is licensed under the MIT License - see the LICENSE file for details.
