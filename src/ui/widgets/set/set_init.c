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
#include <stdlib.h>
#include <string.h>


void ui_set_init() {

    /* create a new window, set title and icon */
    mwin = malloc(sizeof(MainWindow));
    mwin->main = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    mwin->note = gtk_notebook_new();
    mwin->stat = gtk_statusbar_new();
    mwin->vbox = gtk_vbox_new(FALSE, 5);
    mwin->hbox = gtk_hbox_new(FALSE, 5);

    /* initiate main window */
    gtk_window_set_title(GTK_WINDOW(mwin->main), globals_get(CONST_APPNAME));
    gtk_window_set_icon_from_file(GTK_WINDOW(mwin->main), APP_ICON, NULL);
    gtk_container_set_border_width(GTK_CONTAINER(mwin->main), 0);
    g_signal_connect(mwin->main, "destroy", G_CALLBACK(menu_signal_quit), NULL);

    ui_set_tabs();
    ui_set_head();
    ui_set_meta();
    ui_set_menu();

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
    gtk_box_pack_start(GTK_BOX(mwin->vbox), mwin->menu, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mwin->vbox), mwin->note, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(mwin->vbox), mwin->stat, FALSE, FALSE, 0);

    /* push initial status message */
    gtk_statusbar_push(GTK_STATUSBAR(mwin->stat), 1, 
        "Hit Ctrl+D to download new ratings list, or Ctrl+O to open existing");

    /* last steps, show window */
    gtk_container_add(GTK_CONTAINER(mwin->main), mwin->vbox);
    gtk_window_set_default_size(GTK_WINDOW(mwin->main), 830, 460);
    gtk_window_set_position(GTK_WINDOW(mwin->main), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(mwin->main);
}

