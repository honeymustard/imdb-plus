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
#include "ui/env/colors.h"
#include "ui/ui_fill/ui_fill.h"
#include "ui/table/gtk_custom_table.h"
#include "io/readfile.h"


/* parse a new list */
int fill_list(GtkWidget *table, char *filename, int x, int y) {

    int i = 0;

    int cols = 0;
    int rows = 0;

    char temp[50];
    char ***results = NULL;
    
    if(read_file(filename, &cols, &rows, &results) 
        && cols == x && rows == y) {

        for(i = 0; i < gtk_custom_table_get_rows(table); i++) {

            /* make results numeric */
            double imdb = strtod(results[i][1], NULL);
            double year = strtol(results[i][4], NULL, 10);

            imdb = imdb >= 0 && imdb <= 10 ? imdb : 0;
            year = year > 1800 && year < 2200 ? year : 0;

            sprintf(temp, "%d", i + 1);
            gtk_custom_table_set_cell_text(table, 0, i, 
                temp);

            sprintf(temp, "%1.1f", imdb);
            gtk_custom_table_set_cell_text(table, 1, i, 
                temp);

            gtk_custom_table_set_cell_text(table, 2, i, 
                "0");

            gtk_custom_table_set_cell_text(table, 3, i, 
                results[i][2]);

            gtk_custom_table_set_cell_text(table, 4, i, 
                results[i][3]);

            sprintf(temp, "%d", (int)year);
            gtk_custom_table_set_cell_text(table, 5, i, 
                temp);

            gtk_custom_table_set_cell_text(table, 6, i, 
                results[i][5]);

            /* set cell colors */
            gtk_custom_table_set_cell_color(table, 1, i, 
                colors[(int)imdb]); 

            gtk_custom_table_set_cell_color(table, 2, i, 
                not_app);
        }

        free_memory(results, cols, rows);

        gtk_custom_table_set_sortable(table, TRUE);
        gtk_custom_table_sort(table, 0, GTK_CUSTOM_TABLE_ASC);
        gtk_custom_table_set_column_font(table, 4, TEXT_FONT); 

        return 1;
    }
    /* no list file on disk, add default values.. */
    else {

        for(i = 0; i < x; i++) {

            sprintf(temp, "%d", i+1);

            gtk_custom_table_set_cell_text(table, 0, i, 
                temp);
            gtk_custom_table_set_cell_text(table, 1, i, 
                "0.0");
            gtk_custom_table_set_cell_text(table, 2, i, 
                "N/A");
            gtk_custom_table_set_cell_text(table, 3, i, 
                "0");
            gtk_custom_table_set_cell_text(table, 4, i, 
                "N/A");
            gtk_custom_table_set_cell_text(table, 5, i, 
                "0");
            gtk_custom_table_set_cell_text(table, 6, i, 
                "0");
        }
    }

    return 0;
}


/* parse new top 250 list */
int menu_signal_update_top() {
    
    return fill_list(nb_tab_top250, get_global(CONST_TOP_CSV), 6, 250);
}

/* parse new bottom 100 list */
int menu_signal_update_bot() {

    return fill_list(nb_tab_bot100, get_global(CONST_BOT_CSV), 6, 100);
}

