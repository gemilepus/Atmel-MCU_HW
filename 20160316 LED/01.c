#include "AT89X52.H"
//********************** functions ***************************
//********************** Parameter ***************************
sfr  Data=0x80;//P0���BUS��X
sbit SSLED0=0x90; //P10�C�q��ܾ��Ӧ�ƿ�ܿ�X
sbit SSLED1=0x91; //P11�C�q��ܾ��Q��ƿ�ܿ�X
sbit SSLED2=0x92; //P12�C�q��ܾ��ʦ�ƿ�ܿ�X
sbit SSLED3=0x93; //P13�C�q��ܾ��d��ƿ�ܿ�X
 unsigned char code Table[] //0~F�ƽX���
  ={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
 main() 
{
  unsigned char scan;      //���y����  
  unsigned int count[2]={2337,2310}; //�p�ƤQ�i���� 
  unsigned char i;    //�^���p�ƪ��ӡB�Q�B�ʡB�d��� 
  int k=0,deTime=0;
   while(1)     //���а���
    {
			if(deTime!=0){deTime--;}
			if((P3_2!=1)&&(deTime==0)){	
			 k++;
			 if(k>=2){k=0;} 
			 deTime=200;
      }   
       SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
	     i=count[k] % 10;   //���X�Ӧ��
       Data=~Table[i]; //Ū���Ӧ�ƽX��ƿ�X
       SSLED0=0;        //��ܭӦ����ܾ�
       Delay_ms(1);    //���y����  
	     SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S           
       i=(count[k] % 100)/10; //���X�Q��� k
       Data=~Table[i];//Ū���Q��ƽX��ƿ�X
       SSLED1=0;       //��ܤQ�����ܾ�
       Delay_ms(1);   //���y����                 
       SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
	     i=(count[k] % 1000)/100; //���X�ʦ��
       Data=~Table[i]; //Ū���ʦ�ƽX��ƿ�X
       SSLED2=0;       //��ܦʦ����ܾ�
       Delay_ms(1);    //���y����
	     SSLED0=SSLED1=SSLED2=SSLED3=1; //�B�S
       i=count[k]/1000;  //���X�d���
       Data=~Table[i]; //Ū���d��ƽX��ƿ�X
       SSLED3=0;        //��ܤd�����ܾ�
       Delay_ms(1);    //���y����
   } 
}