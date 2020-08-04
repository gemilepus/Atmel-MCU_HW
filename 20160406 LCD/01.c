/*******KEY4.C**********************
*�ʧ@�G�bLCD���"KEY="�A�����LCD���4���
*���}�G�CROW0=P10,ROW1=P11,ROW2=P12,ROW3=P13,ROW4=P14 
*      ��COL0=P20,COL1=P21,COL2=P22,COL3=P23 
*      P0=LCD��Data�AP16=RS�ARW=GND�AP17=EN
*****************************************/
#include "AT89X52.H"   //�Ȧs���βպA�w�q
sfr  Data=0x80;//P0���BUS��X
sbit RS=0x96;  //P16 LCD���O/��Ʊ���,RS=0���O�ARS=1���
               //LCDŪ��/�g�J����,R/W=GND�g�J
sbit EN=0x97;  //P17 LCD�P���X,EN=0�T��LCD�AEN=1�P��LCD
char  Table[16]="U0322310U0322337"; //�}�C�r��
void dataout(int k); //�����ƿ�X
//char Table_TEMP;  //LCD��ܦ�m
int k=0;
void main()
{
 int deTime=0;
 LCD_init();     	// ���m�βM��LCD
 LCD_Cmd(0x80);     //��ХѲĤ@��}�l���   
 dataout(k=0); 
 while(1)   //���а���
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
*��ƦW��: dataout
*�\��y�z: �����X��ưe��LCD��ܼƦr�A�ˬd�O�_��}����
*��J�ѼơGkeyout
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
