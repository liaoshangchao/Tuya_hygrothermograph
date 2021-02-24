/*******************************************************************************************	 
* �ļ����ƣ�lcd.c
* ����������2.8��TFT����LCDҺ������
* ����ƽ̨��STM32F103RCT6ʵ���
* �� �ߣ�Layout
* �� �ڣ�2020-2-18
* �� ����V1.0
* �� �ģ���
* �� ע����
**************************************************************************************/
#include "lcd.h"
#include "stdlib.h"
#include "FONT.H"
#include "../mcc_generated_files/device_config.h"
//#include "../mcc_generated_files/eusart1.h"



 
/*****************LCD�Ļ�����ɫ�ͱ���ɫ**********************/ 
u16 POINT_COLOR=0x0000;				//������ɫ
u16 BACK_COLOR=0xFFFF;  			//����ɫ 

/****************����LCD��Ҫ������Ĭ��Ϊ����*****************/
_lcd_dev lcddev;
	 					    

/*******************************************************************************
 * ������  ��void LCD_WR_REG(u16 data)
 * ��  ��  ��д�Ĵ�������
 * ��  ��  ��data:�Ĵ���ֵ
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_WR_REG(u16 data)
{ 
	LCD_RS_CLR;					//д��ַ����  
 	LCD_CS_CLR; 				//Ƭѡ�˿�����
	DATAOUT(data); 			//�������
	LCD_WR_CLR; 				//д��������	
	LCD_WR_SET; 				//д��������
 	LCD_CS_SET;   			//�ͷ�Ƭѡ�˿�
}


/*******************************************************************************
 * ������  ��void LCD_WR_DATAX(u16 data)
 * ��  ��  ��д���ݺ���
 * ��  ��  ��data:�Ĵ���ֵ
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_WR_DATAX(u16 data)
{
	LCD_RS_SET;					//д��ַ����
	LCD_CS_CLR;					//Ƭѡ�˿�����
	DATAOUT(data);			//�������
	LCD_WR_CLR;					//д��������
	LCD_WR_SET;					//д��������
	LCD_CS_SET;					//�ͷ�Ƭѡ�˿�
}

/*******************************************************************************
 * ������  ��u16 LCD_RD_DATA(void)
 * ��  ��  ����LCD����
 * ��  ��  ����
 * ��  ��  ����
 * ����ֵ  ��t
 ******************************************************************************/
u16 LCD_RD_DATA(void)
{										   
	u16 t;
    TRISD = 0xff;       // 	GPIOB->CRL=0X88888888; //PB0-7  ��������   //	GPIOB->CRH=0X88888888; //PB8-15 ��������
    TRISF = 0xff;       //	GPIOB->ODR=0X0000;     //ȫ�����0

	LCD_RS_SET;												//д��ַ����
	LCD_CS_CLR;												//Ƭѡ�˿�����	
	LCD_RD_CLR;												//��ȡ����(���Ĵ���ʱ,������Ҫ��2��)
	if(lcddev.id==0X8989)__delay_us(2);	//FOR 8989,��ʱ2us					   
	t=DATAIN;  
	LCD_RD_SET;												//������
	LCD_CS_SET; 											//�ͷ�Ƭѡ�˿�

	TRISD = 0x00;
    TRISF = 0x00;   //    GPIOB->CRL=0X33333333; //PB0-7  �������    GPIOB->CRH=0X33333333; //PB8-15 �������
	
    LATD = 0xff ;     //            GPIOB->ODR=0XFFFF;    //ȫ�������
    LATF = 0xff ;
	return t;  												//��ȡ������
}


/*******************************************************************************
 * ������  ��void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
 * ��  ��  ��д�Ĵ���
 * ��  ��  ��LCD_Reg:�Ĵ�����ţ�LCD_RegValue:Ҫд���ֵ
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);  		 //д��Ҫд�ļĴ�����
	LCD_WR_DATA(LCD_RegValue);	    		 
}   


/*******************************************************************************
 * ������  ��u16 LCD_ReadReg(u16 LCD_Reg)
 * ��  ��  �����Ĵ���
 * ��  ��  ��LCD_Reg:�Ĵ������
 * ��  ��  ����
 * ����ֵ  ��LCD_RD_DATA();
 ******************************************************************************/
