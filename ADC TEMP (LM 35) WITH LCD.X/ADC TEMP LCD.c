/*
 * File:   LCD WITH PIC.c
 * Author: LEO
 *
 * Created on May 1, 2022, 10:35 AM
 */

#define _XTAL_FREQ 8000000
#include <xc.h>
#include <stdio.h>

void Lcd_cmd(char c)
{
	PORTD=c&0xf0;
	PORTD&=~0x01;
	PORTD&=~0x02;
	PORTD|=0x04;
	__delay_ms(5);
	PORTD&=~0x04;
	__delay_ms(5);

	PORTD=c<<4;          
	PORTD&=~0x01;
	PORTD&=~0x02;
	PORTD|=0x04;
	__delay_ms(5);
	PORTD&=~0x04;
	__delay_ms(5);

}
void Lcd_data(char d)
{
	PORTD=d&0xf0;
	PORTD|=0x01;
	PORTD&=~0x02;
	PORTD|=0x04;
	__delay_ms(5);
	PORTD&=~0x04;
	__delay_ms(5);

	PORTD=d<<4;
	PORTD|=0x01;
	PORTD&=~0x02;
	PORTD|=0x04;
	__delay_ms(5);
	PORTD&=~0x04;
	__delay_ms(5);


}
void Lcd_initial()
{
	Lcd_cmd(0x02);
	Lcd_cmd(0x28);
	Lcd_cmd(0x0c);
	Lcd_cmd(0x06);
	Lcd_cmd(0x01);
	Lcd_cmd(0x80);
}
void Lcd_string(char *ptr)
{
	while (*ptr!='\0')
	{
		Lcd_data(*ptr++);
	}
}

void adc_init()
{
    ADCON0=0X81;
    ADCON1=0X8e;
}
unsigned int adc_read()
{
    ADCON0|=0X04;
    while(GO_nDONE);
    return ((ADRESH<<8)+ADRESL);
}
int main (void)
{
unsigned int i, temp;
int ar[5];
TRISD=0x00;
TRISA=0XFF;
PORTA=0X00;
PORTD=0X00;
adc_init();
Lcd_initial();
Lcd_data('a');
__delay_ms(100);

while(1)
{
    Lcd_cmd(0x01);
    i=adc_read();
    temp=((i*5)/10.24);
    sprintf(ar,"%d",temp);
  
    Lcd_string("temp_v:");
    Lcd_string(ar);
    __delay_ms(500);
    
}    
    
}

 




