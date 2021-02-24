/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F19196
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "sht30.h"
//#include "LCD/lcd.h"

#include "Tuya_sdk/mcu_api.h"
#include "Tuya_sdk/protocol.h"
#include "Tuya_sdk/system.h"
#include "Tuya_sdk/wifi.h"

#define     RED          0XF800	  //��ɫ
#define     GREEN        0X07E0	  //��ɫ
#define     BLUE         0X001F	  //��ɫ
#define     WHITE        0XFFFF	  //��ɫ
#define WIFI_CONTROL_SELF_MODE 
extern bool Connect_Flag;
bool start_Flag = 0;
bool Charge_Flag = false;
extern bool updata_flag;
extern bool connect_statue;

void Reset_WIFI_SSID();
void task(); 
void LED_Statue();

extern unsigned int wifi_sht30_data[4];
/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    wifi_protocol_init();
    
//    LCD_Init();   	//LCD��ʼ��
//    POINT_COLOR = BLUE;	  																//������ɫ��ɫ
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();


//    WIFI_RST_SetLow();      //��λ��WIFIģ��
//    __delay_ms(100);
//    WIFI_RST_SetHigh();      

    work_statue= Initialize;	
    
    while (1)
    {
        // Add your application code
        SHT30_read_result(sht30_addr);

        wifi_uart_service();
        
        LED_Statue();
        task();
        Reset_WIFI_SSID();


//		LCD_ShowString(30,40,200,24,24,"Temperature:");					//��ʾ�ַ���
//		LCD_ShowString(30,70,200,24,24,"Humidity:");		//��ʾ�ַ���
//		LCD_ShowString(30,100,200,24,24,lcddev.id);						//��ʾLCD ID	      					 
//		LCD_ShowString(30,130,200,24,24,"2021/2/14");	      //��ʾ����	 
					
        

    }
}
/**
 End of File
*/
void task()
{
    switch ( work_statue )
    {
        case Initialize:
        {
            Connect_Flag = 0;
            updata_flag = 0;
            work_statue = Check_Wifi_Connect;
            break;
        }
        
        case Check_Wifi_Connect:
        {
            if ( connect_statue == 1 )      //��ʱ�ж�WIFI��û������·����
            {
                if ( mcu_get_wifi_work_state() == WIFI_CONN_CLOUD )
                {
                    work_statue = UpData;
                    printf("�豸�ɹ������ƶ�\n");
                }
            }
            break;
        }
        
        case UpData:
        {
            Connect_Flag = 1;
            if (  updata_flag == 1   )     //�ж��Ƿ�ʱ�䣬�ϱ�״̬��Ϣ
            {     
                updata_flag = 0;        //����ϱ���־
                all_data_update();
                printf("�����ϱ���\n");
            }
            break;
        }
    }
            
}



void Reset_WIFI_SSID()
{
    if( KEY_GetValue() == 0 )
    {
        __delay_ms(5);
        if( KEY_GetValue() == 0 )
        {
            while(!KEY_GetValue());
            mcu_reset_wifi();                       //�����������
            Connect_Flag = 0 ;
            if( mcu_get_reset_wifi_flag() )         //�ж�������������Ƿ�ɹ�
            {
//                printf("����������óɹ�\n");
                mcu_set_wifi_mode(0);           //����Ϊsmartconfig����ģʽ
                if ( set_wifimode_flag == true )    //�ж�����ģʽ�Ƿ����óɹ�
                {
//                   printf("����ģʽ���óɹ�\n");
                   work_statue= Initialize;
                }  	
            }
        }
    }
}

void LED_Statue()
{
    if ( Connect_Flag == 0 )
    {
        if( connect_statue == 1 )
        {
            LED_Toggle();
        }
    }
    else
    {
        LED_SetHigh();
    }
}
























