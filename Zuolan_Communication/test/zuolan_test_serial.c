#include "zuolan_usart.h"
void main()
{
    while (1)
    {
        if (commandReceived1)
        {
            commandReceived1 = 0;
            memset(rxBuffer1, 0, rxIndex1);
            rxIndex1 = 0;
        }
        if (commandReceived3)
        {
            commandReceived3 = 0;
            memset(rxBuffer3, 0, rxIndex3);
            rxIndex3 = 0;
        }
    }
}