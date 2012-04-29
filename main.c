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
#include "patterns.h"
#include "tables.h"
#include "widgets.h"
#include "lib/gtk_custom_table/gtk_custom_table.h"
#include "lib/download.h"


/* these functions exist somewhere.. */
extern int read_file(char *filename, int *cols, int *rows, char ****results);
extern int regex_to_csv(char *filename, char *out_file, char *pattern);
extern int free_memory(char ***results, int cols, int rows);


/* main window events, I might use these.. */
static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {

    return FALSE;
}

static void destroy(GtkWidget *widget, gpointer data) {
    
    gtk_main_quit();
}


/* convenience function to add one value from one table to another */
void set_imdb_rating(int index, int row, GtkWidget *copy, GtkWidget *paste) {

    if(index < 0) {
        return;
    }
        
    char *table_row[gtk_custom_table_get_rows(copy)];
    gtk_custom_table_get_row(copy, index, table_row);

    gtk_custom_table_set_cell_text(paste, 1, row, table_row[1]);
    gtk_custom_table_set_cell_color(paste, 1, row, 
        colors[atoi(table_row[1]) - 1]);
}


/* parse new top 250 list */
int menu_signal_update_top() {

    int i = 0;
    int cols = 0;
    int rows = 0;

    char ***results;
    
    if(read_file(CONST_TOP_CSV, &cols, &rows, &results) && cols == 6) {

        for(i = 0; i < gtk_custom_table_get_rows(nb_tab_top250); i++) {

            gtk_custom_table_set_cell_text(nb_tab_top250, 0, i, results[i][0]);
            gtk_custom_table_set_cell_text(nb_tab_top250, 1, i, results[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_top250, 2, i, "0");
            gtk_custom_table_set_cell_text(nb_tab_top250, 3, i, results[i][2]);
            gtk_custom_table_set_cell_text(nb_tab_top250, 4, i, results[i][3]);
            gtk_custom_table_set_cell_text(nb_tab_top250, 5, i, results[i][4]);
            gtk_custom_table_set_cell_text(nb_tab_top250, 6, i, results[i][5]);

            gtk_custom_table_set_cell_color_enable(nb_tab_top250, 2, i, FALSE);

            gtk_custom_table_set_cell_color(nb_tab_top250, 1, i, 
                colors[(int)atof(results[i][1])]); 

            /* add 'my rating' to top250 tab if applicable */
            int index_lst = gtk_custom_table_get_indexof(nb_tab_mymovies, results[i][2]);

            if(index_lst >= 0) {
                
                char *table_row[gtk_custom_table_get_rows(nb_tab_mymovies)];

                gtk_custom_table_get_row(nb_tab_mymovies, index_lst, table_row);

                gtk_custom_table_set_cell_text(nb_tab_top250, 2, i, 
                    table_row[2]);

                gtk_custom_table_set_cell_color(nb_tab_top250, 2, i, 
                    colors[atoi(table_row[2]) - 1]);
            }
        }

        free_memory(results, cols, rows);

        gtk_custom_table_set_sortable(nb_tab_top250, TRUE);
        gtk_custom_table_sort(nb_tab_top250, 0, GTK_CUSTOM_TABLE_ASC);

        return 1;
    }

    return 0;
}


/* parse new bottom 100 list */
int menu_signal_update_bot() {

    int i = 0;
    int cols = 0;
    int rows = 0;

    char ***results;
    
    if(read_file(CONST_BOT_CSV, &cols, &rows, &results) && cols == 6) {

        for(i = 0; i < gtk_custom_table_get_rows(nb_tab_bot100); i++) {

            gtk_custom_table_set_cell_text(nb_tab_bot100, 0, i, results[i][0]);
            gtk_custom_table_set_cell_text(nb_tab_bot100, 1, i, results[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_bot100, 2, i, "0");
            gtk_custom_table_set_cell_text(nb_tab_bot100, 3, i, results[i][2]);
            gtk_custom_table_set_cell_text(nb_tab_bot100, 4, i, results[i][3]);
            gtk_custom_table_set_cell_text(nb_tab_bot100, 5, i, results[i][4]);
            gtk_custom_table_set_cell_text(nb_tab_bot100, 6, i, results[i][5]);

            gtk_custom_table_set_cell_color_enable(nb_tab_bot100, 2, i, FALSE);

            gtk_custom_table_set_cell_color(nb_tab_bot100, 1, i, 
                colors[(int)atof(results[i][1])]); 

            /* add 'my rating' to bot100 tab if applicable */
            int index_lst = gtk_custom_table_get_indexof(nb_tab_mymovies, results[i][2]);

            if(index_lst >= 0) {
                
                char *table_row[gtk_custom_table_get_rows(nb_tab_mymovies)];

                gtk_custom_table_get_row(nb_tab_mymovies, index_lst, table_row);

                gtk_custom_table_set_cell_text(nb_tab_bot100, 2, i, 
                    table_row[2]);

                gtk_custom_table_set_cell_color(nb_tab_bot100, 2, i, 
                    colors[atoi(table_row[2]) - 1]);
            }
        }

        free_memory(results, cols, rows);

        gtk_custom_table_set_sortable(nb_tab_bot100, TRUE);
        gtk_custom_table_sort(nb_tab_bot100, 0, GTK_CUSTOM_TABLE_ASC);

        return 1;
    }

    return 0;
}


/* parse new boxoffice list */
int menu_signal_update_box() {

    int i = 0;
    int cols = 0;
    int rows = 0;
    
    char ***results;
    
    if(read_file(CONST_BOX_CSV, &cols, &rows, &results) && cols == 5) {

        /* update boxoffice tab size */
        gtk_custom_table_resize(nb_tab_boxoffice, -1, rows);

        for(i = 0; i < gtk_custom_table_get_rows(nb_tab_boxoffice); i++) {

            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 0, i, results[i][0]);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, "0.0");
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 2, i, "0");
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 3, i, results[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 4, i, results[i][2]);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 5, i, results[i][3]);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 6, i, results[i][4]);

            gtk_custom_table_set_cell_color_enable(nb_tab_boxoffice, 1, i, FALSE);
            gtk_custom_table_set_cell_color_enable(nb_tab_boxoffice, 2, i, FALSE);

            /* add 'my rating' to boxoffice tab if applicable */
            int index_lst = gtk_custom_table_get_indexof(nb_tab_mymovies, results[i][1]);

            if(index_lst >= 0) {
                
                char *table_row[gtk_custom_table_get_rows(nb_tab_mymovies)];

                gtk_custom_table_get_row(nb_tab_mymovies, index_lst, table_row);

                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, 
                    table_row[2]);
                gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, i, 
                    colors[atoi(table_row[2]) - 1]);
            }
            
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

        return 1;
    }

    return 0;
}


