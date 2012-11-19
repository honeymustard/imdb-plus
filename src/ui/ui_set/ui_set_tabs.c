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


void ui_set_tabs() {

    /* create new vboxes for tabs */
    nb_tab_statistics_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_mymovies_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_lists_stats_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_lists_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_compare_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_top250_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_bot100_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_boxoffice_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_allstats_vbox = gtk_vbox_new(FALSE, 0);

    /* initialize scrolled windows */
    nb_statistics_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_mymovies_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_lists_stats_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_lists_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_compare_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_top250_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_bot100_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_boxoffice_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_allstats_scroll = gtk_scrolled_window_new(NULL, NULL);

    /* set scrolled window policies */
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_statistics_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_mymovies_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_lists_stats_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_lists_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
     gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_compare_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_top250_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_bot100_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_boxoffice_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_allstats_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    /* create viewports */
    nb_statistics_view = gtk_viewport_new(NULL, NULL);
    nb_mymovies_view = gtk_viewport_new(NULL, NULL);
    nb_lists_stats_view = gtk_viewport_new(NULL, NULL);
    nb_lists_view = gtk_viewport_new(NULL, NULL);
    nb_compare_view = gtk_viewport_new(NULL, NULL);
    nb_top250_view = gtk_viewport_new(NULL, NULL);
    nb_bot100_view = gtk_viewport_new(NULL, NULL);
    nb_boxoffice_view = gtk_viewport_new(NULL, NULL);
    nb_allstats_view = gtk_viewport_new(NULL, NULL);

    /* add widgets to viewports */
    gtk_container_add(GTK_CONTAINER(nb_statistics_view), 
        nb_tab_statistics);
    gtk_container_add(GTK_CONTAINER(nb_mymovies_view), 
        nb_tab_mymovies); 
    gtk_container_add(GTK_CONTAINER(nb_lists_stats_view), 
        nb_tab_lists_stats);
    gtk_container_add(GTK_CONTAINER(nb_lists_view), 
        nb_tab_lists);
    gtk_container_add(GTK_CONTAINER(nb_compare_view), 
        nb_tab_compare);
    gtk_container_add(GTK_CONTAINER(nb_top250_view), 
        nb_tab_top250);
    gtk_container_add(GTK_CONTAINER(nb_bot100_view), 
        nb_tab_bot100);
    gtk_container_add(GTK_CONTAINER(nb_boxoffice_view), 
        nb_tab_boxoffice);
    gtk_container_add(GTK_CONTAINER(nb_allstats_view), 
        nb_tab_allstats);

    /* disable viewport shadows */
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_statistics_view), 
        GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_mymovies_view), 
        GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_lists_stats_view), 
        GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_lists_view), 
        GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_compare_view), 
        GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_top250_view), 
        GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_bot100_view), 
        GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_boxoffice_view), 
        GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_allstats_view), 
        GTK_SHADOW_NONE);

    /* add viewports to scrollwindows */
    gtk_container_add(GTK_CONTAINER(nb_statistics_scroll), 
        nb_statistics_view); 
    gtk_container_add(GTK_CONTAINER(nb_mymovies_scroll), 
        nb_mymovies_view); 
    gtk_container_add(GTK_CONTAINER(nb_lists_stats_scroll), 
        nb_lists_stats_view); 
    gtk_container_add(GTK_CONTAINER(nb_lists_scroll), 
        nb_lists_view); 
    gtk_container_add(GTK_CONTAINER(nb_compare_scroll), 
        nb_compare_view); 
    gtk_container_add(GTK_CONTAINER(nb_top250_scroll), 
        nb_top250_view); 
    gtk_container_add(GTK_CONTAINER(nb_bot100_scroll), 
        nb_bot100_view); 
    gtk_container_add(GTK_CONTAINER(nb_boxoffice_scroll), 
        nb_boxoffice_view); 
    gtk_container_add(GTK_CONTAINER(nb_allstats_scroll), 
        nb_allstats_view); 

    /* pack scrolled widgets into vboxes */
    gtk_box_pack_start(GTK_BOX(nb_tab_statistics_vbox), 
        nb_statistics_scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nb_tab_mymovies_vbox), 
        nb_mymovies_scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nb_tab_lists_stats_vbox), 
        nb_lists_stats_scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nb_tab_lists_vbox), 
        nb_lists_scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nb_tab_compare_vbox), 
        nb_compare_scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nb_tab_top250_vbox), 
        nb_top250_scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nb_tab_bot100_vbox), 
        nb_bot100_scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nb_tab_boxoffice_vbox), 
        nb_boxoffice_scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nb_tab_allstats_vbox), 
        nb_allstats_scroll, TRUE, TRUE, 0);

    /* append notebook tabs */
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), 
        nb_tab_statistics_vbox, gtk_label_new("Movies Stats"));
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), 
        nb_tab_mymovies_vbox, gtk_label_new("My Movies"));
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), 
        nb_tab_lists_stats_vbox, gtk_label_new("Lists Stats")); 
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), 
        nb_tab_lists_vbox, gtk_label_new("My Lists"));
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), 
        nb_tab_compare_vbox, gtk_label_new("Compare"));
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), 
        nb_tab_top250_vbox, gtk_label_new("Top 250"));
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), 
        nb_tab_bot100_vbox, gtk_label_new("Bottom 100"));
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), 
        nb_tab_boxoffice_vbox, gtk_label_new("Box Office"));
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), 
        nb_tab_allstats_vbox, gtk_label_new("All Stats"));

    /* notebook setup */
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(nb), GTK_POS_TOP);
    gtk_notebook_set_show_tabs(GTK_NOTEBOOK(nb), TRUE);
}

