#include <avr/io.h>
#include <bit.h>
#include <fonts.h>
#include <ext.h>
#include <avr/pgmspace.h>
#include <uart.h>
#include <string.h>


void oled_init(void)
{
    ext_write(0x1000, 0x00, 0xae); // display off
    ext_write(0x1000, 0x00, 0xa1); //segment remap
    ext_write(0x1000, 0x00, 0xda); //common pads hardware: alternative
    ext_write(0x1000, 0x00, 0x12);
    ext_write(0x1000, 0x00, 0xc8); //common output scan direction:com63~com0
    ext_write(0x1000, 0x00, 0xa8); //multiplex ration mode:63
    ext_write(0x1000, 0x00, 0x3f);
    ext_write(0x1000, 0x00, 0xd5); //display divide ratio/osc. freq. mode
    ext_write(0x1000, 0x00, 0x80);
    ext_write(0x1000, 0x00, 0x81); //contrast control
    ext_write(0x1000, 0x00, 0x50);
    ext_write(0x1000, 0x00, 0xd9); //set pre-charge period
    ext_write(0x1000, 0x00, 0x21);
    ext_write(0x1000, 0x00, 0x20); //Set Memory Addressing Mode
    ext_write(0x1000, 0x00, 0x02);
    ext_write(0x1000, 0x00, 0xdb); //VCOM deselect level mode
    ext_write(0x1000, 0x00, 0x30);
    ext_write(0x1000, 0x00, 0xad); //master configuration
    ext_write(0x1000, 0x00, 0x00);
    ext_write(0x1000, 0x00, 0xa4); //out follows RAM content
    ext_write(0x1000, 0x00, 0xa6); //set normal display
    ext_write(0x1000, 0x00, 0xaf); // display on
    //ext_write(0x1000, 0x00, 0xa5); // all pixels on
}

void oled_reset()
    {
        for (int i = 0; i < 8; i++)
        {
            oled_clear_line(i);
        }
        oled_home();
    }

void oled_home()
    {
    oled_goto_pos(0, 0);
    }


void oled_goto_column(int column)
    {
        ext_write(0x1000, 0x00, 0x00 + (column % 16));
	    ext_write(0x1000, 0x00, 0x10 + (column / 16));
    }

void oled_goto_line(int line)
    {
        ext_write(0x1000, 0x00,  0xb0 + line);
    }

void oled_clear_line(int line)
    {
    oled_goto_line(line);
    oled_goto_column(0);
    for (int i = 0; i < 128; i++) {
        oled_write_data(0x00);
        }
    }

void oled_goto_pos(int line, int column)
    {
        oled_goto_line(line);
        oled_goto_column(column);
    }


void oled_print(char* string)
    {
        if (strlen(string) > 0)
        {
            int str_length = strlen(string);
            printf("%d\r\n", str_length);
        }
        for (int i = 0; i < strlen(string); i++) // divide string into characters
        {
            // need choice for upper/lower case

            for (int j = 0; j < 7; j++)
            {
                int print_byte = pgm_read_byte(&(font8[string[i]-32][j])); // fetch byte data from font.h, need choice for font size
                oled_write_data(print_byte);
                
            }
            oled_write_data(0x00);
        }
    } 


void oled_write_data(char data)
    {
        ext_write(0x1200, 0x00, data);
    }