/* update lists from interwebs */
void menu_signal_update(GtkWidget *widget, gpointer data) {
    
    GtkWidget *dialog, *content;

    dialog = gtk_dialog_new_with_buttons(
        "Update Lists", 
        GTK_WINDOW(widget->parent), 
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
        GTK_STOCK_OK, 
        GTK_RESPONSE_ACCEPT, 
        GTK_STOCK_CANCEL, 
        GTK_RESPONSE_REJECT, 
        NULL
    );
    
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GtkAdjustment *adj = (GtkAdjustment*)gtk_adjustment_new(5, 0, 120, 0, 0, 0);
    GtkWidget *pbar = gtk_progress_bar_new_with_adjustment(adj);
    GtkWidget *label = gtk_label_new("Download new lists?\n");

    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), "Waiting..");

    gtk_container_add(GTK_CONTAINER(content), label);
    gtk_container_add(GTK_CONTAINER(content), pbar);

    gtk_container_set_border_width(GTK_CONTAINER(content->parent), 30);
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), APP_ICON, NULL);
    gtk_widget_show_all(GTK_WIDGET(dialog));

    int ret = gtk_dialog_run(GTK_DIALOG(dialog));

    GThread *thread1, *thread2, *thread3;

    /* someone press OK.. download some files */
    if(ret == GTK_RESPONSE_ACCEPT) {

        gtk_label_set_text(GTK_LABEL(label), "Downloading lists..");

        /* begin thread 1 */
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), "Top 250");
        while(gtk_events_pending()) gtk_main_iteration();

        /* download top250 list */
        struct download *dl_top = malloc(sizeof (struct download));
        dl_top->url = CONST_TOP;
        dl_top->saveas = CONST_TOP_SAV;

        thread1 = g_thread_create(&download, dl_top, TRUE, NULL);

        if(thread1 == 0) {
            g_warning("can't create the thread");
        }

        g_thread_join(thread1);

        /* begin thread 2 */
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), "Bottom 100");
        gtk_adjustment_set_value(adj, 40);
        while(gtk_events_pending()) gtk_main_iteration();

        /* download bottom100 list */
        struct download *dl_bot = malloc(sizeof (struct download));
        dl_bot->url = CONST_BOT;
        dl_bot->saveas = CONST_BOT_SAV;

        thread2 = g_thread_create(&download, dl_bot, TRUE, NULL);

        if (thread2 == 0) {
            g_warning("can't create the thread");
        }

        g_thread_join(thread2);

        /* begin thread 3 */
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), "All-time Boxoffice");
        gtk_adjustment_set_value(adj, 80);
        while(gtk_events_pending()) gtk_main_iteration();

        /* download boxoffice list */
        struct download *dl_box = malloc(sizeof (struct download));
        dl_box->url = CONST_BOX;
        dl_box->saveas = CONST_BOX_SAV;

        thread3 = g_thread_create(&download, dl_box, TRUE, NULL);

        if(thread3 == 0) {
            g_warning("can't create the thread");
        }

        g_thread_join(thread3);

        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), "Finished");
        gtk_adjustment_set_value(adj, 120);
        while(gtk_events_pending()) gtk_main_iteration();

        /* all threads have finished, do something with results */

        char *topstat = "ERR";
        char *botstat = "ERR";
        char *boxstat = "ERR";

        char *format = "DL Stats: Top 250: %s | Bottom 100: %s | Boxoffice: %s";

        /* attempt to parse top 250 list */
        if(dl_top->status == DL_STATUS_OK) {

            if(regex_to_csv(CONST_TOP_SAV, CONST_TOP_CSV, pattern_top250)) {
                
                if(menu_signal_update_top()) {
                    topstat = "OK";
                }
            }
        
            remove(CONST_TOP_SAV);
        }

        /* attempt to parse bot 100 list */
        if(dl_bot->status == DL_STATUS_OK) {

            if(regex_to_csv(CONST_BOT_SAV, CONST_BOT_CSV, pattern_bot100)) {

                if(menu_signal_update_bot()) {
                    botstat = "OK";
                }
            }
            
            remove(CONST_BOT_SAV);
        }

        /* attempt to parse boxoffice list */
        if(dl_box->status == DL_STATUS_OK) {

            if(regex_to_csv(CONST_BOX_SAV, CONST_BOX_CSV, pattern_boxoffice) || 
               regex_to_csv(CONST_BOX_SAV, CONST_BOX_CSV, pattern_boxoffice_win)) {

                if(menu_signal_update_box()) {
                    boxstat = "OK";
                }
            }
            
            remove(CONST_BOX_SAV);
        }

        /* free memory */
        free(dl_top);
        free(dl_bot);
        free(dl_box);

        /* set new statusbar message */
        char *temp = malloc(strlen(format) + strlen(topstat) + 
            strlen(botstat) + strlen(boxstat) + 1);

        sprintf(temp, format, topstat, botstat, boxstat);
        gtk_statusbar_push(GTK_STATUSBAR(status), 1, temp);

        gtk_custom_table_refresh(window);
    }
    
    gtk_widget_destroy(dialog);
}



