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
#include "ui/table/gtk_custom_table.h"
#include "io/openfile.h"
#include "io/readfile.h"


/**
 * read and parse a ratings file or list..
 * @param NotebookTab *tab    open file in tab..
 * @param char *filename      filename to open
 */
int open_file(NotebookTab *tab, char *filename) {

    if(filename == NULL) {
        return 0;
    }

    ResultList *list = calloc(1, sizeof(ResultList));
    
    if(!readfile(list, filename) || list->cols < 10) {
        return 0;
    }

    State *state = calloc(1, sizeof(State));
    state->stats = calloc(1, sizeof(Stats));

    int rows[3][3] = {
        {1, 5,  9}, 
        {2, 6, 10}, 
        {3, 7, 11}
    };

    int row = 0;

    state->tab1 = tab;

    if(tab == nb_lists_mov_tab) {

        row = 0;

        state->tab2 = nb_lists_lst_tab;
        state->stat = nb_stats_mov_tab;
    }
    else if(tab == nb_lists_lst_tab) {

        row = 1;

        state->tab2 = nb_lists_mov_tab;
        state->stat = nb_stats_lst_tab;
    }
    else {

        return 0;
    }

    /* attach filenames to tabs */
    if(state->tab1->filename != NULL) {
        free(state->tab1->filename);
    }

    if(state->stat->filename != NULL) {
        free(state->stat->filename);
    }

    state->tab1->filename = malloc(strlen(filename) + 1);
    strcpy(state->tab1->filename, filename);

    state->stat->filename = malloc(strlen(filename) + 1);
    strcpy(state->stat->filename, filename);

    if(strcmp("IMDb Rating", list->results[0][9]) == 0) {

        ui_fill_lists_mov(state, list);
        ui_fill_stats_avg(state->stats);
        ui_fill_stats_mov(state);
        ui_fill_stats_all(state, rows[row]);
    }
    else {

        ui_fill_lists_lst(state, list);
        ui_fill_stats_avg(state->stats);
        ui_fill_stats_lst(state);
        ui_fill_stats_all(state, rows[row]);
    }

    GtkWidget *table_t = state->tab1->table;
    GtkWidget *table_s = state->stat->table;

    gtk_custom_table_set_sortable(table_t, TRUE);
    gtk_custom_table_set_sortable(table_s, TRUE);
    gtk_custom_table_sort(table_t, 0, GTK_CUSTOM_TABLE_ASC);
    gtk_custom_table_set_column_font(table_t, 4, TEXT_FONT); 

    readfile_free(list);

    /* fill comparison tab if applicable */
    if(state->tab1->filename != NULL && 
       state->tab2->filename != NULL) {

        State *s = calloc(1, sizeof(State));
        s->stats = calloc(1, sizeof(Stats));

        s->tab1 = nb_lists_cmp_tab;
        s->tab2 = nb_lists_mov_tab;
        s->tab3 = nb_lists_lst_tab;
        s->stat = nb_stats_cmp_tab;

        ui_fill_lists_cmp(s);
        ui_fill_stats_avg(s->stats);
        ui_fill_stats_cmp(s);
        ui_fill_stats_all(s, rows[2]);

        table_t = s->tab1->table;
        table_s = s->stat->table;

        /* set sortable and sort by index */
        gtk_custom_table_set_sortable(table_t, TRUE);
        gtk_custom_table_set_sortable(table_s, TRUE);
        gtk_custom_table_sort(table_t, 0, GTK_CUSTOM_TABLE_ASC);
        gtk_custom_table_set_column_font(table_t, 4, TEXT_FONT); 

        free(s->stats);
        free(s);
    }

    free(state->stats);
    free(state);
   
    gtk_custom_table_refresh(mwin);

    return 1;
}

