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


#include "ui/globals/globals.h"
#include "ui/widgets/widgets.h"
#include "ui/widgets/fill/fill.h"
#include "ui/table/gtk_custom_table.h"
#include "io/openfile.h"
#include "io/readfile.h"


int tab1 = 0;
int tab2 = 0;

/**
 * read and parse a ratings file or list..
 * @param char *filename    file to open..
 */
int open_file(char *filename, int type) {

    ResultList *list = calloc(1, sizeof(ResultList));
    
    if(!readfile(list, filename) || list->cols < 10) {
        return 0;
    }
    
    set_global(CONST_OPEN_L, filename);
    set_global(CONST_OPEN_M, filename);

    if(type == TAB1) {
        tab1 = 1;
        ui_fill_lists_mov(list, nb_lists_mov_tab, nb_stats_mov_tab, type);
    }
    else {
        tab2 = 1;
        ui_fill_lists_mov(list, nb_lists_lst_tab, nb_stats_lst_tab, type);
    }

    readfile_free(list);

    /* fill comparison tab if applicable */
    if(tab1 && tab2) {

        ui_fill_lists_cmp(nb_lists_mov_tab, nb_lists_lst_tab);
    }
        
    gtk_custom_table_refresh(mwin);

    return 1;
}

