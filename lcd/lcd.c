/*******************************************************************************************	 
* 文件名称：lcd.c
* 功能描述：2.8寸TFT触摸LCD液晶驱动
* 试验平台：STM32F103RCT6实验板
* 作 者：Layout
* 日 期：2020-2-18
* 版 本：V1.0
* 修 改：无
* 备 注：无
**************************************************************************************/
#include "lcd.h"
#include "stdlib.h"
#include "FONT.H"
#include "../mcc_generated_files/device_config.h"
//#include "../mcc_generated_files/eusart1.h"



 
/*****************LCD的画笔颜色和背景色**********************/ 
u16 POINT_COLOR=0x0000;				//画笔颜色
u16 BACK_COLOR=0xFFFF;  			//背景色 

/****************管理LCD重要参数，默认为竖屏*****************/
_lcd_dev lcddev;
	 					    

/*******************************************************************************
 * 函数名  ：void LCD_WR_REG(u16 data)
 * 描  述  ：写寄存器函数
 * 输  入  ：data:寄存器值
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_WR_REG(u16 data)
{ 
	LCD_RS_CLR;					//写地址拉低  
 	LCD_CS_CLR; 				//片选端口拉低
	DATAOUT(data); 			//数据输出
	LCD_WR_CLR; 				//写数据拉低	
	LCD_WR_SET; 				//写数据拉高
 	LCD_CS_SET;   			//释放片选端口
}


/*******************************************************************************
 * 函数名  ：void LCD_WR_DATAX(u16 data)
 * 描  述  ：写数据函数
 * 输  入  ：data:寄存器值
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_WR_DATAX(u16 data)
{
	LCD_RS_SET;					//写地址拉高
	LCD_CS_CLR;					//片选端口拉低
	DATAOUT(data);			//数据输出
	LCD_WR_CLR;					//写数据拉低
	LCD_WR_SET;					//写数据拉高
	LCD_CS_SET;					//释放片选端口
}

/*******************************************************************************
 * 函数名  ：u16 LCD_RD_DATA(void)
 * 描  述  ：读LCD数据
 * 输  入  ：无
 * 输  出  ：无
 * 返回值  ：t
 ******************************************************************************/
u16 LCD_RD_DATA(void)
{										   
	u16 t;
    TRISD = 0xff;       // 	GPIOB->CRL=0X88888888; //PB0-7  上拉输入   //	GPIOB->CRH=0X88888888; //PB8-15 上拉输入
    TRISF = 0xff;       //	GPIOB->ODR=0X0000;     //全部输出0

	LCD_RS_SET;												//写地址拉高
	LCD_CS_CLR;												//片选端口拉低	
	LCD_RD_CLR;												//读取数据(读寄存器时,并不需要读2次)
	if(lcddev.id==0X8989)__delay_us(2);	//FOR 8989,延时2us					   
	t=DATAIN;  
	LCD_RD_SET;												//读数据
	LCD_CS_SET; 											//释放片选端口

	TRISD = 0x00;
    TRISF = 0x00;   //    GPIOB->CRL=0X33333333; //PB0-7  上拉输出    GPIOB->CRH=0X33333333; //PB8-15 上拉输出
	
    LATD = 0xff ;     //            GPIOB->ODR=0XFFFF;    //全部输出高
    LATF = 0xff ;
	return t;  												//读取的数据
}


/*******************************************************************************
 * 函数名  ：void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
 * 描  述  ：写寄存器
 * 输  入  ：LCD_Reg:寄存器编号，LCD_RegValue:要写入的值
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);  		 //写入要写的寄存器号
	LCD_WR_DATA(LCD_RegValue);	    		 
}   


/*******************************************************************************
 * 函数名  ：u16 LCD_ReadReg(u16 LCD_Reg)
 * 描  述  ：读寄存器
 * 输  入  ：LCD_Reg:寄存器编号
 * 输  出  ：无
 * 返回值  ：LCD_RD_DATA();
 ******************************************************************************/
u16 LCD_ReadReg(u16 LCD_Reg)
{										   
 	LCD_WR_REG(LCD_Reg);  //写入要读的寄存器号  
	return LCD_RD_DATA(); 
} 

/*******************************************************************************
 * 函数名  ：void LCD_WriteRAM_Prepare(void)
 * 描  述  ：开始写GRAM
 * 输  入  ：无
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
} 


/*******************************************************************************
 * 函数名  ：void LCD_WriteRAM(u16 RGB_Code)
 * 描  述  ：LCD写GRAM
 * 输  入  ：u16 RGB_Cod
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_WriteRAM(u16 RGB_Code)
{							    
	LCD_WR_DATA(RGB_Code);			//写十六位GRAM
}


/*******************************************************************************
 * 函数名  ：u16 LCD_BGR2RGB(u16 c)
 * 描  述  ：从ILI93xx读出的数据为GBR格式，而我们写入的时候为RGB格式，通过该函数转换。
 * 输  入  ：c:GBR格式的颜色值
 * 输  出  ：无
 * 返回值  ：RGB格式的颜色值
 ******************************************************************************/
u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
}	


