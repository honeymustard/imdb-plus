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
#include "ui/ui.h"
#include "ui/ui_fill/ui_fill.h"
#include "ui/table/gtk_custom_table.h"
#include "io/openfile.h"
#include "io/readfile.h"


int has_open_mov = 0;
int has_open_lst = 0;


/**
 * read and parse a ratings file or list..
 * @param char *filename    file to open..
 */
int open_file(char *filename) {

    int cols = 0;
    int rows = 0;

    char ***results = NULL;
    
    if(!read_file(filename, &cols, &rows, &results) || cols < 10) {
        return 0;
    }

    /* file is a personal ratings file */
    if(strcmp("IMDb Rating", results[0][9]) == 0) {

        set_global(CONST_OPEN_M, filename);
        ui_fill_lists_mov(&results, rows);

        has_open_mov = 1;
    }
    /* file is a list of some kind */
    else {

        set_global(CONST_OPEN_L, filename);
        ui_fill_lists_lst(&results, rows);

        has_open_lst = 1;
    }

    free_memory(results, cols, rows);

    /* fill comparison tab if applicable */
    if(has_open_mov && has_open_lst) {

        ui_fill_stats_cmp_calc(nb_tab_mymovies, nb_tab_lists);
    }
        
    gtk_custom_table_refresh(window);

    return 1;
}

