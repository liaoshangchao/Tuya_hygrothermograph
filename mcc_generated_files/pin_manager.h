/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F19196
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set BL_CTR aliases
#define BL_CTR_TRIS                 TRISCbits.TRISC1
#define BL_CTR_LAT                  LATCbits.LATC1
#define BL_CTR_PORT                 PORTCbits.RC1
#define BL_CTR_WPU                  WPUCbits.WPUC1
#define BL_CTR_OD                   ODCONCbits.ODCC1
#define BL_CTR_ANS                  ANSELCbits.ANSC1
#define BL_CTR_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define BL_CTR_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define BL_CTR_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define BL_CTR_GetValue()           PORTCbits.RC1
#define BL_CTR_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define BL_CTR_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define BL_CTR_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define BL_CTR_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define BL_CTR_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define BL_CTR_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define BL_CTR_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define BL_CTR_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set SCL aliases
#define SCL_TRIS                 TRISCbits.TRISC3
#define SCL_LAT                  LATCbits.LATC3
#define SCL_PORT                 PORTCbits.RC3
#define SCL_WPU                  WPUCbits.WPUC3
#define SCL_OD                   ODCONCbits.ODCC3
#define SCL_ANS                  ANSELCbits.ANSC3
#define SCL_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SCL_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SCL_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SCL_GetValue()           PORTCbits.RC3
#define SCL_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SCL_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define SCL_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define SCL_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define SCL_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define SCL_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define SCL_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set SDA aliases
#define SDA_TRIS                 TRISCbits.TRISC4
#define SDA_LAT                  LATCbits.LATC4
#define SDA_PORT                 PORTCbits.RC4
#define SDA_WPU                  WPUCbits.WPUC4
#define SDA_OD                   ODCONCbits.ODCC4
#define SDA_ANS                  ANSELCbits.ANSC4
#define SDA_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SDA_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SDA_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SDA_GetValue()           PORTCbits.RC4
#define SDA_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SDA_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define SDA_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define SDA_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define SDA_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define SDA_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define SDA_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define SDA_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set KEY aliases
#define KEY_TRIS                 TRISCbits.TRISC6
#define KEY_LAT                  LATCbits.LATC6
#define KEY_PORT                 PORTCbits.RC6
#define KEY_WPU                  WPUCbits.WPUC6
#define KEY_OD                   ODCONCbits.ODCC6
#define KEY_ANS                  ANSELCbits.ANSC6
#define KEY_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define KEY_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define KEY_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define KEY_GetValue()           PORTCbits.RC6
#define KEY_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define KEY_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define KEY_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define KEY_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define KEY_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define KEY_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define KEY_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define KEY_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

// get/set DB1 aliases
#define DB1_TRIS                 TRISDbits.TRISD0
#define DB1_LAT                  LATDbits.LATD0
#define DB1_PORT                 PORTDbits.RD0
#define DB1_WPU                  WPUDbits.WPUD0
#define DB1_OD                   ODCONDbits.ODCD0
#define DB1_ANS                  ANSELDbits.ANSD0
#define DB1_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define DB1_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define DB1_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define DB1_GetValue()           PORTDbits.RD0
#define DB1_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define DB1_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define DB1_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define DB1_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define DB1_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define DB1_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define DB1_SetAnalogMode()      do { ANSELDbits.ANSD0 = 1; } while(0)
#define DB1_SetDigitalMode()     do { ANSELDbits.ANSD0 = 0; } while(0)

// get/set DB2 aliases
#define DB2_TRIS                 TRISDbits.TRISD1
#define DB2_LAT                  LATDbits.LATD1
#define DB2_PORT                 PORTDbits.RD1
#define DB2_WPU                  WPUDbits.WPUD1
#define DB2_OD                   ODCONDbits.ODCD1
#define DB2_ANS                  ANSELDbits.ANSD1
#define DB2_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define DB2_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define DB2_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define DB2_GetValue()           PORTDbits.RD1
#define DB2_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define DB2_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define DB2_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define DB2_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define DB2_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define DB2_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define DB2_SetAnalogMode()      do { ANSELDbits.ANSD1 = 1; } while(0)
#define DB2_SetDigitalMode()     do { ANSELDbits.ANSD1 = 0; } while(0)

