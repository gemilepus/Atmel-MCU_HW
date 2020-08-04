#include "AT89X52.H"
#include "bin.c"
//********************** functions ***************************
//********************** Parameter ***************************
sfr  Data=0x80;//P0���
sfr  LEDScan=0x90;//P1���
sfr  CScan=0xA0;//P2���
char code Column_Scan[4]= {0xFE,0xFD,0xFB,0xF7};
char code Seg_Row_Data[16]= { 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98,0x88,0x83,0xC6,0xA1,0x86,0x8E};
int i=0,TEMP=0,LED_TEMP[4]={0,0,0,0},Key_Data=0,Commandkey=0,deTime=0;
int NumericalA=0,NumericalB=0,TotalNum=0,CommandTemp=0,Comadd=0,Key_T;
char Key_Scan;
sbit RS=0x96;  //P16 LCD���O/��Ʊ���,RS=0���O�ARS=1���
               //LCDŪ��/�g�J����,R/W=GND�g�J
sbit EN=0x97;  //P17 LCD�P���X,EN=0�T��LCD�AEN=1�P��LCD

main() 
{
	
   SCON = 0x50;     //�]�wUART��C�ǿ鬰MODE1�έP�౵��
   TMOD = 0x20;     //�]�wTIMER1��MODE2
   TH1=TL1=256-(28800/9600);  //�]�p�ɾ��M�w��C�ǿ��j�v
   TR1 = 1;          //�}�l�p��
   
   LCD_init();     	// ���m�βM��LCD
   LCD_Cmd(0x80);     //��ХѲĤ@��}�l���    
   while(1){
	LEDScan=0xFF; 			
	Data=Seg_Row_Data[LED_TEMP[i]];
    LEDScan=Column_Scan[i];
		 
	if(RI==1){		 
	RI=0; 
	 // if(deTime!=0)deTime--; 
     //if(Key_Scan!=0x0F){		
     // deTime=5000;

		Key_Scan=SBUF;
		Key_Scan=(Key_Scan+'0');
		//LCD_Data(Key_Scan);		
        
					 if(Key_Scan=='a'){Key_Data=1;Key_T=1;}
					 if(Key_Scan=='b'){Key_Data=2;Key_T=1;}
					 if(Key_Scan=='c'){Key_Data=3;Key_T=1;}
					 if(Key_Scan=='d'){Key_Data=4;Key_T=1;}
					 if(Key_Scan=='e'){Key_Data=5;Key_T=1;}
					 if(Key_Scan=='f'){Key_Data=6;Key_T=1;}
					 if(Key_Scan=='g'){Key_Data=7;Key_T=1;}
					 if(Key_Scan=='h'){Key_Data=8;Key_T=1;}
					 if(Key_Scan=='i'){Key_Data=9;Key_T=1;}
					 if(Key_Scan=='`'){Key_Data=0;Key_T=1;}
				   if(Key_T==1){	 
				        LED_TEMP[3]=LED_TEMP[2];
    	                LED_TEMP[2]=LED_TEMP[1];
    	                LED_TEMP[1]=LED_TEMP[0];
				        LED_TEMP[0]=Key_Data;
                LCD_Data(Key_Data+'0');
                SBUF=Key_Data+'0';while(TI==0); TI=0;					
        }
		
		    	     if(Key_Scan=='['){Commandkey=12;}
					 if(Key_Scan==']'){Commandkey=13;}
					 if(Key_Scan=='Z'){Commandkey=14;}
					 if(Key_Scan=='_'){Commandkey=15;}
					 if(Key_Scan=='='){Commandkey=10;}
					 if(Key_Scan=='^'){Commandkey=11;}
        
    Key_T=0;
	 //} 		 
    }
		 
		if(Commandkey!=0){
			if(Commandkey!=10){
			 if(Commandkey==12 || Commandkey==13 || Commandkey==14 || Commandkey==15){
			   if(Commandkey==12){ LCD_Data('+'); SBUF='+';while(TI==0); TI=0;		}
			   if(Commandkey==13){ LCD_Data('-'); SBUF='-';while(TI==0); TI=0;		}
			   if(Commandkey==14){ LCD_Data('*'); SBUF='*';while(TI==0); TI=0;		}
			   if(Commandkey==15){ LCD_Data('/'); SBUF='/';while(TI==0); TI=0;		}
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
                          if(Commandkey==12){ CommandTemp=1;}
			              if(Commandkey==13){ CommandTemp=2;}
			              if(Commandkey==14){ CommandTemp=3;}
			              if(Commandkey==15){ CommandTemp=4;} 						
                    }
				    else{
					      if(Commandkey==12){ CommandTemp=1;}
			              if(Commandkey==13){ CommandTemp=2;}
			              if(Commandkey==14){ CommandTemp=3;}
			              if(Commandkey==15){ CommandTemp=4;}
                          NumericalA=LED_TEMP[3]*1000+LED_TEMP[2]*100+LED_TEMP[1]*10+LED_TEMP[0];	
                          LED_TEMP[0]=LED_TEMP[1]=LED_TEMP[2]=LED_TEMP[3]=0;						 
				    }   			 
               }
            }
		    if(Commandkey==11){
			   NumericalA=NumericalB=TotalNum=CommandTemp=0;
               LED_TEMP[0]=LED_TEMP[1]=LED_TEMP[2]=LED_TEMP[3]=0;
		       LCD_Cmd(0x01); //�M����ܹ�  
               LCD_Cmd(0x02); //��Ц^��� 
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
					 SBUF='=';while(TI==0); TI=0;
					 if(TotalNum<0){LCD_Data('-');SBUF='-';while(TI==0); TI=0;TotalNum=TotalNum*(-1);}
					 if(TotalNum>=1000){LCD_Data(TotalNum/1000+'0');}
					 if(TotalNum>=100){LCD_Data(TotalNum%1000 / 100+'0');}
					 if(TotalNum>=10){LCD_Data(TotalNum%100 / 10+'0');}	
					 LCD_Data(TotalNum%10+'0');	
				   LED_TEMP[3]=TotalNum/1000;
                   LED_TEMP[2]=TotalNum%1000 / 100;
                   LED_TEMP[1]=TotalNum%100 / 10;
                   LED_TEMP[0]=TotalNum%10; 

				   if(TotalNum>=1000){SBUF=(TotalNum/1000+'0');while(TI==0); TI=0; }
				   if(TotalNum>=100){SBUF=(TotalNum%1000 / 100+'0');while(TI==0); TI=0; }
				   if(TotalNum>=10){SBUF=(TotalNum%100 / 10+'0');while(TI==0); TI=0; }	
				   SBUF=(TotalNum%10+'0');while(TI==0); TI=0;
       }				 			 
			 Commandkey=0;
    }			
    i++;if(i==4)i=0; 
   } 
}

