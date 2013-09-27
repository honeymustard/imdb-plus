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


#include "ui/globals/globals.h"
#include "ui/widgets/widgets.h"
#include "ui/widgets/fill/fill.h"
#include "ui/env/colors.h"
#include "ui/table/gtk_custom_table.h"
#include "io/readfile.h"


#define TOP_COLS 6
#define TOP_ROWS 250


void ui_fill_lists_top_empty() {

    int i = 0;

    char temp[10];

    for(i = 0; i < TOP_ROWS; i++) {

        sprintf(temp, "%d", i+1);

        gtk_custom_table_set_cell_text(nb_lists_top_tab->table, 0, i, 
            temp);
        gtk_custom_table_set_cell_text(nb_lists_top_tab->table, 1, i, 
            "0.0");
        gtk_custom_table_set_cell_text(nb_lists_top_tab->table, 2, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_lists_top_tab->table, 3, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_lists_top_tab->table, 4, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_lists_top_tab->table, 5, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_lists_top_tab->table, 6, i, 
            "0");
    }
}


void ui_fill_lists_top(ResultList *list, NotebookTab *tab) {

    int i = 0;
    char temp[50];

    for(i = 0; i < list->rows; i++) {

        double imdb = strtod(list->results[i][1], NULL);
        double year = strtol(list->results[i][4], NULL, 10);

        imdb = imdb >= 0 && imdb <= 10 ? imdb : 0;
        year = year > 1800 && year < 2200 ? year : 0;

        sprintf(temp, "%d", i + 1);
        gtk_custom_table_set_cell_text(tab->table, 0, i, 
            temp);
        sprintf(temp, "%1.1f", imdb);
        gtk_custom_table_set_cell_text(tab->table, 1, i, 
            temp);
        gtk_custom_table_set_cell_text(tab->table, 2, i, 
            "0");
        gtk_custom_table_set_cell_text(tab->table, 3, i, 
            list->results[i][2]);
        gtk_custom_table_set_cell_text(tab->table, 4, i, 
            list->results[i][3]);
        sprintf(temp, "%d", (int)year);
        gtk_custom_table_set_cell_text(tab->table, 5, i, 
            temp);
        gtk_custom_table_set_cell_text(tab->table, 6, i, 
            list->results[i][5]);

        /* set cell colors */
        gtk_custom_table_set_cell_color(tab->table, 1, i, 
            colors[(int)imdb]); 

        gtk_custom_table_set_cell_color(tab->table, 2, i, 
            not_app);
    }

    gtk_custom_table_set_sortable(tab->table, TRUE);
    gtk_custom_table_sort(tab->table, 0, GTK_CUSTOM_TABLE_ASC);
    gtk_custom_table_set_column_font(tab->table, 4, TEXT_FONT); 
}


int ui_fill_lists_top_update() {
 
    ResultList *list = calloc(1, sizeof(ResultList));
    
    if(readfile(list, get_global(CONST_TOP_CSV)) 
        && list->cols == TOP_COLS && list->rows == TOP_ROWS) {
   
        ui_fill_lists_top(list, nb_lists_top_tab);

        readfile_free(list);

        return 1;
    }

    free(list);

    ui_fill_lists_top_empty();

    return 0;
}