// get/set DB3 aliases
#define DB3_TRIS                 TRISDbits.TRISD2
#define DB3_LAT                  LATDbits.LATD2
#define DB3_PORT                 PORTDbits.RD2
#define DB3_WPU                  WPUDbits.WPUD2
#define DB3_OD                   ODCONDbits.ODCD2
#define DB3_ANS                  ANSELDbits.ANSD2
#define DB3_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define DB3_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define DB3_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define DB3_GetValue()           PORTDbits.RD2
#define DB3_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define DB3_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define DB3_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define DB3_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define DB3_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define DB3_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define DB3_SetAnalogMode()      do { ANSELDbits.ANSD2 = 1; } while(0)
#define DB3_SetDigitalMode()     do { ANSELDbits.ANSD2 = 0; } while(0)

// get/set DB4 aliases
#define DB4_TRIS                 TRISDbits.TRISD3
#define DB4_LAT                  LATDbits.LATD3
#define DB4_PORT                 PORTDbits.RD3
#define DB4_WPU                  WPUDbits.WPUD3
#define DB4_OD                   ODCONDbits.ODCD3
#define DB4_ANS                  ANSELDbits.ANSD3
#define DB4_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define DB4_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define DB4_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define DB4_GetValue()           PORTDbits.RD3
#define DB4_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define DB4_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define DB4_SetPullup()          do { WPUDbits.WPUD3 = 1; } while(0)
#define DB4_ResetPullup()        do { WPUDbits.WPUD3 = 0; } while(0)
#define DB4_SetPushPull()        do { ODCONDbits.ODCD3 = 0; } while(0)
#define DB4_SetOpenDrain()       do { ODCONDbits.ODCD3 = 1; } while(0)
#define DB4_SetAnalogMode()      do { ANSELDbits.ANSD3 = 1; } while(0)
#define DB4_SetDigitalMode()     do { ANSELDbits.ANSD3 = 0; } while(0)

// get/set DB5 aliases
#define DB5_TRIS                 TRISDbits.TRISD4
#define DB5_LAT                  LATDbits.LATD4
#define DB5_PORT                 PORTDbits.RD4
#define DB5_WPU                  WPUDbits.WPUD4
#define DB5_OD                   ODCONDbits.ODCD4
#define DB5_ANS                  ANSELDbits.ANSD4
#define DB5_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define DB5_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define DB5_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define DB5_GetValue()           PORTDbits.RD4
#define DB5_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define DB5_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define DB5_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define DB5_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define DB5_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define DB5_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define DB5_SetAnalogMode()      do { ANSELDbits.ANSD4 = 1; } while(0)
#define DB5_SetDigitalMode()     do { ANSELDbits.ANSD4 = 0; } while(0)

// get/set DB6 aliases
#define DB6_TRIS                 TRISDbits.TRISD5
#define DB6_LAT                  LATDbits.LATD5
#define DB6_PORT                 PORTDbits.RD5
#define DB6_WPU                  WPUDbits.WPUD5
#define DB6_OD                   ODCONDbits.ODCD5
#define DB6_ANS                  ANSELDbits.ANSD5
#define DB6_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define DB6_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define DB6_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define DB6_GetValue()           PORTDbits.RD5
#define DB6_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define DB6_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define DB6_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define DB6_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define DB6_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define DB6_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define DB6_SetAnalogMode()      do { ANSELDbits.ANSD5 = 1; } while(0)
#define DB6_SetDigitalMode()     do { ANSELDbits.ANSD5 = 0; } while(0)

// get/set DB7 aliases
#define DB7_TRIS                 TRISDbits.TRISD6
#define DB7_LAT                  LATDbits.LATD6
#define DB7_PORT                 PORTDbits.RD6
#define DB7_WPU                  WPUDbits.WPUD6
#define DB7_OD                   ODCONDbits.ODCD6
#define DB7_ANS                  ANSELDbits.ANSD6
#define DB7_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define DB7_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define DB7_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define DB7_GetValue()           PORTDbits.RD6
#define DB7_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define DB7_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define DB7_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define DB7_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define DB7_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define DB7_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define DB7_SetAnalogMode()      do { ANSELDbits.ANSD6 = 1; } while(0)
#define DB7_SetDigitalMode()     do { ANSELDbits.ANSD6 = 0; } while(0)

