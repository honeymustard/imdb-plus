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


#include "../ui.h"


/* parse new top 250 list */
int menu_signal_update_top() {

    int i = 0;

    int cols = 0;
    int rows = 0;

    char ***results;
    
    if(read_file(get_global(CONST_TOP_CSV), &cols, &rows, &results) 
        && rows == 250 && cols == 6) {

        for(i = 0; i < gtk_custom_table_get_rows(nb_tab_top250); i++) {

            gtk_custom_table_set_cell_text(nb_tab_top250, 0, i, 
                results[i][0]);
            gtk_custom_table_set_cell_text(nb_tab_top250, 1, i, 
                results[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_top250, 2, i, 
                "0");
            gtk_custom_table_set_cell_text(nb_tab_top250, 3, i, 
                results[i][2]);
            gtk_custom_table_set_cell_text(nb_tab_top250, 4, i, 
                results[i][3]);
            gtk_custom_table_set_cell_text(nb_tab_top250, 5, i, 
                results[i][4]);
            gtk_custom_table_set_cell_text(nb_tab_top250, 6, i, 
                results[i][5]);

            /* set cell colors */
            int rating = (int)atof(results[i][1]);

            gtk_custom_table_set_cell_color(nb_tab_top250, 1, i, 
                colors[rating <= 10 && rating > 0 ? rating : 0]); 

            gtk_custom_table_set_cell_color(nb_tab_top250, 2, i, not_app);
        }

        free_memory(results, cols, rows);

        gtk_custom_table_set_sortable(nb_tab_top250, TRUE);
        gtk_custom_table_sort(nb_tab_top250, 0, GTK_CUSTOM_TABLE_ASC);
        gtk_custom_table_set_column_font(nb_tab_top250, 4, TEXT_FONT); 

        return 1;
    }
    /* no top250 file on disk, add default values.. */
    else {

        char temp[10];

        for(i = 0; i < 250; i++) {

            sprintf(temp, "%d", i+1);

            gtk_custom_table_set_cell_text(nb_tab_top250, 0, i, 
                temp);
            gtk_custom_table_set_cell_text(nb_tab_top250, 1, i, 
                "0.0");
            gtk_custom_table_set_cell_text(nb_tab_top250, 2, i, 
                "N/A");
            gtk_custom_table_set_cell_text(nb_tab_top250, 3, i, 
                "0");
            gtk_custom_table_set_cell_text(nb_tab_top250, 4, i, 
                "N/A");
            gtk_custom_table_set_cell_text(nb_tab_top250, 5, i, 
                "0");
            gtk_custom_table_set_cell_text(nb_tab_top250, 6, i, 
                "0");
        }
    }

    return 0;
}


