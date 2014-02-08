/*
 * This file is part of the am644-disp project.
 *
 * Copyright (C) 2013,2014 Urja Rannikko <urjaman@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include "main.h"
#include "uart.h"
#include "console.h"
#include "lib.h"
#include "appdb.h"
#include "ciface.h"
#include "glcd.h"
#include "rgbbl.h"

#if 0
static void sendcrlf(void) {
	sendstr_P(PSTR("\r\n"));
}
#endif

void echo_cmd(void) {
	unsigned char i;
	for (i=1;i<token_count;i++) {
		sendstr(tokenptrs[i]);
		SEND(' ');
	}
}

void lcdw_cmd(void)
{
	if (token_count >= 3) {
		uint8_t y = astr2luint(tokenptrs[1]);	
		uint8_t x = astr2luint(tokenptrs[2]);
		lcd_gotoxy(x,y);
		for (uint8_t i=3;i<token_count;i++) {
			lcd_puts(tokenptrs[i]);
			lcd_putchar(' ');
		}
		
	}
}

void blset_cmd(void)
{
    if (token_count >= 3) {
        uint8_t r = astr2luint(tokenptrs[1]);
        uint8_t g = astr2luint(tokenptrs[2]);
        uint8_t b = astr2luint(tokenptrs[3]);
        rgbbl_set(r,g,b);
    }
}

void lcdr_cmd(void)
{
	lcd_init();
}

void lcdbr_cmd(void) {
	if (token_count >= 2) {
		uint32_t val = astr2luint(tokenptrs[1]);
		if (val>63) return;
		st7565_set_contrast(val);
	}
}

static void bargraph(uint8_t x, uint8_t y, uint8_t h, uint8_t w, uint8_t f) {
	struct drawdata *dd;
	make_drawdata(dd,w,h);
	drawrect(dd,0,0,w*LCD_CHARW,h*LCD_CHARH,1);
	fillrect(dd,0,0,f,h*LCD_CHARH,1);
	lcd_gotoxy(x,y);
	lcd_write_block(dd->d,w,h);
}

void lgfxt_cmd(void) {
    struct drawdata *dd;
    make_drawdata(dd,LCD_MAXX,LCD_MAXY);
    uint8_t xc = dd->w/2;
    uint8_t yc = dd->h/2;
    fillrect(dd,1,1,6,6,1);
    fillrect(dd,120,0,8,8,1);
    fillrect(dd,121,1,6,6,0);
    drawline(dd,7,9,1,63,1);
    drawline(dd,1,63,127,57,1);
    drawline(dd,1,57,127,63,1);
    drawline(dd,121,9,127,63,1);
    fillcircle(dd,xc,yc,3,1);
    drawcircle(dd,xc,yc,5,1);
    drawcircle(dd,xc,yc,8,1);
    drawcircle(dd,xc,yc,11,1);
    drawcircle(dd,xc,yc,14,1);
    drawcircle(dd,xc,yc,17,1);
    drawcircle(dd,xc,yc,20,1);
    lcd_gotoxy(0,0);
    lcd_write_block(dd->d,LCD_MAXX,LCD_MAXY);
}


void lcdbg_cmd(void) {
	if (token_count >= 6) {
		uint8_t y = astr2luint(tokenptrs[1]);	
		uint8_t x = astr2luint(tokenptrs[2]);
		uint8_t h = astr2luint(tokenptrs[3]);	
		uint8_t w = astr2luint(tokenptrs[4]);
		uint8_t f = astr2luint(tokenptrs[5]);
		bargraph(x,y,h,w,f);
	}
}

void luint2outdual(unsigned long int val) {
	unsigned char buf[11];
	luint2str(buf,val);
	sendstr(buf);
	sendstr_P(PSTR(" ("));
	luint2xstr(buf,val);
	sendstr(buf);
	sendstr_P(PSTR("h) "));
}


void lbench_cmd(void) {
	uint16_t start = TCNT1;
	for (uint8_t i=0;i<=32;i++) {
		bargraph(0,0,LCD_MAXY,LCD_MAXX,i*4);
	}
	uint16_t passed = TCNT1 - start;
	luint2outdual(passed);
}

void lcdc_cmd(void)
{
	for (uint8_t y=0;y<6;y++) {
		lcd_gotoxy(0,y);
		for (uint8_t i=0;i<LCD_MAXX;i++) lcd_putchar(i+(y*16)+32);
	}
	for (uint8_t y=6;y<8;y++) {
		lcd_gotoxy(0,y);
		for (uint8_t i=0;i<LCD_MAXX;i++) lcd_putchar(i+((y-6)*16)+0xA0);
	}
}

unsigned long int calc_opdo(unsigned long int val1, unsigned long int val2, unsigned char *op) {
	switch (*op) {
		case '+':
			val1 += val2;
			break;
		case '-':
			val1 -= val2;
			break;
		case '*':
			val1 *= val2;
			break;
		case '/':
			val1 /= val2;
			break;
		case '%':
			val1 %= val2;
			break;
		case '&':
			val1 &= val2;
			break;
		case '|':
			val1 |= val2;
			break;

		case '<':
			val1 = val1 << val2;
			break;

		case '>':
			val1 = val1 >> val2;
			break;
	}
	return val1;
}


unsigned long int closureparser(unsigned char firsttok, unsigned char*ptr) {
	unsigned char *op=NULL;
	unsigned char i,n;
	unsigned long int val1, val2;
	if (token_count <= firsttok) return 0;
	val1 = astr2luint(tokenptrs[firsttok]);
	sendstr_P(PSTR("{ "));
	luint2outdual(val1);
	n=0;
	for(i=firsttok+1;i<token_count;i++) {
		if (n&1) {
			sendstr(op);
			SEND(' ');
			if (*(tokenptrs[i]) == '(') {
				val2 = closureparser((i+1),&i);
			} else {
				val2 = astr2luint(tokenptrs[i]);
				luint2outdual(val2);
			}
			val1 = calc_opdo(val1,val2,op);
		} else {
			if (*(tokenptrs[i]) == ')') {
				sendstr_P(PSTR("} "));
				*ptr = i+1;
				return val1;
			}
			op = tokenptrs[i];
		}
		n++;
	}
	return val1;
}

void calc_cmd(void) {
	unsigned char *op=NULL;
	unsigned char i,n;
	unsigned long int val1;
	unsigned long int val2;
	if (token_count < 2) return;

	if (*(tokenptrs[1]) == '(') {
		val1 = closureparser(2,&i);
	} else {
		val1 = astr2luint(tokenptrs[1]);
		luint2outdual(val1);
		i=2;
	}
	n=0;
	for (;i<token_count;i++) {
		if (n&1) {
			sendstr(op);
			SEND(' ');
			if (*(tokenptrs[i]) == '(') {
				val2 = closureparser((i+1),&i);
			} else {
				val2 = astr2luint(tokenptrs[i]);
				luint2outdual(val2);
			}
			val1 = calc_opdo(val1,val2,op);
		} else {
			op = tokenptrs[i];
		}
		n++;
	}
	sendstr_P(PSTR("= "));
	luint2outdual(val1);
}

void help_cmd(void) {
	unsigned char i;
	const struct command_t * ctptr;
	PGM_P name;
	for(i=0;;i++) {
		ctptr = &(appdb[i]);
		name = (PGM_P)pgm_read_word(&(ctptr->name));
		if (!name) break;
		sendstr_P(name);
		SEND(' ');
	}
}



void bljump_cmd(void) {
	void (*btloader)(void)	= (void*)(BTLOADERADDR>>1); // Make PM
	_delay_ms(100);
	btloader();
}
