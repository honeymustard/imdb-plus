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
#include "ui/ui_set/ui_set.h"


/* minor convenience function for tabs-creation */
static void ui_set_make(char *title, GtkWidget *tab, GtkWidget *vbox, 
    GtkWidget *scroll, GtkWidget *view) {

    vbox = gtk_vbox_new(FALSE, 0);
    scroll = gtk_scrolled_window_new(NULL, NULL);
    view = gtk_viewport_new(NULL, NULL);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(view), tab);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(view), GTK_SHADOW_NONE);
    gtk_container_add(GTK_CONTAINER(scroll), view); 
    gtk_box_pack_start(GTK_BOX(vbox), scroll, TRUE, TRUE, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), vbox, gtk_label_new(title));
}


void ui_set_tabs() {
    
    ui_set_make(NAME_STATS_MOV, nb_stats_mov_tab, nb_stats_mov_vbox, 
        nb_stats_mov_scroll, nb_stats_mov_view);
    ui_set_make(NAME_LISTS_MOV, nb_lists_mov_tab, nb_lists_mov_vbox, 
        nb_lists_mov_scroll, nb_lists_mov_view);
    ui_set_make(NAME_STATS_LST, nb_stats_lst_tab, nb_stats_lst_vbox, 
        nb_stats_lst_scroll, nb_stats_lst_view);
    ui_set_make(NAME_LISTS_LST, nb_lists_lst_tab, nb_lists_lst_vbox, 
        nb_lists_lst_scroll, nb_lists_lst_view);
    ui_set_make(NAME_STATS_CMP, nb_stats_cmp_tab, nb_stats_cmp_vbox, 
        nb_stats_cmp_scroll, nb_stats_cmp_view);
    ui_set_make(NAME_LISTS_CMP, nb_lists_cmp_tab, nb_lists_cmp_vbox, 
        nb_lists_cmp_scroll, nb_lists_cmp_view);
    ui_set_make(NAME_LISTS_TOP, nb_lists_top_tab, nb_lists_top_vbox, 
        nb_lists_top_scroll, nb_lists_top_view);
    ui_set_make(NAME_LISTS_BOT, nb_lists_bot_tab, nb_lists_bot_vbox, 
        nb_lists_bot_scroll, nb_lists_bot_view);
    ui_set_make(NAME_LISTS_BOX, nb_lists_box_tab, nb_lists_box_vbox, 
        nb_lists_box_scroll, nb_lists_box_view);
    ui_set_make(NAME_STATS_ALL, nb_stats_all_tab, nb_stats_all_vbox, 
        nb_stats_all_scroll, nb_stats_all_view);
}

