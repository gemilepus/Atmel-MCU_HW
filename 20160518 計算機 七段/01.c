#include "AT89X52.H"
#include "bin.c"
//********************** functions ***************************
//********************** Parameter ***************************
sfr  Data=0x80;//P0資料
sfr  LEDScan=0x90;//P1資料
sfr  CScan=0xA0;//P2資料
void delay_1ms(int count);
void LEDTypeLoad(void);
void LEDTypeError(void);
char code Column_Scan[4]= {0xFE,0xFD,0xFB,0xF7};
char code Seg_Row_Data[16]= { 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98,0x88,0x83,0xC6,0xA1,0x86,0x8E};
int i=0,TEMP=0,Key_Scan,LED_TEMP[4]={0,0,0,0,},Key_Data=0,Commandkey=0;
int NumericalA=0,NumericalB=0,TotalNum=0,CommandTemp=0,CommandTemp2=0;
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
      }
			else{
				Commandkey=Key_Data;

      }
	  }  
		if(Commandkey!=0){
			if(Commandkey!=10){
			 if(Commandkey==12){// +
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
              CommandTemp=0;						
           }
					 else{
						 CommandTemp=1;
             NumericalA=LED_TEMP[3]*1000+LED_TEMP[2]*100+LED_TEMP[1]*10+LED_TEMP[0];	
             LED_TEMP[0]=LED_TEMP[1]=LED_TEMP[2]=LED_TEMP[3]=0;						 
				   }   			 
       }	
			 if(Commandkey==13){// -
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
              CommandTemp=0;						
           }
					 else{
						 CommandTemp=2;
             NumericalA=LED_TEMP[3]*1000+LED_TEMP[2]*100+LED_TEMP[1]*10+LED_TEMP[0];	
             LED_TEMP[0]=LED_TEMP[1]=LED_TEMP[2]=LED_TEMP[3]=0;						 
				   }   			 
       }	 
			 if(Commandkey==14){// *
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
              CommandTemp=0;						
           }
					 else{
						 CommandTemp=3;
             NumericalA=LED_TEMP[3]*1000+LED_TEMP[2]*100+LED_TEMP[1]*10+LED_TEMP[0];	
             LED_TEMP[0]=LED_TEMP[1]=LED_TEMP[2]=LED_TEMP[3]=0;						 
				   }   			  
       }	
			 if(Commandkey==15){//
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
              CommandTemp=0;						
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
					TotalNum=NumericalA;
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
//
void LEDTypeLoad(void){
	int f;
	for(f=3;f>=0;f--){
		LEDScan=Column_Scan[f];
			  Data=B1111_1011;delay_1ms(100);
        Data=B1111_1101;delay_1ms(100);
        Data=B1111_1110;delay_1ms(100);
        Data=B1101_1111;delay_1ms(100);
        Data=B1110_1111;delay_1ms(100);
        Data=B1111_1111;delay_1ms(100);
        Data=B0111_1111;delay_1ms(100);	
     }
}
/*void LEDTypeError(void){
	char code Errortype[13]={0xFF,0xFF,0xFF,0xFF,0x86,0xAF,0xAF,0xA3,0xAF,0xFF,0xFF,0xFF,0xFF};
	int i=0,j=0,k=3,deTime1=0;
	while(1) {
	  LEDScan=0xFF;
	  Data=Errortype[j+k];
    LEDScan=Column_Scan[i];
    deTime1++;
    if(deTime1==6000){
       j++;
	     deTime1=0;	
	  }
    if(j==10)break;
    i++;if(i==4)i=0;
    k--;if(k==-1)k=3;
	}
}*/