// get/set DB8 aliases
#define DB8_TRIS                 TRISDbits.TRISD7
#define DB8_LAT                  LATDbits.LATD7
#define DB8_PORT                 PORTDbits.RD7
#define DB8_WPU                  WPUDbits.WPUD7
#define DB8_OD                   ODCONDbits.ODCD7
#define DB8_ANS                  ANSELDbits.ANSD7
#define DB8_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define DB8_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define DB8_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define DB8_GetValue()           PORTDbits.RD7
#define DB8_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define DB8_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define DB8_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define DB8_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define DB8_SetPushPull()        do { ODCONDbits.ODCD7 = 0; } while(0)
#define DB8_SetOpenDrain()       do { ODCONDbits.ODCD7 = 1; } while(0)
#define DB8_SetAnalogMode()      do { ANSELDbits.ANSD7 = 1; } while(0)
#define DB8_SetDigitalMode()     do { ANSELDbits.ANSD7 = 0; } while(0)

// get/set WIFI_RST aliases
#define WIFI_RST_TRIS                 TRISEbits.TRISE0
#define WIFI_RST_LAT                  LATEbits.LATE0
#define WIFI_RST_PORT                 PORTEbits.RE0
#define WIFI_RST_WPU                  WPUEbits.WPUE0
#define WIFI_RST_OD                   ODCONEbits.ODCE0
#define WIFI_RST_ANS                  ANSELEbits.ANSE0
#define WIFI_RST_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define WIFI_RST_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define WIFI_RST_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define WIFI_RST_GetValue()           PORTEbits.RE0
#define WIFI_RST_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define WIFI_RST_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define WIFI_RST_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define WIFI_RST_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define WIFI_RST_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define WIFI_RST_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define WIFI_RST_SetAnalogMode()      do { ANSELEbits.ANSE0 = 1; } while(0)
#define WIFI_RST_SetDigitalMode()     do { ANSELEbits.ANSE0 = 0; } while(0)

// get/set LCD_CS aliases
#define LCD_CS_TRIS                 TRISEbits.TRISE1
#define LCD_CS_LAT                  LATEbits.LATE1
#define LCD_CS_PORT                 PORTEbits.RE1
#define LCD_CS_WPU                  WPUEbits.WPUE1
#define LCD_CS_OD                   ODCONEbits.ODCE1
#define LCD_CS_ANS                  ANSELEbits.ANSE1
#define LCD_CS_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define LCD_CS_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define LCD_CS_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define LCD_CS_GetValue()           PORTEbits.RE1
#define LCD_CS_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define LCD_CS_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define LCD_CS_SetPullup()          do { WPUEbits.WPUE1 = 1; } while(0)
#define LCD_CS_ResetPullup()        do { WPUEbits.WPUE1 = 0; } while(0)
#define LCD_CS_SetPushPull()        do { ODCONEbits.ODCE1 = 0; } while(0)
#define LCD_CS_SetOpenDrain()       do { ODCONEbits.ODCE1 = 1; } while(0)
#define LCD_CS_SetAnalogMode()      do { ANSELEbits.ANSE1 = 1; } while(0)
#define LCD_CS_SetDigitalMode()     do { ANSELEbits.ANSE1 = 0; } while(0)

// get/set LED aliases
#define LED_TRIS                 TRISEbits.TRISE3
#define LED_LAT                  LATEbits.LATE3
#define LED_PORT                 PORTEbits.RE3
#define LED_WPU                  WPUEbits.WPUE3
#define LED_OD                   ODCONEbits.ODCE3
#define LED_ANS                  ANSELEbits.ANSE3
#define LED_SetHigh()            do { LATEbits.LATE3 = 1; } while(0)
#define LED_SetLow()             do { LATEbits.LATE3 = 0; } while(0)
#define LED_Toggle()             do { LATEbits.LATE3 = ~LATEbits.LATE3; } while(0)
#define LED_GetValue()           PORTEbits.RE3
#define LED_SetDigitalInput()    do { TRISEbits.TRISE3 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISEbits.TRISE3 = 0; } while(0)
#define LED_SetPullup()          do { WPUEbits.WPUE3 = 1; } while(0)
#define LED_ResetPullup()        do { WPUEbits.WPUE3 = 0; } while(0)
#define LED_SetPushPull()        do { ODCONEbits.ODCE3 = 0; } while(0)
#define LED_SetOpenDrain()       do { ODCONEbits.ODCE3 = 1; } while(0)
#define LED_SetAnalogMode()      do { ANSELEbits.ANSE3 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELEbits.ANSE3 = 0; } while(0)

