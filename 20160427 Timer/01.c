/*******KEY4.C**********************
*動作：在LCD顯示"KEY="，按鍵由LCD顯示4位數
*接腳：列ROW0=P10,ROW1=P11,ROW2=P12,ROW3=P13,ROW4=P14 
*      行COL0=P20,COL1=P21,COL2=P22,COL3=P23 
*      P0=LCD的Data，P16=RS，RW=GND，P17=EN
*****************************************/
#include "AT89X52.H"   //暫存器及組態定義
#define T  10000 //延時10000uS
//#define T  10000*110592/120000 //頻率由12MHz改為11.0592MHz
sfr  Data=0x80;//P0資料BUS輸出
sbit RS=0x96;  //P16 LCD指令/資料控制,RS=0指令，RS=1資料
               //LCD讀取/寫入控制,R/W=GND寫入
sbit EN=0x97;  //P17 LCD致能輸出,EN=0禁能LCD，EN=1致能LCD
void dataout(void); //按鍵資料輸出
int sec=0,min=10,hor=12;
int TIMEONOFF=1,deTime=0,secd=0;
main()
{
	LCD_init();     	// 重置及清除LCD
  LCD_Cmd(0x80);    //游標由第一行開始顯示  
  TMOD=0x10;  /*0001 0000,設定Timer1為mode1內部計時
               bit7:GATE=0,不使用INT1腳控制
			         bit6:C/T=0,內部計時
			         bit5-4:MODE=01，mode1 */
	TL1= (65536-T) % 256; //將低8-bit計數值存入TL1 
  TH1= (65536-T) / 256; //將高8-bit計數值存入TH1
  TR1=1;        //啟動Timer1   //10000uS
  dataout();//LCD 顯示 	
   while(1)    //不斷循環執行 
   {
		if(deTime!=0){deTime--;}
		if((P3_2!=1)&&(deTime==0)){
       if(TIMEONOFF==0){
				 TIMEONOFF=1;
       }
       else{
				 TIMEONOFF=0;
       }			 
			 deTime=9000;
    }
		if((P3_3!=1)&&(deTime==0)){
        TIMEONOFF=0;
		    sec=0;min=0;hor=0; 
				deTime=9000;
			  dataout();
    }		
     if(TIMEONOFF==1){ 
			 if(TF1==1){  //等待溢位，若TF1=0自我循環
				  TF1=0;      //若計時溢位TF1=1，清除TF1=0
				  secd++;
			 }
			 if(secd==20){
					sec++;
          if(sec>59){sec=0;min++;}
				  if(min>59){min=0;hor++;}
				  if(hor>23){hor=0;}
	        dataout();
					secd=0;
       }					
			}
	 }
}		   
/***********************************************************
*函數名稱: dataout
*功能描述: 按鍵輸出資料送到LCD顯示數字，檢查是否放開按鍵
*輸入參數：keyout
************************************************************/      
void dataout(void) 
{    
    LCD_Cmd(0x80);        //由第一行開始顯示 
    LCD_Data(hor/10+'0'); //時的十位數到LCD顯示
    LCD_Data(hor%10+'0'); //時的個位數到LCD顯示
    LCD_Data(':');
    
    LCD_Data(min/10+'0'); //分的十位數到LCD顯示
    LCD_Data(min%10+'0'); //分的個位數到LCD顯示
    LCD_Data(':');
    
    LCD_Data(sec/10+'0'); //秒的十位數到LCD顯示
    LCD_Data(sec%10+'0'); //秒的個位數到LCD顯示
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
