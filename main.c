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
#include <sys/stat.h>
#include <sys/types.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "master.h"
#include "tables.h"
#include "widgets.h"
#include "lib/colors.h"
#include "lib/globals.h"
#include "lib/readfile.h"
#include "lib/events/events.h"
#include "lib/gtk_custom_table/gtk_custom_table.h"


/**
 * main program entry point
 */
int main(int argc, char *argv[]) {

    g_thread_init(NULL);

    gtk_init(&argc, &argv);

    /* create home directory */
    if(strcmp(OS, "WINDOWS") != 0) { 

        char *home = getenv("HOME");
        char *path = malloc(strlen(home) + strlen(APP_DIRE) + 3);

        strcpy(path, home);
        strcat(path, "/");
        strcat(path, APP_DIRE);
        strcat(path, "/");

        set_global(CONST_HOME, path);

        mkdir(path, S_IRWXU);

        /* path constants */
        char *top_tmp = malloc(strlen(path) + strlen(TOP_TMP) + 1);
        char *top_csv = malloc(strlen(path) + strlen(TOP_CSV) + 1);
        char *bot_tmp = malloc(strlen(path) + strlen(BOT_TMP) + 1);
        char *bot_csv = malloc(strlen(path) + strlen(BOT_CSV) + 1);
        char *box_tmp = malloc(strlen(path) + strlen(BOX_TMP) + 1);
        char *box_csv = malloc(strlen(path) + strlen(BOX_CSV) + 1);

        strcpy(top_tmp, path);
        strcpy(top_csv, path);
        strcpy(bot_tmp, path);
        strcpy(bot_csv, path);
        strcpy(box_tmp, path);
        strcpy(box_csv, path);

        strcat(top_tmp, TOP_TMP);
        strcat(top_csv, TOP_CSV);
        strcat(bot_tmp, BOT_TMP);
        strcat(bot_csv, BOT_CSV);
        strcat(box_tmp, BOX_TMP);
        strcat(box_csv, BOX_CSV);

        set_global(CONST_TOP_TMP, top_tmp);
        set_global(CONST_TOP_CSV, top_csv);
        set_global(CONST_BOT_TMP, bot_tmp);
        set_global(CONST_BOT_CSV, bot_csv);
        set_global(CONST_BOX_TMP, box_tmp);
        set_global(CONST_BOX_CSV, box_csv);
    }

    int i = 0;
    int j = 0;

    /* create a new window, set title and icon */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), APP_TITL);
    gtk_window_set_icon_from_file(GTK_WINDOW(window), APP_ICON, NULL);

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
    nb_tab_top250 = gtk_custom_table_new(TABLE_TP250_COLS, 
        250, 500, 500, nb_tab_top250_cols);
    nb_tab_bot100 = gtk_custom_table_new(TABLE_BT100_COLS, 
        100, 500, 500, nb_tab_bot100_cols);
    nb_tab_boxoffice = gtk_custom_table_new(TABLE_BOXOF_COLS, 
        50, 500, 500, nb_tab_boxoffice_cols);
    nb_tab_mymovies = gtk_custom_table_new(TABLE_MYMOV_COLS, 
        50, 500, 500, nb_tab_mymovies_cols);
    nb_tab_lists = gtk_custom_table_new(TABLE_MYLST_COLS, 
        50, 500, 500, nb_tab_mymovies_cols);
    nb_tab_lists_stats = gtk_custom_table_new(TABLE_STATS_COLS, 
        10, 500, 500, nb_tab_statistics_cols);

    /* set primary columns to enable quick searches */
    gtk_custom_table_set_column_prime(nb_tab_top250, 3, 
        TRUE);
    gtk_custom_table_set_column_prime(nb_tab_bot100, 3, 
        TRUE);
    gtk_custom_table_set_column_prime(nb_tab_boxoffice, 3, 
        TRUE);
    gtk_custom_table_set_column_prime(nb_tab_mymovies, 3, 
        TRUE);
    gtk_custom_table_set_column_prime(nb_tab_lists, 3, 
        TRUE);

    /* set statistics headers */
    for(i = 0; i < TABLE_STATS_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_statistics, i, 
            nb_tab_statistics_headers[i]);
    }

    /* set lists statistics headers */
    for(i = 0; i < TABLE_STATS_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_lists_stats, i, 
            nb_tab_statistics_headers[i]);
    }

    /* set top 250 headers */
    for(i = 0; i < TABLE_TP250_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_top250, i, 
            nb_tab_top250_headers[i]);
    }

    /* set bottom 100 headers */
    for(i = 0; i < TABLE_TP250_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_bot100, i, 
            nb_tab_top250_headers[i]);
    }

    /* set boxoffice headers */
    for(i = 0; i < TABLE_BOXOF_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_boxoffice, i, 
            nb_tab_boxoffice_headers[i]);
    }

    /* set my-movies headers */
    for(i = 0; i < TABLE_MYMOV_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_mymovies, i, 
            nb_tab_mymovies_headers[i]);
    }

    /* set my-lists headers */
    for(i = 0; i < TABLE_MYMOV_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_lists, i, 
            nb_tab_mymovies_headers[i]);
    }

    /* set automatic numbering columns and a graph column */
    gtk_custom_table_set_column_index(nb_tab_mymovies, 0, 
        TRUE);
    gtk_custom_table_set_column_index(nb_tab_lists, 0, 
        TRUE);
    gtk_custom_table_set_column_graph(nb_tab_statistics, 3, 
        TRUE);
    gtk_custom_table_set_column_graph(nb_tab_lists_stats, 3, 
        TRUE);

    char temp[10];

    /* set statistics table values */
    for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {

        sprintf(temp, "%d", (j + 1));

        gtk_custom_table_set_cell_text(nb_tab_statistics, 0, i, 
            temp);
        gtk_custom_table_set_cell_text(nb_tab_statistics, 1, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 2, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 3, i, 
            "3");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 4, i, 
            "0.00 %");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 5, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 6, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 7, i, 
            "0.00");

        /* set cell colors */
        gtk_custom_table_set_cell_color(nb_tab_statistics, 0, i, 
            colors[j]);
        gtk_custom_table_set_cell_color(nb_tab_statistics, 3, i, 
            graph_bg);
    }
    
    /* statistics footer */
    gtk_custom_table_set_foot_text(nb_tab_statistics, 0, 
        "0");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 1, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 2, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 3, 
        "");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 4, 
        "0.00 %");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 5, 
        "0");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 6, 
        "0");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 7, 
        "0.00");

    gtk_custom_table_set_graph_color(nb_tab_statistics, 3, 
        graph_fg1);

    /* set lists statistics table values */
    for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {

        sprintf(temp, "%d", (j + 1));

        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 0, i, 
            temp);
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 1, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 2, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 3, i, 
            "3");
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 4, i, 
            "0.00 %");
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 5, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 6, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 7, i, 
            "0.00");

        /* set cell colors */
        gtk_custom_table_set_cell_color(nb_tab_lists_stats, 0, i, 
            colors[j]);
        gtk_custom_table_set_cell_color(nb_tab_lists_stats, 3, i, 
            graph_bg);
    }
    
    /* lists statistics footer */
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 0, 
        "0");
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 1, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 2, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 3, 
        "");
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 4, 
        "0.00 %");
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 5, 
        "0");
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 6, 
        "0");
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 7, 
        "0.00");

    gtk_custom_table_set_graph_color(nb_tab_lists_stats, 3, 
        graph_fg2);

    int no_results = 1;

    /* set top 250 table values */
    FILE *fp_top250 = fopen(get_global(CONST_TOP_CSV), "rb");

    if(fp_top250 != NULL) {

        fclose(fp_top250);

        int cols = 0;
        int rows = 0;

        char ***results;

        if(read_file(get_global(CONST_TOP_CSV), &cols, &rows, &results) 
            && rows == 250 && cols == 6) {

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

            gtk_custom_table_set_cell_text(nb_tab_top250, 0, i, 
                temp);
            gtk_custom_table_set_cell_text(nb_tab_top250, 1, i, 
                "0.0");
            gtk_custom_table_set_cell_text(nb_tab_top250, 2, i, 
                "N/A");
            gtk_custom_table_set_cell_text(nb_tab_top250, 3, i, 
                "0");
            gtk_custom_table_set_cell_text(nb_tab_top250, 4, i, 
                "N/A");
            gtk_custom_table_set_cell_text(nb_tab_top250, 5, i, 
                "0");
            gtk_custom_table_set_cell_text(nb_tab_top250, 6, i, 
                "0");
        }
    }

    no_results = 1;

    /* set bottom 100 table values */
    FILE *fp_bot100 = fopen(get_global(CONST_BOT_CSV), "rb");

    if(fp_bot100 != NULL) {
        
        fclose(fp_bot100);

        int cols = 0;
        int rows = 0;

        char ***results;

        if(read_file(get_global(CONST_BOT_CSV), &cols, &rows, &results) 
            && rows == 100 && cols == 6) {

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

            gtk_custom_table_set_cell_text(nb_tab_bot100, 0, i, 
                temp);
            gtk_custom_table_set_cell_text(nb_tab_bot100, 1, i, 
                "0.0");
            gtk_custom_table_set_cell_text(nb_tab_bot100, 2, i, 
                "N/A");
            gtk_custom_table_set_cell_text(nb_tab_bot100, 3, i, 
                "0");
            gtk_custom_table_set_cell_text(nb_tab_bot100, 4, i, 
                "N/A");
            gtk_custom_table_set_cell_text(nb_tab_bot100, 5, i, 
                "0");
            gtk_custom_table_set_cell_text(nb_tab_bot100, 6, i, 
                "0");
        }
    }

    no_results = 1;

    /* set all-time boxoffice table values */
    FILE *fp_boxoffice = fopen(get_global(CONST_BOX_CSV), "rb");

    if(fp_boxoffice != NULL) {

        fclose(fp_boxoffice);


        int cols = 0;
        int rows = 0;

        char ***results;

        if(read_file(get_global(CONST_BOX_CSV), &cols, &rows, &results) 
            && cols == 5) {

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
 
                /* search for current film's imdb rating in other tables */
                int index1 = gtk_custom_table_get_indexof(nb_tab_mymovies, 
                    results[i][1]);
                int index2 = gtk_custom_table_get_indexof(nb_tab_top250, 
                    results[i][1]);
                int index3 = gtk_custom_table_get_indexof(nb_tab_bot100, 
                    results[i][1]);
                int index4 = gtk_custom_table_get_indexof(nb_tab_lists, 
                    results[i][1]);

                /* copy imdb ratings from other tabs to box office tab */
                char *rating1 = index1 >= 0 ? 
                    gtk_custom_table_get_cell_value(nb_tab_mymovies, 1, index1) : "0";
                char *rating2 = index2 >= 0 ? 
                    gtk_custom_table_get_cell_value(nb_tab_top250, 1, index2) : "0";
                char *rating3 = index3 >= 0 ? 
                    gtk_custom_table_get_cell_value(nb_tab_bot100, 1, index3) : "0";
                char *rating4 = index4 >= 0 ? 
                    gtk_custom_table_get_cell_value(nb_tab_lists, 1, index4) : "0";

                /* translate ratings */
                int num1 = atoi(rating1);
                int num2 = atoi(rating2);
                int num3 = atoi(rating3);
                int num4 = atoi(rating4);

                /* apply first discovered value to table */
                if (num1 > 0) {
                    gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, 
                        rating1);
                    gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, i, 
                        colors[num1 - 1]);
                }
                else if(num2 > 0) {
                    gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, 
                        rating2);
                    gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, i, 
                        colors[num2 - 1]);
                }
                else if(num3 > 0) {
                    gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, 
                        rating3);
                    gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, i, 
                        colors[num3 - 1]);
                }
                else if(num4 > 0) {
                    gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, 
                        rating4);
                    gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, i, 
                        colors[num4 - 1]);
                }
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

            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 0, i, 
                temp);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, 
                "0.0");
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 2, i, 
                "0");
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 3, i, 
                "N/A");
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 4, i, 
                "N/A");
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 5, i, 
                "0");
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 6, i, 
                "$0");
        }
    }

    /* set default my-movies/my-lists values */
    for(i = 0; i < 50; i++) {

        sprintf(temp, "%d.", i+1);

        gtk_custom_table_set_cell_text(nb_tab_mymovies, 0, i, 
            temp);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 1, i, 
            "0.0");
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 2, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 3, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 4, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 5, i, 
            "0");

        gtk_custom_table_set_cell_text(nb_tab_lists, 0, i, 
            temp);
        gtk_custom_table_set_cell_text(nb_tab_lists, 1, i, 
            "0.0");
        gtk_custom_table_set_cell_text(nb_tab_lists, 2, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_lists, 3, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_tab_lists, 4, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_tab_lists, 5, i, 
            "0");
    }

    /* create new vboxes for tabs */
    nb_tab_statistics_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_top250_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_bot100_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_boxoffice_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_mymovies_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_lists_vbox = gtk_vbox_new(FALSE, 0);
    nb_tab_lists_stats_vbox = gtk_vbox_new(FALSE, 0);

    /* initialize scrolled windows */
    nb_statistics_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_top250_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_bot100_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_boxoffice_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_mymovies_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_lists_scroll = gtk_scrolled_window_new(NULL, NULL);
    nb_lists_stats_scroll = gtk_scrolled_window_new(NULL, NULL);

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
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(nb_lists_stats_scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    /* create viewports */
    nb_statistics_view = gtk_viewport_new(NULL, NULL);
    nb_top250_view = gtk_viewport_new(NULL, NULL);
    nb_bot100_view = gtk_viewport_new(NULL, NULL);
    nb_boxoffice_view = gtk_viewport_new(NULL, NULL);
    nb_mymovies_view = gtk_viewport_new(NULL, NULL);
    nb_lists_view = gtk_viewport_new(NULL, NULL);
    nb_lists_stats_view = gtk_viewport_new(NULL, NULL);

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
    gtk_container_add(GTK_CONTAINER(nb_lists_stats_view), 
        nb_tab_lists_stats);

    /* disable viewport shadows */
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_statistics_view), 
        GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_top250_view), 
        GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_bot100_view), 
        GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_boxoffice_view), 
        GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_mymovies_view), 
        GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_lists_view), 
        GTK_SHADOW_NONE);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(nb_lists_stats_view), 
        GTK_SHADOW_NONE);
 
    /* add viewports to scrollwindows */
    gtk_container_add(GTK_CONTAINER(nb_statistics_scroll), 
        nb_statistics_view); 
    gtk_container_add(GTK_CONTAINER(nb_top250_scroll), 
        nb_top250_view); 
    gtk_container_add(GTK_CONTAINER(nb_bot100_scroll), 
        nb_bot100_view); 
    gtk_container_add(GTK_CONTAINER(nb_boxoffice_scroll), 
        nb_boxoffice_view); 
    gtk_container_add(GTK_CONTAINER(nb_mymovies_scroll), 
        nb_mymovies_view); 
    gtk_container_add(GTK_CONTAINER(nb_lists_scroll), 
        nb_lists_view); 
    gtk_container_add(GTK_CONTAINER(nb_lists_stats_scroll), 
        nb_lists_stats_view); 

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
    gtk_box_pack_start(GTK_BOX(nb_tab_lists_stats_vbox), 
        nb_lists_stats_scroll, TRUE, TRUE, 0);

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
        nb_tab_top250_vbox, gtk_label_new("Top 250"));
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), 
        nb_tab_bot100_vbox, gtk_label_new("Bottom 100"));
    gtk_notebook_append_page(GTK_NOTEBOOK(nb), 
        nb_tab_boxoffice_vbox, gtk_label_new("Box Office"));

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
    gtk_window_add_accel_group(GTK_WINDOW(window), 
        group_file);
    gtk_window_add_accel_group(GTK_WINDOW(window), 
        group_edit);
    gtk_window_add_accel_group(GTK_WINDOW(window), 
        group_help);

    /* set accelerator groups */
    gtk_menu_set_accel_group(GTK_MENU(menu_file), 
        group_file);
    gtk_menu_set_accel_group(GTK_MENU(menu_edit), 
        group_edit);
    gtk_menu_set_accel_group(GTK_MENU(menu_help), 
        group_help);

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
    gtk_menu_append(GTK_MENU(menu_file), 
        menu_file_item_open);
    gtk_menu_append(GTK_MENU(menu_file), 
        menu_file_item_new);
    gtk_menu_append(GTK_MENU(menu_file), 
        menu_file_item_space);
    gtk_menu_append(GTK_MENU(menu_file), 
        menu_file_item_exit);
    gtk_menu_append(GTK_MENU(menu_edit), 
        menu_edit_item_update);
    gtk_menu_append(GTK_MENU(menu_help), 
        menu_help_item_about);

    /* attach callback functions to menu-items */
    gtk_signal_connect_object(GTK_OBJECT(menu_file_item_open), 
        "activate", GTK_SIGNAL_FUNC(menu_signal_open), (gpointer)window);
    gtk_signal_connect_object(GTK_OBJECT(menu_file_item_new), 
        "activate", GTK_SIGNAL_FUNC(menu_signal_new), (gpointer)window);
    gtk_signal_connect_object(GTK_OBJECT(menu_file_item_exit), 
        "activate", GTK_SIGNAL_FUNC(menu_signal_quit), (gpointer)window);
    gtk_signal_connect_object(GTK_OBJECT(menu_edit_item_update), 
        "activate", GTK_SIGNAL_FUNC(menu_signal_update), (gpointer)window);
    gtk_signal_connect_object(GTK_OBJECT(menu_help_item_about), 
        "activate", GTK_SIGNAL_FUNC(menu_signal_about), (gpointer)window);

    /* create menu items */
    menu_file_item = gtk_menu_item_new_with_mnemonic("_File");
    menu_edit_item = gtk_menu_item_new_with_mnemonic("_Edit");
    menu_help_item = gtk_menu_item_new_with_mnemonic("_Help");

    /* add submenus to menu items */
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_file_item), 
        menu_file);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_edit_item), 
        menu_edit);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_help_item), 
        menu_help);

    /* add to main menubar */
    gtk_menu_bar_append(GTK_MENU_BAR(menubar), 
        menu_file_item);
    gtk_menu_bar_append(GTK_MENU_BAR(menubar), 
        menu_edit_item);
    gtk_menu_bar_append(GTK_MENU_BAR(menubar), 
        menu_help_item);

    /* add widgets to main vbox */
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), nb, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), status, FALSE, FALSE, 0);

    /* push initial status message */
    gtk_statusbar_push(GTK_STATUSBAR(status), 1, 
        "Hit Ctrl+D to download new ratings list, or Ctrl+O to open existing");

    /* last steps, show window */
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_window_set_default_size(GTK_WINDOW(window), 880, 460);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_widget_show_all(window);

    /* just in case */
    gdk_threads_enter();
    gtk_main();
    gdk_threads_leave();

    return 0;
}

