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


#include "globals.h"
#include "../master.h"


char *const_home;
char *const_top_tmp;
char *const_top_csv;
char *const_bot_tmp;
char *const_bot_csv;
char *const_box_tmp;
char *const_box_csv;


/**
 * Gets a stored global variable..
 * @param int global     global id
 */
char *get_global(int global) {

    if(global == CONST_HOME) {
        return const_home;
    }
    else if(global == CONST_TOP_TMP) {
        return const_top_tmp;
    }
    else if(global == CONST_TOP_CSV) {
        return const_top_csv;
    }
    else if(global == CONST_TOP_URL) {
        return TOP_URL;
    }
    else if(global == CONST_BOT_TMP) {
        return const_bot_tmp;
    }
    else if(global == CONST_BOT_CSV) {
        return const_bot_csv;
    }
    else if(global == CONST_BOT_URL) {
        return BOT_URL;
    }
    else if(global == CONST_BOX_TMP) {
        return const_box_tmp;
    }
    else if(global == CONST_BOX_CSV) {
        return const_box_csv;
    }
    else if(global == CONST_BOX_URL) {
        return BOX_URL;
    }

    return "";
}


/**
 * Sets a global variable to a value..
 * @param int global     global id
 * @param char *value    string value
 */
int set_global(int global, char *value) {

    if(global == CONST_HOME) {
        const_home = value;
    }
    else if(global == CONST_TOP_TMP) {
        const_top_tmp = value;
    }
    else if(global == CONST_TOP_CSV) {
        const_top_csv = value;
    }
    else if(global == CONST_BOT_TMP) {
        const_bot_tmp = value;
    }
    else if(global == CONST_BOT_CSV) {
        const_bot_csv = value;
    }
    else if(global == CONST_BOX_TMP) {
        const_box_tmp = value;
    }
    else if(global == CONST_BOX_CSV) {
        const_box_csv = value;
    }

    return 0;
}