/*******************************************************************************
 * 函数名  ：void opt_delay(u8 l)
 * 描  述  ：当mdk -O1时间优化时需要设置,延时l
 * 输  入  ：u8 l
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void opt_delay(u8 l)
{
	while(l--);
}


/*******************************************************************************
 * 函数名  ：u16 LCD_ReadPoint(u16 x,u16 y)
 * 描  述  ：读取个某点的颜色值
 * 输  入  ：x,y:坐标
 * 输  出  ：无
 * 返回值  ：此点的颜色
 ******************************************************************************/
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r,g,b;
	if(x>=lcddev.width||y>=lcddev.height)return 0;	//超过了范围,直接返回		   
	LCD_SetCursor(x,y);
	if(lcddev.id==0X9341||lcddev.id==0X6804||lcddev.id==0X5310||lcddev.id==0X1963)LCD_WR_REG(0X2E);//9341/6804/3510/1963 发送读GRAM指令
	else if(lcddev.id==0X5510)LCD_WR_REG(0X2E00);		//5510 发送读GRAM指令
	else LCD_WR_REG(0X22);      		 								//其他IC发送读GRAM指令
    TRISD = 0xff;       // 	GPIOB->CRL=0X88888888; //PB0-7  上拉输入   //	GPIOB->CRH=0X88888888; //PB8-15 上拉输入
    TRISF = 0xff;       //	GPIOB->ODR=0X0000;     //全部输出0

	LCD_RS_SET;																			//数据/命令拉高
	LCD_CS_CLR;	    																//片选拉低
		
	LCD_RD_CLR;		   																//读取数据(读GRAM时,第一次为假读)
	opt_delay(2);																		//延时		
 	r=DATAIN;  																			//实际坐标颜色 
	LCD_RD_SET;																			//读数据拉高	
	if(lcddev.id==0X1963)
	{
		LCD_CS_SET;
        TRISD = 0x00;
        TRISF = 0x00;   //    GPIOB->CRL=0X33333333; //PB0-7  上拉输出    GPIOB->CRH=0X33333333; //PB8-15 上拉输出
	
        LATD = 0xff ;     //            GPIOB->ODR=0XFFFF;    //全部输出高
        LATF = 0xff ;  												//全部输出高  
		return r;																			//1963直接读就可以 
 	}

	LCD_RD_CLR;					   													//读数据后拉低
	opt_delay(2);																		//延时					   
 	r=DATAIN;  																			//实际坐标颜色
	LCD_RD_SET;																			//读数据拉高
 	if(lcddev.id==0X9341||lcddev.id==0X5310||lcddev.id==0X5510)														//9341要分2次读出
	{	 	
		LCD_RD_CLR;					   												//读数据后拉低
		opt_delay(2);																	//延时			   
		b=DATAIN;																			//读取颜色值 
	 	LCD_RD_SET;																		//读数据拉高
		g=r&0XFF;																			//对于9341,第一次读取的是RG的值,R在前,G在后,各占8位
		g<<=8;
	}
	else if(lcddev.id==0X6804)
	{
		LCD_RD_CLR;					   
	 	LCD_RD_SET;
		r=DATAIN;																			//6804第二次读取的才是真实值 
	}	 
	LCD_CS_SET;																			//片选拉高
	TRISD = 0x00;
    TRISF = 0x00;   //    GPIOB->CRL=0X33333333; //PB0-7  上拉输出    GPIOB->CRH=0X33333333; //PB8-15 上拉输出
	
    LATD = 0xff ;     //            GPIOB->ODR=0XFFFF;    //全部输出高
    LATF = 0xff ; 													//全部输出高  
	if(lcddev.id==0X9325||lcddev.id==0X4535||lcddev.id==0X4531||lcddev.id==0X8989||lcddev.id==0XB505)return r;	//这几种IC直接返回颜色值
	else if(lcddev.id==0X9341||lcddev.id==0X5310||lcddev.id==0X5510)return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));//ILI9341/NT35310/NT35510需要公式转换一下
	else return LCD_BGR2RGB(r);											//其他IC
}		 

/*******************************************************************************
 * 函数名  ：void LCD_DisplayOn(void)
 * 描  述  ：LCD开启显示
 * 输  入  ：无
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_DisplayOn(void)
{					   
	if(lcddev.id==0X9341||lcddev.id==0X6804||lcddev.id==0X5310||lcddev.id==0X1963)LCD_WR_REG(0X29);	//开启显示
	else if(lcddev.id==0X5510)LCD_WR_REG(0X2900);																										//开启显示
	else LCD_WriteReg(0X07,0x0173); 				 																												//开启显示
}	 

/*******************************************************************************
 * 函数名  ：void LCD_DisplayOff(void)
 * 描  述  ：LCD关闭显示
 * 输  入  ：无
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_DisplayOff(void)
{	   
	if(lcddev.id==0X9341||lcddev.id==0X6804||lcddev.id==0X5310||lcddev.id==0X1963)LCD_WR_REG(0X28);	//关闭显示
	else if(lcddev.id==0X5510)LCD_WR_REG(0X2800);																										//关闭显示
	else LCD_WriteReg(0X07,0x0);																																		//关闭显示 
}   
   

/*******************************************************************************
 * 函数名  ：void LCD_SetCursor(u16 Xpos, u16 Ypos)
 * 描  述  ：设置光标位置
 * 输  入  ：Xpos:横坐标pos:纵坐标
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	 
 	if(lcddev.id==0X9341||lcddev.id==0X5310)
	{		    
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(Xpos>>8);LCD_WR_DATA(Xpos&0XFF); 			 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(Ypos>>8);LCD_WR_DATA(Ypos&0XFF); 		
	}else if(lcddev.id==0X6804)
	{
		if(lcddev.dir==1)Xpos=lcddev.width-1-Xpos;		//横屏时处理
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(Xpos>>8);LCD_WR_DATA(Xpos&0XFF); 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(Ypos>>8);LCD_WR_DATA(Ypos&0XFF); 
	}else if(lcddev.id==0X1963)
	{  			 		
		if(lcddev.dir==0)															//x坐标需要变换
		{
			Xpos=lcddev.width-1-Xpos;
			LCD_WR_REG(lcddev.setxcmd); 
			LCD_WR_DATA(0);LCD_WR_DATA(0); 		
			LCD_WR_DATA(Xpos>>8);LCD_WR_DATA(Xpos&0XFF);		 	 
		}else
		{
			LCD_WR_REG(lcddev.setxcmd); 
			LCD_WR_DATA(Xpos>>8);LCD_WR_DATA(Xpos&0XFF); 		
			LCD_WR_DATA((lcddev.width-1)>>8);LCD_WR_DATA((lcddev.width-1)&0XFF);		 	 			
		}	
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(Ypos>>8);LCD_WR_DATA(Ypos&0XFF); 		
		LCD_WR_DATA((lcddev.height-1)>>8);LCD_WR_DATA((lcddev.height-1)&0XFF); 			 		
		
	}else if(lcddev.id==0X5510)
	{
		LCD_WR_REG(lcddev.setxcmd);LCD_WR_DATA(Xpos>>8); 		
		LCD_WR_REG(lcddev.setxcmd+1);LCD_WR_DATA(Xpos&0XFF);			 
		LCD_WR_REG(lcddev.setycmd);LCD_WR_DATA(Ypos>>8);  		
		LCD_WR_REG(lcddev.setycmd+1);LCD_WR_DATA(Ypos&0XFF);			
	}else
	{
		if(lcddev.dir==1)Xpos=lcddev.width-1-Xpos;				//横屏其实就是调转x,y坐标
		LCD_WriteReg(lcddev.setxcmd, Xpos);
		LCD_WriteReg(lcddev.setycmd, Ypos);
	}	 
} 		 

/*******************************************************************************
 * 函数名  ：void LCD_Scan_Dir(u8 dir)
 * 描  述  ：设置LCD的自动扫描方向
 * 输  入  ：dir:0~7,代表8个方向(具体定义见lcd.h)
 * 输  出  ：无
 * 返回值  ：无
 * 注  意  ：其他函数可能会受到此函数设置的影响（尤其是9341/6804）
 * 					所以,一般设置为L2R_U2D即可,如果设置为其他扫描方式,可能导致显示不正常.
 *         	9320/9325/9328/9341等IC已经实际测试	
 ******************************************************************************/