u16 LCD_ReadReg(u16 LCD_Reg)
{										   
 	LCD_WR_REG(LCD_Reg);  //д��Ҫ���ļĴ�����  
	return LCD_RD_DATA(); 
} 

/*******************************************************************************
 * ������  ��void LCD_WriteRAM_Prepare(void)
 * ��  ��  ����ʼдGRAM
 * ��  ��  ����
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
} 


/*******************************************************************************
 * ������  ��void LCD_WriteRAM(u16 RGB_Code)
 * ��  ��  ��LCDдGRAM
 * ��  ��  ��u16 RGB_Cod
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_WriteRAM(u16 RGB_Code)
{							    
	LCD_WR_DATA(RGB_Code);			//дʮ��λGRAM
}


/*******************************************************************************
 * ������  ��u16 LCD_BGR2RGB(u16 c)
 * ��  ��  ����ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��ͨ���ú���ת����
 * ��  ��  ��c:GBR��ʽ����ɫֵ
 * ��  ��  ����
 * ����ֵ  ��RGB��ʽ����ɫֵ
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
 * ������  ��void opt_delay(u8 l)
 * ��  ��  ����mdk -O1ʱ���Ż�ʱ��Ҫ����,��ʱl
 * ��  ��  ��u8 l
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void opt_delay(u8 l)
{
	while(l--);
}


/*******************************************************************************
 * ������  ��u16 LCD_ReadPoint(u16 x,u16 y)
 * ��  ��  ����ȡ��ĳ�����ɫֵ
 * ��  ��  ��x,y:����
 * ��  ��  ����
 * ����ֵ  ���˵����ɫ
 ******************************************************************************/
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r,g,b;
	if(x>=lcddev.width||y>=lcddev.height)return 0;	//�����˷�Χ,ֱ�ӷ���		   
	LCD_SetCursor(x,y);
	if(lcddev.id==0X9341||lcddev.id==0X6804||lcddev.id==0X5310||lcddev.id==0X1963)LCD_WR_REG(0X2E);//9341/6804/3510/1963 ���Ͷ�GRAMָ��
	else if(lcddev.id==0X5510)LCD_WR_REG(0X2E00);		//5510 ���Ͷ�GRAMָ��
	else LCD_WR_REG(0X22);      		 								//����IC���Ͷ�GRAMָ��
    TRISD = 0xff;       // 	GPIOB->CRL=0X88888888; //PB0-7  ��������   //	GPIOB->CRH=0X88888888; //PB8-15 ��������
    TRISF = 0xff;       //	GPIOB->ODR=0X0000;     //ȫ�����0

	LCD_RS_SET;																			//����/��������
	LCD_CS_CLR;	    																//Ƭѡ����
		
	LCD_RD_CLR;		   																//��ȡ����(��GRAMʱ,��һ��Ϊ�ٶ�)
	opt_delay(2);																		//��ʱ		
 	r=DATAIN;  																			//ʵ��������ɫ 
	LCD_RD_SET;																			//����������	
	if(lcddev.id==0X1963)
	{
		LCD_CS_SET;
        TRISD = 0x00;
        TRISF = 0x00;   //    GPIOB->CRL=0X33333333; //PB0-7  �������    GPIOB->CRH=0X33333333; //PB8-15 �������
	
        LATD = 0xff ;     //            GPIOB->ODR=0XFFFF;    //ȫ�������
        LATF = 0xff ;  												//ȫ�������  
		return r;																			//1963ֱ�Ӷ��Ϳ��� 
 	}

	LCD_RD_CLR;					   													//�����ݺ�����
	opt_delay(2);																		//��ʱ					   
 	r=DATAIN;  																			//ʵ��������ɫ
	LCD_RD_SET;																			//����������
 	if(lcddev.id==0X9341||lcddev.id==0X5310||lcddev.id==0X5510)														//9341Ҫ��2�ζ���
	{	 	
		LCD_RD_CLR;					   												//�����ݺ�����
		opt_delay(2);																	//��ʱ			   
		b=DATAIN;																			//��ȡ��ɫֵ 
	 	LCD_RD_SET;																		//����������
		g=r&0XFF;																			//����9341,��һ�ζ�ȡ����RG��ֵ,R��ǰ,G�ں�,��ռ8λ
		g<<=8;
	}
	else if(lcddev.id==0X6804)
	{
		LCD_RD_CLR;					   
	 	LCD_RD_SET;
		r=DATAIN;																			//6804�ڶ��ζ�ȡ�Ĳ�����ʵֵ 
	}	 
	LCD_CS_SET;																			//Ƭѡ����
	TRISD = 0x00;
    TRISF = 0x00;   //    GPIOB->CRL=0X33333333; //PB0-7  �������    GPIOB->CRH=0X33333333; //PB8-15 �������
	
    LATD = 0xff ;     //            GPIOB->ODR=0XFFFF;    //ȫ�������
    LATF = 0xff ; 													//ȫ�������  
	if(lcddev.id==0X9325||lcddev.id==0X4535||lcddev.id==0X4531||lcddev.id==0X8989||lcddev.id==0XB505)return r;	//�⼸��ICֱ�ӷ�����ɫֵ
	else if(lcddev.id==0X9341||lcddev.id==0X5310||lcddev.id==0X5510)return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));//ILI9341/NT35310/NT35510��Ҫ��ʽת��һ��
	else return LCD_BGR2RGB(r);											//����IC
}		 

