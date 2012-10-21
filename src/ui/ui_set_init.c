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


#include "ui.h"


/* table column width descriptions */
int nb_tab_statistics_cols[TABLE_STATS_COLS] = {
    60, 60, 60, -1, 85, 85, 85, 85
};

int nb_tab_mymovies_cols[TABLE_MYMOV_COLS] = {
    60, 60, 60, 100, -1, 80, 55
};

int nb_tab_lists_stats_cols[TABLE_LSTST_COLS] = {
    60, 60, 60, -1, 85, 85, 85, 85
};

int nb_tab_mylists_cols[TABLE_MYLST_COLS] = {
    60, 60, 60, 100, -1, 80, 55
};

int nb_tab_compare_cols[TABLE_COMPR_COLS] = {
    60, 60, 60, -1, 85, 85, 85, 85
};

int nb_tab_top250_cols[TABLE_TP250_COLS] = {
    60, 60, 60, 100, -1, 55, 80 
};

int nb_tab_bot100_cols[TABLE_BT100_COLS] = {
    60, 60, 60, 100, -1, 55, 80
};

int nb_tab_boxoffice_cols[TABLE_BOXOF_COLS] = {
    60, 60, 60, 100, -1, 55, 140, 
};

int nb_tab_allstats_cols[TABLE_ALLST_COLS] = {
    60, 60, 60, -1, 85, 85, 85, 85
};


void ui_set_init() {

    /* create a new window, set title and icon */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    /* create title string */
    char *title = malloc(strlen(APP_NAME) + 
        strlen(get_global(CONST_VERSION)) + 2);

    strcpy(title, APP_NAME);
    strcat(title, "-");
    strcat(title, get_global(CONST_VERSION));

    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_icon_from_file(GTK_WINDOW(window), APP_ICON, NULL);

    free(title);

    /* connect window signals to callbacks */
    g_signal_connect(window, "destroy", 
        G_CALLBACK(menu_signal_quit), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(window), 0);

    /* create notebook, statusbar and containers */
    nb = gtk_notebook_new();
    status = gtk_statusbar_new();
    vbox = gtk_vbox_new(FALSE, 5);
    hbox = gtk_hbox_new(FALSE, 5);

    /* initialize new table widgets */
    nb_tab_statistics = gtk_custom_table_new(TABLE_STATS_COLS, 
        10, 500, 500, nb_tab_statistics_cols);
    nb_tab_mymovies = gtk_custom_table_new(TABLE_MYMOV_COLS, 
        50, 500, 500, nb_tab_mymovies_cols);
    nb_tab_lists_stats = gtk_custom_table_new(TABLE_LSTST_COLS, 
        10, 500, 500, nb_tab_lists_stats_cols);
    nb_tab_lists = gtk_custom_table_new(TABLE_MYLST_COLS, 
        50, 500, 500, nb_tab_mylists_cols);
    nb_tab_compare = gtk_custom_table_new(TABLE_COMPR_COLS, 
        10, 500, 500, nb_tab_compare_cols);
    nb_tab_top250 = gtk_custom_table_new(TABLE_TP250_COLS, 
        250, 500, 500, nb_tab_top250_cols);
    nb_tab_bot100 = gtk_custom_table_new(TABLE_BT100_COLS, 
        100, 500, 500, nb_tab_bot100_cols);
    nb_tab_boxoffice = gtk_custom_table_new(TABLE_BOXOF_COLS, 
        50, 500, 500, nb_tab_boxoffice_cols);
    nb_tab_allstats = gtk_custom_table_new(TABLE_ALLST_COLS, 
        12, 500, 500, nb_tab_allstats_cols);

    ui_set_headers();
    ui_set_meta();
    ui_set_stats();
    ui_set_lists();
    ui_set_tabs();
    ui_set_menu();

    /* add widgets to main vbox */
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), nb, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), status, FALSE, FALSE, 0);

    /* push initial status message */
    gtk_statusbar_push(GTK_STATUSBAR(status), 1, 
        "Hit Ctrl+D to download new ratings list, or Ctrl+O to open existing");

    /* last steps, show window */
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_window_set_default_size(GTK_WINDOW(window), 830, 460);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(window);
}

