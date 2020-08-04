/*******KEY4.C**********************
*�ʧ@�G�bLCD���"KEY="�A�����LCD���4���
*���}�G�CROW0=P10,ROW1=P11,ROW2=P12,ROW3=P13,ROW4=P14 
*      ��COL0=P20,COL1=P21,COL2=P22,COL3=P23 
*      P0=LCD��Data�AP16=RS�ARW=GND�AP17=EN
*****************************************/
#include "AT89X52.H"   //�Ȧs���βպA�w�q
#define T  10000 //����10000uS
//#define T  10000*110592/120000 //�W�v��12MHz�אּ11.0592MHz
sfr  Data=0x80;//P0���BUS��X
sbit RS=0x96;  //P16 LCD���O/��Ʊ���,RS=0���O�ARS=1���
               //LCDŪ��/�g�J����,R/W=GND�g�J
sbit EN=0x97;  //P17 LCD�P���X,EN=0�T��LCD�AEN=1�P��LCD
void dataout(void); //�����ƿ�X
int sec=0,min=10,hor=12;
int TIMEONOFF=1,deTime=0,secd=0;
main()
{
	LCD_init();     	// ���m�βM��LCD
  LCD_Cmd(0x80);    //��ХѲĤ@��}�l���  
  TMOD=0x10;  /*0001 0000,�]�wTimer1��mode1�����p��
               bit7:GATE=0,���ϥ�INT1�}����
			         bit6:C/T=0,�����p��
			         bit5-4:MODE=01�Amode1 */
	TL1= (65536-T) % 256; //�N�C8-bit�p�ƭȦs�JTL1 
  TH1= (65536-T) / 256; //�N��8-bit�p�ƭȦs�JTH1
  TR1=1;        //�Ұ�Timer1   //10000uS
  dataout();//LCD ��� 	
   while(1)    //���_�`������ 
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
			 if(TF1==1){  //���ݷ���A�YTF1=0�ۧڴ`��
				  TF1=0;      //�Y�p�ɷ���TF1=1�A�M��TF1=0
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
*��ƦW��: dataout
*�\��y�z: �����X��ưe��LCD��ܼƦr�A�ˬd�O�_��}����
*��J�ѼơGkeyout
************************************************************/      
void dataout(void) 
{    
    LCD_Cmd(0x80);        //�ѲĤ@��}�l��� 
    LCD_Data(hor/10+'0'); //�ɪ��Q��ƨ�LCD���
    LCD_Data(hor%10+'0'); //�ɪ��Ӧ�ƨ�LCD���
    LCD_Data(':');
    
    LCD_Data(min/10+'0'); //�����Q��ƨ�LCD���
    LCD_Data(min%10+'0'); //�����Ӧ�ƨ�LCD���
    LCD_Data(':');
    
    LCD_Data(sec/10+'0'); //���Q��ƨ�LCD���
    LCD_Data(sec%10+'0'); //���Ӧ�ƨ�LCD���
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
