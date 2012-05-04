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

#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <curl/curl.h>
#include <gdk/gdkkeysyms.h>
#include "master.h"
#include "tables.h"
#include "widgets.h"
#include "lib/events/events.h"
#include "lib/gtk_custom_table/gtk_custom_table.h"


/* solid green to solid red, for ratings */
double colors[10][3] = {
    {1.00, 0.00, 0.00}, 
    {1.00, 0.15, 0.00}, 
    {1.00, 0.35, 0.00}, 
    {1.00, 0.55, 0.00}, 
    {1.00, 0.75, 0.00}, 
    {1.00, 0.95, 0.00}, 
    {0.85, 1.00, 0.00}, 
    {0.65, 1.00, 0.00}, 
    {0.35, 1.00, 0.00}, 
    {0.00, 1.00, 0.00}, 
};


/* graph background colors */
double graph_bg[3] = {
    0.90, 
    0.90, 
    1.00,
};


/**
 * main program entry point
 */
int main(int argc, char *argv[]) {

    curl_global_init(CURL_GLOBAL_ALL);
    g_thread_init(NULL);

    gtk_init(&argc, &argv);

    int i = 0;
    int j = 0;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), APP_TITL);
    gtk_window_set_icon_from_file(GTK_WINDOW(window), APP_ICON, NULL);

    /* connect window signals to callbacks */
    g_signal_connect(window, "destroy", 
        G_CALLBACK(menu_signal_quit), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(window), 0);

    status = gtk_statusbar_new();
    vbox = gtk_vbox_new(FALSE, 5);
    hbox = gtk_hbox_new(FALSE, 5);

    nb = gtk_notebook_new();

    /* initialize new drawingarea widgets */
    nb_tab_statistics = gtk_custom_table_new(TABLE_STATS_COLS, 10, 500, 500, 
        nb_tab_statistics_cols);
    nb_tab_top250 = gtk_custom_table_new(TABLE_TP250_COLS, 250, 500, 500, 
        nb_tab_top250_cols);
    nb_tab_bot100 = gtk_custom_table_new(TABLE_BT100_COLS, 100, 500, 500, 
        nb_tab_bot100_cols);
    nb_tab_boxoffice = gtk_custom_table_new(TABLE_BOXOF_COLS, 50, 500, 500, 
        nb_tab_boxoffice_cols);
    nb_tab_mymovies = gtk_custom_table_new(TABLE_MYMOV_COLS, 50, 500, 500, 
        nb_tab_mymovies_cols);
    nb_tab_lists = gtk_custom_table_new(TABLE_MYLST_COLS, 50, 500, 500, 
        nb_tab_mymovies_cols);

    /* set primary columns to enable quick searches */
    gtk_custom_table_set_column_prime(nb_tab_top250, 3, TRUE);
    gtk_custom_table_set_column_prime(nb_tab_bot100, 3, TRUE);
    gtk_custom_table_set_column_prime(nb_tab_boxoffice, 3, TRUE);
    gtk_custom_table_set_column_prime(nb_tab_mymovies, 3, TRUE);
    gtk_custom_table_set_column_prime(nb_tab_lists, 3, TRUE);

    /* set header text */
    for(i = 0; i < TABLE_STATS_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_statistics, i, 
            nb_tab_statistics_headers[i]);
    }

    for(i = 0; i < TABLE_TP250_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_top250, i, 
            nb_tab_top250_headers[i]);
        gtk_custom_table_set_head_text(nb_tab_bot100, i, 
            nb_tab_top250_headers[i]);
    }

    for(i = 0; i < TABLE_BOXOF_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_boxoffice, i, 
            nb_tab_boxoffice_headers[i]);
    }

    for(i = 0; i < TABLE_MYMOV_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_mymovies, i, 
            nb_tab_mymovies_headers[i]);
        gtk_custom_table_set_head_text(nb_tab_lists, i, 
            nb_tab_mymovies_headers[i]);
    }

    gtk_custom_table_set_column_index(nb_tab_mymovies, 0, TRUE);
    gtk_custom_table_set_column_index(nb_tab_lists, 0, TRUE);

    char temp[10];

    int vote_counter = 10;

    gtk_custom_table_set_column_graph(nb_tab_statistics, 3, TRUE);

    /* statistics main rows */
    for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {

        sprintf(temp, "%d", vote_counter--);
        gtk_custom_table_set_cell_text(nb_tab_statistics, 0, i, temp);
        gtk_custom_table_set_cell_text(nb_tab_statistics, 1, i, "0.00");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 2, i, "0.00");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 3, i, "2");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 4, i, "0.00 %");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 5, i, "0");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 6, i, "0");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 7, i, "0.00");

        gtk_custom_table_set_cell_color(nb_tab_statistics, 0, i, colors[j]);
        gtk_custom_table_set_cell_color(nb_tab_statistics, 1, i, colors[j]);
        gtk_custom_table_set_cell_color(nb_tab_statistics, 2, i, graph_bg);
        gtk_custom_table_set_cell_color(nb_tab_statistics, 3, i, graph_bg);
    }
    
    /* statistics footer */
    gtk_custom_table_set_foot_text(nb_tab_statistics, 0, "0");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 1, "0.00");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 2, "0.00");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 3, "");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 4, "0.00 %");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 5, "0");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 6, "0");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 7, "0.00");


    int no_results = 1;

    /* check for pre-parsed top250 csv file.. */
    FILE *fp_top250 = fopen(CONST_TOP_CSV, "rb");

    if(fp_top250 != NULL) {

        fclose(fp_top250);

        int cols = 0;
        int rows = 0;

        char ***results;

        if(read_file(CONST_TOP_CSV, &cols, &rows, &results) && cols == 6) {

            for(i = 0; i < gtk_custom_table_get_rows(nb_tab_top250); i++) {

                gtk_custom_table_set_cell_text(nb_tab_top250, 0, i, 
                    results[i][0]);
                gtk_custom_table_set_cell_text(nb_tab_top250, 1, i, 
                    results[i][1]);
                gtk_custom_table_set_cell_text(nb_tab_top250, 2, i, 
                    "0");
                gtk_custom_table_set_cell_text(nb_tab_top250, 3, i, 
                    results[i][2]);
                gtk_custom_table_set_cell_text(nb_tab_top250, 4, i, 
                    results[i][3]);
                gtk_custom_table_set_cell_text(nb_tab_top250, 5, i, 
                    results[i][4]);
                gtk_custom_table_set_cell_text(nb_tab_top250, 6, i, 
                    results[i][5]);
                
                gtk_custom_table_set_cell_color(nb_tab_top250, 1, i, 
                        colors[(int)atof(results[i][1])]); 
            }

            free_memory(results, cols, rows);

            gtk_custom_table_set_sortable(nb_tab_top250, TRUE);
            gtk_custom_table_sort(nb_tab_top250, 0, GTK_CUSTOM_TABLE_ASC);

            no_results = !no_results;
        }
    }

    /* no top250 file on disk, add default values.. */
    if(no_results) {

        for(i = 0; i < 250; i++) {

            sprintf(temp, "%d.", i+1);
            gtk_custom_table_set_cell_text(nb_tab_top250, 0, i, temp);
            gtk_custom_table_set_cell_text(nb_tab_top250, 1, i, "0.0");
            gtk_custom_table_set_cell_text(nb_tab_top250, 2, i, "N/A");
            gtk_custom_table_set_cell_text(nb_tab_top250, 3, i, "0");
            gtk_custom_table_set_cell_text(nb_tab_top250, 4, i, "N/A");
            gtk_custom_table_set_cell_text(nb_tab_top250, 5, i, "0");
            gtk_custom_table_set_cell_text(nb_tab_top250, 6, i, "0");
        }
    }

    no_results = 1;

    /* check for pre-parsed bot100 csv file.. */
    FILE *fp_bot100 = fopen(CONST_BOT_CSV, "rb");

    if(fp_bot100 != NULL) {
        
        fclose(fp_bot100);

        int cols = 0;
        int rows = 0;

        char ***results;

        if(read_file(CONST_BOT_CSV, &cols, &rows, &results) && cols == 6) {

            for(i = 0; i < gtk_custom_table_get_rows(nb_tab_bot100); i++) {

                gtk_custom_table_set_cell_text(nb_tab_bot100, 0, i, 
                    results[i][0]);
                gtk_custom_table_set_cell_text(nb_tab_bot100, 1, i, 
                    results[i][1]);
                gtk_custom_table_set_cell_text(nb_tab_bot100, 2, i, 
                    "0");
                gtk_custom_table_set_cell_text(nb_tab_bot100, 3, i, 
                    results[i][2]);
                gtk_custom_table_set_cell_text(nb_tab_bot100, 4, i, 
                    results[i][3]);
                gtk_custom_table_set_cell_text(nb_tab_bot100, 5, i, 
                    results[i][4]);
                gtk_custom_table_set_cell_text(nb_tab_bot100, 6, i, 
                    results[i][5]);
                
                gtk_custom_table_set_cell_color(nb_tab_bot100, 1, i, 
                        colors[(int)atof(results[i][1])]); 
            }

            free_memory(results, cols, rows);

            gtk_custom_table_set_sortable(nb_tab_bot100, TRUE);
            gtk_custom_table_sort(nb_tab_bot100, 0, GTK_CUSTOM_TABLE_ASC);

            no_results = !no_results;
        }
    }

    /* no bot100 file on disk, add default values.. */
    if(no_results) {

        for(i = 0; i < 100; i++) {

            sprintf(temp, "%d.", i+1);
            gtk_custom_table_set_cell_text(nb_tab_bot100, 0, i, temp);
            gtk_custom_table_set_cell_text(nb_tab_bot100, 1, i, "0.0");
            gtk_custom_table_set_cell_text(nb_tab_bot100, 2, i, "N/A");
            gtk_custom_table_set_cell_text(nb_tab_bot100, 3, i, "0");
            gtk_custom_table_set_cell_text(nb_tab_bot100, 4, i, "N/A");
            gtk_custom_table_set_cell_text(nb_tab_bot100, 5, i, "0");
            gtk_custom_table_set_cell_text(nb_tab_bot100, 6, i, "0");
        }
    }

    no_results = 1;

    FILE *fp_boxoffice = fopen(CONST_BOX_CSV, "rb");

    if(fp_boxoffice != NULL) {

        fclose(fp_boxoffice);


        int cols = 0;
        int rows = 0;

        char ***results;

        if(read_file(CONST_BOX_CSV, &cols, &rows, &results) && cols == 5) {

            /* update boxoffice tab size */
            gtk_custom_table_resize(nb_tab_boxoffice, -1, rows);

            for(i = 0; i < gtk_custom_table_get_rows(nb_tab_boxoffice); i++) {

                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 0, i, 
                    results[i][0]);
                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, 
                    "0.0");
                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 2, i, 
                    "0");
                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 3, i, 
                    results[i][1]);
                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 4, i, 
                    results[i][2]);
                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 5, i, 
                    results[i][3]);
                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 6, i, 
                    results[i][4]);
 
                /* find imdb ratings and insert them into boxoffice.. */
                int index1 = gtk_custom_table_get_indexof(nb_tab_mymovies, results[i][1]);
                int index2 = gtk_custom_table_get_indexof(nb_tab_top250, results[i][1]);
                int index3 = gtk_custom_table_get_indexof(nb_tab_bot100, results[i][1]);
                int index4 = gtk_custom_table_get_indexof(nb_tab_lists, results[i][1]);

                set_imdb_rating(index1, i, nb_tab_mymovies, nb_tab_boxoffice);
                set_imdb_rating(index2, i, nb_tab_top250, nb_tab_boxoffice);
                set_imdb_rating(index3, i, nb_tab_bot100, nb_tab_boxoffice);
                set_imdb_rating(index4, i, nb_tab_lists, nb_tab_boxoffice);

            }

            free_memory(results, cols, rows);

            gtk_custom_table_set_sortable(nb_tab_boxoffice, TRUE);
            gtk_custom_table_sort(nb_tab_boxoffice, 0, GTK_CUSTOM_TABLE_ASC);

            no_results = !no_results;
        }
    }

    /* no boxoffice file on disk, add default values.. */
    if(no_results) {

        for(i = 0; i < 50; i++) {

            sprintf(temp, "%d.", i+1);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 0, i, temp);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, "0.0");
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 2, i, "0");
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 3, i, "N/A");
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 4, i, "N/A");
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 5, i, "0");
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 6, i, "$0");
        }
    }

    for(i = 0; i < 50; i++) {

        sprintf(temp, "%d.", i+1);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 0, i, temp);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 1, i, "0.0");
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 2, i, "0");
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 3, i, "N/A");
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 4, i, "N/A");
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 5, i, "0");

        gtk_custom_table_set_cell_text(nb_tab_lists, 0, i, temp);
        gtk_custom_table_set_cell_text(nb_tab_lists, 1, i, "0.0");
        gtk_custom_table_set_cell_text(nb_tab_lists, 2, i, "0");
        gtk_custom_table_set_cell_text(nb_tab_lists, 3, i, "N/A");
        gtk_custom_table_set_cell_text(nb_tab_lists, 4, i, "N/A");
        gtk_custom_table_set_cell_text(nb_tab_lists, 5, i, "0");
    }

    /* create new vboxes for tabs */
    nb_tab_statistics_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_top250_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_bot100_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_boxoffice_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_mymovies_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_lists_vbox = gtk_vbox_new(FALSE, 0);

    /* initialize scrolled windows */
    nb_statistics_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_top250_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_bot100_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_boxoffice_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_mymovies_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_lists_scroll = gtk_scrolled_window_new(NULL, NULL);

    /* set scrolled window policies */
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_statistics_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_top250_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_bot100_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_boxoffice_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_mymovies_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_lists_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    /* create viewports */
    nb_statistics_view = gtk_viewport_new(NULL, NULL);
    nb_top250_view = gtk_viewport_new(NULL, NULL);
    nb_bot100_view = gtk_viewport_new(NULL, NULL);
    nb_boxoffice_view = gtk_viewport_new(NULL, NULL);
    nb_mymovies_view = gtk_viewport_new(NULL, NULL);
    nb_lists_view = gtk_viewport_new(NULL, NULL);

    /* add widgets to viewports */
    gtk_container_add(GTK_CONTAINER(nb_statistics_view), 
        nb_tab_statistics);
    gtk_container_add(GTK_CONTAINER(nb_top250_view), 
        nb_tab_top250);
    gtk_container_add(GTK_CONTAINER(nb_bot100_view), 
        nb_tab_bot100);
    gtk_container_add(GTK_CONTAINER(nb_boxoffice_view), 
        nb_tab_boxoffice);
    gtk_container_add(GTK_CONTAINER(nb_mymovies_view), 
        nb_tab_mymovies);
    gtk_container_add(GTK_CONTAINER(nb_lists_view), 
        nb_tab_lists);

    /* disable viewport shadows */
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(
        nb_statistics_view), GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(
        nb_top250_view), GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(
        nb_bot100_view), GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(
        nb_boxoffice_view), GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(
        nb_mymovies_view), GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(
        nb_lists_view), GTK_SHADOW_NONE);

    /* add viewports to scrollwindows */
    gtk_container_add(GTK_CONTAINER(
        nb_statistics_scroll), nb_statistics_view); 
    gtk_container_add(GTK_CONTAINER(
        nb_top250_scroll), nb_top250_view); 
    gtk_container_add(GTK_CONTAINER(
        nb_bot100_scroll), nb_bot100_view); 
    gtk_container_add(GTK_CONTAINER(
        nb_boxoffice_scroll), nb_boxoffice_view); 
    gtk_container_add(GTK_CONTAINER(
        nb_mymovies_scroll), nb_mymovies_view); 
    gtk_container_add(GTK_CONTAINER(
        nb_lists_scroll), nb_lists_view); 

    /* pack scrolled widgets into vboxes */
    gtk_box_pack_start(GTK_BOX(nb_tab_statistics_vbox), 
        nb_statistics_scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nb_tab_top250_vbox), 
        nb_top250_scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nb_tab_bot100_vbox), 
        nb_bot100_scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nb_tab_boxoffice_vbox), 
        nb_boxoffice_scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nb_tab_mymovies_vbox), 
        nb_mymovies_scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(nb_tab_lists_vbox), 
        nb_lists_scroll, TRUE, TRUE, 0);

    /* append notebook tabs */
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), nb_tab_statistics_vbox, 
        gtk_label_new("Movies Stats"));
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), nb_tab_mymovies_vbox, 
        gtk_label_new("My Movies"));
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), nb_tab_lists_vbox, 
        gtk_label_new("My Lists"));
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), nb_tab_top250_vbox, 
        gtk_label_new("Top 250"));
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), nb_tab_bot100_vbox, 
        gtk_label_new("Bottom 100"));
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), nb_tab_boxoffice_vbox, 
        gtk_label_new("Box Office"));

    /* notebook setup */
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(nb), GTK_POS_TOP);
    gtk_notebook_set_show_tabs(GTK_NOTEBOOK(nb), TRUE);

    menubar = gtk_menu_bar_new();

    /* create menu items */
    menu_file_item_open = gtk_menu_item_new_with_mnemonic("_Open");
    menu_file_item_new = gtk_menu_item_new_with_mnemonic("_Download");
    menu_file_item_exit = gtk_menu_item_new_with_mnemonic("_Exit");
    menu_file_item_space = gtk_separator_menu_item_new();
    menu_edit_item_update = gtk_menu_item_new_with_mnemonic("_Update");
    menu_help_item_about = gtk_menu_item_new_with_mnemonic("_About");

    /* create menus */
    menu_file = gtk_menu_new();
    menu_edit = gtk_menu_new();
    menu_help = gtk_menu_new();

    /* create accelerator groups */
    GtkAccelGroup *group_file = gtk_accel_group_new();
    GtkAccelGroup *group_edit = gtk_accel_group_new();
    GtkAccelGroup *group_help = gtk_accel_group_new();

    /* add accelerator groups */
    gtk_window_add_accel_group(GTK_WINDOW(window), group_file);
    gtk_window_add_accel_group(GTK_WINDOW(window), group_edit);
    gtk_window_add_accel_group(GTK_WINDOW(window), group_help);

    /* set accelerator groups */
    gtk_menu_set_accel_group(GTK_MENU(menu_file), group_file);
    gtk_menu_set_accel_group(GTK_MENU(menu_edit), group_edit);
    gtk_menu_set_accel_group(GTK_MENU(menu_help), group_help);

    /* add accelerator keys to menu */
    gtk_widget_add_accelerator(menu_file_item_open, "activate", 
        group_file, GDK_O, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(menu_file_item_new, "activate", 
        group_file, GDK_D, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(menu_file_item_exit, "activate", 
        group_file, GDK_Q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(menu_edit_item_update, "activate", 
        group_edit, GDK_U, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(menu_help_item_about, "activate", 
        group_help, GDK_A, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

    /* append menu items to menus */
    gtk_menu_append(GTK_MENU(menu_file), menu_file_item_open);
    gtk_menu_append(GTK_MENU(menu_file), menu_file_item_new);
    gtk_menu_append(GTK_MENU(menu_file), menu_file_item_space);
    gtk_menu_append(GTK_MENU(menu_file), menu_file_item_exit);
    gtk_menu_append(GTK_MENU(menu_edit), menu_edit_item_update);
    gtk_menu_append(GTK_MENU(menu_help), menu_help_item_about);

    /* attach callback functions to menu-items */
    gtk_signal_connect_object(GTK_OBJECT(menu_file_item_open), "activate", 
        GTK_SIGNAL_FUNC(menu_signal_open), (gpointer)window);
    gtk_signal_connect_object(GTK_OBJECT(menu_file_item_new), "activate", 
        GTK_SIGNAL_FUNC(menu_signal_new), (gpointer)window);
    gtk_signal_connect_object(GTK_OBJECT(menu_file_item_exit), "activate", 
        GTK_SIGNAL_FUNC(menu_signal_quit), (gpointer)window);
    gtk_signal_connect_object(GTK_OBJECT(menu_edit_item_update), "activate", 
        GTK_SIGNAL_FUNC(menu_signal_update), (gpointer)window);
    gtk_signal_connect_object(GTK_OBJECT(menu_help_item_about), "activate", 
        GTK_SIGNAL_FUNC(menu_signal_about), (gpointer)window);

    /* create menu items */
    menu_file_item = gtk_menu_item_new_with_mnemonic("_File");
    menu_edit_item = gtk_menu_item_new_with_mnemonic("_Edit");
    menu_help_item = gtk_menu_item_new_with_mnemonic("_Help");

    /* add submenus to menu items */
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_file_item), menu_file);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_edit_item), menu_edit);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_help_item), menu_help);

    /* add to main menubar */
    gtk_menu_bar_append(GTK_MENU_BAR(menubar), menu_file_item);
    gtk_menu_bar_append(GTK_MENU_BAR(menubar), menu_edit_item);
    gtk_menu_bar_append(GTK_MENU_BAR(menubar), menu_help_item);

    /* add widgets to main vbox */
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), nb, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), status, FALSE, FALSE, 0);

    /* push initial status message */
    gtk_statusbar_push(GTK_STATUSBAR(status), 1, 
        "Hit Ctrl+D to download new ratings list, or Ctrl+O to open existing");

    /* last steps, show window */
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 440);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(window);

    /* just in case */
    gdk_threads_enter();
    gtk_main();
    gdk_threads_leave();

    return 0;
}

