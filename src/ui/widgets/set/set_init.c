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


#include "main.h"
#include "ui/globals/globals.h"
#include "ui/widgets/widgets.h"
#include "ui/widgets/fill/fill.h"
#include "ui/widgets/set/set.h"
#include "ui/events/events.h"
#include "ui/table/gtk_custom_table.h"


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
    60, 60, 60, 100, -1, 80, 55
};

int nb_lists_lst_cols[COLS_LISTS_LST] = {
    60, 60, 60, 100, -1, 80, 55
};

int nb_lists_cmp_cols[COLS_LISTS_CMP] = {
    60, 60, 60, 100, -1, 80, 55
};

int nb_lists_top_cols[COLS_LISTS_TOP] = {
    60, 60, 60, 100, -1, 55, 100 
};

int nb_lists_bot_cols[COLS_LISTS_BOT] = {
    60, 60, 60, 100, -1, 55, 100
};

int nb_lists_box_cols[COLS_LISTS_BOX] = {
    60, 60, 60, 100, -1, 55, 140, 
};


static char *ui_set_create_title() {

    char *tmp = NULL;

    tmp = malloc(strlen(APP_NAME) + strlen(globals_get(CONST_VERSION)) + 2);

    strcpy(tmp, APP_NAME);
    strcat(tmp, "-");
    strcat(tmp, globals_get(CONST_VERSION));

    return tmp;
}


void ui_set_init() {

    /* create a new window, set title and icon */
    mwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    note = gtk_notebook_new();
    stat = gtk_statusbar_new();
    vbox = gtk_vbox_new(FALSE, 5);
    hbox = gtk_hbox_new(FALSE, 5);

    char *title = ui_set_create_title();

    gtk_window_set_title(GTK_WINDOW(mwin), title);

    free(title);

    gtk_window_set_icon_from_file(GTK_WINDOW(mwin), APP_ICON, NULL);

    /* connect window signals to callbacks */
    g_signal_connect(mwin, "destroy", 
        G_CALLBACK(menu_signal_quit), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(mwin), 0);

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

    ui_set_head();
    ui_set_meta();
    ui_set_tabs();
    ui_set_menu();

    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(note), GTK_POS_TOP);
    gtk_notebook_set_show_tabs(GTK_NOTEBOOK(note), TRUE);

    ui_fill_lists_top_update();
    ui_fill_lists_bot_update();
    ui_fill_lists_box_update();
    ui_fill_lists_lst_empty();
    ui_fill_lists_mov_empty();
    ui_fill_lists_cmp_empty();
    ui_fill_stats_lst_empty();
    ui_fill_stats_mov_empty();
    ui_fill_stats_cmp_empty();
    ui_fill_stats_all_empty();

    /* add widgets to main vbox */
    gtk_box_pack_start(GTK_BOX(vbox), menu, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), note, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), stat, FALSE, FALSE, 0);

    /* push initial status message */
    gtk_statusbar_push(GTK_STATUSBAR(stat), 1, 
        "Hit Ctrl+D to download new ratings list, or Ctrl+O to open existing");

    /* last steps, show window */
    gtk_container_add(GTK_CONTAINER(mwin), vbox);
    gtk_window_set_default_size(GTK_WINDOW(mwin), 830, 460);
    gtk_window_set_position(GTK_WINDOW(mwin), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(mwin);
}