/*******************************************************************************
 * ������  ��void LCD_DisplayOn(void)
 * ��  ��  ��LCD������ʾ
 * ��  ��  ����
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_DisplayOn(void)
{					   
	if(lcddev.id==0X9341||lcddev.id==0X6804||lcddev.id==0X5310||lcddev.id==0X1963)LCD_WR_REG(0X29);	//������ʾ
	else if(lcddev.id==0X5510)LCD_WR_REG(0X2900);																										//������ʾ
	else LCD_WriteReg(0X07,0x0173); 				 																												//������ʾ
}	 

/*******************************************************************************
 * ������  ��void LCD_DisplayOff(void)
 * ��  ��  ��LCD�ر���ʾ
 * ��  ��  ����
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_DisplayOff(void)
{	   
	if(lcddev.id==0X9341||lcddev.id==0X6804||lcddev.id==0X5310||lcddev.id==0X1963)LCD_WR_REG(0X28);	//�ر���ʾ
	else if(lcddev.id==0X5510)LCD_WR_REG(0X2800);																										//�ر���ʾ
	else LCD_WriteReg(0X07,0x0);																																		//�ر���ʾ 
}   
   

/*******************************************************************************
 * ������  ��void LCD_SetCursor(u16 Xpos, u16 Ypos)
 * ��  ��  �����ù��λ��
 * ��  ��  ��Xpos:������Ypos:������
 * ��  ��  ����
 * ����ֵ  ����
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
		if(lcddev.dir==1)Xpos=lcddev.width-1-Xpos;		//����ʱ����
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(Xpos>>8);LCD_WR_DATA(Xpos&0XFF); 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(Ypos>>8);LCD_WR_DATA(Ypos&0XFF); 
	}else if(lcddev.id==0X1963)
	{  			 		
		if(lcddev.dir==0)															//x������Ҫ�任
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
		if(lcddev.dir==1)Xpos=lcddev.width-1-Xpos;				//������ʵ���ǵ�תx,y����
		LCD_WriteReg(lcddev.setxcmd, Xpos);
		LCD_WriteReg(lcddev.setycmd, Ypos);
	}	 
} 		 

/*******************************************************************************
 * ������  ��void LCD_Scan_Dir(u8 dir)
 * ��  ��  ������LCD���Զ�ɨ�跽��
 * ��  ��  ��dir:0~7,����8������(���嶨���lcd.h)
 * ��  ��  ����
 * ����ֵ  ����
 * ע  ��  �������������ܻ��ܵ��˺������õ�Ӱ�죨������9341/6804��
 * 					����,һ������ΪL2R_U2D����,�������Ϊ����ɨ�跽ʽ,���ܵ�����ʾ������.
 *         	9320/9325/9328/9341��IC�Ѿ�ʵ�ʲ���	
 ******************************************************************************/
