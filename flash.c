/*
 * This file is part of the frser-atmega644 project.
 *
 * Copyright (C) 2010,2011 Urja Rannikko <urjaman@gmail.com>
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
#include "flash.h"
#include "uart.h"
#include "frser.h"

static uint8_t flash_prot_in_use=0;

static void flash_portclear(void) {
// So that every test function can assume this reset/safe setup.
	DDRA=0;
	DDRB=0;
	DDRC=0;
	DDRD=0;
	PORTA=0;
	PORTB=0;
	PORTC=0;
	PORTD=0;
}

void flash_set_safe(void) {
	flash_portclear();
}

//#define SD(x) SEND(X)
#define SD(x)

uint8_t flash_get_proto(void) {
	return flash_prot_in_use;
}

uint8_t flash_idle_clock(void) {
	return 0;
}

uint8_t flash_plausible_protocols(void) {
	uint8_t protocols = SUPPORTED_BUSTYPES;
	return protocols;
}

void flash_select_protocol(uint8_t allowed_protocols) {
	flash_prot_in_use = 0;
	return;
}

static void spi_uninit_check(void)
{
}

uint8_t flash_read(uint32_t addr) {
	return 0xFF;
}

void flash_readn(uint32_t addr, uint32_t len) {
	if (len==0) len = ((uint32_t)1<<24);
		while (len--) SEND(0xFF);
}

void flash_write(uint32_t addr, uint8_t data) {
			return;
}

	
void flash_spiop(uint32_t sbytes, uint32_t rbytes) {
	while (sbytes--) RECEIVE();
	SEND(S_ACK);
	while (rbytes--) SEND(0xFF);
}
