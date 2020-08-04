#include "AT89X52.H"
#include "bin.c"
//********************** functions ***************************
//********************** Parameter ***************************
sfr  Data=0x80;//P0資料
sfr  LEDScan=0x90;//P1資料
sfr  CScan=0xA0;//P2資料
char code Column_Scan[4]= {0xFE,0xFD,0xFB,0xF7};
char code Seg_Row_Data[16]= { 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98,0x88,0x83,0xC6,0xA1,0x86,0x8E};
int i=0,TEMP=0,Key_Scan,LED_TEMP[4]={0,0,0,0,},Key_Data=0,Commandkey=0,deTime=0;
int NumericalA=0,NumericalB=0,TotalNum=0,CommandTemp=0,Comadd=0;
sbit RS=0x96;  //P16 LCD指令/資料控制,RS=0指令，RS=1資料
               //LCD讀取/寫入控制,R/W=GND寫入
sbit EN=0x97;  //P17 LCD致能輸出,EN=0禁能LCD，EN=1致能LCD
main() 
{
	LCD_init();     	// 重置及清除LCD
  LCD_Cmd(0x80);     //游標由第一行開始顯示    
   while(1){
		LEDScan=0xFF; 			
	  Data=Seg_Row_Data[LED_TEMP[i]];
    LEDScan=Column_Scan[i];
    Key_Scan=CScan&0x0F;
	  if(deTime!=0)deTime--; 
    if((Key_Scan!=0x0F)&&(deTime==0)){		
      deTime=5000;
    	if (Key_Scan==0x07) {
        	Key_Data=i*4;
		  }
        else if(Key_Scan==0x0B){
        	Key_Data=i*4+1;
		  } 
        else if(Key_Scan==0x0D){
        	Key_Data=i*4+2;
		  } 
        else if(Key_Scan==0x0E){
        	Key_Data=i*4+3;
		  }
			
      if(Key_Data<10){
				 LED_TEMP[3]=LED_TEMP[2];
    	   LED_TEMP[2]=LED_TEMP[1];
    	   LED_TEMP[1]=LED_TEMP[0];
				 LED_TEMP[0]=Key_Data;
         LCD_Data(Key_Data+'0');				
      }
			else{
				Commandkey=Key_Data;

      }
	  }  
		if(Commandkey!=0){
			if(Commandkey!=10){
			 if(Commandkey==12){// +
				 LCD_Data('+');	
				   if(CommandTemp!=0){
						  NumericalB=LED_TEMP[3]*1000+LED_TEMP[2]*100+LED_TEMP[1]*10+LED_TEMP[0];
						  LED_TEMP[0]=LED_TEMP[1]=LED_TEMP[2]=LED_TEMP[3]=0;
						  if(CommandTemp==1){
								  NumericalA=NumericalA+NumericalB;
              }	
						  if(CommandTemp==2){
								  NumericalA=NumericalA-NumericalB;
              }	
						  if(CommandTemp==3){
								  NumericalA=NumericalA*NumericalB;
              }			
						  if(CommandTemp==4){
								  NumericalA=NumericalA/NumericalB;
              }
              CommandTemp=1;						
           }
					 else{
						 CommandTemp=1;
             NumericalA=LED_TEMP[3]*1000+LED_TEMP[2]*100+LED_TEMP[1]*10+LED_TEMP[0];	
             LED_TEMP[0]=LED_TEMP[1]=LED_TEMP[2]=LED_TEMP[3]=0;						 
				   }   			 
       }	
			 if(Commandkey==13){// -
				  LCD_Data('-');	
				   if(CommandTemp!=0){
						  NumericalB=LED_TEMP[3]*1000+LED_TEMP[2]*100+LED_TEMP[1]*10+LED_TEMP[0];
						  LED_TEMP[0]=LED_TEMP[1]=LED_TEMP[2]=LED_TEMP[3]=0;
						  if(CommandTemp==1){
								  NumericalA=NumericalA+NumericalB;
              }
						  if(CommandTemp==2){
								  NumericalA=NumericalA-NumericalB;
              }	
						  if(CommandTemp==3){
								  NumericalA=NumericalA*NumericalB;
              }			
						  if(CommandTemp==4){
								  NumericalA=NumericalA/NumericalB;
              }
              CommandTemp=2;						
           }
					 else{
						 CommandTemp=2;
             NumericalA=LED_TEMP[3]*1000+LED_TEMP[2]*100+LED_TEMP[1]*10+LED_TEMP[0];	
             LED_TEMP[0]=LED_TEMP[1]=LED_TEMP[2]=LED_TEMP[3]=0;						 
				   }   			 
       }	 
			 if(Commandkey==14){// *
				 LCD_Data('*');	
				   if(CommandTemp!=0){
						  NumericalB=LED_TEMP[3]*1000+LED_TEMP[2]*100+LED_TEMP[1]*10+LED_TEMP[0];
						  LED_TEMP[0]=LED_TEMP[1]=LED_TEMP[2]=LED_TEMP[3]=0;
						  if(CommandTemp==1){
								  NumericalA=NumericalA+NumericalB;
              }	
						  if(CommandTemp==2){
								  NumericalA=NumericalA-NumericalB;
              }	
						  if(CommandTemp==3){
								  NumericalA=NumericalA*NumericalB;
              }			
						  if(CommandTemp==4){
								  NumericalA=NumericalA/NumericalB;
              }
              CommandTemp=3;						
           }
					 else{
						 CommandTemp=3;
             NumericalA=LED_TEMP[3]*1000+LED_TEMP[2]*100+LED_TEMP[1]*10+LED_TEMP[0];	
             LED_TEMP[0]=LED_TEMP[1]=LED_TEMP[2]=LED_TEMP[3]=0;						 
				   }   			  
       }	
			 if(Commandkey==15){//
				 LCD_Data('/');	
				  if(CommandTemp!=0){
						  NumericalB=LED_TEMP[3]*1000+LED_TEMP[2]*100+LED_TEMP[1]*10+LED_TEMP[0];
						  LED_TEMP[0]=LED_TEMP[1]=LED_TEMP[2]=LED_TEMP[3]=0;
						  if(CommandTemp==1){
								  NumericalA=NumericalA+NumericalB;
              }	
						  if(CommandTemp==2){
								  NumericalA=NumericalA-NumericalB;
              }	
						  if(CommandTemp==3){
								  NumericalA=NumericalA*NumericalB;
              }		
						  if(CommandTemp==4){
								  NumericalA=NumericalA/NumericalB;
              }
              CommandTemp=4;						
           }
					 else{
						 CommandTemp=4;
             NumericalA=LED_TEMP[3]*1000+LED_TEMP[2]*100+LED_TEMP[1]*10+LED_TEMP[0];	
             LED_TEMP[0]=LED_TEMP[1]=LED_TEMP[2]=LED_TEMP[3]=0;						 
				   }   			 
       }	
		   if(Commandkey==11){
				  NumericalA=NumericalB=TotalNum=CommandTemp=0;
          LED_TEMP[0]=LED_TEMP[1]=LED_TEMP[2]=LED_TEMP[3]=0;
				    LCD_Cmd(0x01); //清除顯示幕  
            LCD_Cmd(0x02); //游標回原位 
	    
       }
		 }
		   if(Commandkey==10){
				  	
				   if(CommandTemp!=0){
						  NumericalB=LED_TEMP[3]*1000+LED_TEMP[2]*100+LED_TEMP[1]*10+LED_TEMP[0];
						  if(CommandTemp==1){
								  NumericalA=NumericalA+NumericalB;
              }	
						  if(CommandTemp==2){
								  NumericalA=NumericalA-NumericalB;
              }	
						  if(CommandTemp==3){
								  NumericalA=NumericalA*NumericalB;
              }			
						  if(CommandTemp==4){
								  NumericalA=NumericalA/NumericalB;
              }
              CommandTemp=0;						
           } 
					 TotalNum=NumericalA;
					 LCD_Cmd(0xA9);
					 LCD_Data('=');
					 if(TotalNum<0){LCD_Data('-');TotalNum=TotalNum*(-1);}
					 if(TotalNum>=1000){LCD_Data(TotalNum/1000+'0');}
					 if(TotalNum>=100){LCD_Data(TotalNum%1000 / 100+'0');}
					 if(TotalNum>=10){LCD_Data(TotalNum%100 / 10+'0');}	
					 LCD_Data(TotalNum%10+'0');	
				   LED_TEMP[3]=TotalNum/1000;
           LED_TEMP[2]=TotalNum%1000 / 100;
           LED_TEMP[1]=TotalNum%100 / 10;
           LED_TEMP[0]=TotalNum%10;   
       }				 			 
			 Commandkey=0;
    }			
    i++;if(i==4)i=0; 
   } 
}

