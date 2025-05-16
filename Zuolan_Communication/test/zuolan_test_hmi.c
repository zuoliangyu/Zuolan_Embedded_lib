#include "zuolan_hmi.h"
#include "math.h"
void main()
{
    char zuolan_char_data[6] = "hello";
    int zuolan_int_data = 10;
    float zuolan_float_data = 10.5;
    int zuolan_wave_data[1024];
    for (int i = 0; i < 1024; i++)
    {
        // 构建一个周期的正弦波，并且把幅度设置为0~200
        zuolan_wave_data[i] = (sin(i * 2 * 3.14 / 1024) + 1) * 100;
    }
    Zuolan_HMI_Send_String("char_data", zuolan_char_data);
    Zuolan_HMI_Send_Int("int_data", zuolan_int_data);
    Zuolan_HMI_Send_Float("float_data", zuolan_float_data, 1);
    for (int i = 0; i < 1024; i++)
    {
        Zuolan_HMI_Write_Wave_Low("low_wave", 0, zuolan_wave_data[i]);
    }
    Zuolan_HMI_Wave_Clear("low_wave", 0);
    
    Zuolan_HMI_Write_Wave_Fast("fast_wave", 0, 1024, zuolan_wave_data);
}