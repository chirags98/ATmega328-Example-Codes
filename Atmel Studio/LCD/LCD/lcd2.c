/*
 * lcd2.c
 *
 * Created: 23-Nov-17 10:13:30 PM
 *  Author: Chirag
 */

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "lcd2.h"

static unsigned int temp;
static unsigned int unit;
static unsigned int tens;
static unsigned int hundred;
static unsigned int thousand;
static unsigned int million;

/*
* Function Name:lcd_print
* Input: row, column, value, digits -> value is the integer you want to print
* Output: Integer is printed to the desired location and upto the desired number of digits
* Logic:
* Example Call: lcd_print(1,1,val,3)
*/
//002 and not 0020
static void lcd_print5(char row, char coloumn, unsigned int value, int digits, char* str)
{
	if(value)
	{
		//count the number of trailing zeros
		unsigned int num = value;
		unsigned char count = 0;
		while (num != 0)
		{
			if ((num & 1) == 1)
			{
				break;
			}
			else
			{
				count++;
				num = num >> 1;
			}
		}
		
		unsigned char flag=0;
		if(row==0||coloumn==0)
			lcd_home();
		else
			lcd_cursor(row,coloumn);
	
		if(digits==5 || flag==1)
		{	
			million=value/10000+48;
			//if(count < 5)
			lcd_wr_char(million);
			
			flag=1;
		}
		if(digits==4 || flag==1)
		{
			temp = value/1000;
			thousand = temp%10 + 48;
			//if(count < 4)
			lcd_wr_char(thousand);
			
			flag=1;
		}
		if(digits==3 || flag==1)
		{
			temp = value/100;
			hundred = temp%10 + 48;
			//if(count < 3)
			lcd_wr_char(hundred);
			flag=1;
		}
		if(digits==2 || flag==1)
		{
			temp = value/10;
			tens = temp%10 + 48;
			//if(count < 2)
			lcd_wr_char(tens);
			flag=1;
		}
		if(digits==1 || flag==1)
		{
			unit = value%10 + 48;
			if(count < 1)
				lcd_wr_char(unit);
		}
		if(digits>5)
		{
			lcd_wr_char('E');
		}
	}
	
	else	//if(value==0)
	{
		lcd_wr_char('0'); //print one 0
		lcd_wr_char('0'); //print one 0
	}
	
	while(*str != '\0')
	{
		lcd_wr_char(*str);
		str++;
	}
}

//20mA and not 0020mA
void lcd_print2(char row, char coloumn, unsigned int value, int digits, char* str)
{
	unsigned char flag=0;
	char count = 0;
	
	if(row==0||coloumn==0)
	{
		lcd_home();
	}
	else
	{
		lcd_cursor(row,coloumn);
	}
	
	if(digits==5 || flag==1)
	{
		million=value/10000+48;
		if(million != '0')
		{
			lcd_wr_char(million);
			count++;	
		}
		flag=1;
	}
	if(digits==4 || flag==1)
	{
		temp = value/1000;
		thousand = temp%10 + 48;
		if(thousand != '0' || count != 0)	//If any non zero value has already been printed
		{
			lcd_wr_char(thousand);
			count++;
		}
		flag=1;
	}
	if(digits==3 || flag==1)
	{
		temp = value/100;
		hundred = temp%10 + 48;
		if(hundred != '0' || count != 0)
		{
			lcd_wr_char(hundred);
			count++;
		}
		flag=1;
	}
	if(digits==2 || flag==1)
	{
		temp = value/10;
		tens = temp%10 + 48;
		if(tens != '0' || count != 0)
		{
			lcd_wr_char(tens);
			count++;
		}
		flag=1;
	}
	if(digits==1 || flag==1)
	{
		unit = value%10 + 48;
		lcd_wr_char(unit);
		count++;
	}
	if(digits>5)
	{
		lcd_wr_char('E');
	}
	
	while(*str != '\0')
	{
		lcd_wr_char(*str);
		count++;
		digits++;
		str++;		
	}
	
	//Clear the remaining chars if not enough chars were printed
	if(count<digits)
	{
		while(count != digits)
		{
			lcd_wr_char(32);
			count++;
		}	
	}
}

//20 and not 0020
void lcd_print3(char row, char coloumn, unsigned int value, int digits)
{
	unsigned char flag=0;
	char count = 0;
	
	if(row==0||coloumn==0)
	{
		lcd_home();
	}
	else
	{
		lcd_cursor(row,coloumn);
	}
	
	if(digits==5 || flag==1)
	{
		million=value/10000+48;
		if(million != '0')
		{
			lcd_wr_char(million);
			count++;
		}
		flag=1;
	}
	if(digits==4 || flag==1)
	{
		temp = value/1000;
		thousand = temp%10 + 48;
		if(thousand != '0' || count != 0)	//If any non zero value has already been printed
		{
			lcd_wr_char(thousand);
			count++;
		}
		flag=1;
	}
	
	if(digits==3 || flag==1)
	{
		temp = value/100;
		hundred = temp%10 + 48;
		if(hundred != '0' || count != 0)
		{
			lcd_wr_char(hundred);
			count++;
		}
		flag=1;
	}
	if(digits==2 || flag==1)
	{
		temp = value/10;
		tens = temp%10 + 48;
		if(tens != '0' || count != 0)
		{
			lcd_wr_char(tens);
			count++;
		}
		flag=1;
	}
	if(digits==1 || flag==1)
	{
		unit = value%10 + 48;
		lcd_wr_char(unit);
		count++;
	}
	if(digits>5)
	{
		lcd_wr_char('E');
	}
}

//27.345A //27mA ...
void lcd_print4(char row, char col, float value, char* str1, char* str2)
{
	//Print in mA, mW, mW etc
	if (value<1000)
	{
		lcd_print2(row,col,value,4, str1);
		/*
		//Clear chars after printing
		char space_count = 4;
		while(value/10 != 0)
		{
			value=value/10;
			space_count--;
		}
		
		while(space_count!=0)
		{
			lcd_string(" ");
			space_count--;
		}	
		*/
	}
	
	//Print in A, V, W etc and clear the space after(incase previous was >=10000)
	else if (value>=1000 && value < 10000)
	{
		lcd_print3(row, col, value/1000, 1);
		lcd_string2(row, col+1, ".");				//Print the decimal point
		
		lcd_print5(row, col+2, (int)value%1000, 3, str2);		
		//lcd_string(str2);
		
		/*							//Print A, V etc
		lcd_print(row, col+2, (int)value%1000, 3);
		lcd_string(str2);							//Print A, V etc
		*/
		
		lcd_string("  ");
	}
	
	//Print in A, V, W etc
	else if (value>=10000)
	{
		lcd_print3(row, col, value/1000, 2);
		lcd_string2(row, col+2, ".");				//Print the decimal point
		
		lcd_print5(row, col+3, (int)value%1000, 3, str2);
		//lcd_string(str2);		//Print A, V etc
		
		/*					
		lcd_print(row, col+3, (int)value%1000, 3);
		lcd_string(str2);							//Print A, V etc
		*/
		lcd_string(" ");
	}	
} 
