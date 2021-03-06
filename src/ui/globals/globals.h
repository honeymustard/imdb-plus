/***********************************************************************
 *
 * Copyright (C) 2011-2013  Adrian Solumsmo
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/


#ifndef _GLOBALS_
#define _GLOBALS_

/* global constants */
typedef enum {

    CONST_HOME,
    CONST_DOWN,
    CONST_TOP_TMP,
    CONST_TOP_CSV,
    CONST_TOP_URL,
    CONST_BOT_TMP,
    CONST_BOT_CSV,
    CONST_BOT_URL,
    CONST_BOX_TMP,
    CONST_BOX_CSV,
    CONST_BOX_URL,
    CONST_RAT_URL,
    CONST_VERSION,
    CONST_APPNAME,
    CONST_PATHNAME,
    CONST_BASENAME,
    CONST_OPEN_MOV, 
    CONST_OPEN_LST, 
    CONST_EOL

} Global;


void   globals_init();
char * globals_get(Global global);
void   globals_set(Global global, char *value);
void   globals_free();

#endif

