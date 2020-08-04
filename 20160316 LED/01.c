#include "AT89X52.H"
//********************** functions ***************************
//********************** Parameter ***************************
sfr  Data=0x80;//P0資料BUS輸出
sbit SSLED0=0x90; //P10七段顯示器個位數選擇輸出
sbit SSLED1=0x91; //P11七段顯示器十位數選擇輸出
sbit SSLED2=0x92; //P12七段顯示器百位數選擇輸出
sbit SSLED3=0x93; //P13七段顯示器千位數選擇輸出
 unsigned char code Table[] //0~F數碼資料
  ={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
 main() 
{
  unsigned char scan;      //掃描次數  
  unsigned int count[2]={2337,2310}; //計數十進制初值 
  unsigned char i;    //擷取計數的個、十、百、千位數 
  int k=0,deTime=0;
   while(1)     //重覆執行
    {
			if(deTime!=0){deTime--;}
			if((P3_2!=1)&&(deTime==0)){	
			 k++;
			 if(k>=2){k=0;} 
			 deTime=200;
      }   
       SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒
	     i=count[k] % 10;   //取出個位數
       Data=~Table[i]; //讀取個位數碼資料輸出
       SSLED0=0;        //選擇個位數顯示器
       Delay_ms(1);    //掃描延時  
	     SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒           
       i=(count[k] % 100)/10; //取出十位數 k
       Data=~Table[i];//讀取十位數碼資料輸出
       SSLED1=0;       //選擇十位數顯示器
       Delay_ms(1);   //掃描延時                 
       SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒
	     i=(count[k] % 1000)/100; //取出百位數
       Data=~Table[i]; //讀取百位數碼資料輸出
       SSLED2=0;       //選擇百位數顯示器
       Delay_ms(1);    //掃描延時
	     SSLED0=SSLED1=SSLED2=SSLED3=1; //遮沒
       i=count[k]/1000;  //取出千位數
       Data=~Table[i]; //讀取千位數碼資料輸出
       SSLED3=0;        //選擇千位數顯示器
       Delay_ms(1);    //掃描延時
   } 
}