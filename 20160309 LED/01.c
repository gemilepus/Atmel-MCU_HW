#include "AT89X52.H"
void delay_1ms(int count);
main()
{
 while(1){
   P0=0x81;
   delay_1ms(8000);
   P0=0x82;
   delay_1ms(2000);
   P0=0x24;
   delay_1ms(8000);
	 P0=0x44;
	 delay_1ms(2000);
 }
}
void delay_1ms(int count)
{ int i,j;
   for(i=0;i<count;i++) for(j=0;j<40;j++);
}