// get/set LCD_RS aliases
#define LCD_RS_TRIS                 TRISEbits.TRISE4
#define LCD_RS_LAT                  LATEbits.LATE4
#define LCD_RS_PORT                 PORTEbits.RE4
#define LCD_RS_WPU                  WPUEbits.WPUE4
#define LCD_RS_OD                   ODCONEbits.ODCE4
#define LCD_RS_ANS                  ANSELEbits.ANSE4
#define LCD_RS_SetHigh()            do { LATEbits.LATE4 = 1; } while(0)
#define LCD_RS_SetLow()             do { LATEbits.LATE4 = 0; } while(0)
#define LCD_RS_Toggle()             do { LATEbits.LATE4 = ~LATEbits.LATE4; } while(0)
#define LCD_RS_GetValue()           PORTEbits.RE4
#define LCD_RS_SetDigitalInput()    do { TRISEbits.TRISE4 = 1; } while(0)
#define LCD_RS_SetDigitalOutput()   do { TRISEbits.TRISE4 = 0; } while(0)
#define LCD_RS_SetPullup()          do { WPUEbits.WPUE4 = 1; } while(0)
#define LCD_RS_ResetPullup()        do { WPUEbits.WPUE4 = 0; } while(0)
#define LCD_RS_SetPushPull()        do { ODCONEbits.ODCE4 = 0; } while(0)
#define LCD_RS_SetOpenDrain()       do { ODCONEbits.ODCE4 = 1; } while(0)
#define LCD_RS_SetAnalogMode()      do { ANSELEbits.ANSE4 = 1; } while(0)
#define LCD_RS_SetDigitalMode()     do { ANSELEbits.ANSE4 = 0; } while(0)

// get/set LCD_WR aliases
#define LCD_WR_TRIS                 TRISEbits.TRISE5
#define LCD_WR_LAT                  LATEbits.LATE5
#define LCD_WR_PORT                 PORTEbits.RE5
#define LCD_WR_WPU                  WPUEbits.WPUE5
#define LCD_WR_OD                   ODCONEbits.ODCE5
#define LCD_WR_ANS                  ANSELEbits.ANSE5
#define LCD_WR_SetHigh()            do { LATEbits.LATE5 = 1; } while(0)
#define LCD_WR_SetLow()             do { LATEbits.LATE5 = 0; } while(0)
#define LCD_WR_Toggle()             do { LATEbits.LATE5 = ~LATEbits.LATE5; } while(0)
#define LCD_WR_GetValue()           PORTEbits.RE5
#define LCD_WR_SetDigitalInput()    do { TRISEbits.TRISE5 = 1; } while(0)
#define LCD_WR_SetDigitalOutput()   do { TRISEbits.TRISE5 = 0; } while(0)
#define LCD_WR_SetPullup()          do { WPUEbits.WPUE5 = 1; } while(0)
#define LCD_WR_ResetPullup()        do { WPUEbits.WPUE5 = 0; } while(0)
#define LCD_WR_SetPushPull()        do { ODCONEbits.ODCE5 = 0; } while(0)
#define LCD_WR_SetOpenDrain()       do { ODCONEbits.ODCE5 = 1; } while(0)
#define LCD_WR_SetAnalogMode()      do { ANSELEbits.ANSE5 = 1; } while(0)
#define LCD_WR_SetDigitalMode()     do { ANSELEbits.ANSE5 = 0; } while(0)

