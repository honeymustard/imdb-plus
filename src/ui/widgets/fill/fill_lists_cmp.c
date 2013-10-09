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


void ui_fill_lists_cmp_empty() {

    int i = 0;
    char temp[10];

    GtkWidget *table = nb_lists_cmp_tab->table;

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


void ui_fill_lists_cmp(State *state) {
    
    gtk_notebook_set_tab_label_text(GTK_NOTEBOOK(note), 
        state->tab1->vbox, globals_get(CONST_OPEN_T));

    /* make some aliases */
    GtkWidget *table1 = state->tab1->table;
    GtkWidget *table2 = state->tab2->table;
    GtkWidget *table3 = state->tab3->table;

    int i = 0;

    char temp[100];

    int total_rows = 0;

    int table_rows1 = gtk_custom_table_get_rows(table2);
    int table_rows2 = gtk_custom_table_get_rows(table3);
    
    int table_min = table_rows1 < table_rows2 ? table_rows1 : table_rows2;

    Movie **movies = malloc(sizeof(Movie *) * table_min);
    Movie *movie = calloc(1, sizeof(Movie));

    for(i = 0; i < table_rows1; i++) {

        char *id = gtk_custom_table_get_cell_text(table2, 3, i);

        if(gtk_custom_table_get_indexof(table3, id) < 0) {
            continue;
        }

        strcpy(movie->id_str, id);
        strcpy(movie->name_str, gtk_custom_table_get_cell_text(table2, 4, i));

        movie->vote = atof(gtk_custom_table_get_cell_text(table2, 2, i));
        movie->imdb = atof(gtk_custom_table_get_cell_text(table2, 1, i));
        movie->time = atof(gtk_custom_table_get_cell_text(table2, 5, i));
        movie->year = atof(gtk_custom_table_get_cell_text(table2, 6, i));

        ui_fill_add_vote(state->stats, movie);

        movies[total_rows] = calloc(1, sizeof(Movie));
        memcpy(movies[total_rows], movie, sizeof(Movie));
        
        total_rows++;
    }

    gtk_custom_table_resize(table1, -1, total_rows);

    for(i = 0; i < total_rows; i++) {

        sprintf(temp, "%d", i + 1);

        gtk_custom_table_set_cell_text(table1, 0, i, 
            temp);
        gtk_custom_table_set_cell_text(table1, 1, i, 
            movies[i]->imdb_str);
        gtk_custom_table_set_cell_text(table1, 2, i, 
            movies[i]->vote_str);
        gtk_custom_table_set_cell_text(table1, 3, i, 
            movies[i]->id_str);
        gtk_custom_table_set_cell_text(table1, 4, i, 
            movies[i]->name_str);
        gtk_custom_table_set_cell_text(table1, 5, i, 
            movies[i]->time_str);
        gtk_custom_table_set_cell_text(table1, 6, i, 
            movies[i]->year_str);

        /* set background colors */
        gtk_custom_table_set_cell_color(table1, 1, i, 
            not_app);
        gtk_custom_table_set_cell_color(table1, 2, i, 
            not_app);

        int imdb = (int)movies[i]->imdb;
        int vote = (int)movies[i]->vote;

        /* set cell colors for imdb and vote values */
        gtk_custom_table_set_cell_color(table1, 1, i, 
            imdb > 0 ? colors[imdb - 1] : not_app);
        gtk_custom_table_set_cell_color(table1, 2, i, 
            vote > 0 ? colors[vote - 1] : not_app);

        free(movies[i]);
    }

    free(movies);
    free(movie);
}

