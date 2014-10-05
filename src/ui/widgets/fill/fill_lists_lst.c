/***********************************************************************
 *
 * Copyright (C) 2011-2014  Adrian Solumsmo
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
#include "gtk-custom-table/include/gtk_custom_table.h"


void ui_fill_lists_lst_empty() {

    int i = 0;
    char temp[10];

    GtkWidget *table = nb_lists_lst_tab->table;

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


/**
 * fill a tab with values from a list file
 * @param State *state        current state
 * @param ResultList *list    filelist with data
 */
void ui_fill_lists_lst(State *state, ResultList *list) {

    /* make some aliases */
    GtkWidget *table1 = state->tab1->table;

    int i = 0;
    int j = 0;

    Movie *movie = calloc(1, sizeof(Movie));

    char temp[100];

    /* update tab with new data */
    gtk_custom_table_resize(table1, -1, list->rows - 1);

    for(i = 1, j = 0; i < list->rows; i++, j++) {

        strcpy(movie->id_str, list->results[i][1]);
        strcpy(movie->name_str, list->results[i][5]);

        movie->vote = 0;
        movie->imdb = strtod(list->results[i][8], NULL);
        movie->time = strtol(list->results[i][9], NULL, 10);
        movie->year = strtol(list->results[i][10], NULL, 10);
     
        ui_fill_stats_lst_add(state->stats, movie);

        /* add text to cells */
        sprintf(temp, "%d", i);
        gtk_custom_table_set_cell_text(table1, 0, j, temp);
        gtk_custom_table_set_cell_text(table1, 1, j, movie->imdb_str); 
        gtk_custom_table_set_cell_text(table1, 2, j, "0");
        gtk_custom_table_set_cell_text(table1, 3, j, "0");
        gtk_custom_table_set_cell_text(table1, 4, j, movie->id_str);
        gtk_custom_table_set_cell_text(table1, 5, j, movie->name_str);
        gtk_custom_table_set_cell_text(table1, 6, j, movie->time_str);
        gtk_custom_table_set_cell_text(table1, 7, j, movie->year_str);

        /* set background colors */
        gtk_custom_table_set_cell_color(table1, 1, j, not_app);
        gtk_custom_table_set_cell_color(table1, 2, j, not_app);
        gtk_custom_table_set_cell_color(table1, 3, j, not_app);

        /* set cell colors for imdb and vote values */
        int imdb = (int)movie->imdb;

        gtk_custom_table_set_cell_color(table1, 1, j, 
            imdb > 0 ? colors[imdb - 1] : not_app);
        gtk_custom_table_set_cell_color(table1, 2, j, not_app);
        gtk_custom_table_set_cell_color(table1, 3, j, not_app);
    }
}

