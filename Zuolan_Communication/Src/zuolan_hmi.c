/**
 * @file my_hmi.c
 * @author 左岚，bilibili空间@https://space.bilibili.com/27619688
 * @brief HMI人机交互实现文件
 */
#include "zuolan_hmi.h"
#include "math.h"

// 根据配置选择HMI串口
#if USART1_MODE_HMI
#define huart_hmi huart1
#elif USART2_MODE_HMI
#define huart_hmi huart2
#elif USART3_MODE_HMI
#define huart_hmi huart3
#endif

/**
 * @brief 向HMI控件发送字符串数据
 * @param obj_name 控件名称（建议格式：页面名.控件名，例如"page1.text1"）
 * @param show_data 要显示的字符串内容
 */
void zuolan_HMI_Send_String(char *obj_name, char *show_data)
{
    zuolan_printf(&huart_hmi, "%s.txt=\"%s\"%s", obj_name, show_data, HMI_END_CMD);
}

/**
 * @brief 向HMI控件发送整数数据
 * @param obj_name 控件名称（建议格式：页面名.控件名，例如"page1.number1"）
 * @param show_data 要显示的整数值
 */
void zuolan_HMI_Send_Int(char *obj_name, int show_data)
{
    zuolan_printf(&huart_hmi, "%s.val=%d%s", obj_name, show_data, HMI_END_CMD);
}

/**
 * @brief 向HMI控件发送浮点数数据
 * @param obj_name 控件名称（建议格式：页面名.控件名，例如"page1.float1"）
 * @param show_data 要显示的浮点数值
 * @param point_index 小数点后保留的位数
 */
void zuolan_HMI_Send_Float(char *obj_name, float show_data, int point_index)
{
    int temp = show_data * pow(10, point_index);
    zuolan_printf(&huart_hmi, "%s.val=%d%s", obj_name, temp, HMI_END_CMD);
}

/**
 * @brief 清除指定通道上的波形数据
 * @param obj_name 波形控件名称（建议格式：页面名.控件名，例如"page1.wave1"）
 * @param ch 波形通道编号（0 ~ 3）
 */
void zuolan_HMI_Wave_Clear(char *obj_name, int ch)
{
    zuolan_printf(&huart_hmi, "cle %s,%d%s", obj_name, ch, HMI_END_CMD);
}

/**
 * @brief 向指定波形控件添加单点数据（实时逐点发送，速度较慢）
 * @param obj_name 波形控件名称（建议格式：页面名.控件名，例如"page1.wave1"）
 * @param ch 波形通道编号（0 ~ 3）
 * @param val 数据值（0 ~ 255，需调用前归一化处理，0表示最底部）
 */
void zuolan_HMI_Write_Wave_Low(char *obj_name, int ch, int val)
{
    zuolan_printf(&huart_hmi, "add %s.id,%d,%d%s", obj_name, ch, val, HMI_END_CMD);
}

/**
 * @brief 向指定波形控件快速发送多点数据
 * @param obj_name 波形控件名称（建议格式：页面名.控件名，例如"page1.wave1"）
 * @param ch 波形通道编号（0 ~ 3）
 * @param len 数据长度 (最大1024)
 * @param val 数据值数组（每个值范围0 ~ 255，需调用前归一化处理）
 */
void zuolan_HMI_Write_Wave_Fast(char *obj_name, int ch, int len, int *val)
{
    zuolan_printf(&huart_hmi, "addt %s.id,%d,%d%s", obj_name, ch, len, HMI_END_CMD);
    HAL_Delay(100);
    for (int i = 0; i < len; i++)
    {
        zuolan_printf(&huart_hmi, "%c", val[i]);
    }
    zuolan_printf(&huart_hmi, "\x01%s", HMI_END_CMD);
}