void LCD_Scan_Dir(u8 dir)
{
	u16 regval=0;
	u16 dirreg=0;
	u16 temp;   
	if((lcddev.dir==1&&lcddev.id!=0X6804&&lcddev.id!=0X1963)||(lcddev.dir==0&&lcddev.id==0X1963))			//横屏时，对6804和1963不改变扫描方向！竖屏时1963改变方向				
	{			   
		switch(dir)//方向转换
		{
			case 0:dir=6;break;
			case 1:dir=7;break;
			case 2:dir=4;break;
			case 3:dir=5;break;
			case 4:dir=1;break;
			case 5:dir=0;break;
			case 6:dir=3;break;
			case 7:dir=2;break;	     
		}
	} 
	if(lcddev.id==0x9341||lcddev.id==0X6804||lcddev.id==0X5310||lcddev.id==0X5510||lcddev.id==0X1963)  //9341/6804/5310/5510/1963,特殊处理
	{
		switch(dir)
		{
			case L2R_U2D://从左到右,从上到下
				regval|=(0<<7)|(0<<6)|(0<<5); 
				break;
			case L2R_D2U://从左到右,从下到上
				regval|=(1<<7)|(0<<6)|(0<<5); 
				break;
			case R2L_U2D://从右到左,从上到下
				regval|=(0<<7)|(1<<6)|(0<<5); 
				break;
			case R2L_D2U://从右到左,从下到上
				regval|=(1<<7)|(1<<6)|(0<<5); 
				break;	 
			case U2D_L2R://从上到下,从左到右
				regval|=(0<<7)|(0<<6)|(1<<5); 
				break;
			case U2D_R2L://从上到下,从右到左
				regval|=(0<<7)|(1<<6)|(1<<5); 
				break;
			case D2U_L2R://从下到上,从左到右
				regval|=(1<<7)|(0<<6)|(1<<5); 
				break;
			case D2U_R2L://从下到上,从右到左
				regval|=(1<<7)|(1<<6)|(1<<5); 
				break;	 
		}
		if(lcddev.id==0X5510)dirreg=0X3600;
		else dirreg=0X36;
 		if((lcddev.id!=0X5310)&&(lcddev.id!=0X5510)&&(lcddev.id!=0X1963))regval|=0X08;//5310/5510/1963不需要BGR   
		if(lcddev.id==0X6804)regval|=0x02;//6804的BIT6和9341的反了	   
		LCD_WriteReg(dirreg,regval);
		if(lcddev.id!=0X1963)//1963不做坐标处理
		{
			if(regval&0X20)
			{
				if(lcddev.width<lcddev.height)//交换X,Y
				{
					temp=lcddev.width;
					lcddev.width=lcddev.height;
					lcddev.height=temp;
				}
			}else  
			{
				if(lcddev.width>lcddev.height)//交换X,Y
				{
					temp=lcddev.width;
					lcddev.width=lcddev.height;
					lcddev.height=temp;
				}
			}  
		}
		
		if(lcddev.id==0X5510)
		{
			LCD_WR_REG(lcddev.setxcmd);LCD_WR_DATA(0); 
			LCD_WR_REG(lcddev.setxcmd+1);LCD_WR_DATA(0); 
			LCD_WR_REG(lcddev.setxcmd+2);LCD_WR_DATA((lcddev.width-1)>>8); 
			LCD_WR_REG(lcddev.setxcmd+3);LCD_WR_DATA((lcddev.width-1)&0XFF); 
			LCD_WR_REG(lcddev.setycmd);LCD_WR_DATA(0); 
			LCD_WR_REG(lcddev.setycmd+1);LCD_WR_DATA(0); 
			LCD_WR_REG(lcddev.setycmd+2);LCD_WR_DATA((lcddev.height-1)>>8); 
			LCD_WR_REG(lcddev.setycmd+3);LCD_WR_DATA((lcddev.height-1)&0XFF);
		}else
		{
			LCD_WR_REG(lcddev.setxcmd); 
			LCD_WR_DATA(0);LCD_WR_DATA(0);
			LCD_WR_DATA((lcddev.width-1)>>8);LCD_WR_DATA((lcddev.width-1)&0XFF);
			LCD_WR_REG(lcddev.setycmd); 
			LCD_WR_DATA(0);LCD_WR_DATA(0);
			LCD_WR_DATA((lcddev.height-1)>>8);LCD_WR_DATA((lcddev.height-1)&0XFF);  
		}
  	}else 
	{
		switch(dir)
		{
			case L2R_U2D:					//从左到右,从上到下
				regval|=(1<<5)|(1<<4)|(0<<3); 
				break;
			case L2R_D2U:					//从左到右,从下到上
				regval|=(0<<5)|(1<<4)|(0<<3); 
				break;
			case R2L_U2D:					//从右到左,从上到下
				regval|=(1<<5)|(0<<4)|(0<<3);
				break;
			case R2L_D2U:					//从右到左,从下到上
				regval|=(0<<5)|(0<<4)|(0<<3); 
				break;	 
			case U2D_L2R:					//从上到下,从左到右
				regval|=(1<<5)|(1<<4)|(1<<3); 
				break;
			case U2D_R2L:					//从上到下,从右到左
				regval|=(1<<5)|(0<<4)|(1<<3); 
				break;
			case D2U_L2R:					//从下到上,从左到右
				regval|=(0<<5)|(1<<4)|(1<<3); 
				break;
			case D2U_R2L:					//从下到上,从右到左
				regval|=(0<<5)|(0<<4)|(1<<3); 
				break;	 
		} 
		dirreg=0X03;
		regval|=1<<12; 
		LCD_WriteReg(dirreg,regval);
	}
}     

