#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>

#include <gui.h>
#include <ext.h>
#include <oled.h>

void gui_menu(void)
{
oled_goto_pos(0,0);
oled_print8("Valg 1");
oled_goto_pos(2,0);
oled_print8("Valg 2");
oled_goto_pos(4,0);
oled_print8("Valg 3");
oled_goto_pos(6,0);
oled_print8("Valg 4");
}