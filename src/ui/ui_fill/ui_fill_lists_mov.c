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


void ui_fill_lists_mov_empty() {

    int i = 0;
    char temp[10];

    for(i = 0; i < 50; i++) {

        sprintf(temp, "%d", i+1);

        gtk_custom_table_set_cell_text(nb_lists_mov_tab, 0, i, 
            temp);
        gtk_custom_table_set_cell_text(nb_lists_mov_tab, 1, i, 
            "0.0");
        gtk_custom_table_set_cell_text(nb_lists_mov_tab, 2, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_lists_mov_tab, 3, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_lists_mov_tab, 4, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_lists_mov_tab, 5, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_lists_mov_tab, 6, i, 
            "0");
    }
}


void ui_fill_lists_mov(char ****results, int rows) {
    
    int i = 0;
    int j = 0;

    /* clear associated color from lists */
    for(i = 0; i < gtk_custom_table_get_rows(nb_lists_lst_tab); i++) {
        
        gtk_custom_table_set_cell_text(nb_lists_lst_tab, 2, i, 
            "0");
        gtk_custom_table_set_cell_color(nb_lists_lst_tab, 2, i, 
            not_app);
    }

    /* clear associated color from top250 */
    for(i = 0; i < gtk_custom_table_get_rows(nb_lists_top_tab); i++) {
        
        gtk_custom_table_set_cell_text(nb_lists_top_tab, 2, i, 
            "0");
        gtk_custom_table_set_cell_color(nb_lists_top_tab, 2, i, 
            not_app);
    }

    /* clear associated color from bot100 */
    for(i = 0; i < gtk_custom_table_get_rows(nb_lists_bot_tab); i++) {
        
        gtk_custom_table_set_cell_text(nb_lists_bot_tab, 2, i, 
            "0");
        gtk_custom_table_set_cell_color(nb_lists_bot_tab, 2, i, 
            not_app);
    }

    /* clear associated color from boxoffice */
    for(i = 0; i < gtk_custom_table_get_rows(nb_lists_box_tab); i++) {
        
        gtk_custom_table_set_cell_text(nb_lists_box_tab, 2, i, 
            "0");
        gtk_custom_table_set_cell_color(nb_lists_box_tab, 2, i, 
            not_app);
    }

    Movie *movie = malloc(sizeof(Movie));
    Stats *stats = calloc(1, sizeof(Stats));

    char temp[100];

    /* update mymovies tab with new data */
    gtk_custom_table_resize(nb_lists_mov_tab, -1, rows - 1);

    /* add text to widget table */
    for(i = 1, j = 0; i < rows; i++, j++) {

        ui_fill_stats_mov_calc(stats, movie, (*results)[i]);

        /* add text to cells */
        sprintf(temp, "%d", i);
        gtk_custom_table_set_cell_text(nb_lists_mov_tab, 0, j, 
            temp);
        gtk_custom_table_set_cell_text(nb_lists_mov_tab, 1, j, 
            movie->imdb_str);
        gtk_custom_table_set_cell_text(nb_lists_mov_tab, 2, j, 
            movie->vote_str);
        gtk_custom_table_set_cell_text(nb_lists_mov_tab, 3, j, 
            movie->id);
        gtk_custom_table_set_cell_text(nb_lists_mov_tab, 4, j, 
            movie->title);
        gtk_custom_table_set_cell_text(nb_lists_mov_tab, 5, j, 
            movie->time_str);
        gtk_custom_table_set_cell_text(nb_lists_mov_tab, 6, j, 
            movie->year_str);

        /* set background colors */
        gtk_custom_table_set_cell_color(nb_lists_mov_tab, 1, j, 
            not_app);
        gtk_custom_table_set_cell_color(nb_lists_mov_tab, 2, j, 
            not_app);

        /* set cell colors for imdb and vote values */
        gtk_custom_table_set_cell_color(nb_lists_mov_tab, 1, j, 
            (int)movie->imdb > 0 ? colors[(int)movie->imdb - 1] : not_app);
        gtk_custom_table_set_cell_color(nb_lists_mov_tab, 2, j, 
            (int)movie->vote > 0 ? colors[(int)movie->vote - 1] : not_app);

        int index = 0;

        /* add 'my rating' to top250 tab */
        if((index = gtk_custom_table_get_indexof(nb_lists_top_tab, 
                movie->id)) >= 0) {

            gtk_custom_table_set_cell_text(nb_lists_top_tab, 2, 
                index, movie->vote_str);

            gtk_custom_table_set_cell_color(nb_lists_top_tab, 2, 
                index, colors[(int)movie->vote > 0 ? (int)movie->vote - 1 : 0]);
        }

        /* add 'my rating' to bottom100 tab if applicable */
        if((index = gtk_custom_table_get_indexof(nb_lists_bot_tab, 
                movie->id)) >= 0) {

            /* set cell values */
            gtk_custom_table_set_cell_text(nb_lists_bot_tab, 2, 
                index, movie->vote_str);

            gtk_custom_table_set_cell_color(nb_lists_bot_tab, 2, 
                index, colors[(int)movie->vote > 0 ? (int)movie->vote - 1 : 0]);
        }

        /* add 'my rating' and imdb-rating to boxoffice */
        if((index = gtk_custom_table_get_indexof(nb_lists_box_tab, 
                movie->id)) >= 0) {

            /* set cell values */
            gtk_custom_table_set_cell_text(nb_lists_box_tab, 1, 
                index, movie->imdb_str);
            gtk_custom_table_set_cell_text(nb_lists_box_tab, 2, 
                index, movie->vote_str);

            /* set cell colors */
            gtk_custom_table_set_cell_color(nb_lists_box_tab, 1, 
                index, colors[(int)movie->imdb > 0 ? (int)movie->imdb - 1 : 0]);
            gtk_custom_table_set_cell_color(nb_lists_box_tab, 2, 
                index, colors[(int)movie->vote > 0 ? (int)movie->vote - 1 : 0]);
        }

        /* add 'my rating' to lists tab if applicable */
        if((index = gtk_custom_table_get_indexof(nb_lists_lst_tab, 
                movie->id)) >= 0) {

            gtk_custom_table_set_cell_text(nb_lists_lst_tab, 2, 
                index, movie->vote_str);
            gtk_custom_table_set_cell_color(nb_lists_lst_tab, 2, 
                index, colors[(int)movie->vote > 0 ? (int)movie->vote - 1 : 0]);
        }
    }

    ui_fill_stats_avg_calc(stats, rows);

    ui_fill_stats_mov(stats, rows);
    ui_fill_stats_all(stats, 1, 5, 9);

    free(stats);
    free(movie);

    /* set sortable and sort by index */
    gtk_custom_table_set_sortable(nb_lists_mov_tab, TRUE);
    gtk_custom_table_sort(nb_lists_mov_tab, 0, GTK_CUSTOM_TABLE_ASC);
    gtk_custom_table_set_column_font(nb_lists_mov_tab, 4, TEXT_FONT); 
}