// get/set DB10 aliases
#define DB10_TRIS                 TRISFbits.TRISF0
#define DB10_LAT                  LATFbits.LATF0
#define DB10_PORT                 PORTFbits.RF0
#define DB10_WPU                  WPUFbits.WPUF0
#define DB10_OD                   ODCONFbits.ODCF0
#define DB10_ANS                  ANSELFbits.ANSF0
#define DB10_SetHigh()            do { LATFbits.LATF0 = 1; } while(0)
#define DB10_SetLow()             do { LATFbits.LATF0 = 0; } while(0)
#define DB10_Toggle()             do { LATFbits.LATF0 = ~LATFbits.LATF0; } while(0)
#define DB10_GetValue()           PORTFbits.RF0
#define DB10_SetDigitalInput()    do { TRISFbits.TRISF0 = 1; } while(0)
#define DB10_SetDigitalOutput()   do { TRISFbits.TRISF0 = 0; } while(0)
#define DB10_SetPullup()          do { WPUFbits.WPUF0 = 1; } while(0)
#define DB10_ResetPullup()        do { WPUFbits.WPUF0 = 0; } while(0)
#define DB10_SetPushPull()        do { ODCONFbits.ODCF0 = 0; } while(0)
#define DB10_SetOpenDrain()       do { ODCONFbits.ODCF0 = 1; } while(0)
#define DB10_SetAnalogMode()      do { ANSELFbits.ANSF0 = 1; } while(0)
#define DB10_SetDigitalMode()     do { ANSELFbits.ANSF0 = 0; } while(0)

// get/set DB11 aliases
#define DB11_TRIS                 TRISFbits.TRISF1
#define DB11_LAT                  LATFbits.LATF1
#define DB11_PORT                 PORTFbits.RF1
#define DB11_WPU                  WPUFbits.WPUF1
#define DB11_OD                   ODCONFbits.ODCF1
#define DB11_ANS                  ANSELFbits.ANSF1
#define DB11_SetHigh()            do { LATFbits.LATF1 = 1; } while(0)
#define DB11_SetLow()             do { LATFbits.LATF1 = 0; } while(0)
#define DB11_Toggle()             do { LATFbits.LATF1 = ~LATFbits.LATF1; } while(0)
#define DB11_GetValue()           PORTFbits.RF1
#define DB11_SetDigitalInput()    do { TRISFbits.TRISF1 = 1; } while(0)
#define DB11_SetDigitalOutput()   do { TRISFbits.TRISF1 = 0; } while(0)
#define DB11_SetPullup()          do { WPUFbits.WPUF1 = 1; } while(0)
#define DB11_ResetPullup()        do { WPUFbits.WPUF1 = 0; } while(0)
#define DB11_SetPushPull()        do { ODCONFbits.ODCF1 = 0; } while(0)
#define DB11_SetOpenDrain()       do { ODCONFbits.ODCF1 = 1; } while(0)
#define DB11_SetAnalogMode()      do { ANSELFbits.ANSF1 = 1; } while(0)
#define DB11_SetDigitalMode()     do { ANSELFbits.ANSF1 = 0; } while(0)

// get/set DB12 aliases
#define DB12_TRIS                 TRISFbits.TRISF2
#define DB12_LAT                  LATFbits.LATF2
#define DB12_PORT                 PORTFbits.RF2
#define DB12_WPU                  WPUFbits.WPUF2
#define DB12_OD                   ODCONFbits.ODCF2
#define DB12_ANS                  ANSELFbits.ANSF2
#define DB12_SetHigh()            do { LATFbits.LATF2 = 1; } while(0)
#define DB12_SetLow()             do { LATFbits.LATF2 = 0; } while(0)
#define DB12_Toggle()             do { LATFbits.LATF2 = ~LATFbits.LATF2; } while(0)
#define DB12_GetValue()           PORTFbits.RF2
#define DB12_SetDigitalInput()    do { TRISFbits.TRISF2 = 1; } while(0)
#define DB12_SetDigitalOutput()   do { TRISFbits.TRISF2 = 0; } while(0)
#define DB12_SetPullup()          do { WPUFbits.WPUF2 = 1; } while(0)
#define DB12_ResetPullup()        do { WPUFbits.WPUF2 = 0; } while(0)
#define DB12_SetPushPull()        do { ODCONFbits.ODCF2 = 0; } while(0)
#define DB12_SetOpenDrain()       do { ODCONFbits.ODCF2 = 1; } while(0)
#define DB12_SetAnalogMode()      do { ANSELFbits.ANSF2 = 1; } while(0)
#define DB12_SetDigitalMode()     do { ANSELFbits.ANSF2 = 0; } while(0)

