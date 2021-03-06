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

struct command_t {
	PGM_P name;
	void(*function)(void);
};

extern const struct command_t appdb[] PROGMEM;

void *find_appdb(unsigned char* cmd);
void echo_cmd(void);
void help_cmd(void);
void calc_cmd(void);
void bljump_cmd(void);
void blset_cmd(void);
void dlf_cmd(void);
void rcapt_cmd(void);
void dkbd_cmd(void);
void dld_cmd(void);
void eed_cmd(void);
void dls_cmd(void);