void LCD_Scan_Dir(u8 dir)
{
	u16 regval=0;
	u16 dirreg=0;
	u16 temp;   
	if((lcddev.dir==1&&lcddev.id!=0X6804&&lcddev.id!=0X1963)||(lcddev.dir==0&&lcddev.id==0X1963))			//����ʱ����6804��1963���ı�ɨ�跽������ʱ1963�ı䷽��				
	{			   
		switch(dir)//����ת��
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
	if(lcddev.id==0x9341||lcddev.id==0X6804||lcddev.id==0X5310||lcddev.id==0X5510||lcddev.id==0X1963)  //9341/6804/5310/5510/1963,���⴦��
	{
		switch(dir)
		{
			case L2R_U2D://������,���ϵ���
				regval|=(0<<7)|(0<<6)|(0<<5); 
				break;
			case L2R_D2U://������,���µ���
				regval|=(1<<7)|(0<<6)|(0<<5); 
				break;
			case R2L_U2D://���ҵ���,���ϵ���
				regval|=(0<<7)|(1<<6)|(0<<5); 
				break;
			case R2L_D2U://���ҵ���,���µ���
				regval|=(1<<7)|(1<<6)|(0<<5); 
				break;	 
			case U2D_L2R://���ϵ���,������
				regval|=(0<<7)|(0<<6)|(1<<5); 
				break;
			case U2D_R2L://���ϵ���,���ҵ���
				regval|=(0<<7)|(1<<6)|(1<<5); 
				break;
			case D2U_L2R://���µ���,������
				regval|=(1<<7)|(0<<6)|(1<<5); 
				break;
			case D2U_R2L://���µ���,���ҵ���
				regval|=(1<<7)|(1<<6)|(1<<5); 
				break;	 
		}
		if(lcddev.id==0X5510)dirreg=0X3600;
		else dirreg=0X36;
 		if((lcddev.id!=0X5310)&&(lcddev.id!=0X5510)&&(lcddev.id!=0X1963))regval|=0X08;//5310/5510/1963����ҪBGR   
		if(lcddev.id==0X6804)regval|=0x02;//6804��BIT6��9341�ķ���	   
		LCD_WriteReg(dirreg,regval);
		if(lcddev.id!=0X1963)//1963�������괦��
		{
			if(regval&0X20)
			{
				if(lcddev.width<lcddev.height)//����X,Y
				{
					temp=lcddev.width;
					lcddev.width=lcddev.height;
					lcddev.height=temp;
				}
			}else  
			{
				if(lcddev.width>lcddev.height)//����X,Y
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
			case L2R_U2D:					//������,���ϵ���
				regval|=(1<<5)|(1<<4)|(0<<3); 
				break;
			case L2R_D2U:					//������,���µ���
				regval|=(0<<5)|(1<<4)|(0<<3); 
				break;
			case R2L_U2D:					//���ҵ���,���ϵ���
				regval|=(1<<5)|(0<<4)|(0<<3);
				break;
			case R2L_D2U:					//���ҵ���,���µ���
				regval|=(0<<5)|(0<<4)|(0<<3); 
				break;	 
			case U2D_L2R:					//���ϵ���,������
				regval|=(1<<5)|(1<<4)|(1<<3); 
				break;
			case U2D_R2L:					//���ϵ���,���ҵ���
				regval|=(1<<5)|(0<<4)|(1<<3); 
				break;
			case D2U_L2R:					//���µ���,������
				regval|=(0<<5)|(1<<4)|(1<<3); 
				break;
			case D2U_R2L:					//���µ���,���ҵ���
				regval|=(0<<5)|(0<<4)|(1<<3); 
				break;	 
		} 
		dirreg=0X03;
		regval|=1<<12; 
		LCD_WriteReg(dirreg,regval);
	}
}     

/*******************************************************************************
 * ������  ��void LCD_DrawPoint(u16 x,u16 y)
 * ��  ��  ������
 * ��  ��  ��x,y:����
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);				//���ù��λ�� 
	LCD_WriteRAM_Prepare();		//��ʼд��GRAM
	LCD_WR_DATA(POINT_COLOR); //�˵����ɫ
}	 

/*******************************************************************************
 * ������  ��void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
 * ��  ��  �����ٻ���
 * ��  ��  ��x,y:���꣬color:��ɫ
 * ��  ��  ����
 * ����ֵ  ����
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
		if(lcddev.dir==1)x=lcddev.width-1-x;				//����ʱ����
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(x>>8);LCD_WR_DATA(x&0XFF);			 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(y>>8);LCD_WR_DATA(y&0XFF); 		
	}else
	{
 		if(lcddev.dir==1)x=lcddev.width-1-x;				//������ʵ���ǵ�תx,y����
		LCD_WriteReg(lcddev.setxcmd,x);
		LCD_WriteReg(lcddev.setycmd,y);
	}	
	LCD_RS_CLR;
 	LCD_CS_CLR; 
	DATAOUT(lcddev.wramcmd);											//дָ��  
	LCD_WR_CLR; 
	LCD_WR_SET; 
 	LCD_CS_SET; 
	LCD_WR_DATA(color);														//д����
}

/*******************************************************************************
 * ������  ��void LCD_SSD_BackLightSet(u8 pwm)
 * ��  ��  ��SSD1963 ��������
 * ��  ��  ��pwm:����ȼ�,0~100.Խ��Խ��.
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_SSD_BackLightSet(u8 pwm)
{	
	LCD_WR_REG(0xBE);					//����PWM���
	LCD_WR_DATA(0x05);				//1����PWMƵ��
//	LCD_WR_DATA(pwm*2.55);		//2����PWMռ�ձ�
	LCD_WR_DATA(0x01);				//3����C
	LCD_WR_DATA(0xFF);				//4����D
	LCD_WR_DATA(0x00);				//5����E
	LCD_WR_DATA(0x00);				//6����F
}

/*******************************************************************************
 * ������  ��void LCD_Display_Dir(u8 dir)
 * ��  ��  ������LCD��ʾ����
 * ��  ��  ��dir:0,������1,����
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_Display_Dir(u8 dir)
{
	if(dir==0)							//����
	{
		lcddev.dir=0;					//����
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
			lcddev.wramcmd=0X2C;	//����д��GRAM��ָ�� 
			lcddev.setxcmd=0X2B;	//����дX����ָ��
			lcddev.setycmd=0X2A;	//����дY����ָ��
			lcddev.width=480;			//���ÿ��480
			lcddev.height=800;		//���ø߶�800  
		}else
		{
			lcddev.wramcmd=0X22;
	 		lcddev.setxcmd=0X20;
			lcddev.setycmd=0X21;  
		}
	}else 										//����
	{	  				
		lcddev.dir=1;						//����
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
			lcddev.wramcmd=0X2C;	//����д��GRAM��ָ�� 
			lcddev.setxcmd=0X2A;	//����дX����ָ��
			lcddev.setycmd=0X2B;	//����дY����ָ��
			lcddev.width=800;			//���ÿ��800
			lcddev.height=480;		//���ø߶�480  
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
	LCD_Scan_Dir(DFT_SCAN_DIR);	//Ĭ��ɨ�跽��
}	 

/*******************************************************************************
 * ������  ��void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height)
 * ��  ��  �����ô���,���Զ����û������굽�������Ͻ�(sx,sy)
 * ��  ��  ��sx,sy:������ʼ����(���Ͻ�)��width,height:���ڿ�Ⱥ͸߶�,�������0�������С:width*height.
 * ��  ��  ����
 * ����ֵ  ����
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
	}else if(lcddev.id==0X1963)									//1963�������⴦��
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
	}else																			//��������IC
	{
		if(lcddev.dir==1)												//����
		{
			/***************����ֵ***************/
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
		hsareg=0X50;heareg=0X51;						//ˮƽ���򴰿ڼĴ���
		vsareg=0X52;veareg=0X53;						//��ֱ���򴰿ڼĴ���	   							  
		/**********���üĴ���ֵ*****************/
		LCD_WriteReg(hsareg,hsaval);
		LCD_WriteReg(heareg,heaval);
		LCD_WriteReg(vsareg,vsaval);
		LCD_WriteReg(veareg,veaval);		
		LCD_SetCursor(sx,sy);								//���ù��λ��
	}
}