/**
 * read and parse a ratings file or list..
 * @param char *filename    file to open..
 */
int menu_open_ratings(char *filename) {

    int cols = 0;
    int rows = 0;

    char ***results;
            
    if(!read_file(filename, &cols, &rows, &results) || cols < 10) {
        return 0;
    }

    int i = 0;
    int j = 0;

    char temp[100];

    if(strcmp("IMDb Rating", results[0][9]) == 0) {

        double stats[10][4] = {{0}};

        int graph_apex = 0;
        int year_average = 0;
        int vote_average = 0;

        for(i = 1; i < rows; i++) {

            /* add up amount of votes per rating */
            stats[atoi(results[i][8])-1][2] += 1;
            /* add up year average per rating */
            stats[atoi(results[i][8])-1][3] += atoi(results[i][11]);

            /* add up total vote and year averages */
            vote_average += atoi(results[i][8]);
            year_average += atoi(results[i][11]);
        }

        for(i = 0; i < 10; i++) {

            /* calculate year averages for each rating */
            stats[i][3] = stats[i][2] != 0 ? stats[i][3] / stats[i][2] : 0;
            /* calculate percentage for each rating */
            stats[i][1] = stats[i][2] != 0 ? (stats[i][2] / rows) * 100: 0;
            /* find graph apex, i.e. the longest bar on screen */
            graph_apex = stats[i][2] > graph_apex ? stats[i][2]: graph_apex;
        }

        /* add statistics to widget table */
        for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {
            
            /* calculate graph value from vote amounts, graph is 0-100 */
            stats[i][0] = stats[i][2] != 0 ? 100 / (graph_apex / stats[i][2]) : 0;

            /* add statistics to table row */
            sprintf(temp, "%1.0f", stats[i][0]);
            gtk_custom_table_set_cell_text(nb_tab_statistics, 1, j, temp);
            sprintf(temp, "%3.2f %%", stats[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_statistics, 2, j, temp);
            sprintf(temp, "%1.0f", stats[i][2]);
            gtk_custom_table_set_cell_text(nb_tab_statistics, 3, j, temp);
            sprintf(temp, "%1.2f", stats[i][3]);
            gtk_custom_table_set_cell_text(nb_tab_statistics, 4, j, temp);
        }

        /* add statistics footer */
        sprintf(temp, "%1.1f", (double)vote_average / (rows -1));
        gtk_custom_table_set_foot_text(nb_tab_statistics, 0, temp);
        sprintf(temp, "You have rated %d, on average %1.2f", 
            (rows - 1), (double)vote_average / (rows - 1));
        gtk_custom_table_set_foot_text(nb_tab_statistics, 1, temp);
        gtk_custom_table_set_foot_text(nb_tab_statistics, 2, "100.00 %");
        sprintf(temp, "%d", (rows - 1));
        gtk_custom_table_set_foot_text(nb_tab_statistics, 3, temp);
        sprintf(temp, "%4.2f", (double)year_average / (rows - 1));
        gtk_custom_table_set_foot_text(nb_tab_statistics, 4, temp);

        gtk_custom_table_set_sortable(nb_tab_statistics, TRUE);

        /* update mymovies tab with new data */
        gtk_custom_table_resize(nb_tab_mymovies, -1, (rows - 1));
        
        /* add text to widget table */
        for(i = 1, j = 0; i < rows; i++, j++) {

            sprintf(temp, "%d", i);

            gtk_custom_table_set_cell_text(nb_tab_mymovies, 0, j, temp);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 1, j, results[i][9]);
            gtk_custom_table_set_cell_color(nb_tab_mymovies, 1, j, 
                colors[(int)atoi(results[i][9]) - 1]);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 2, j, results[i][8]);
            gtk_custom_table_set_cell_color(nb_tab_mymovies, 2, j, 
                colors[atoi(results[i][8]) - 1]);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 3, j, results[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 4, j, results[i][5]);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 5, j, results[i][11]);

            /* add 'my rating' to top250 tab if applicable */
            int index_top = gtk_custom_table_get_indexof(nb_tab_top250, 
                results[i][1]);

            if(index_top >= 0) {

                gtk_custom_table_set_cell_text(nb_tab_top250, 2, index_top, 
                    results[i][8]);
                gtk_custom_table_set_cell_color(nb_tab_top250, 2, index_top, 
                    colors[atoi(results[i][8]) - 1]);
            }

            /* add 'my rating' to boxoffice tab if applicable */
            int index_box = gtk_custom_table_get_indexof(nb_tab_boxoffice, 
                results[i][1]);

            if(index_box >= 0) {

                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, index_box, 
                    results[i][9]);
                gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, index_box, 
                    colors[atoi(results[i][9]) - 1]);
                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 2, index_box, 
                    results[i][8]);
                gtk_custom_table_set_cell_color(nb_tab_boxoffice, 2, index_box, 
                    colors[atoi(results[i][8]) - 1]);
            }

            /* add 'my rating' to lists tab if applicable */
            int index_lst = gtk_custom_table_get_indexof(nb_tab_lists, 
                results[i][1]);

            if(index_lst >= 0) {

                gtk_custom_table_set_cell_text(nb_tab_lists, 2, index_lst, 
                    results[i][8]);
                gtk_custom_table_set_cell_color(nb_tab_lists, 2, index_lst, 
                    colors[atoi(results[i][8]) - 1]);
            }
        }

        gtk_custom_table_set_sortable(nb_tab_mymovies, TRUE);
        gtk_custom_table_sort(nb_tab_mymovies, 0, GTK_CUSTOM_TABLE_ASC);

        free_memory(results, cols, rows);
    }
    else {

        /* update lists tab with new data */
        gtk_custom_table_resize(nb_tab_lists, -1, (rows - 1));

        /* add text to widget table */
        for(i = 1, j = 0; i < rows; i++, j++) {

            sprintf(temp, "%d", i);

            gtk_custom_table_set_cell_text(nb_tab_lists, 0, j, temp);
            gtk_custom_table_set_cell_text(nb_tab_lists, 1, j, results[i][8]); 
            gtk_custom_table_set_cell_text(nb_tab_lists, 2, j, "0");
            gtk_custom_table_set_cell_text(nb_tab_lists, 3, j, results[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_lists, 4, j, results[i][5]);
            gtk_custom_table_set_cell_text(nb_tab_lists, 5, j, results[i][10]);
            
            /* make sure value falls within color range.. */
            int cell_to_color = (int)atoi(results[i][8]) - 1;

            if(cell_to_color < 10 && cell_to_color >= 0) {
                gtk_custom_table_set_cell_color(nb_tab_lists, 1, j, 
                    colors[(int)atoi(results[i][8]) - 1]);
            }

            /* add 'my rating' to lists tab if applicable */
            int index_lst = gtk_custom_table_get_indexof(nb_tab_mymovies, 
                results[i][1]);

            if(index_lst >= 0) {
                
                char *table_row[gtk_custom_table_get_rows(nb_tab_mymovies)];

                gtk_custom_table_get_row(nb_tab_mymovies, index_lst, table_row);

                gtk_custom_table_set_cell_text(nb_tab_lists, 2, j, 
                    table_row[2]);
                gtk_custom_table_set_cell_color(nb_tab_lists, 2, j, 
                    colors[atoi(table_row[2]) - 1]);
            }

            /* add imdb-rating to boxoffice tab if applicable */
            int index_box = gtk_custom_table_get_indexof(nb_tab_boxoffice, 
                results[i][8]);

            if(index_box >= 0) {

                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, index_box, 
                    results[i][8]);

                if(cell_to_color < 10 && cell_to_color >= 0) {
                    gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, 
                        index_box, colors[(int)atoi(results[i][8]) - 1]);
                }
            }
        }

        gtk_custom_table_set_sortable(nb_tab_lists, TRUE);
        gtk_custom_table_sort(nb_tab_lists, 0, GTK_CUSTOM_TABLE_ASC);

        free_memory(results, cols, rows);
    }

    gtk_custom_table_refresh(window);

    return 1;
}


