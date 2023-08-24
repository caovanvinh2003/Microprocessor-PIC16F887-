#include<16f887.h>
#device adc=10
#fuses hs
#use delay(clock=20M)
#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7)
unsigned int16 kq5,kq7,kq;
unsigned int8 chuc,dv,nhan;
#INT_RDA
void ngatuart()
{
   chuc=getc();
   dv=getc();
}
void main()
{
set_tris_a(0xff);
set_tris_c(0x80);
set_tris_e(0xff);
setup_adc(ADC_CLOCK_DIV_32);
setup_adc_ports(san5|san7|vss_vdd);
enable_interrupts(INT_RDA);
enable_interrupts(GLOBAL);


   while(true)
   {
//!   nhan=chuc*10+dv;
 set_adc_channel(7); delay_us(200);
         kq7 = read_adc()/2.046;
         putc(kq7);
         delay_ms(100);
//!      if(nhan==5)
//!      {
//!         set_adc_channel(5); delay_us(200);
//!         kq5 = read_adc()/2.046;
//!         putc(kq5);
//!         delay_ms(100);
//!      }
//!       if(nhan==7)
//!      {
//!         set_adc_channel(7); delay_us(200);
//!         kq7 = read_adc()/2.046;
//!         putc(kq7);
//!         delay_ms(100);
//!      }
//!        if(nhan==10)
//!      {
//!         set_adc_channel(5); delay_us(200);
//!         kq5 = read_adc()/2.046;
//!         putc(kq5);
//!         delay_ms(100);
//!         set_adc_channel(7); delay_us(200);
//!         kq7 = read_adc()/2.046;
//!         putc(kq7);
//!         delay_ms(100);
//!      }
//!         if(nhan=13) break;
      
   
   }
}