/******************************************************************************************************
 * ������  ��void LCD_Init(void)
 * ��  ��  �����ô���,���Զ����û������굽�������Ͻ�(sx,sy)
 * ��  ��  ��sx,sy:������ʼ����(���Ͻ�)��width,height:���ڿ�Ⱥ͸߶�,�������0�������С:width*height.
 * ��  ��  ����
 * ����ֵ  ����
 * ע  ��  ��������ռ�ýϴ�flash,�û����Ը����Լ���ʵ�����,ɾ��δ�õ���LCD��ʼ������.�Խ�ʡ�ռ�
 ******************************************************************************************************/
void LCD_Init(void)
{ 
	__delay_ms(50); 																																									// delay 50 ms 
	LCD_WriteReg(0x0000,0x0001);
	__delay_ms(50); 																																									// delay 50 ms 
  	lcddev.id = LCD_ReadReg(0x0000);   
	if(lcddev.id<0XFF||lcddev.id==0XFFFF||lcddev.id==0X9300)																				//����ID����ȷ,����lcddev.id==0X9300�жϣ���Ϊ9341��δ����λ������»ᱻ����9300
	{	
 		/*****************����9341 ID�Ķ�ȡ ***********************/		
		LCD_WR_REG(0XD3);				   
		LCD_RD_DATA(); 									//dummy read 	
 		LCD_RD_DATA();   	    					//����0X00
  		lcddev.id=LCD_RD_DATA();   		//��ȡ93								   
 		lcddev.id<<=8;
		lcddev.id|=LCD_RD_DATA();  			//��ȡ41 	   			   
 		if(lcddev.id!=0X9341)						//��9341,�����ǲ���6804
		{	
 			LCD_WR_REG(0XBF);				   
			LCD_RD_DATA(); 								//dummy read 	 
	 		LCD_RD_DATA();   	    				//����0X01			   
	 		LCD_RD_DATA(); 								//����0XD0 			  	
	  		lcddev.id=LCD_RD_DATA();		//�������0X68 
			lcddev.id<<=8;
	  		lcddev.id|=LCD_RD_DATA();		//�������0X04	  
			if(lcddev.id!=0X6804)					//Ҳ����6804,���Կ����ǲ���NT35310
			{ 
				LCD_WR_REG(0XD4);				   
				LCD_RD_DATA(); 							//dummy read  
				LCD_RD_DATA();   						//����0X01	 
				lcddev.id=LCD_RD_DATA();		//����0X53	
				lcddev.id<<=8;	 
				lcddev.id|=LCD_RD_DATA();		//�������0X10	 
				if(lcddev.id!=0X5310)				//Ҳ����NT35310,���Կ����ǲ���NT35510
				{
					LCD_WR_REG(0XDA00);	
					LCD_RD_DATA();   					//����0X00	 
					LCD_WR_REG(0XDB00);	
					lcddev.id=LCD_RD_DATA();	//����0X80
					lcddev.id<<=8;	
					LCD_WR_REG(0XDC00);	
					lcddev.id|=LCD_RD_DATA();	//����0X00		
					if(lcddev.id==0x8000)lcddev.id=0x5510;				//NT35510���ص�ID��8000H,Ϊ��������,����ǿ������Ϊ5510
					if(lcddev.id!=0X5510)			//Ҳ����NT5510,���Կ����ǲ���SSD1963
					{
						LCD_WR_REG(0XA1);
						lcddev.id=LCD_RD_DATA();
						lcddev.id=LCD_RD_DATA();	//����0X57
						lcddev.id<<=8;	 
						lcddev.id|=LCD_RD_DATA();	//����0X61	
						if(lcddev.id==0X5761)lcddev.id=0X1963;			//SSD1963���ص�ID��5761H,Ϊ��������,����ǿ������Ϊ1963
					}
				}
			}
 		}  	
	}
// 	printf(" LCD ID:%x\r\n",lcddev.id); 									//��ӡLCD ID  
	if(lcddev.id==0X9341)																	//9341��ʼ��
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
    //LCD_WriteReg(0x0000,0x0001);//�����ڲ�ʱ��
    LCD_WriteReg(0x0001,0x0100);     
    LCD_WriteReg(0x0002,0x0700);//��Դ����                    
		//LCD_WriteReg(0x0003,(1<<3)|(1<<4) ); 	//65K  RGB
		//DRIVE TABLE(�Ĵ��� 03H)
		//BIT3=AM BIT4:5=ID0:1
		//AM ID0 ID1   FUNCATION
		// 0  0   0	   R->L D->U
		// 1  0   0	   D->U	R->L
		// 0  1   0	   L->R D->U
		// 1  1   0    D->U	L->R
		// 0  0   1	   R->L U->D
		// 1  0   1    U->D	R->L
		// 0  1   1    L->R U->D �����������.
		// 1  1   1	   U->D	L->R
		LCD_WriteReg(0x0003,(1<<12)|(3<<4)|(0<<3) );//65K    
		LCD_WriteReg(0x0004,0x0000);                                   
		LCD_WriteReg(0x0008,0x0202);	           
		LCD_WriteReg(0x0009,0x0000);         
		LCD_WriteReg(0x000a,0x0000);//display setting         
		LCD_WriteReg(0x000c,0x0001);//display setting          
		LCD_WriteReg(0x000d,0x0000);//0f3c          
		LCD_WriteReg(0x000f,0x0000);
		//��Դ����
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
		//٤��У��
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
		LCD_WriteReg(0x0050,0x0000); //ˮƽGRAM��ʼλ�� 
		LCD_WriteReg(0x0051,0x00ef); //ˮƽGRAM��ֹλ��                    
		LCD_WriteReg(0x0052,0x0000); //��ֱGRAM��ʼλ��                    
		LCD_WriteReg(0x0053,0x013f); //��ֱGRAM��ֹλ��  

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
		//������ʾ����    
		LCD_WriteReg(0x0007,0x0133); 
	}else if(lcddev.id==0x9320)//����OK.
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
		//ˮƽGRAM��ֹλ��Set X End.
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

	LCD_Display_Dir(1);		 	//Ĭ��Ϊ����
    LCD_LED;					//��������
	LCD_Clear(WHITE);
}  		  
  
