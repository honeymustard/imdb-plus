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


#include "ui/widgets/widgets.h"
#include "ui/widgets/set/set.h"
#include "ui/table/gtk_custom_table.h"


char *nb_stats_mov_headers[COLS_STATS_MOV] = {
    "Vote", 
    "IMDb", 
    "Flux", 
    "Graph", 
    "Percent", 
    "Movies", 
    "Runtime", 
    "Year", 
};

char *nb_stats_lst_headers[COLS_STATS_LST] = {
    "Vote", 
    "IMDb", 
    "Flux", 
    "Graph", 
    "Percent", 
    "Movies", 
    "Runtime", 
    "Year", 
};

char *nb_stats_cmp_headers[COLS_STATS_CMP] = {
    "Vote", 
    "IMDb", 
    "Flux", 
    "Graph", 
    "Percent", 
    "Movies", 
    "Runtime", 
    "Year", 
};

char *nb_stats_all_headers[COLS_STATS_ALL] = {
    "Vote", 
    "IMDb", 
    "Flux", 
    "", 
    "", 
    "Percent", 
    "Movies", 
    "Runtime", 
    "Year",
};

char *nb_lists_mov_headers[COLS_LISTS_MOV] = {
    "#", "IMDb", "Vote", "Vote", "IMDb ID", "Title", "Runtime", "Year", 
};

char *nb_lists_lst_headers[COLS_LISTS_LST] = {
    "#", "IMDb", "Vote", "Vote", "IMDb ID", "Title", "Runtime", "Year", 
};

char *nb_lists_cmp_headers[COLS_LISTS_CMP] = {
    "#", "IMDb", "Vote", "Vote", "IMDb ID", "Title", "Runtime", "Year", 
};

char *nb_lists_top_headers[COLS_LISTS_TOP] = {
    "#", "IMDb", "Vote", "Vote", "IMDb ID", "Title", "Year", "Votes", 
};

char *nb_lists_bot_headers[COLS_LISTS_BOT] = {
    "#", "IMDb", "Vote", "Vote", "IMDb ID", "Title", "Year", "Votes", 
};

char *nb_lists_box_headers[COLS_LISTS_BOX] = {
    "#", "IMDb", "Vote", "Vote", "IMDb ID", "Title", "Year", "Gross USD", 
};


/* convenience function for header application */
static void ui_apply_headers(NotebookTab *tab, char **headers, int cols) {

    int i = 0;

    for(i = 0; i < cols; i++) {

        gtk_custom_table_set_head_text(tab->table, i, headers[i]);
    }
}


void ui_set_head() {

    ui_apply_headers(nb_stats_mov_tab, nb_stats_mov_headers, COLS_STATS_MOV);
    ui_apply_headers(nb_stats_lst_tab, nb_stats_lst_headers, COLS_STATS_LST);
    ui_apply_headers(nb_stats_cmp_tab, nb_stats_cmp_headers, COLS_STATS_CMP);
    ui_apply_headers(nb_lists_mov_tab, nb_lists_mov_headers, COLS_LISTS_MOV);
    ui_apply_headers(nb_lists_lst_tab, nb_lists_lst_headers, COLS_LISTS_LST);
    ui_apply_headers(nb_lists_cmp_tab, nb_lists_cmp_headers, COLS_LISTS_CMP);
    ui_apply_headers(nb_lists_top_tab, nb_lists_top_headers, COLS_LISTS_TOP);
    ui_apply_headers(nb_lists_bot_tab, nb_lists_bot_headers, COLS_LISTS_BOT);
    ui_apply_headers(nb_lists_box_tab, nb_lists_box_headers, COLS_LISTS_BOX);
}

