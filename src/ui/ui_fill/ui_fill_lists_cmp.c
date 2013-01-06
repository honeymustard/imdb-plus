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


#include "ui/ui.h"
#include "ui/env/colors.h"
#include "ui/ui_fill/ui_fill.h"
#include "ui/table/gtk_custom_table.h"


void ui_fill_lists_cmp_empty() {

    int i = 0;
    char temp[10];

    for(i = 0; i < 50; i++) {

        sprintf(temp, "%d", i+1);

        gtk_custom_table_set_cell_text(nb_lists_cmp_tab, 0, i, 
            temp);
        gtk_custom_table_set_cell_text(nb_lists_cmp_tab, 1, i, 
            "0.0");
        gtk_custom_table_set_cell_text(nb_lists_cmp_tab, 2, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_lists_cmp_tab, 3, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_lists_cmp_tab, 4, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_lists_cmp_tab, 5, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_lists_cmp_tab, 6, i, 
            "0");
    }
}


void ui_fill_lists_cmp(GtkWidget *table1, GtkWidget *table2) {
    
    int i = 0;

    Movie *movie = malloc(sizeof(Movie));
    Stats *stats = calloc(1, sizeof(Stats));

    char temp[100];

    int total_rows = 0;

    int table_rows1 = gtk_custom_table_get_rows(table1);
    int table_rows2 = gtk_custom_table_get_rows(table2);
    
    int table_min = table_rows1 < table_rows2 ? table_rows1 : table_rows2;

    Movie **movies = malloc(sizeof(Movie *) * table_min);

    for(i = 0; i < table_rows1; i++) {

        char *id = gtk_custom_table_get_cell_text(table1, 3, i);

        if(gtk_custom_table_get_indexof(table2, id) < 0) {
            continue;
        }

        ui_fill_stats_cmp_calc(stats, movie, i, table1, id);

        movies[total_rows] = malloc(sizeof(Movie));
        memcpy(movies[total_rows], movie, sizeof(Movie));
        
        total_rows++;
    }

    gtk_custom_table_resize(nb_lists_cmp_tab, -1, total_rows);

    for(i = 0; i < total_rows; i++) {

        gtk_custom_table_set_cell_text(nb_lists_cmp_tab, 1, i, 
            movies[i]->imdb_str);
        gtk_custom_table_set_cell_text(nb_lists_cmp_tab, 2, i, 
            movies[i]->vote_str);
        gtk_custom_table_set_cell_text(nb_lists_cmp_tab, 3, i, 
            movies[i]->id);
        gtk_custom_table_set_cell_text(nb_lists_cmp_tab, 4, i, 
            movies[i]->title);
        gtk_custom_table_set_cell_text(nb_lists_cmp_tab, 5, i, 
            movies[i]->time_str);
        gtk_custom_table_set_cell_text(nb_lists_cmp_tab, 6, i, 
            movies[i]->year_str);

        /* set background colors */
        gtk_custom_table_set_cell_color(nb_lists_cmp_tab, 1, i, 
            not_app);
        gtk_custom_table_set_cell_color(nb_lists_cmp_tab, 2, i, 
            not_app);

        int imdb = (int)movies[i]->imdb;
        int vote = (int)movies[i]->vote;

        /* set cell colors for imdb and vote values */
        gtk_custom_table_set_cell_color(nb_lists_cmp_tab, 1, i, 
            imdb > 0 ? colors[imdb - 1] : not_app);
        gtk_custom_table_set_cell_color(nb_lists_cmp_tab, 2, i, 
            vote > 0 ? colors[vote - 1] : not_app);

        free(movies[i]);
    }

    free(movies);

    ui_fill_stats_avg_calc(stats, total_rows);

    ui_fill_stats_cmp(stats, total_rows);
    ui_fill_stats_all(stats, 3, 7, 11);

    free(stats);
    free(movie);

    /* set sortable and sort by index */
    gtk_custom_table_set_sortable(nb_lists_cmp_tab, TRUE);
    gtk_custom_table_sort(nb_lists_cmp_tab, 2, GTK_CUSTOM_TABLE_DESC);
    gtk_custom_table_set_column_font(nb_lists_cmp_tab, 4, TEXT_FONT); 

    for(i = 0; i < total_rows; i++) {

        sprintf(temp, "%d", i + 1);

        gtk_custom_table_set_cell_text(nb_lists_cmp_tab, 0, i, 
            temp);
    }
}

