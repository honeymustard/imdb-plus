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


#include <string.h>
#include <stdlib.h>
#include "globals.h"


char *globals[CONST_EOL];


/**
 * initiates global constants array to NULL..
 */
void globals_init() {

    int i = 0;

    for(i = 0; i < CONST_EOL; i++) {
        globals[i] = NULL;
    }
}


/**
 * gets a stored global variable..
 * @param Global global     global id
 * @return char *           returns global or NULL
 */
char *globals_get(Global global) {

    return globals[global];
}


/**
 * sets a global variable to a value..
 * @param Global global     global id
 * @param char *value       string value
 */
void globals_set(Global global, char *value) {

    if(value == NULL) {

        if(globals[global] != NULL) {
            free(globals[global]);
        }

        globals[global] = NULL;

        return;
    }

    /* global and value may be equal */
    char *temp = malloc(strlen(value) + 1);
    strcpy(temp, value);

    if(globals[global] != NULL) {
        free(globals[global]);
    }

    globals[global] = temp;
}


/**
 * free all global variables..
 */
void globals_free() { 

    int i = 0;

    for(i = 0; i < CONST_EOL; i++) {
        if(globals[i] != NULL) {
            free(globals[i]);
            globals[i] = NULL;
        }
    }
} 

