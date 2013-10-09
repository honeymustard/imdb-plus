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


void ui_fill_lists_lst_empty() {

    int i = 0;
    char temp[10];

    GtkWidget *table = nb_lists_lst_tab->table;

    for(i = 0; i < 50; i++) {

        sprintf(temp, "%d", i+1);

        gtk_custom_table_set_cell_text(table, 0, i, temp);
        gtk_custom_table_set_cell_text(table, 1, i, "0.0");
        gtk_custom_table_set_cell_text(table, 2, i, "0");
        gtk_custom_table_set_cell_text(table, 3, i, "N/A");
        gtk_custom_table_set_cell_text(table, 4, i, "N/A");
        gtk_custom_table_set_cell_text(table, 5, i, "0");
        gtk_custom_table_set_cell_text(table, 6, i, "0");
    }
}


void ui_fill_lists_lst(State *state, ResultList *list) {

    /* make some aliases */
    GtkWidget *table1 = state->tab1->table;
    GtkWidget *table2 = state->tab2->table;

    gtk_notebook_set_tab_label_text(GTK_NOTEBOOK(note), 
        state->tab1->vbox, globals_get(CONST_OPEN_T));

    int i = 0;
    int j = 0;

    Movie *movie = calloc(1, sizeof(Movie));

    char temp[100];

    gtk_custom_table_resize(table1, -1, list->rows - 1);

    for(i = 1, j = 0; i < list->rows; i++, j++) {

        strcpy(movie->id_str, list->results[i][1]);
        strcpy(movie->name_str, list->results[i][5]);

        movie->vote = 0;
        movie->imdb = strtod(list->results[i][8], NULL);
        movie->time = strtol(list->results[i][9], NULL, 10);
        movie->year = strtol(list->results[i][10], NULL, 10);
     
        ui_fill_add_imdb(state->stats, movie);

        sprintf(temp, "%d", i);
        gtk_custom_table_set_cell_text(table1, 0, j, 
            temp);
        gtk_custom_table_set_cell_text(table1, 1, j, 
            movie->imdb_str); 
        gtk_custom_table_set_cell_text(table1, 2, j, 
            "0");
        gtk_custom_table_set_cell_text(table1, 3, j, 
            movie->id_str);
        gtk_custom_table_set_cell_text(table1, 4, j, 
            movie->name_str);
        gtk_custom_table_set_cell_text(table1, 5, j, 
            movie->time_str);
        gtk_custom_table_set_cell_text(table1, 6, j, 
            movie->year_str);

        /* set background colors */
        gtk_custom_table_set_cell_color(table1, 1, j, 
            not_app);
        gtk_custom_table_set_cell_color(table1, 2, j, 
            not_app);

        /* set cell colors for imdb and vote values */
        gtk_custom_table_set_cell_color(table1, 1, j, 
            (int)movie->imdb > 0 ? colors[(int)movie->imdb - 1] : not_app);
        gtk_custom_table_set_cell_color(table1, 2, j, 
            not_app);

        int index = 0;

        /* add 'my rating' to lists tab if applicable */
        if((index = gtk_custom_table_get_indexof(table2, 
                movie->id_str)) >= 0) {
            
            char *rating = gtk_custom_table_get_cell_text(table2, 2, 
                index);

            /* add new background color to rating */
            gtk_custom_table_set_cell_text(table1, 2, j, 
                rating);

            gtk_custom_table_set_cell_color(table1, 2, j, 
                atoi(rating) > 0 ? colors[atoi(rating) - 1] : not_app);
        }

        GtkWidget *tab_box = nb_lists_box_tab->table;

        /* add imdb-rating to boxoffice tab if applicable */
        if((index = gtk_custom_table_get_indexof(tab_box, 
                movie->id_str)) >= 0) {

            gtk_custom_table_set_cell_text(tab_box, 1, 
                index, movie->imdb_str);

            int color = (int)movie->imdb > 0 ? (int)movie->imdb - 1 : 0;

            gtk_custom_table_set_cell_color(tab_box, 1, 
                index, colors[color]);
        }
    }
}

