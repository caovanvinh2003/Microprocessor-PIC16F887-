#include<16f887.h>
#fuses intrc_io
#use delay(clock=8M)
int32 i,LED,a,j,LED1;
int count=1;
const unsigned int8 ma7doan[10]={0xC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90};
//xu ly nut up down
void XULY_NUTNHAN()
{
   if(input(pin_e0)==0) //phim up
   {
      delay_ms(20);
      if(input(pin_e0)==0)
      {
      count++;
      while(input(pin_e0)==0);
      if (count==11) count=1;
      }
   }
   else if(input(pin_e1)==0) //phim down
   {
      delay_ms(20);
      if(input(pin_e1)==0)
      {
      count--;
      while(input(pin_e1)==0);
      if (count==0) count=10;
      }
   }
}
//xuat ma 7 doan ra
void xuatma7doan()
{
//!output_a(ma7doan[count/1%10]); //led7doan hang don vi
//!output_b(ma7doan[count/10%10]); //led7doan hang chuc
output_a(0xff-1-2-32-64);
}
   
   

void choptat()
{
   for(i=0;i<3;i++)
   {
   
   led=0xFFFF; //1111 1111 1111 1111 1111 1111
   output_d(LED);
   output_c(LED>>8);
   delay_ms(200);
   XULY_NUTNHAN();
   led=0x0000; //0000 0000 0000 0000 0000 0000
   output_d(LED);
   output_c(LED>>8);
   delay_ms(200);
   XULY_NUTNHAN();
   xuatma7doan();
   if(count!=1) break;
   }
}

void sangdanpst()
{
LED=0x0001; //0000 0000 0000 0000 0000 0001
   for(i=0;i<=16;i++)
   {
   LED=(LED<<1)+0x01;
   output_d(LED);
   output_c(LED>>8);
   delay_ms(200);
   XULY_NUTNHAN();
   xuatma7doan();
   if(count!=2) break;
   }
}
void sangdantsp()
{
   for(i=0;i<=24;i++)
   {

   LED=~(0xffff>>i);
   if(count!=4) break;
    output_d(LED);
   output_c(LED>>8);
   delay_ms(200);
   XULY_NUTNHAN();
   xuatma7doan();
   
   }
 }
   
void tatdanpst()
{
   for(i=0;i<=16;i++)
   {

 
   LED=0xffff<<i; //1111 1111 1111 1111 1111 1111
   output_d(LED);
   output_c(LED>>8);
   delay_ms(200);
   XULY_NUTNHAN();
   xuatma7doan();
   if(count!=5) break;
   }
}

void tatdantsp()
{
   for(i=0;i<=16;i++)
   {


   LED=0xffff>>i;
   output_d(LED);
   output_c(LED>>8);
   delay_ms(200);
   XULY_NUTNHAN();
   xuatma7doan();
   if(count!=3) break;
   }
}
 
void sangdichpst()
{
   for(i=0;i<=16;i++)
   {


   LED=0x0001<<i; 
   output_d(LED);
   output_c(LED>>8);
   delay_ms(200);
   XULY_NUTNHAN();
   xuatma7doan();
   if(count!=6) break;
   }
}

void sangdichtsp()
{
   for(i=0;i<=16;i++)
   {


   LED=0x8001>>i;  
   output_d(LED);
   output_c(LED>>8);
   delay_ms(200);
   XULY_NUTNHAN();
   xuatma7doan();
   if(count!=7) break;
   }
}

void sangdich3ledpst()
{
   for(i=0;i<=24;i++)
   {
   LED=0x0007<<i;
   output_d(LED);
   output_c(LED>>8);
   delay_ms(200);
   XULY_NUTNHAN();
   xuatma7doan();
   if(count!=8) break;
   }
}

void sangdich3ledtsp()
{
   for(i=0;i<=16;i++)
   { 


   LED=0xE000>>i;
   output_d(LED);
   output_c(LED>>8);
   delay_ms(200);
   XULY_NUTNHAN();
   xuatma7doan();
   if(count!=9) break;
   }
} 

void sangdontsp()
{
a=0;
for(i=0;i<16;i++)
   {
   
   LED1=0x8000; 
   for(j=0;j<16-i;j++)
   {
      LED=LED1|a;
      if(count!=10) break;
      output_d(LED);
      output_c(LED>>8);
      delay_ms(200);
      XULY_NUTNHAN();
      xuatma7doan();
      LED1=LED1>>1;
      
   }
   a=LED; 
   }
}



void main()
{
set_tris_d(0);
set_tris_c(0);
set_tris_a(0);
set_tris_b(0);
set_tris_e(1);
while(true)
{
    switch (count) 
         {
    case 1:
      choptat();
      break;
    case 2:
      sangdanpst();
      break;
    case 3:
   tatdantsp();
         
         break;
     case 4:
         sangdantsp();  
         
        break;
     case 5: 
         tatdanpst();
             
        break;
      case 6:
         sangdichpst();
            
        break;
      case 7:
         sangdichtsp();    
         break;
        case 8:
         sangdich3ledpst();    
         break;
       case 9:
       sangdich3ledtsp();    
       break;
        case 10:
       sangdontsp();    
       break;

         }
   
}
   
}
