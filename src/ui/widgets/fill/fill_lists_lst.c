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


void ui_fill_lists_lst_empty() {

    int i = 0;

    char temp[10];

    for(i = 0; i < 50; i++) {

        sprintf(temp, "%d", i+1);

        gtk_custom_table_set_cell_text(nb_lists_lst_tab->table, 0, i, 
            temp);
        gtk_custom_table_set_cell_text(nb_lists_lst_tab->table, 1, i, 
            "0.0");
        gtk_custom_table_set_cell_text(nb_lists_lst_tab->table, 2, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_lists_lst_tab->table, 3, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_lists_lst_tab->table, 4, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_lists_lst_tab->table, 5, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_lists_lst_tab->table, 6, i, 
            "0");
    }
}


void ui_fill_lists_lst(ResultList *list, NotebookTab *tab, Stats *stats) {

    gtk_notebook_set_tab_label_text(GTK_NOTEBOOK(note), 
        tab->vbox, get_global(CONST_OPEN_T));

    int i = 0;
    int j = 0;

    Movie *movie = malloc(sizeof(Movie));

    char temp[100];

    gtk_custom_table_resize(tab->table, -1, list->rows - 1);

    for(i = 1, j = 0; i < list->rows; i++, j++) {

        ui_fill_stats_lst_calc(stats, movie, list->results[i]);

        sprintf(temp, "%d", i);
        gtk_custom_table_set_cell_text(tab->table, 0, j, 
            temp);
        gtk_custom_table_set_cell_text(tab->table, 1, j, 
            movie->imdb_str); 
        gtk_custom_table_set_cell_text(tab->table, 2, j, 
            "0");
        gtk_custom_table_set_cell_text(tab->table, 3, j, 
            movie->id);
        gtk_custom_table_set_cell_text(tab->table, 4, j, 
            movie->title);
        gtk_custom_table_set_cell_text(tab->table, 5, j, 
            movie->time_str);
        gtk_custom_table_set_cell_text(tab->table, 6, j, 
            movie->year_str);

        /* set background colors */
        gtk_custom_table_set_cell_color(tab->table, 1, j, 
            not_app);
        gtk_custom_table_set_cell_color(tab->table, 2, j, 
            not_app);

        /* set cell colors for imdb and vote values */
        gtk_custom_table_set_cell_color(tab->table, 1, j, 
            (int)movie->imdb > 0 ? colors[(int)movie->imdb - 1] : not_app);
        gtk_custom_table_set_cell_color(tab->table, 2, j, 
            not_app);

        /*
        int index = 0;

        * add 'my rating' to lists tab if applicable *
        if((index = gtk_custom_table_get_indexof(nb_lists_mov_tab, 
                movie->id)) >= 0) {
            
            char *rating = gtk_custom_table_get_cell_text(nb_lists_mov_tab, 2, 
                index);

            * add new background color to rating *
            gtk_custom_table_set_cell_text(tab->table, 2, j, 
                rating);

            gtk_custom_table_set_cell_color(tab->table, 2, j, 
                atoi(rating) > 0 ? colors[atoi(rating) - 1] : not_app);
        }

        * add imdb-rating to boxoffice tab if applicable *
        if((index = gtk_custom_table_get_indexof(nb_lists_box_tab, 
                movie->id)) >= 0) {

            gtk_custom_table_set_cell_text(nb_lists_box_tab, 1, 
                index, movie->imdb_str);

            gtk_custom_table_set_cell_color(nb_lists_box_tab, 1, 
                index, colors[(int)movie->imdb > 0 ? (int)movie->imdb - 1 : 0]);
        }
        */
    }

    ui_fill_stats_avg(stats);

    free(movie);

    /* set sortable and sort by index */
    gtk_custom_table_set_sortable(tab->table, TRUE);
    gtk_custom_table_sort(tab->table, 0, GTK_CUSTOM_TABLE_ASC);
    gtk_custom_table_set_column_font(tab->table, 4, TEXT_FONT); 
}