/***********************************************************
*��ƦW��: LCD_Data
*�\��y�z: �ǰe��ƨ��r��LCD
*��J�ѼơGdat
************************************************************/
void LCD_Data(char dat)  //�ǰe��ƨ�LCD
{
    Data=dat; //��ưe��BUS
    RS=1;  EN=1;//��Ƽg�J��LCD��
    Delay_ms(1);   //LCD���ݼg�J����
    EN=0;          //�T��LCD    
}
/***************************************************************
*��ƦW��: LCD_Cmd
*�\��y�z: �ǰe�R�O���r��LCD
*��J�ѼơGCmd
************************************************************/
void LCD_Cmd(unsigned char Cmd) //�ǰe�R�O��LCD
{
    Data=Cmd;  //�R�O�e��BUS
    RS=0;   EN=1; //�R�O�g�J��LCD��
    Delay_ms(1);    //LCD���ݼg�J����     
    EN=0;           //�T��LCD
}
/***************************************************************
*��ƦW��: LCD_init
*�\��y�z: �ҩl�Ƥ�r��LCD
*****************************************************************/
void LCD_init(void)    //LCD���ҩl�{��  
{
    LCD_Cmd(0x38);/*0011 1000,8bit�ǿ�,���2��,5*7�r��
                    bit4:DL=1,8bit�ǿ�,
                    bit3:N=1,���2��
                    bit2:F=0,5*7�r��*/    
    LCD_Cmd(0x0c);/*0000 1100,��ܹ�ON,����ܴ��,��Ф��{�{
                    bit2:D=1,��ܹ�ON
                    bit1:C=0,����ܴ��
	                  bit0:B=0,��Ф��{�{*/
    LCD_Cmd(0x06);/*0000 0110,//��ܧ���Хk��,��в���T�� 
                    bit1:I/D=1,��ܧ���Хk��,
                    bit0:S=0,��в���T��*/  
    LCD_Cmd(0x01); //�M����ܹ�  
    LCD_Cmd(0x02); //��Ц^���  
}
