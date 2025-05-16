/**
 * @file my_hmi.h
 * @author 左岚，bilibili空间@https://space.bilibili.com/27619688
 * @brief HMI人机交互接口头文件
 */
#ifndef __MY_HMI_H__
#define __MY_HMI_H__
#include "config_usart.h"
#include "zuolan_usart.h"
void zuolan_HMI_Send_String(char *obj_name, char *show_data);
void zuolan_HMI_Send_Int(char *obj_name, int show_data);
void zuolan_HMI_Send_Float(char *obj_name, float show_data, int point_index);
void zuolan_HMI_Wave_Clear(char *obj_name, int ch);
void zuolan_HMI_Write_Wave_Low(char *obj_name, int ch, int val);
void zuolan_HMI_Write_Wave_Fast(char *obj_name, int ch, int len, int *val);

#endif // __MY_HMI_H__
