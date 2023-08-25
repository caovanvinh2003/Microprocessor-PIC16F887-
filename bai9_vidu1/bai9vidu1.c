#INCLUDE<16F887.H>
#FUSES INTRC_IO
#USE DELAY(CLOCK=8M)
#define     lcd_e       pin_c7
#define     lcd_rw      pin_c6
#define     lcd_rs      pin_c5
#define     output_lcd  output_d
#INCLUDE<TV_LCD.C>

SIGNED INT16 i,y,N,SPEED=0;
unsigned int16 j;
SIGNED INT8 che_do=0;
const unsigned int8 ma7doan[10]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
void XUATMA7DOAN()
{
output_b(ma7doan[speed/1%10]);
}
VOID XULYNUTNHAN()
{
IF (INPUT(PIN_E2)==0)
      {DELAY_MS(20);
         IF (INPUT(PIN_E2)==0)
            {  che_do++;
               while(INPUT(PIN_E2)==0);
               if (che_do==4) che_do=0;
            }
       }
ELSE IF (INPUT(PIN_E1)==0)
      {DELAY_MS(20);
         IF (INPUT(PIN_E1)==0)
            {  che_do--;
               while(INPUT(PIN_E1)==0);
               if (che_do==-1) che_do=3;
            }
       }       
} 
VOID HIENTHILCD()
{
LCD_COMMAND(0X80+3);
lcd_data(" SANG DAN 12 LED");
LCD_COMMAND(0XC0+3);
lcd_data(" TAT DAN 12 LED");
LCD_COMMAND(0X94+3);
LCD_DATA(" SANG DICH 12 LED");
LCD_COMMAND(0XD4+3);
LCD_DATA(" TAT DICH 12 LED");
IF (CHE_DO==0) { LCD_COMMAND(0XC0); LCD_DATA("  "); LCD_COMMAND(0XD4); LCD_DATA("  "); LCD_COMMAND(0X80); lcd_data(0x7e); }
IF (CHE_DO==1) { LCD_COMMAND(0X94); LCD_DATA("  "); LCD_COMMAND(0X80); LCD_DATA("  "); LCD_COMMAND(0XC0); lcd_data(0x7e); }
IF (CHE_DO==2) { LCD_COMMAND(0XD4); LCD_DATA("  ");LCD_COMMAND(0XC0); LCD_DATA("  "); LCD_COMMAND(0X94); lcd_data(0x7e); }
IF (CHE_DO==3) { LCD_COMMAND(0X80); LCD_DATA("  "); LCD_COMMAND(0X94); LCD_DATA("  ");LCD_COMMAND(0XD4); lcd_data(0x7e); }
}
VOID TOCDO()
{
IF (INPUT(PIN_E0)==0)
      {DELAY_MS(20);
         IF (INPUT(PIN_E0)==0)
            {  SPEED++;
               while(INPUT(PIN_E0)==0);
               if (speed==9) SPEED=0;
            }
       }
}     
      

VOID CHECKSPEED()
{
if(speed==0)  { for(j=0;j<=50000;j++) TOCDO(); delay_ms(1);}
if(speed==1) { for(j=0;j<=10000;j++) TOCDO(); delay_ms(1);}
if(speed==2) { for(j=0;j<=1000;j++) TOCDO(); delay_ms(1); }
if(speed==3) { for(j=0;j<=5;j++) TOCDO();delay_ms(1); }
if(speed==4) { for(j=0;j<=3;j++) TOCDO();  delay_ms(1);}
if(speed==5) delay_ms(200);
if(speed==6) delay_ms(100);
if(speed==7) delay_ms(50);
if(speed==8) delay_ms(20);
if(speed==9) delay_ms(1);
}
VOID SANGDAN()
{
   FOR(i=0;i<13;i++)
         {
            Y=~(0XFFF<<i);
            OUTPUT_A(Y);
            OUTPUT_C(Y>>8&0x0f);
             TOCDO(); CHECKSPEED();
            XULYNUTNHAN();
            XUATMA7DOAN();
            HIENTHILCD();
            IF (CHE_DO!=0) BREAK;
   }
}
VOID TATDAN()
{
         FOR(i=0;i<13;i++)
         {
            Y=0XFFF<<i;
            OUTPUT_A(Y);
            OUTPUT_C(Y>>8&0x0f);
            
            XULYNUTNHAN();   TOCDO(); CHECKSPEED(); XUATMA7DOAN();
             HIENTHILCD();
            IF (CHE_DO!=1) BREAK;
         }
}
VOID SANGDICH()
{
   FOR(i=0;i<13;i++)
   {
      Y=0X001<<i;
      OUTPUT_A(Y);
      OUTPUT_C((Y>>8)&0X0F);
   
      XULYNUTNHAN(); TOCDO(); CHECKSPEED(); XUATMA7DOAN();
       HIENTHILCD();
     IF (CHE_DO!=2) BREAK;
   }
}
VOID TATDICH()
{
   FOR(i=0;i<13;i++)
   {
      Y=~(0X001<<i);
      OUTPUT_A(Y);
      OUTPUT_C((Y>>8)&0X0F);
      
      XULYNUTNHAN();  TOCDO(); CHECKSPEED(); XUATMA7DOAN();
       HIENTHILCD();
         IF (CHE_DO!=3) BREAK;
   }
}


VOID MAIN()
{
   SET_TRIS_A(0);
   SET_TRIS_C(0);
   SET_TRIS_B(0);
   SET_TRIS_D(0);
   SET_TRIS_E(0XFF);
   LCD_SETUP();
   
   WHILE(TRUE)
   { 
   SWITCH (CHE_DO)
      { case 0: sangdan();   break;
         case 1: tatdan();  break;
         case 2: sangdich(); break;
         case 3: tatdich(); break;
      }
   }
}
