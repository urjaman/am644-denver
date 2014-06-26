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
#include "rgbbl.h"
#include "denlcd.h"
#include "denkbd.h"

#if 1
static void sendcrlf(void) {
	sendstr_P(PSTR("\r\n"));
}
#endif


void luint2outdual(unsigned long int val) {
	unsigned char buf[11];
	luint2str(buf,val);
	sendstr(buf);
	sendstr_P(PSTR(" ("));
	luint2xstr(buf,val);
	sendstr(buf);
	sendstr_P(PSTR("h) "));
}

void echo_cmd(void) {
	unsigned char i;
	for (i=1;i<token_count;i++) {
		sendstr(tokenptrs[i]);
		SEND(' ');
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



#define BUFCNT 16

static uint8_t rem_capt(uint8_t *buf, uint8_t len, uint16_t captime) {
    do {
        if (uart_isdata()) return 255;
    } while (PINA&_BV(0));
    uint8_t pa = PINA&_BV(0);
    uint8_t n;
    for (n=0;n<len;n++) {
        uint8_t i;
        for (i=0;i<80;i++) {
            _delay_us(9.1667); // substracted the loop fuzz from 10us
            if ((PINA&_BV(0)) != pa) break;
        }
        buf[n] = i;
        if (pa) buf[n] |= 0x80;
        if (captime <= i) {
            n++;
            break;
        }
        captime -= i;
        pa = PINA&_BV(0);
    }
    return n;
}

static void printcap(uint8_t pv, uint16_t l)
{
	unsigned char buf[11];
    if (pv) SEND('H');
    else SEND('L');
	luint2str(buf,l);
	sendstr(buf);
    SEND(' ');
}

void rcapt_cmd(void)
{
    uint8_t cc[BUFCNT];
    uint8_t cd[BUFCNT][20];
    uint8_t ci;
    for (ci=0;ci<BUFCNT;ci++) {
        uint8_t ct = rem_capt(cd[ci],20,10200);
        if (ct>20) break;
        cc[ci] = ct;
        SEND('.');
    }
    if (ci) {
        for (uint8_t n=0;n<ci;n++) {
            uint8_t pv=0;
            uint16_t tlt=0;
            sendcrlf();
            for (uint8_t z=0;z<cc[n];z++) {
                if ((cd[n][z]&0x80) != pv) {
                    printcap(pv,tlt);
                    tlt = 0;
                    pv = cd[n][z]&0x80;
                }
                tlt += cd[n][z]&0x7F;
            }
            printcap(pv,tlt);
        }
    }
}


void dkbd_cmd(void)
{
    while (!uart_isdata()) {
        if (denkbd_isdata()) {
            uint8_t d = denkbd_getkey();
            sendstr_P(denkbd_keyname(d));
            sendcrlf();
        }
    }
}

void dlf_cmd(void)
{
    /* pattern, eg 0xFF makes it len 20 0xFF 0xFF ... 0xF8 */
    /* 0xAA 0x 55 makes 0xAA 0x55 0xAA 0x55 ... 0x58 */
    if (token_count >= 2) {
        uint8_t buf[20];
        uint8_t po = 0;
        uint8_t pl = token_count - 1;
        for (uint8_t i=0;i<20;i++) {
            buf[i] = astr2luint(tokenptrs[1+po]); 
            po++;
            if (po>=pl) po = 0; 
                   }
        denlcd_frame(buf);
        sendstr_P(PSTR("DONE"));
    }
}

void dls_cmd(void)
{
    if (token_count >= 2) {
        uint8_t buf[19];
        memset(buf,0,19);
        denlcd_write_string(buf,tokenptrs[1]);
        denlcd_frame(buf);
        sendstr_P(PSTR("DONE"));
    }
}

static uint16_t ee_write_string(uint16_t offset, const uint8_t *line)
{
    uint16_t len = strlen((char*)line);
    eeprom_update_block(line,(void*)offset,len);
    eeprom_update_byte((void*)(offset+len), 0xFF);
    return offset+len;
}

void dld_cmd(void)
{
    const uint8_t crlf[3] = { '\r', '\n', 0 };
    uint16_t offset = 0;
    for (int i=0;i<156;i++) {
        uint8_t buf[20];
        uint8_t msg[6];
        uint8_t desc[16];
        uint8_t B = i>>3;
        uint8_t b = 7 - (i&7);
        memset(buf,0,20);
        buf[B] |= _BV(b);
        msg[0] = (B/10) | 0x30;
        msg[1] = (B%10) | 0x30;
        msg[2] = '-';
        msg[3] = 0x30 | b;
        msg[4] = ':';
        msg[5] = 0;
        denlcd_frame(buf);
        sendcrlf();
        sendstr(msg);
        getline(desc,16);
        if (strncmp_P((char*)desc,PSTR("QUIT"),4)==0) break;
        offset = ee_write_string(offset,msg);
        offset = ee_write_string(offset,desc);
        offset = ee_write_string(offset,crlf);
    }
    sendcrlf();
    sendstr_P(PSTR("Wrote "));
    luint2outdual(offset);
    sendstr_P(PSTR(" bytes"));
}

void eed_cmd(void)
{
    for (int i=0;i<2048;i++) {
        uint8_t b = eeprom_read_byte((void*)i);
        if ((b>126)||(b<1)) break;
        SEND(b);
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
