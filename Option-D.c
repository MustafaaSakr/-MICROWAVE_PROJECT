#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "string.h"
#include "stdlib.h"
#include "KPD.h"
#include "LCD.h"
#include "GPIO_INIT.h"
#include "functions.h"
#include "GPIO_INIT.h"

//take_cooking_time function returns "1" if taking the time is successful,
//returns "0" if the entered time is invalid *not between 1-30*,
//returns *2* otherwise.

uint32_t take_cooking_time(void)
{
	char D1='I',D2='I',D3='I',D4='I';    //variables to store numbers entered from keyboard
  char text_s[10] = {'0','0',0};       //temp array to store the digits entered
	char text_m[10] = {'0','0',0};
	uint32_t m,s;	                           //variables to store the changed values(m and s) from char to integers
	lcd_gotoxy(7,2);
	lcd_write_string("00:00");
	
	D1=Keypad_Getkey();                 //taking the first digit from the keypad
	lcd_gotoxy(11,2);
	lcd_write(D1);
	delay_ms(100);
	if((D1!='I') && (D2=='I') && (D3=='I') && (D4=='I') )  //converting digits from *char* to *int*
	{
		text_s[1]= D1;
		s=atoi(text_s);
		if(Keypad_Getkey()=='*')             //time taken, go to cook
		{
			return 1;
		}
	}
	
	D2=Keypad_Getkey();               //taking the second digit from the keypad
	lcd_gotoxy(10,2);
	lcd_write(D1);
	delay_ms(100);
	lcd_gotoxy(11,2);
	lcd_write(D2);

	if((D1!='I') && (D2!='I') && (D3=='I') && (D4=='I'))  //converting digits from *char* to *int*
	{
			text_s[0]=D1;
			text_s[1]=D2;
			s=atoi(text_s);
		  if(Keypad_Getkey()=='*')            //time taken, go to cook
		  {
				return 1;
		  }
	}
	
	D3=Keypad_Getkey();            //taking the third digit from the keypad
	lcd_gotoxy(8,2);
	lcd_write(D1);
	delay_ms(100);
	lcd_gotoxy(10,2);
	lcd_write(D2);
	delay_ms(100);
	lcd_gotoxy(11,2);
	lcd_write(D3);

	if((D1!='I') && (D2!='I') && (D3!='I') && (D4=='I'))  //converting digits from *char* to *int*
	{
  	  text_s[0]=D2;
	    text_s[1]=D3;
	    s=atoi(text_s);
		
	  	text_m[1]=D1;
	  	m=atoi(text_m);
      
      if(Keypad_Getkey()=='*')     //time taken, go to cook
		  {
				return 1;
		  }		
	}
	
	D4=Keypad_Getkey();           //taking the fourth digit from the keypad
	lcd_gotoxy(7,2);
	lcd_write(D1);
	delay_ms(100);
	lcd_gotoxy(8,2);
	lcd_write(D2);
	delay_ms(100);
	lcd_gotoxy(10,2);
	lcd_write(D3);
	delay_ms(100);
	lcd_gotoxy(11,2);
	lcd_write(D4);
	delay_ms(100);
	if((D1!='I') && (D2!='I') && (D3!='I') && (D4!='I'))  //converting digits from *char* to *int*
	{
		text_s[1]=D4;
		text_s[0]=D3;
		s=atoi(text_s);
	
		text_m[1]=D2;
		text_m[0]=D1;
		m=atoi(text_m);
		if((m>30)||((m>=30)&&(s>=1)))  //checking if the time entered is valid
		{
			return 0;
		}
		while(1)
		{
			if(Keypad_Getkey()=='*')   //time taken, go to cook
		  {
				return 1;
		  }
		
		}
		
	}	
	return 2;
}

void Option_D()
{
	uint32_t take_cooking_time_return,SW;
	lcd_cmd(lcd_Clear);
	lcd_cmd(first_line1);
	Vaild:
	lcd_write_string("Cooking Time?");
	take_cooking_time_return=take_cooking_time();
	if(take_cooking_time_return==1)
	{
		while(1)
		{
			if((Read_SW()&0x10)==0x00)
			{
				GPIO_PORTF_DATA_R|=Red;
				lcd_cmd(lcd_Clear);
			}
			if((Read_SW()&0x01)==0x00)
			{
				GPIO_PORTF_DATA_R|=Blue;
				//start timer
				lcd_write_string("  Cooking Done  ");
				break;
			}
		}
	}
	
	else if(take_cooking_time_return==0)
	{
		lcd_cmd(lcd_Clear);
 	  lcd_write_string("Enter valid time");
		delay_ms(6000);
		lcd_cmd(lcd_Clear);
		goto Vaild;
	}
}