// get/set DB13 aliases
#define DB13_TRIS                 TRISFbits.TRISF3
#define DB13_LAT                  LATFbits.LATF3
#define DB13_PORT                 PORTFbits.RF3
#define DB13_WPU                  WPUFbits.WPUF3
#define DB13_OD                   ODCONFbits.ODCF3
#define DB13_ANS                  ANSELFbits.ANSF3
#define DB13_SetHigh()            do { LATFbits.LATF3 = 1; } while(0)
#define DB13_SetLow()             do { LATFbits.LATF3 = 0; } while(0)
#define DB13_Toggle()             do { LATFbits.LATF3 = ~LATFbits.LATF3; } while(0)
#define DB13_GetValue()           PORTFbits.RF3
#define DB13_SetDigitalInput()    do { TRISFbits.TRISF3 = 1; } while(0)
#define DB13_SetDigitalOutput()   do { TRISFbits.TRISF3 = 0; } while(0)
#define DB13_SetPullup()          do { WPUFbits.WPUF3 = 1; } while(0)
#define DB13_ResetPullup()        do { WPUFbits.WPUF3 = 0; } while(0)
#define DB13_SetPushPull()        do { ODCONFbits.ODCF3 = 0; } while(0)
#define DB13_SetOpenDrain()       do { ODCONFbits.ODCF3 = 1; } while(0)
#define DB13_SetAnalogMode()      do { ANSELFbits.ANSF3 = 1; } while(0)
#define DB13_SetDigitalMode()     do { ANSELFbits.ANSF3 = 0; } while(0)

// get/set DB14 aliases
#define DB14_TRIS                 TRISFbits.TRISF4
#define DB14_LAT                  LATFbits.LATF4
#define DB14_PORT                 PORTFbits.RF4
#define DB14_WPU                  WPUFbits.WPUF4
#define DB14_OD                   ODCONFbits.ODCF4
#define DB14_ANS                  ANSELFbits.ANSF4
#define DB14_SetHigh()            do { LATFbits.LATF4 = 1; } while(0)
#define DB14_SetLow()             do { LATFbits.LATF4 = 0; } while(0)
#define DB14_Toggle()             do { LATFbits.LATF4 = ~LATFbits.LATF4; } while(0)
#define DB14_GetValue()           PORTFbits.RF4
#define DB14_SetDigitalInput()    do { TRISFbits.TRISF4 = 1; } while(0)
#define DB14_SetDigitalOutput()   do { TRISFbits.TRISF4 = 0; } while(0)
#define DB14_SetPullup()          do { WPUFbits.WPUF4 = 1; } while(0)
#define DB14_ResetPullup()        do { WPUFbits.WPUF4 = 0; } while(0)
#define DB14_SetPushPull()        do { ODCONFbits.ODCF4 = 0; } while(0)
#define DB14_SetOpenDrain()       do { ODCONFbits.ODCF4 = 1; } while(0)
#define DB14_SetAnalogMode()      do { ANSELFbits.ANSF4 = 1; } while(0)
#define DB14_SetDigitalMode()     do { ANSELFbits.ANSF4 = 0; } while(0)

// get/set DB15 aliases
#define DB15_TRIS                 TRISFbits.TRISF5
#define DB15_LAT                  LATFbits.LATF5
#define DB15_PORT                 PORTFbits.RF5
#define DB15_WPU                  WPUFbits.WPUF5
#define DB15_OD                   ODCONFbits.ODCF5
#define DB15_ANS                  ANSELFbits.ANSF5
#define DB15_SetHigh()            do { LATFbits.LATF5 = 1; } while(0)
#define DB15_SetLow()             do { LATFbits.LATF5 = 0; } while(0)
#define DB15_Toggle()             do { LATFbits.LATF5 = ~LATFbits.LATF5; } while(0)
#define DB15_GetValue()           PORTFbits.RF5
#define DB15_SetDigitalInput()    do { TRISFbits.TRISF5 = 1; } while(0)
#define DB15_SetDigitalOutput()   do { TRISFbits.TRISF5 = 0; } while(0)
#define DB15_SetPullup()          do { WPUFbits.WPUF5 = 1; } while(0)
#define DB15_ResetPullup()        do { WPUFbits.WPUF5 = 0; } while(0)
#define DB15_SetPushPull()        do { ODCONFbits.ODCF5 = 0; } while(0)
#define DB15_SetOpenDrain()       do { ODCONFbits.ODCF5 = 1; } while(0)
#define DB15_SetAnalogMode()      do { ANSELFbits.ANSF5 = 1; } while(0)
#define DB15_SetDigitalMode()     do { ANSELFbits.ANSF5 = 0; } while(0)

