#include "AT89X52.H"
//********************** functions ***************************
//********************** Parameter ***************************
sfr  Data=0x80;//P0資料
sfr  LEDScan=0x90;//P1資料
sfr  CScan=0xA0;//P2資料
char code Column_Scan[4]= {0xFE,0xFD,0xFB,0xF7};
char code Seg_Row_Data[16]= { 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98,0x88,0x83,0xC6,0xA1,0x86,0x8E};
int i=0,TEMP=0,Key_Scan,LED_TEMP[4]={0,0,0,0,};
main() 
{
  int k=0,deTime=0;
   while(1){
		LEDScan=0xFF; 			
	  Data=Seg_Row_Data[LED_TEMP[i]];
    LEDScan=Column_Scan[i];
    Key_Scan=CScan&0x0F;
	  if(deTime!=0)deTime--; 
    if((Key_Scan!=0x0F)&&(deTime==0)){		
      deTime=5000;
    	LED_TEMP[3]=LED_TEMP[2];
    	LED_TEMP[2]=LED_TEMP[1];
    	LED_TEMP[1]=LED_TEMP[0];
    	if (Key_Scan==0x07) {
        	LED_TEMP[0]=i*4;
		  }
        else if(Key_Scan==0x0B){
        	LED_TEMP[0]=i*4+1;
		  } 
        else if(Key_Scan==0x0D){
        	LED_TEMP[0]=i*4+2;
		  } 
        else if(Key_Scan==0x0E){
        	LED_TEMP[0]=i*4+3;
		  }
	  }  
    i++;if(i==4)i=0; 
   } 
}