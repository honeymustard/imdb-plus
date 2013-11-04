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
#include <stdlib.h>


int nb_stats_mov_cols[COLS_STATS_MOV] = {
    60, 60, 60, -1, 85, 85, 85, 85
};

int nb_stats_lst_cols[COLS_STATS_LST] = {
    60, 60, 60, -1, 85, 85, 85, 85
};

int nb_stats_cmp_cols[COLS_STATS_CMP] = {
    60, 60, 60, -1, 85, 85, 85, 85
};

int nb_stats_all_cols[COLS_STATS_ALL] = {
    60, 60, 60, -1, 35, 85, 85, 85, 85
};

int nb_lists_mov_cols[COLS_LISTS_MOV] = {
    60, 60, 60, 60, 100, -1, 80, 55
};

int nb_lists_lst_cols[COLS_LISTS_LST] = {
    60, 60, 60, 60, 100, -1, 80, 55
};

int nb_lists_cmp_cols[COLS_LISTS_CMP] = {
    60, 60, 60, 60, 100, -1, 80, 55
};

int nb_lists_top_cols[COLS_LISTS_TOP] = {
    60, 60, 60, 60, 100, -1, 55, 100 
};

int nb_lists_bot_cols[COLS_LISTS_BOT] = {
    60, 60, 60, 60, 100, -1, 55, 100
};

int nb_lists_box_cols[COLS_LISTS_BOX] = {
    60, 60, 60, 60, 100, -1, 55, 140, 
};


/* minor convenience function for tab-creation */
static void ui_set_make(char *title, NotebookTab *tab) {

    tab->is_open = 0;
    tab->has_changed = 0;
    tab->type = TAB_TYPE_NONE;
    tab->vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    tab->scroll = gtk_scrolled_window_new(NULL, NULL);
    tab->view = gtk_viewport_new(NULL, NULL);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(tab->scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(tab->view), tab->table);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(tab->view), GTK_SHADOW_NONE);
    gtk_container_add(GTK_CONTAINER(tab->scroll), tab->view); 
    gtk_box_pack_start(GTK_BOX(tab->vbox), tab->scroll, TRUE, TRUE, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(mwin->note), tab->vbox, 
        gtk_label_new(title));
}


void ui_set_tabs() {

    /* initialize new table widgets */
    nb_stats_mov_tab = malloc(sizeof(NotebookTab));
    nb_stats_lst_tab = malloc(sizeof(NotebookTab));
    nb_stats_cmp_tab = malloc(sizeof(NotebookTab));
    nb_stats_all_tab = malloc(sizeof(NotebookTab));
    nb_lists_mov_tab = malloc(sizeof(NotebookTab));
    nb_lists_lst_tab = malloc(sizeof(NotebookTab));
    nb_lists_cmp_tab = malloc(sizeof(NotebookTab));
    nb_lists_top_tab = malloc(sizeof(NotebookTab));
    nb_lists_bot_tab = malloc(sizeof(NotebookTab));
    nb_lists_box_tab = malloc(sizeof(NotebookTab));

    nb_stats_mov_tab->table = gtk_custom_table_new(COLS_STATS_MOV, 
        10, 500, 500, nb_stats_mov_cols);
    nb_stats_lst_tab->table = gtk_custom_table_new(COLS_STATS_LST, 
        10, 500, 500, nb_stats_lst_cols);
    nb_stats_cmp_tab->table = gtk_custom_table_new(COLS_STATS_CMP, 
        10, 500, 500, nb_stats_cmp_cols);
    nb_stats_all_tab->table = gtk_custom_table_new(COLS_STATS_ALL, 
        12, 500, 500, nb_stats_all_cols);
    nb_lists_mov_tab->table = gtk_custom_table_new(COLS_LISTS_MOV, 
        50, 500, 500, nb_lists_mov_cols);
    nb_lists_lst_tab->table = gtk_custom_table_new(COLS_LISTS_LST, 
        50, 500, 500, nb_lists_lst_cols);
    nb_lists_cmp_tab->table = gtk_custom_table_new(COLS_LISTS_CMP, 
        50, 500, 500, nb_lists_cmp_cols);
    nb_lists_top_tab->table = gtk_custom_table_new(COLS_LISTS_TOP, 
        250, 500, 500, nb_lists_top_cols);
    nb_lists_bot_tab->table = gtk_custom_table_new(COLS_LISTS_BOT, 
        100, 500, 500, nb_lists_bot_cols);
    nb_lists_box_tab->table = gtk_custom_table_new(COLS_LISTS_BOX, 
        50, 500, 500, nb_lists_box_cols);

    ui_set_make(NAME_STATS_MOV, nb_stats_mov_tab); 
    ui_set_make(NAME_LISTS_MOV, nb_lists_mov_tab); 
    ui_set_make(NAME_STATS_LST, nb_stats_lst_tab); 
    ui_set_make(NAME_LISTS_LST, nb_lists_lst_tab); 
    ui_set_make(NAME_STATS_CMP, nb_stats_cmp_tab); 
    ui_set_make(NAME_LISTS_CMP, nb_lists_cmp_tab); 
    ui_set_make(NAME_LISTS_TOP, nb_lists_top_tab); 
    ui_set_make(NAME_LISTS_BOT, nb_lists_bot_tab); 
    ui_set_make(NAME_LISTS_BOX, nb_lists_box_tab); 
    ui_set_make(NAME_STATS_ALL, nb_stats_all_tab);

    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(mwin->note), GTK_POS_TOP);
    gtk_notebook_set_show_tabs(GTK_NOTEBOOK(mwin->note), TRUE);
}