// get/set DB16 aliases
#define DB16_TRIS                 TRISFbits.TRISF6
#define DB16_LAT                  LATFbits.LATF6
#define DB16_PORT                 PORTFbits.RF6
#define DB16_WPU                  WPUFbits.WPUF6
#define DB16_OD                   ODCONFbits.ODCF6
#define DB16_ANS                  ANSELFbits.ANSF6
#define DB16_SetHigh()            do { LATFbits.LATF6 = 1; } while(0)
#define DB16_SetLow()             do { LATFbits.LATF6 = 0; } while(0)
#define DB16_Toggle()             do { LATFbits.LATF6 = ~LATFbits.LATF6; } while(0)
#define DB16_GetValue()           PORTFbits.RF6
#define DB16_SetDigitalInput()    do { TRISFbits.TRISF6 = 1; } while(0)
#define DB16_SetDigitalOutput()   do { TRISFbits.TRISF6 = 0; } while(0)
#define DB16_SetPullup()          do { WPUFbits.WPUF6 = 1; } while(0)
#define DB16_ResetPullup()        do { WPUFbits.WPUF6 = 0; } while(0)
#define DB16_SetPushPull()        do { ODCONFbits.ODCF6 = 0; } while(0)
#define DB16_SetOpenDrain()       do { ODCONFbits.ODCF6 = 1; } while(0)
#define DB16_SetAnalogMode()      do { ANSELFbits.ANSF6 = 1; } while(0)
#define DB16_SetDigitalMode()     do { ANSELFbits.ANSF6 = 0; } while(0)

// get/set DB17 aliases
#define DB17_TRIS                 TRISFbits.TRISF7
#define DB17_LAT                  LATFbits.LATF7
#define DB17_PORT                 PORTFbits.RF7
#define DB17_WPU                  WPUFbits.WPUF7
#define DB17_OD                   ODCONFbits.ODCF7
#define DB17_ANS                  ANSELFbits.ANSF7
#define DB17_SetHigh()            do { LATFbits.LATF7 = 1; } while(0)
#define DB17_SetLow()             do { LATFbits.LATF7 = 0; } while(0)
#define DB17_Toggle()             do { LATFbits.LATF7 = ~LATFbits.LATF7; } while(0)
#define DB17_GetValue()           PORTFbits.RF7
#define DB17_SetDigitalInput()    do { TRISFbits.TRISF7 = 1; } while(0)
#define DB17_SetDigitalOutput()   do { TRISFbits.TRISF7 = 0; } while(0)
#define DB17_SetPullup()          do { WPUFbits.WPUF7 = 1; } while(0)
#define DB17_ResetPullup()        do { WPUFbits.WPUF7 = 0; } while(0)
#define DB17_SetPushPull()        do { ODCONFbits.ODCF7 = 0; } while(0)
#define DB17_SetOpenDrain()       do { ODCONFbits.ODCF7 = 1; } while(0)
#define DB17_SetAnalogMode()      do { ANSELFbits.ANSF7 = 1; } while(0)
#define DB17_SetDigitalMode()     do { ANSELFbits.ANSF7 = 0; } while(0)

// get/set RG1 procedures
#define RG1_SetHigh()            do { LATGbits.LATG1 = 1; } while(0)
#define RG1_SetLow()             do { LATGbits.LATG1 = 0; } while(0)
#define RG1_Toggle()             do { LATGbits.LATG1 = ~LATGbits.LATG1; } while(0)
#define RG1_GetValue()              PORTGbits.RG1
#define RG1_SetDigitalInput()    do { TRISGbits.TRISG1 = 1; } while(0)
#define RG1_SetDigitalOutput()   do { TRISGbits.TRISG1 = 0; } while(0)
#define RG1_SetPullup()             do { WPUGbits.WPUG1 = 1; } while(0)
#define RG1_ResetPullup()           do { WPUGbits.WPUG1 = 0; } while(0)
#define RG1_SetAnalogMode()         do { ANSELGbits.ANSG1 = 1; } while(0)
#define RG1_SetDigitalMode()        do { ANSELGbits.ANSG1 = 0; } while(0)