/* open new ratings download dialog */
void menu_signal_new(GtkWidget *widget, gpointer data) {
    
    dialog = gtk_dialog_new_with_buttons(
        "Download Ratings", 
        GTK_WINDOW(widget->parent), 
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
        GTK_STOCK_OK, 
        GTK_RESPONSE_ACCEPT, 
        GTK_STOCK_CANCEL, 
        GTK_RESPONSE_REJECT, 
        NULL
    );
    
    GtkAdjustment *adj = (GtkAdjustment*)gtk_adjustment_new(5, 0, 120, 0, 0, 0);
    GtkWidget *vbox = gtk_vbox_new(FALSE, 5);

    GtkWidget *pbar = gtk_progress_bar_new_with_adjustment(adj);
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), "Waiting..");

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    entry = gtk_entry_new();

    GtkWidget *label = gtk_label_new(" Enter unique IMDb ID i.e. 4854451\n");
    gtk_container_add(GTK_CONTAINER(content), label);

    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), pbar, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(content), vbox);

    gtk_container_set_border_width(GTK_CONTAINER(content->parent), 30);
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), APP_ICON, NULL);
    gtk_widget_show_all(GTK_WIDGET(dialog));

    /* run dialog */
    if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {

        /* copy entered text */
        char entered[100];
        strcpy(entered, gtk_entry_get_text(GTK_ENTRY(entry)));

        /* number should presumably be larger or smaller than this */
        int enter_len = strlen(entered);

        if(enter_len <= 6 || enter_len >= 20) {
            return;
        }

        /* download from this url.. */
        char load[100];
        strcpy(load, CONST_URL);
        strcat(load, entered);

        /* save to this path.. */
        char save[100];
        strcpy(save, CONST_PREFIX);
        strcat(save, entered);
        strcat(save, ".csv");

        /* set this progressbar message */
        char pbar_text[50];
        strcpy(pbar_text, "Downloading: ");
        strcat(pbar_text, entered);
        strcat(pbar_text, ".csv..");

        gtk_label_set_text(GTK_LABEL(label), "Downloading ratings..");
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), pbar_text);
        gtk_adjustment_set_value(adj, 20);
        while(gtk_events_pending()) gtk_main_iteration();

        /* download new file */
        struct download *dl = malloc(sizeof (struct download));
        dl->url = load;
        dl->saveas = save;

        GThread *thread = g_thread_create(&download, dl, TRUE, NULL);

        if(thread == 0) {
            g_warning("can't create the thread");
        }

        g_thread_join(thread);

        free(dl);

        char *temp = NULL;
        char *stat = NULL;
        char *info = NULL;
        int adjustment = 0;

        /* open fresh ratings */
        if(menu_open_ratings(save)) {

            stat = "Opened ratings file: ";
            info = "finished";
            adjustment = 120;
        }
        else {
            
            stat = "Could not open file: ";
            info = "Waiting..";
            adjustment = 5;
                  
            remove(save);
        }

        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), info);
        gtk_adjustment_set_value(adj, adjustment);

        temp = malloc(strlen(stat) + strlen(save) + 1);
        strcpy(temp, stat),
        strcat(temp, save);
            
        gtk_statusbar_push(GTK_STATUSBAR(status), 1, temp);

        while(gtk_events_pending()) gtk_main_iteration();

        gtk_widget_destroy(dialog);
    }
        
    if(GTK_IS_WIDGET(dialog)) {
        gtk_widget_destroy(dialog);
    }
}