/*******************************************************************************
 * 函数名  ：void LCD_DrawPoint(u16 x,u16 y)
 * 描  述  ：画点
 * 输  入  ：x,y:坐标
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);				//设置光标位置 
	LCD_WriteRAM_Prepare();		//开始写入GRAM
	LCD_WR_DATA(POINT_COLOR); //此点的颜色
}	 

/*******************************************************************************
 * 函数名  ：void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
 * 描  述  ：快速画点
 * 输  入  ：x,y:坐标，color:颜色
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
{	   
	if(lcddev.id==0X9341||lcddev.id==0X5310)
	{
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(x>>8);LCD_WR_DATA(x&0XFF);  			 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(y>>8);LCD_WR_DATA(y&0XFF); 		 	 
	}else if(lcddev.id==0X5510)
	{
		LCD_WR_REG(lcddev.setxcmd);LCD_WR_DATA(x>>8);  
		LCD_WR_REG(lcddev.setxcmd+1);LCD_WR_DATA(x&0XFF);	  
		LCD_WR_REG(lcddev.setycmd);LCD_WR_DATA(y>>8);  
		LCD_WR_REG(lcddev.setycmd+1);LCD_WR_DATA(y&0XFF); 
	}else if(lcddev.id==0X1963)
	{
		if(lcddev.dir==0)x=lcddev.width-1-x;
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(x>>8);LCD_WR_DATA(x&0XFF); 		
		LCD_WR_DATA(x>>8);LCD_WR_DATA(x&0XFF); 		
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(y>>8);LCD_WR_DATA(y&0XFF); 		
		LCD_WR_DATA(y>>8);LCD_WR_DATA(y&0XFF); 		
	}else if(lcddev.id==0X6804)
	{		    
		if(lcddev.dir==1)x=lcddev.width-1-x;				//横屏时处理
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(x>>8);LCD_WR_DATA(x&0XFF);			 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(y>>8);LCD_WR_DATA(y&0XFF); 		
	}else
	{
 		if(lcddev.dir==1)x=lcddev.width-1-x;				//横屏其实就是调转x,y坐标
		LCD_WriteReg(lcddev.setxcmd,x);
		LCD_WriteReg(lcddev.setycmd,y);
	}	
	LCD_RS_CLR;
 	LCD_CS_CLR; 
	DATAOUT(lcddev.wramcmd);											//写指令  
	LCD_WR_CLR; 
	LCD_WR_SET; 
 	LCD_CS_SET; 
	LCD_WR_DATA(color);														//写数据
}

/*******************************************************************************
 * 函数名  ：void LCD_SSD_BackLightSet(u8 pwm)
 * 描  述  ：SSD1963 背光设置
 * 输  入  ：pwm:背光等级,0~100.越大越亮.
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_SSD_BackLightSet(u8 pwm)
{	
	LCD_WR_REG(0xBE);					//配置PWM输出
	LCD_WR_DATA(0x05);				//1设置PWM频率
//	LCD_WR_DATA(pwm*2.55);		//2设置PWM占空比
	LCD_WR_DATA(0x01);				//3设置C
	LCD_WR_DATA(0xFF);				//4设置D
	LCD_WR_DATA(0x00);				//5设置E
	LCD_WR_DATA(0x00);				//6设置F
}

/*******************************************************************************
 * 函数名  ：void LCD_Display_Dir(u8 dir)
 * 描  述  ：设置LCD显示方向
 * 输  入  ：dir:0,竖屏；1,横屏
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_Display_Dir(u8 dir)
{
	if(dir==0)							//竖屏
	{
		lcddev.dir=0;					//竖屏
		lcddev.width=240;
		lcddev.height=320;
		if(lcddev.id==0X9341||lcddev.id==0X6804||lcddev.id==0X5310)
		{
			lcddev.wramcmd=0X2C;
	 		lcddev.setxcmd=0X2A;
			lcddev.setycmd=0X2B;  	 
			if(lcddev.id==0X6804||lcddev.id==0X5310)
			{
				lcddev.width=320;
				lcddev.height=480;
			}
		}else if(lcddev.id==0x5510)
		{
			lcddev.wramcmd=0X2C00;
	 		lcddev.setxcmd=0X2A00;
			lcddev.setycmd=0X2B00; 
			lcddev.width=480;
			lcddev.height=800;
		}else if(lcddev.id==0X1963)
		{
			lcddev.wramcmd=0X2C;	//设置写入GRAM的指令 
			lcddev.setxcmd=0X2B;	//设置写X坐标指令
			lcddev.setycmd=0X2A;	//设置写Y坐标指令
			lcddev.width=480;			//设置宽度480
			lcddev.height=800;		//设置高度800  
		}else
		{
			lcddev.wramcmd=0X22;
	 		lcddev.setxcmd=0X20;
			lcddev.setycmd=0X21;  
		}
	}else 										//横屏
	{	  				
		lcddev.dir=1;						//横屏
		lcddev.width=320;
		lcddev.height=240;
		if(lcddev.id==0X9341||lcddev.id==0X5310)
		{
			lcddev.wramcmd=0X2C;
	 		lcddev.setxcmd=0X2A;
			lcddev.setycmd=0X2B;  	 
		}else if(lcddev.id==0X6804)	 
		{
 			lcddev.wramcmd=0X2C;
	 		lcddev.setxcmd=0X2B;
			lcddev.setycmd=0X2A; 
		}else if(lcddev.id==0x5510)
		{
			lcddev.wramcmd=0X2C00;
	 		lcddev.setxcmd=0X2A00;
			lcddev.setycmd=0X2B00; 
			lcddev.width=800;
			lcddev.height=480;
		}else if(lcddev.id==0X1963)
		{
			lcddev.wramcmd=0X2C;	//设置写入GRAM的指令 
			lcddev.setxcmd=0X2A;	//设置写X坐标指令
			lcddev.setycmd=0X2B;	//设置写Y坐标指令
			lcddev.width=800;			//设置宽度800
			lcddev.height=480;		//设置高度480  
		}else
		{
			lcddev.wramcmd=0X22;
	 		lcddev.setxcmd=0X21;
			lcddev.setycmd=0X20;  
		}
		if(lcddev.id==0X6804||lcddev.id==0X5310)
		{ 	 
			lcddev.width=480;
			lcddev.height=320; 			
		}
	} 
	LCD_Scan_Dir(DFT_SCAN_DIR);	//默认扫描方向
}	 

/*******************************************************************************
 * 函数名  ：void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height)
 * 描  述  ：设置窗口,并自动设置画点坐标到窗口左上角(sx,sy)
 * 输  入  ：sx,sy:窗口起始坐标(左上角)，width,height:窗口宽度和高度,必须大于0，窗体大小:width*height.
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height)
{    
	u8 hsareg,heareg,vsareg,veareg;
	u16 hsaval,heaval,vsaval,veaval; 
	u16 twidth,theight;
	twidth=sx+width-1;
	theight=sy+height-1;
	if(lcddev.id==0X9341||lcddev.id==0X5310||lcddev.id==0X6804||(lcddev.dir==1&&lcddev.id==0X1963))
	{
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(sx>>8); 
		LCD_WR_DATA(sx&0XFF);	 
		LCD_WR_DATA(twidth>>8); 
		LCD_WR_DATA(twidth&0XFF);  
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(sy>>8); 
		LCD_WR_DATA(sy&0XFF); 
		LCD_WR_DATA(theight>>8); 
		LCD_WR_DATA(theight&0XFF); 
	}else if(lcddev.id==0X1963)									//1963竖屏特殊处理
	{
		sx=lcddev.width-width-sx; 
		height=sy+height-1; 
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(sx>>8); 
		LCD_WR_DATA(sx&0XFF);	 
		LCD_WR_DATA((sx+width-1)>>8); 
		LCD_WR_DATA((sx+width-1)&0XFF);  
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(sy>>8); 
		LCD_WR_DATA(sy&0XFF); 
		LCD_WR_DATA(height>>8); 
		LCD_WR_DATA(height&0XFF); 		
	}else if(lcddev.id==0X5510)
	{
		LCD_WR_REG(lcddev.setxcmd);LCD_WR_DATA(sx>>8);  
		LCD_WR_REG(lcddev.setxcmd+1);LCD_WR_DATA(sx&0XFF);	  
		LCD_WR_REG(lcddev.setxcmd+2);LCD_WR_DATA(twidth>>8);   
		LCD_WR_REG(lcddev.setxcmd+3);LCD_WR_DATA(twidth&0XFF);   
		LCD_WR_REG(lcddev.setycmd);LCD_WR_DATA(sy>>8);   
		LCD_WR_REG(lcddev.setycmd+1);LCD_WR_DATA(sy&0XFF);  
		LCD_WR_REG(lcddev.setycmd+2);LCD_WR_DATA(theight>>8);   
		LCD_WR_REG(lcddev.setycmd+3);LCD_WR_DATA(theight&0XFF);  
	}else																			//其他驱动IC
	{
		if(lcddev.dir==1)												//横屏
		{
			/***************窗口值***************/
			hsaval=sy;				
			heaval=theight;
			vsaval=lcddev.width-twidth-1;
			veaval=lcddev.width-sx-1;				
		}else
		{ 
			hsaval=sx;				
			heaval=twidth;
			vsaval=sy;
			veaval=theight;
		} 
		hsareg=0X50;heareg=0X51;						//水平方向窗口寄存器
		vsareg=0X52;veareg=0X53;						//垂直方向窗口寄存器	   							  
		/**********设置寄存器值*****************/
		LCD_WriteReg(hsareg,hsaval);
		LCD_WriteReg(heareg,heaval);
		LCD_WriteReg(vsareg,vsaval);
		LCD_WriteReg(veareg,veaval);		
		LCD_SetCursor(sx,sy);								//设置光标位置
	}
}

