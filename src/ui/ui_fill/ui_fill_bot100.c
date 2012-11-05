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


#include "ui_fill.h"


/* parse new bottom 100 list */
int menu_signal_update_bot() {

    int i = 0;
    int cols = 0;
    int rows = 0;

    char ***results;
    
    if(read_file(get_global(CONST_BOT_CSV), &cols, &rows, &results) 
        && rows == 100 && cols == 6) {

        for(i = 0; i < gtk_custom_table_get_rows(nb_tab_bot100); i++) {

            gtk_custom_table_set_cell_text(nb_tab_bot100, 0, i, 
                results[i][0]);
            gtk_custom_table_set_cell_text(nb_tab_bot100, 1, i, 
                results[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_bot100, 2, i, 
                "0");
            gtk_custom_table_set_cell_text(nb_tab_bot100, 3, i, 
                results[i][2]);
            gtk_custom_table_set_cell_text(nb_tab_bot100, 4, i, 
                results[i][3]);
            gtk_custom_table_set_cell_text(nb_tab_bot100, 5, i, 
                results[i][4]);
            gtk_custom_table_set_cell_text(nb_tab_bot100, 6, i, 
                results[i][5]);

            /* clear cell color */
            gtk_custom_table_set_cell_color_enable(nb_tab_bot100, 2, i, 
                FALSE);

            gtk_custom_table_set_cell_color(nb_tab_bot100, 1, i, 
                colors[(int)atof(results[i][1])]); 
        }

        free_memory(results, cols, rows);

        gtk_custom_table_set_sortable(nb_tab_bot100, TRUE);
        gtk_custom_table_sort(nb_tab_bot100, 0, GTK_CUSTOM_TABLE_ASC);

        return 1;
    }

    return 0;
}

