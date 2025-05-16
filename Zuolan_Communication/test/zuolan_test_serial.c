#include "zuolan_serial.h"
void main()
{
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
}