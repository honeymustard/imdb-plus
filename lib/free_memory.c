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

#include <stdlib.h>


/**
 * free memory from temporary char array..
 * @param char ***results    array to be freed
 * @param int cols           cols in array
 * @param int rows           rows in array
 * @return                   returns 1
 */
int free_memory(char ***results, int cols, int rows) {
 
    int i = 0;
    int j = 0;

    /* free memory occupied by results.. */
    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++) {

            if(results[i][j] != NULL) {
                free(results[i][j]);
            }
        }

        free(results[i]); 
    }

    return 1;
}

