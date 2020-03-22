/*
 * LCD.h
 *
 * Created: 5/20/2017 2:02:43 PM
 *  Author: Chirag
 */ 


#ifndef LCD_H_
#define LCD_H_

void lcd_start(void);
void lcd_port_config (void);
void lcd_wr_char(char);
void lcd_string(char*);
void lcd_string2(char, char, char*);
void lcd_clear(void);
void lcd_print(char, char , unsigned int , int);
void lcd_cursor(char,char);
void lcd_home(void);

#endif /* LCD_H_ */