/*******************************************************************************
 * ������  ��void LCD_Clear(u16 color)
 * ��  ��  ����������
 * ��  ��  ��color:Ҫ���������ɫ
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 							//�õ��ܵ���
	if((lcddev.id==0X6804)&&(lcddev.dir==1))//6804������ʱ�����⴦��  
	{						    
 		lcddev.dir=0;	 
 		lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;  	 			
		LCD_SetCursor(0x00,0x0000);						//���ù��λ��  
 		lcddev.dir=1;	 
  		lcddev.setxcmd=0X2B;
		lcddev.setycmd=0X2A;  	 
 	}else LCD_SetCursor(0x00,0x0000);				//���ù��λ�� 
	LCD_WriteRAM_Prepare();     						//��ʼд��GRAM	  	  
	for(index=0;index<totalpoint;index++)LCD_WR_DATA(color);	
}  

/*******************************************************************************
 * ������  ��void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
 * ��  ��  ����ָ�����������ָ����ɫ
 * ��  ��  �������С:(xend-xsta+1)*(yend-ysta+1) color:Ҫ���������ɫ
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
	u16 temp;
	if((lcddev.id==0X6804)&&(lcddev.dir==1))		//6804������ʱ�����⴦��  
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
		 	LCD_SetCursor(sx,i);      							//���ù��λ�� 
			LCD_WriteRAM_Prepare();     						//��ʼд��GRAM	  
			for(j=0;j<xlen;j++)LCD_WR_DATA(color);	//���ù��λ�� 	    
		}
	}
}  

/*******************************************************************************
 * ������  ��void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
 * ��  ��  ����ָ�����������ָ����ɫ
 * ��  ��  ��(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   color:Ҫ���������ɫ
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 								//�õ����Ŀ��
	height=ey-sy+1;								//�߶�
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM
		for(j=0;j<width;j++)LCD_WR_DATA(color[i*width+j]);//д������ 
	}	  
} 

/*******************************************************************************
 * ������  ��void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
 * ��  ��  ������
 * ��  ��  ��x1,y1:������꣬x2,y2:�յ�����
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; 												//������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; 									//���õ������� 
	else if(delta_x==0)incx=0;						//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;						//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )						//������� 
	{  
		LCD_DrawPoint(uRow,uCol);						//���� 
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
 * ������  ��void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
 * ��  ��  ��������
 * ��  ��  ��(x1,y1),(x2,y2):���εĶԽ�����
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

/*******************************************************************************
 * ������  ��void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
 * ��  ��  ����ָ��λ�û�һ��ָ����С��Բ
 * ��  ��  ��(x,y):���ĵ㣬r���뾶
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             								//�ж��¸���λ�õı�־
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
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									  

/*******************************************************************************
 * ������  ��void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
 * ��  ��  ����ָ��λ����ʾһ���ַ�
 * ��  ��  ��x,y:��ʼ���꣬num:Ҫ��ʾ���ַ�:" "��size:�����С 12/16/24��mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);			//�õ�����һ���ַ���Ӧ������ռ���ֽ���	
 	num=num-' ';																		//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 				//����1206����
		else if(size==16)temp=asc2_1608[num][t];			//����1608����
		else if(size==24)temp=asc2_2412[num][t];			//����2412����
		else return;																	//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=lcddev.height)return;									//��������
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=lcddev.width)return;								//��������
				break;
			}
		}  	 
	}  	    	   	 	  
}   

/*******************************************************************************
 * ������  ��u32 LCD_Pow(u8 m,u8 n)
 * ��  ��  ��m^n����
 * ��  ��  ��u8 m,u8 n
 * ��  ��  ����
 * ����ֵ  ��m^n�η�
 ******************************************************************************/
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}		

 
/*******************************************************************************
 * ������  ��void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
 * ��  ��  ����ʾ����,��λΪ0,����ʾ
 * ��  ��  ��x,y :������꣬len :���ֵ�λ����size:�����С��num:��ֵ(0~4294967295)
 * ��  ��  ����
 * ����ֵ  ����
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
 * ������  ��void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
 * ��  ��  ����ʾ����,��λΪ0,������ʾ
 * ��  ��  ��x,y :������꣬num:��ֵ(0~999999999)��len :���ֵ�λ����size:�����С��mode:
*        [7]:0,�����;1,���0��[6:1]:������[0]:0,�ǵ�����ʾ;1,������ʾ
 * ��  ��  ����
 * ����ֵ  ��m^n�η�
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
 * ������  ��void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
 * ��  ��  ����ʾ�ַ���
 * ��  ��  ��x,y:������꣬width,height:�����С��size:�����С��*p:�ַ�����ʼ��ַ 
 * ��  ��  ����
 * ����ֵ  ����
 ******************************************************************************/
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))			//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;					//�˳�
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}






