/***********************************************************
*函數名稱: LCD_Data
*功能描述: 傳送資料到文字型LCD
*輸入參數：dat
************************************************************/
void LCD_Data(char dat)  //傳送資料到LCD
{
    Data=dat; //資料送到BUS
    RS=1;  EN=1;//資料寫入到LCD內
    Delay_ms(1);   //LCD等待寫入完成
    EN=0;          //禁能LCD    
}
/***************************************************************
*函數名稱: LCD_Cmd
*功能描述: 傳送命令到文字型LCD
*輸入參數：Cmd
************************************************************/
void LCD_Cmd(unsigned char Cmd) //傳送命令到LCD
{
    Data=Cmd;  //命令送到BUS
    RS=0;   EN=1; //命令寫入到LCD內
    Delay_ms(1);    //LCD等待寫入完成     
    EN=0;           //禁能LCD
}
/***************************************************************
*函數名稱: LCD_init
*功能描述: 啟始化文字型LCD
*****************************************************************/
void LCD_init(void)    //LCD的啟始程式  
{
    LCD_Cmd(0x38);/*0011 1000,8bit傳輸,顯示2行,5*7字型
                    bit4:DL=1,8bit傳輸,
                    bit3:N=1,顯示2行
                    bit2:F=0,5*7字型*/    
    LCD_Cmd(0x0c);/*0000 1100,顯示幕ON,不顯示游標,游標不閃爍
                    bit2:D=1,顯示幕ON
                    bit1:C=0,不顯示游標
	                  bit0:B=0,游標不閃爍*/
    LCD_Cmd(0x06);/*0000 0110,//顯示完游標右移,游標移位禁能 
                    bit1:I/D=1,顯示完游標右移,
                    bit0:S=0,游標移位禁能*/  
    LCD_Cmd(0x01); //清除顯示幕  
    LCD_Cmd(0x02); //游標回原位  
}