/******************************************************************************************************
 * 函数名  ：void LCD_Init(void)
 * 描  述  ：设置窗口,并自动设置画点坐标到窗口左上角(sx,sy)
 * 输  入  ：sx,sy:窗口起始坐标(左上角)，width,height:窗口宽度和高度,必须大于0，窗体大小:width*height.
 * 输  出  ：无
 * 返回值  ：无
 * 注  意  ：本函数占用较大flash,用户可以根据自己的实际情况,删掉未用到的LCD初始化代码.以节省空间
 ******************************************************************************************************/
void LCD_Init(void)
{ 
	__delay_ms(50); 																																									// delay 50 ms 
	LCD_WriteReg(0x0000,0x0001);
	__delay_ms(50); 																																									// delay 50 ms 
  	lcddev.id = LCD_ReadReg(0x0000);   
	if(lcddev.id<0XFF||lcddev.id==0XFFFF||lcddev.id==0X9300)																				//读到ID不正确,新增lcddev.id==0X9300判断，因为9341在未被复位的情况下会被读成9300
	{	
 		/*****************尝试9341 ID的读取 ***********************/		
		LCD_WR_REG(0XD3);				   
		LCD_RD_DATA(); 									//dummy read 	
 		LCD_RD_DATA();   	    					//读到0X00
  		lcddev.id=LCD_RD_DATA();   		//读取93								   
 		lcddev.id<<=8;
		lcddev.id|=LCD_RD_DATA();  			//读取41 	   			   
 		if(lcddev.id!=0X9341)						//非9341,尝试是不是6804
		{	
 			LCD_WR_REG(0XBF);				   
			LCD_RD_DATA(); 								//dummy read 	 
	 		LCD_RD_DATA();   	    				//读回0X01			   
	 		LCD_RD_DATA(); 								//读回0XD0 			  	
	  		lcddev.id=LCD_RD_DATA();		//这里读回0X68 
			lcddev.id<<=8;
	  		lcddev.id|=LCD_RD_DATA();		//这里读回0X04	  
			if(lcddev.id!=0X6804)					//也不是6804,尝试看看是不是NT35310
			{ 
				LCD_WR_REG(0XD4);				   
				LCD_RD_DATA(); 							//dummy read  
				LCD_RD_DATA();   						//读回0X01	 
				lcddev.id=LCD_RD_DATA();		//读回0X53	
				lcddev.id<<=8;	 
				lcddev.id|=LCD_RD_DATA();		//这里读回0X10	 
				if(lcddev.id!=0X5310)				//也不是NT35310,尝试看看是不是NT35510
				{
					LCD_WR_REG(0XDA00);	
					LCD_RD_DATA();   					//读回0X00	 
					LCD_WR_REG(0XDB00);	
					lcddev.id=LCD_RD_DATA();	//读回0X80
					lcddev.id<<=8;	
					LCD_WR_REG(0XDC00);	
					lcddev.id|=LCD_RD_DATA();	//读回0X00		
					if(lcddev.id==0x8000)lcddev.id=0x5510;				//NT35510读回的ID是8000H,为方便区分,我们强制设置为5510
					if(lcddev.id!=0X5510)			//也不是NT5510,尝试看看是不是SSD1963
					{
						LCD_WR_REG(0XA1);
						lcddev.id=LCD_RD_DATA();
						lcddev.id=LCD_RD_DATA();	//读回0X57
						lcddev.id<<=8;	 
						lcddev.id|=LCD_RD_DATA();	//读回0X61	
						if(lcddev.id==0X5761)lcddev.id=0X1963;			//SSD1963读回的ID是5761H,为方便区分,我们强制设置为1963
					}
				}
			}
 		}  	
	}
// 	printf(" LCD ID:%x\r\n",lcddev.id); 									//打印LCD ID  
	if(lcddev.id==0X9341)																	//9341初始化
	{	 
		LCD_WR_REG(0xCF);  
		LCD_WR_DATAX(0x00); 
		LCD_WR_DATAX(0xC1); 
		LCD_WR_DATAX(0X30); 
		LCD_WR_REG(0xED);  
		LCD_WR_DATAX(0x64); 
		LCD_WR_DATAX(0x03); 
		LCD_WR_DATAX(0X12); 
		LCD_WR_DATAX(0X81); 
		LCD_WR_REG(0xE8);  
		LCD_WR_DATAX(0x85); 
		LCD_WR_DATAX(0x10); 
		LCD_WR_DATAX(0x7A); 
		LCD_WR_REG(0xCB);  
		LCD_WR_DATAX(0x39); 
		LCD_WR_DATAX(0x2C); 
		LCD_WR_DATAX(0x00); 
		LCD_WR_DATAX(0x34); 
		LCD_WR_DATAX(0x02); 
		LCD_WR_REG(0xF7);  
		LCD_WR_DATAX(0x20); 
		LCD_WR_REG(0xEA);  
		LCD_WR_DATAX(0x00); 
		LCD_WR_DATAX(0x00); 
		LCD_WR_REG(0xC0);    										//Power control 
		LCD_WR_DATAX(0x1B);   									//VRH[5:0] 
		LCD_WR_REG(0xC1);    										//Power control 
		LCD_WR_DATAX(0x01);   									//SAP[2:0];BT[3:0] 
		LCD_WR_REG(0xC5);    										//VCM control 
		LCD_WR_DATAX(0x30); 	 									//3F
		LCD_WR_DATAX(0x30); 	 									//3C
		LCD_WR_REG(0xC7);    										//VCM control2 
		LCD_WR_DATAX(0XB7); 
		LCD_WR_REG(0x36);    										// Memory Access Control 
		LCD_WR_DATAX(0x48); 
		LCD_WR_REG(0x3A);   
		LCD_WR_DATAX(0x55); 
		LCD_WR_REG(0xB1);   
		LCD_WR_DATAX(0x00);   
		LCD_WR_DATAX(0x1A); 
		LCD_WR_REG(0xB6);    										// Display Function Control 
		LCD_WR_DATAX(0x0A); 
		LCD_WR_DATAX(0xA2); 
		LCD_WR_REG(0xF2);    										// 3Gamma Function Disable 
		LCD_WR_DATAX(0x00); 
		LCD_WR_REG(0x26);    										//Gamma curve selected 
		LCD_WR_DATAX(0x01); 
		LCD_WR_REG(0xE0);    										//Set Gamma 
		LCD_WR_DATAX(0x0F); 
		LCD_WR_DATAX(0x2A); 
		LCD_WR_DATAX(0x28); 
		LCD_WR_DATAX(0x08); 
		LCD_WR_DATAX(0x0E); 
		LCD_WR_DATAX(0x08); 
		LCD_WR_DATAX(0x54); 
		LCD_WR_DATAX(0XA9); 
		LCD_WR_DATAX(0x43); 
		LCD_WR_DATAX(0x0A); 
		LCD_WR_DATAX(0x0F); 
		LCD_WR_DATAX(0x00); 
		LCD_WR_DATAX(0x00); 
		LCD_WR_DATAX(0x00); 
		LCD_WR_DATAX(0x00); 		 
		LCD_WR_REG(0XE1);    										//Set Gamma 
		LCD_WR_DATAX(0x00); 
		LCD_WR_DATAX(0x15); 
		LCD_WR_DATAX(0x17); 
		LCD_WR_DATAX(0x07); 
		LCD_WR_DATAX(0x11); 
		LCD_WR_DATAX(0x06); 
		LCD_WR_DATAX(0x2B); 
		LCD_WR_DATAX(0x56); 
		LCD_WR_DATAX(0x3C); 
		LCD_WR_DATAX(0x05); 
		LCD_WR_DATAX(0x10); 
		LCD_WR_DATAX(0x0F); 
		LCD_WR_DATAX(0x3F); 
		LCD_WR_DATAX(0x3F); 
		LCD_WR_DATAX(0x0F); 
		LCD_WR_REG(0x2B); 
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0x01);
		LCD_WR_DATAX(0x3f);
		LCD_WR_REG(0x2A); 
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0x00);
		LCD_WR_DATAX(0xef);	 
		LCD_WR_REG(0x11); //Exit Sleep
		__delay_ms(120);
		LCD_WR_REG(0x29); //display on	
	}
	else if(lcddev.id==0x9325)//9325
	{
		LCD_WriteReg(0x00E5,0x78F0); 
		LCD_WriteReg(0x0001,0x0100); 
		LCD_WriteReg(0x0002,0x0700); 
		LCD_WriteReg(0x0003,0x1030); 
		LCD_WriteReg(0x0004,0x0000); 
		LCD_WriteReg(0x0008,0x0202);  
		LCD_WriteReg(0x0009,0x0000);
		LCD_WriteReg(0x000A,0x0000); 
		LCD_WriteReg(0x000C,0x0000); 
		LCD_WriteReg(0x000D,0x0000);
		LCD_WriteReg(0x000F,0x0000);
		//power on sequence VGHVGL
		LCD_WriteReg(0x0010,0x0000);   
		LCD_WriteReg(0x0011,0x0007);  
		LCD_WriteReg(0x0012,0x0000);  
		LCD_WriteReg(0x0013,0x0000); 
		LCD_WriteReg(0x0007,0x0000); 
		//vgh 
		LCD_WriteReg(0x0010,0x1690);   
		LCD_WriteReg(0x0011,0x0227);
		//delayms(100);
		//vregiout 
		LCD_WriteReg(0x0012,0x009D); //0x001b
		//delayms(100); 
		//vom amplitude
		LCD_WriteReg(0x0013,0x1900);
		//delayms(100); 
		//vom H
		LCD_WriteReg(0x0029,0x0025); 
		LCD_WriteReg(0x002B,0x000D); 
		//gamma
		LCD_WriteReg(0x0030,0x0007);
		LCD_WriteReg(0x0031,0x0303);
		LCD_WriteReg(0x0032,0x0003);// 0006
		LCD_WriteReg(0x0035,0x0206);
		LCD_WriteReg(0x0036,0x0008);
		LCD_WriteReg(0x0037,0x0406); 
		LCD_WriteReg(0x0038,0x0304);//0200
		LCD_WriteReg(0x0039,0x0007); 
		LCD_WriteReg(0x003C,0x0602);// 0504
		LCD_WriteReg(0x003D,0x0008); 
		//ram
		LCD_WriteReg(0x0050,0x0000); 
		LCD_WriteReg(0x0051,0x00EF);
		LCD_WriteReg(0x0052,0x0000); 
		LCD_WriteReg(0x0053,0x013F);  
		LCD_WriteReg(0x0060,0xA700); 
		LCD_WriteReg(0x0061,0x0001); 
		LCD_WriteReg(0x006A,0x0000); 
		//
		LCD_WriteReg(0x0080,0x0000); 
		LCD_WriteReg(0x0081,0x0000); 
		LCD_WriteReg(0x0082,0x0000); 
		LCD_WriteReg(0x0083,0x0000); 
		LCD_WriteReg(0x0084,0x0000); 
		LCD_WriteReg(0x0085,0x0000); 
		//
		LCD_WriteReg(0x0090,0x0010); 
		LCD_WriteReg(0x0092,0x0600); 
		
		LCD_WriteReg(0x0007,0x0133);
		LCD_WriteReg(0x00,0x0022);//
	}else if(lcddev.id==0x9328)//ILI9328   OK  
	{
  	LCD_WriteReg(0x00EC,0x108F);// internal timeing      
 	LCD_WriteReg(0x00EF,0x1234);// ADD        
		//LCD_WriteReg(0x00e7,0x0010);      
    //LCD_WriteReg(0x0000,0x0001);//开启内部时钟
    LCD_WriteReg(0x0001,0x0100);     
    LCD_WriteReg(0x0002,0x0700);//电源开启                    
		//LCD_WriteReg(0x0003,(1<<3)|(1<<4) ); 	//65K  RGB
		//DRIVE TABLE(寄存器 03H)
		//BIT3=AM BIT4:5=ID0:1
		//AM ID0 ID1   FUNCATION
		// 0  0   0	   R->L D->U
		// 1  0   0	   D->U	R->L
		// 0  1   0	   L->R D->U
		// 1  1   0    D->U	L->R
		// 0  0   1	   R->L U->D
		// 1  0   1    U->D	R->L
		// 0  1   1    L->R U->D 正常就用这个.
		// 1  1   1	   U->D	L->R
		LCD_WriteReg(0x0003,(1<<12)|(3<<4)|(0<<3) );//65K    
		LCD_WriteReg(0x0004,0x0000);                                   
		LCD_WriteReg(0x0008,0x0202);	           
		LCD_WriteReg(0x0009,0x0000);         
		LCD_WriteReg(0x000a,0x0000);//display setting         
		LCD_WriteReg(0x000c,0x0001);//display setting          
		LCD_WriteReg(0x000d,0x0000);//0f3c          
		LCD_WriteReg(0x000f,0x0000);
		//电源配置
		LCD_WriteReg(0x0010,0x0000);   
		LCD_WriteReg(0x0011,0x0007);
		LCD_WriteReg(0x0012,0x0000);                                                                 
		LCD_WriteReg(0x0013,0x0000);                 
		LCD_WriteReg(0x0007,0x0001);                 
		__delay_ms(50); 
		LCD_WriteReg(0x0010,0x1490);   
		LCD_WriteReg(0x0011,0x0227);
		__delay_ms(50); 
		LCD_WriteReg(0x0012,0x008A);                  
		__delay_ms(50); 
		LCD_WriteReg(0x0013,0x1a00);   
		LCD_WriteReg(0x0029,0x0006);
		LCD_WriteReg(0x002b,0x000d);
		__delay_ms(50); 
		LCD_WriteReg(0x0020,0x0000);                                                            
		LCD_WriteReg(0x0021,0x0000);           
		__delay_ms(50); 
		//伽马校正
		LCD_WriteReg(0x0030,0x0000); 
		LCD_WriteReg(0x0031,0x0604);   
		LCD_WriteReg(0x0032,0x0305);
		LCD_WriteReg(0x0035,0x0000);
		LCD_WriteReg(0x0036,0x0C09); 
		LCD_WriteReg(0x0037,0x0204);
		LCD_WriteReg(0x0038,0x0301);        
		LCD_WriteReg(0x0039,0x0707);     
		LCD_WriteReg(0x003c,0x0000);
		LCD_WriteReg(0x003d,0x0a0a);
		__delay_ms(50); 
		LCD_WriteReg(0x0050,0x0000); //水平GRAM起始位置 
		LCD_WriteReg(0x0051,0x00ef); //水平GRAM终止位置                    
		LCD_WriteReg(0x0052,0x0000); //垂直GRAM起始位置                    
		LCD_WriteReg(0x0053,0x013f); //垂直GRAM终止位置  

		 LCD_WriteReg(0x0060,0xa700);        
		LCD_WriteReg(0x0061,0x0001); 
		LCD_WriteReg(0x006a,0x0000);
		LCD_WriteReg(0x0080,0x0000);
		LCD_WriteReg(0x0081,0x0000);
		LCD_WriteReg(0x0082,0x0000);
		LCD_WriteReg(0x0083,0x0000);
		LCD_WriteReg(0x0084,0x0000);
		LCD_WriteReg(0x0085,0x0000);
	
		LCD_WriteReg(0x0090,0x0010);     
		LCD_WriteReg(0x0092,0x0600);  
		//开启显示设置    
		LCD_WriteReg(0x0007,0x0133); 
	}else if(lcddev.id==0x9320)//测试OK.
	{
		LCD_WriteReg(0x00,0x0000);
		LCD_WriteReg(0x01,0x0100);	//Driver Output Contral.
		LCD_WriteReg(0x02,0x0700);	//LCD Driver Waveform Contral.
		LCD_WriteReg(0x03,0x1030);//Entry Mode Set.
		//LCD_WriteReg(0x03,0x1018);	//Entry Mode Set.
	
		LCD_WriteReg(0x04,0x0000);	//Scalling Contral.
		LCD_WriteReg(0x08,0x0202);	//Display Contral 2.(0x0207)
		LCD_WriteReg(0x09,0x0000);	//Display Contral 3.(0x0000)
		LCD_WriteReg(0x0a,0x0000);	//Frame Cycle Contal.(0x0000)
		LCD_WriteReg(0x0c,(1<<0));	//Extern Display Interface Contral 1.(0x0000)
		LCD_WriteReg(0x0d,0x0000);	//Frame Maker Position.
		LCD_WriteReg(0x0f,0x0000);	//Extern Display Interface Contral 2.	    
		__delay_ms(50); 
		LCD_WriteReg(0x07,0x0101);	//Display Contral.
		__delay_ms(50); 								  
		LCD_WriteReg(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));	//Power Control 1.(0x16b0)
		LCD_WriteReg(0x11,0x0007);								//Power Control 2.(0x0001)
		LCD_WriteReg(0x12,(1<<8)|(1<<4)|(0<<0));				//Power Control 3.(0x0138)
		LCD_WriteReg(0x13,0x0b00);								//Power Control 4.
		LCD_WriteReg(0x29,0x0000);								//Power Control 7.
	
		LCD_WriteReg(0x2b,(1<<14)|(1<<4));	    
		LCD_WriteReg(0x50,0);	//Set X Star
		//水平GRAM终止位置Set X End.
		LCD_WriteReg(0x51,239);	//Set Y Star
		LCD_WriteReg(0x52,0);	//Set Y End.t.
		LCD_WriteReg(0x53,319);	//
	
		LCD_WriteReg(0x60,0x2700);	//Driver Output Control.
		LCD_WriteReg(0x61,0x0001);	//Driver Output Control.
		LCD_WriteReg(0x6a,0x0000);	//Vertical Srcoll Control.
	
		LCD_WriteReg(0x80,0x0000);	//Display Position? Partial Display 1.
		LCD_WriteReg(0x81,0x0000);	//RAM Address Start? Partial Display 1.
		LCD_WriteReg(0x82,0x0000);	//RAM Address End-Partial Display 1.
		LCD_WriteReg(0x83,0x0000);	//Displsy Position? Partial Display 2.
		LCD_WriteReg(0x84,0x0000);	//RAM Address Start? Partial Display 2.
		LCD_WriteReg(0x85,0x0000);	//RAM Address End? Partial Display 2.
	
		LCD_WriteReg(0x90,(0<<7)|(16<<0));	//Frame Cycle Contral.(0x0013)
		LCD_WriteReg(0x92,0x0000);	//Panel Interface Contral 2.(0x0000)
		LCD_WriteReg(0x93,0x0001);	//Panel Interface Contral 3.
		LCD_WriteReg(0x95,0x0110);	//Frame Cycle Contral.(0x0110)
		LCD_WriteReg(0x97,(0<<8));	//
		LCD_WriteReg(0x98,0x0000);	//Frame Cycle Contral.	   
		LCD_WriteReg(0x07,0x0173);	//(0x0173)
	}

	LCD_Display_Dir(1);		 	//默认为竖屏
    LCD_LED;					//点亮背光
	LCD_Clear(WHITE);
}  		  
  
