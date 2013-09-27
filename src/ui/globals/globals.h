/****************************************************************************
*
* Copyright (C) 2011-2012  Adrian Solumsmo
* 
* imdb-plus program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* imdb-plus program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*****************************************************************************/


#ifndef _GLOBALS_
#define _GLOBALS_

/* global constants */
#define CONST_HOME    1
#define CONST_DOWN    2
#define CONST_TOP_TMP 3
#define CONST_TOP_CSV 4
#define CONST_TOP_URL 5
#define CONST_BOT_TMP 6
#define CONST_BOT_CSV 7
#define CONST_BOT_URL 8
#define CONST_BOX_TMP 9
#define CONST_BOX_CSV 10
#define CONST_BOX_URL 11
#define CONST_RAT_URL 12 
#define CONST_VERSION 13
#define CONST_OPEN_M  14
#define CONST_OPEN_L  15
#define CONST_OPEN_R  16
#define CONST_OPEN_T  17
#define CONST_OPEN_S  18
#define CONST_EOL     19

char *get_global(int global);
void set_global(int global, char *value);
void free_globals();

#endif