// get/set RG2 procedures
#define RG2_SetHigh()            do { LATGbits.LATG2 = 1; } while(0)
#define RG2_SetLow()             do { LATGbits.LATG2 = 0; } while(0)
#define RG2_Toggle()             do { LATGbits.LATG2 = ~LATGbits.LATG2; } while(0)
#define RG2_GetValue()              PORTGbits.RG2
#define RG2_SetDigitalInput()    do { TRISGbits.TRISG2 = 1; } while(0)
#define RG2_SetDigitalOutput()   do { TRISGbits.TRISG2 = 0; } while(0)
#define RG2_SetPullup()             do { WPUGbits.WPUG2 = 1; } while(0)
#define RG2_ResetPullup()           do { WPUGbits.WPUG2 = 0; } while(0)
#define RG2_SetAnalogMode()         do { ANSELGbits.ANSG2 = 1; } while(0)
#define RG2_SetDigitalMode()        do { ANSELGbits.ANSG2 = 0; } while(0)

// get/set LCD_RD aliases
#define LCD_RD_TRIS                 TRISHbits.TRISH2
#define LCD_RD_LAT                  LATHbits.LATH2
#define LCD_RD_PORT                 PORTHbits.RH2
#define LCD_RD_WPU                  WPUHbits.WPUH2
#define LCD_RD_OD                   ODCONHbits.ODCH2
#define LCD_RD_SetHigh()            do { LATHbits.LATH2 = 1; } while(0)
#define LCD_RD_SetLow()             do { LATHbits.LATH2 = 0; } while(0)
#define LCD_RD_Toggle()             do { LATHbits.LATH2 = ~LATHbits.LATH2; } while(0)
#define LCD_RD_GetValue()           PORTHbits.RH2
#define LCD_RD_SetDigitalInput()    do { TRISHbits.TRISH2 = 1; } while(0)
#define LCD_RD_SetDigitalOutput()   do { TRISHbits.TRISH2 = 0; } while(0)
#define LCD_RD_SetPullup()          do { WPUHbits.WPUH2 = 1; } while(0)
#define LCD_RD_ResetPullup()        do { WPUHbits.WPUH2 = 0; } while(0)
#define LCD_RD_SetPushPull()        do { ODCONHbits.ODCH2 = 0; } while(0)
#define LCD_RD_SetOpenDrain()       do { ODCONHbits.ODCH2 = 1; } while(0)

// get/set LCD_RST aliases
#define LCD_RST_TRIS                 TRISHbits.TRISH3
#define LCD_RST_LAT                  LATHbits.LATH3
#define LCD_RST_PORT                 PORTHbits.RH3
#define LCD_RST_WPU                  WPUHbits.WPUH3
#define LCD_RST_OD                   ODCONHbits.ODCH3
#define LCD_RST_SetHigh()            do { LATHbits.LATH3 = 1; } while(0)
#define LCD_RST_SetLow()             do { LATHbits.LATH3 = 0; } while(0)
#define LCD_RST_Toggle()             do { LATHbits.LATH3 = ~LATHbits.LATH3; } while(0)
#define LCD_RST_GetValue()           PORTHbits.RH3
#define LCD_RST_SetDigitalInput()    do { TRISHbits.TRISH3 = 1; } while(0)
#define LCD_RST_SetDigitalOutput()   do { TRISHbits.TRISH3 = 0; } while(0)
#define LCD_RST_SetPullup()          do { WPUHbits.WPUH3 = 1; } while(0)
#define LCD_RST_ResetPullup()        do { WPUHbits.WPUH3 = 0; } while(0)
#define LCD_RST_SetPushPull()        do { ODCONHbits.ODCH3 = 0; } while(0)
#define LCD_RST_SetOpenDrain()       do { ODCONHbits.ODCH3 = 1; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/