/*******************************************************************************
 * 函数名  ：void LCD_Clear(u16 color)
 * 描  述  ：清屏函数
 * 输  入  ：color:要清屏的填充色
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 							//得到总点数
	if((lcddev.id==0X6804)&&(lcddev.dir==1))//6804横屏的时候特殊处理  
	{						    
 		lcddev.dir=0;	 
 		lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;  	 			
		LCD_SetCursor(0x00,0x0000);						//设置光标位置  
 		lcddev.dir=1;	 
  		lcddev.setxcmd=0X2B;
		lcddev.setycmd=0X2A;  	 
 	}else LCD_SetCursor(0x00,0x0000);				//设置光标位置 
	LCD_WriteRAM_Prepare();     						//开始写入GRAM	  	  
	for(index=0;index<totalpoint;index++)LCD_WR_DATA(color);	
}  

/*******************************************************************************
 * 函数名  ：void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
 * 描  述  ：在指定区域内填充指定颜色
 * 输  入  ：区域大小:(xend-xsta+1)*(yend-ysta+1) color:要清屏的填充色
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
	u16 temp;
	if((lcddev.id==0X6804)&&(lcddev.dir==1))		//6804横屏的时候特殊处理  
	{
		temp=sx;
		sx=sy;
		sy=lcddev.width-ex-1;	  
		ex=ey;
		ey=lcddev.width-temp-1;
 		lcddev.dir=0;	 
 		lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;  	 			
		LCD_Fill(sx,sy,ex,ey,color);  
 		lcddev.dir=1;	 
  		lcddev.setxcmd=0X2B;
		lcddev.setycmd=0X2A;  	 
 	}else
	{
		xlen=ex-sx+1;	 
		for(i=sy;i<=ey;i++)
		{
		 	LCD_SetCursor(sx,i);      							//设置光标位置 
			LCD_WriteRAM_Prepare();     						//开始写入GRAM	  
			for(j=0;j<xlen;j++)LCD_WR_DATA(color);	//设置光标位置 	    
		}
	}
}  

/*******************************************************************************
 * 函数名  ：void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
 * 描  述  ：在指定区域内填充指定颜色
 * 输  入  ：(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   color:要清屏的填充色
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 								//得到填充的宽度
	height=ey-sy+1;								//高度
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//设置光标位置 
		LCD_WriteRAM_Prepare();     //开始写入GRAM
		for(j=0;j<width;j++)LCD_WR_DATA(color[i*width+j]);//写入数据 
	}	  
} 

/*******************************************************************************
 * 函数名  ：void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
 * 描  述  ：画线
 * 输  入  ：x1,y1:起点坐标，x2,y2:终点坐标
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; 												//计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; 									//设置单步方向 
	else if(delta_x==0)incx=0;						//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;						//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )						//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol);						//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    

/*******************************************************************************
 * 函数名  ：void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
 * 描  述  ：画矩形
 * 输  入  ：(x1,y1),(x2,y2):矩形的对角坐标
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

/*******************************************************************************
 * 函数名  ：void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
 * 描  述  ：在指定位置画一个指定大小的圆
 * 输  入  ：(x,y):中心点，r：半径
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             								//判断下个点位置的标志
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);           //7     	         
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									  

/*******************************************************************************
 * 函数名  ：void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
 * 描  述  ：在指定位置显示一个字符
 * 输  入  ：x,y:起始坐标，num:要显示的字符:" "，size:字体大小 12/16/24，mode:叠加方式(1)还是非叠加方式(0)
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);			//得到字体一个字符对应点阵集所占的字节数	
 	num=num-' ';																		//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 				//调用1206字体
		else if(size==16)temp=asc2_1608[num][t];			//调用1608字体
		else if(size==24)temp=asc2_2412[num][t];			//调用2412字体
		else return;																	//没有的字库
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=lcddev.height)return;									//超区域了
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=lcddev.width)return;								//超区域了
				break;
			}
		}  	 
	}  	    	   	 	  
}   

/*******************************************************************************
 * 函数名  ：u32 LCD_Pow(u8 m,u8 n)
 * 描  述  ：m^n函数
 * 输  入  ：u8 m,u8 n
 * 输  出  ：无
 * 返回值  ：m^n次方
 ******************************************************************************/
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}		

 
/*******************************************************************************
 * 函数名  ：void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
 * 描  述  ：显示数字,高位为0,则不显示
 * 输  入  ：x,y :起点坐标，len :数字的位数，size:字体大小，num:数值(0~4294967295)
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 

/*******************************************************************************
 * 函数名  ：void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
 * 描  述  ：显示数字,高位为0,还是显示
 * 输  入  ：x,y :起点坐标，num:数值(0~999999999)，len :数字的位数，size:字体大小，mode:
*        [7]:0,不填充;1,填充0，[6:1]:保留，[0]:0,非叠加显示;1,叠加显示
 * 输  出  ：无
 * 返回值  ：m^n次方
 ******************************************************************************/
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
	 
/*******************************************************************************
 * 函数名  ：void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
 * 描  述  ：显示字符串
 * 输  入  ：x,y:起点坐标，width,height:区域大小，size:字体大小，*p:字符串起始地址 
 * 输  出  ：无
 * 返回值  ：无
 ******************************************************************************/
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))			//判断是不是非法字符!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;					//退出
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}






























