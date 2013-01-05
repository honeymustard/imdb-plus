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
    
    ui_set_make("Movies Stats", nb_tab_statistics, nb_tab_statistics_vbox, 
        nb_statistics_scroll, nb_statistics_view);
    ui_set_make("My Movies", nb_tab_mymovies, nb_tab_mymovies_vbox, 
        nb_mymovies_scroll, nb_mymovies_view);
    ui_set_make("Lists Stats", nb_tab_lists_stats, nb_tab_lists_stats_vbox, 
        nb_lists_stats_scroll, nb_lists_stats_view);
    ui_set_make("My Lists", nb_tab_lists, nb_tab_lists_vbox, 
        nb_lists_scroll, nb_lists_view);
    ui_set_make("Compare Stats", nb_tab_compare, nb_tab_compare_vbox, 
        nb_compare_scroll, nb_compare_view);
    ui_set_make("Compare", nb_tab_lists_cmp, nb_tab_lists_cmp_vbox, 
        nb_lists_cmp_scroll, nb_lists_cmp_view);
    ui_set_make("Top 250", nb_tab_top250, nb_tab_top250_vbox, 
        nb_top250_scroll, nb_top250_view);
    ui_set_make("Bottom 100", nb_tab_bot100, nb_tab_bot100_vbox, 
        nb_bot100_scroll, nb_bot100_view);
    ui_set_make("Boxoffice", nb_tab_boxoffice, nb_tab_boxoffice_vbox, 
        nb_boxoffice_scroll, nb_boxoffice_view);
    ui_set_make("Allstats", nb_tab_allstats, nb_tab_allstats_vbox, 
        nb_allstats_scroll, nb_allstats_view);

    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(nb), GTK_POS_TOP);
    gtk_notebook_set_show_tabs(GTK_NOTEBOOK(nb), TRUE);
}

