#ifndef __CHINESE_H
#define __CHINESE_H	 
#include "LCD.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32�����塪����չʵ��
//�Զ��庺����ʾ  ����			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/7/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


void TEST_FONT(void);
void Test_Show_CH_Font16(u16 x,u16 y,u8 index,u16 color);
void Test_Show_CH_Font24(u16 x,u16 y,u8 index,u16 color);		  				    
#endif