/* open a ratings/list file from dialog */
void menu_signal_open(GtkWidget *widget, gpointer data) {

    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new(
        "Open File", 
        GTK_WINDOW(widget), 
        GTK_FILE_CHOOSER_ACTION_OPEN,
        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
        GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
        NULL);    

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), APP_ICON, NULL);

    if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {

        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        
        char *temp = NULL;
        char *stat = NULL;

        /* attempt to open ratings file */
        if(menu_open_ratings(filename)) {
            stat = "Opened ratings file: ";
        }
        else {
            stat = "Unable to open file: ";
        }

        temp = malloc(strlen(stat) + strlen(filename) + 1);
        strcpy(temp, stat),
        strcat(temp, filename);
            
        gtk_statusbar_push(GTK_STATUSBAR(status), 1, temp);

        free(temp);
    }

    gtk_widget_destroy(dialog);
}


/**
 * displays an about dialog on menu event..
 */
void menu_signal_about(GtkWidget *widget, gpointer data) {
    
    GtkWidget *dialog = gtk_about_dialog_new();

    /* show some interesting factoids */
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), 
        APP_NAME);
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), 
        APP_VERS); 
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), 
        APP_COPY);
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), 
        APP_DESC);
    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog), 
        APP_AUTH);
    gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(dialog), 
        APP_LICN);
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), 
        APP_HOME);

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(APP_ICON, NULL);
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), APP_ICON, NULL);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    gtk_dialog_run(GTK_DIALOG (dialog));

    gtk_widget_destroy(dialog);
}



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
    g_signal_connect(window, "delete-event", 
        G_CALLBACK(delete_event), NULL);
    g_signal_connect(window, "destroy", 
        G_CALLBACK(destroy), NULL);

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

    gtk_custom_table_set_column_graph(nb_tab_statistics, 1, TRUE);

    /* statistics main rows */
    for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {

        sprintf(temp, "%d", vote_counter--);
        gtk_custom_table_set_cell_text(nb_tab_statistics, 0, i, temp);
        gtk_custom_table_set_cell_text(nb_tab_statistics, 1, i, "2");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 2, i, "0.00 %");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 3, i, "0");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 4, i, "0.00");

        gtk_custom_table_set_cell_color(nb_tab_statistics, 0, i, colors[j]);
        gtk_custom_table_set_cell_color(nb_tab_statistics, 1, i, graph_bg);
        gtk_custom_table_set_cell_color(nb_tab_statistics, 4, i, colors[j]);
    }
    
    /* statistics footer */
    gtk_custom_table_set_foot_text(nb_tab_statistics, 0, "0");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 1, "");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 2, "0.00 %");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 3, "0");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 4, "0.00");


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
        GTK_SIGNAL_FUNC(menu_signal_open), NULL);
    gtk_signal_connect_object(GTK_OBJECT(menu_file_item_new), "activate", 
        GTK_SIGNAL_FUNC(menu_signal_new), (gpointer)window);
    gtk_signal_connect_object(GTK_OBJECT(menu_file_item_exit), "activate", 
        GTK_SIGNAL_FUNC(destroy), NULL);
    gtk_signal_connect_object(GTK_OBJECT(menu_edit_item_update), "activate", 
        GTK_SIGNAL_FUNC(menu_signal_update), (gpointer)window);
    gtk_signal_connect_object(GTK_OBJECT(menu_help_item_about), "activate", 
        GTK_SIGNAL_FUNC(menu_signal_about), NULL);

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

    gtk_statusbar_push(GTK_STATUSBAR(status), 1, 
        "Hit Ctrl+D to download new ratings list, or Ctrl+O to open existing");

    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_window_set_default_size(GTK_WINDOW(window), 740, 440);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    gtk_widget_show_all(window);

    gdk_threads_enter();
    gtk_main();
    gdk_threads_leave();

    return 0;
}

