/*******KEY4.C**********************
*動作：在LCD顯示"KEY="，按鍵由LCD顯示4位數
*接腳：列ROW0=P10,ROW1=P11,ROW2=P12,ROW3=P13,ROW4=P14 
*      行COL0=P20,COL1=P21,COL2=P22,COL3=P23 
*      P0=LCD的Data，P16=RS，RW=GND，P17=EN
*****************************************/
#include "AT89X52.H"   //暫存器及組態定義
sfr  Data=0x80;//P0資料BUS輸出
sbit RS=0x96;  //P16 LCD指令/資料控制,RS=0指令，RS=1資料
               //LCD讀取/寫入控制,R/W=GND寫入
sbit EN=0x97;  //P17 LCD致能輸出,EN=0禁能LCD，EN=1致能LCD
char  Table[16]="U0322310U0322337"; //陣列字元
void dataout(int k); //按鍵資料輸出
//char Table_TEMP;  //LCD顯示位置
int k=0;
void main()
{
 int deTime=0;
 LCD_init();     	// 重置及清除LCD
 LCD_Cmd(0x80);     //游標由第一行開始顯示   
 dataout(k=0); 
 while(1)   //重覆執行
 {
		if(deTime!=0){deTime--;}
		if((P3_2!=1)&&(deTime==0)){	
			  k++;
			  if(k>=2){k=0;} 	
				dataout(k);
			  deTime=18000;
    }
  }
}
/***********************************************************
*函數名稱: dataout
*功能描述: 按鍵輸出資料送到LCD顯示數字，檢查是否放開按鍵
*輸入參數：keyout
************************************************************/
void dataout(int k) 
{ 
	int j,r,s;
	if(k==0){r=0;s=8;}
  if(k==1){r=8;s=0;}
	 for(j=r+0; j<=r+7; j++)
	 { 
	   LCD_Data(Table[j]);
   }
	 LCD_Cmd(0xA9);
	for(j=s+0; j<=s+7; j++)
	{
	  LCD_Data(Table[j]);
  }
	LCD_Cmd(0x80);
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
