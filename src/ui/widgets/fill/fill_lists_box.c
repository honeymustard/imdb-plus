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
#include "ui/env/colors.h"
#include "ui/table/gtk_custom_table.h"
#include "io/readfile.h"


void ui_fill_lists_box_empty() {

    int i = 0;
    char temp[50];

    GtkWidget *table = nb_lists_box_tab->table;

    for(i = 0; i < 50; i++) {

        sprintf(temp, "%d", i+1);

        gtk_custom_table_set_cell_text(table, 0, i, temp);
        gtk_custom_table_set_cell_text(table, 1, i, "0.0");
        gtk_custom_table_set_cell_text(table, 2, i, "0");
        gtk_custom_table_set_cell_text(table, 3, i, "0");
        gtk_custom_table_set_cell_text(table, 4, i, "N/A");
        gtk_custom_table_set_cell_text(table, 5, i, "N/A");
        gtk_custom_table_set_cell_text(table, 6, i, "0");
        gtk_custom_table_set_cell_text(table, 7, i, "0");
    }
}


void ui_fill_lists_box(ResultList *list) {

    int i = 0;
    char temp[50];

    GtkWidget *table = nb_lists_box_tab->table;

    gtk_custom_table_resize(table, -1, list->rows);

    for(i = 0; i < list->rows; i++) {

        double imdb = strtod(list->results[i][5], NULL);
        double year = strtol(list->results[i][3], NULL, 10);

        imdb = imdb >= 0 && imdb <= 10 ? imdb : 0;
        year = year > 1800 && year < 2200 ? year : 0;

        sprintf(temp, "%d", i + 1);
        gtk_custom_table_set_cell_text(table, 0, i, temp);
        sprintf(temp, "%1.1f", imdb);
        gtk_custom_table_set_cell_text(table, 1, i, temp);
        gtk_custom_table_set_cell_text(table, 2, i, "0");
        gtk_custom_table_set_cell_text(table, 3, i, "0");
        gtk_custom_table_set_cell_text(table, 4, i, list->results[i][1]);
        gtk_custom_table_set_cell_text(table, 5, i, list->results[i][2]);
        sprintf(temp, "%d", (int)year);
        gtk_custom_table_set_cell_text(table, 6, i, temp);

        char *strip = gtk_custom_table_string_strip_alpha(list->results[i][4]);
        char *value = gtk_custom_table_string_thousand_separator(strip);

        gtk_custom_table_set_cell_text(table, 7, i, value);

        free(strip);
        free(value);

        /* set cell colors */
        gtk_custom_table_set_cell_color(table, 1, i, 
            (int)imdb > 0 ? colors[(int)imdb - 1] : not_app);
        gtk_custom_table_set_cell_color(table, 2, i, not_app);
        gtk_custom_table_set_cell_color(table, 3, i, not_app);
    }
}


int ui_fill_lists_box_update() {

    ResultList *list = calloc(1, sizeof(ResultList));
    
    if(readfile(list, globals_get(CONST_BOX_CSV)) 
        && list->cols == BOX_COLS) {
        
        ui_fill_lists_box(list);
        ui_fill_lists_box_add(list);

        GtkWidget *table = nb_lists_box_tab->table;

        gtk_custom_table_set_sortable(table, TRUE);
        gtk_custom_table_sort(table, 0, GTK_CUSTOM_TABLE_ASC);
        gtk_custom_table_set_column_font(table, 5, TEXT_FONT); 

        readfile_free(list);

        return 1;
    }

    free(list);

    ui_fill_lists_box_empty();

    return 0;
}

