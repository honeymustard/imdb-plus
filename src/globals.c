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


#include <string.h>
#include <stdlib.h>
#include "globals.h"
#include "../main.h"


int initiated = 0;

char *constants[CONST_EOL];


/**
 * Initiates global constants array to NULL..
 */
void init_globals() {

    if(initiated) return;
    
    int i = 0;

    for(i = 0; i < CONST_EOL; i++) {
        constants[i] = NULL;
    }
        
    initiated = 1;
}


/**
 * Gets a stored global variable..
 * @param int global     global id
 */
char *get_global(int global) {

    init_globals();

    return constants[global];
}


/**
 * Sets a global variable to a value..
 * @param int global     global id
 * @param char *value    string value
 */
int set_global(int global, char *value) {

    init_globals();

    if(constants[global] != NULL) {
        free(constants[global]);
    }

    constants[global] = malloc(strlen(value) + 1);
    strcpy(constants[global], value);

    return 1;
}

