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
#include <libgen.h>


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
    state->tab1->is_open = 1;

    globals_set(CONST_PATHNAME, filename);

    if(tab == nb_lists_mov_tab) {

        globals_set(CONST_OPEN_MOV, filename);

        row = 0;

        state->tab1_vcol = 2;
        state->tab2_vcol = 3;
        state->tab2 = nb_lists_lst_tab;
        state->stat = nb_stats_mov_tab;
    }
    else if(tab == nb_lists_lst_tab) {

        globals_set(CONST_OPEN_LST, filename);

        row = 1;

        state->tab1_vcol = 3;
        state->tab2_vcol = 2;
        state->tab2 = nb_lists_mov_tab;
        state->stat = nb_stats_lst_tab;
    }
    else {

        return 0;
    }

    filename = globals_get(CONST_PATHNAME);

    char *temp = malloc(strlen(filename));
    strcpy(temp, filename);

    char *filebase = basename(temp);

    char filetabs[255];
    char filestat[255];

    strcpy(filetabs, filebase); 
    strcpy(&filetabs[15], "...");

    strcpy(filestat, "Stats: ");
    strcat(filestat, filetabs);

    globals_set(CONST_BASENAME, filebase);

    /* set notebook titles */
    gtk_notebook_set_tab_label_text(GTK_NOTEBOOK(mwin->note), 
        state->tab1->vbox, filetabs);
    gtk_notebook_set_tab_label_text(GTK_NOTEBOOK(mwin->note), 
        state->stat->vbox, filestat);

    free(temp);

    /* opened file is a ratings list */
    if(strcmp("IMDb Rating", list->results[0][9]) == 0) {

        tab->type = TAB_TYPE_MOV;
        ui_fill_lists_mov(state, list);
        ui_fill_lists_mov_add(state);
        ui_fill_stats_avg(state->stats);
        ui_fill_stats_mov(state);
        ui_fill_stats_all(state, rows[row]);
    }
    /* opened file is a regular list */
    else {

        tab->type = TAB_TYPE_LST;
        ui_fill_lists_lst(state, list);
        ui_fill_lists_lst_add(state);
        ui_fill_stats_avg(state->stats);
        ui_fill_stats_lst(state);
        ui_fill_stats_all(state, rows[row]);
    }

    /* sort and set tables */
    GtkWidget *table_t = state->tab1->table;
    GtkWidget *table_s = state->stat->table;

    gtk_custom_table_set_sortable(table_t, TRUE);
    gtk_custom_table_set_sortable(table_s, TRUE);
    gtk_custom_table_sort(table_s, 0, GTK_CUSTOM_TABLE_DESC);
    gtk_custom_table_sort(table_t, 0, GTK_CUSTOM_TABLE_ASC);
    gtk_custom_table_set_column_font(table_t, 5, TEXT_FONT); 

    readfile_free(list);

    /* fill comparison tab if applicable */
    if(state->tab1->is_open && state->tab2->is_open) {

        State *s = calloc(1, sizeof(State));
        s->stats = calloc(1, sizeof(Stats));

        s->tab1 = nb_lists_cmp_tab;
        s->tab2 = nb_lists_mov_tab;
        s->tab3 = nb_lists_lst_tab;
        s->stat = nb_stats_cmp_tab;

        ui_fill_lists_cmp(s);
        ui_fill_lists_cmp_add(s);
        ui_fill_stats_avg(s->stats);
        ui_fill_stats_cmp(s);
        ui_fill_stats_all(s, rows[2]);

        table_t = s->tab1->table;
        table_s = s->stat->table;

        /* set sortable and sort by index */
        gtk_custom_table_set_sortable(table_t, TRUE);
        gtk_custom_table_set_sortable(table_s, TRUE);
        gtk_custom_table_sort(table_s, 0, GTK_CUSTOM_TABLE_DESC);
        gtk_custom_table_sort(table_t, 0, GTK_CUSTOM_TABLE_ASC);
        gtk_custom_table_set_column_font(table_t, 5, TEXT_FONT); 

        free(s->stats);
        free(s);
    }

    free(state->stats);
    free(state);
   
    ui_fill_lists_box_update();
    gtk_custom_table_refresh(mwin->main);

    return 1;
}

