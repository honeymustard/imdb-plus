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


#include "events.h"
#include "../patterns.h"
#include "../gtk_custom_table/gtk_custom_table.h"


/* parse new top 250 list */
int menu_signal_update_top() {

    int i = 0;
    int cols = 0;
    int rows = 0;

    char ***results;
    
    if(read_file(CONST_TOP_CSV, &cols, &rows, &results) 
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

            /* clear cell color */
            gtk_custom_table_set_cell_color_enable(nb_tab_top250, 2, i, 
                FALSE);

            gtk_custom_table_set_cell_color(nb_tab_top250, 1, i, 
                colors[(int)atof(results[i][1])]); 

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

            /* clear cell color */
            gtk_custom_table_set_cell_color_enable(nb_tab_bot100, 2, i, 
                FALSE);

            gtk_custom_table_set_cell_color(nb_tab_bot100, 1, i, 
                colors[(int)atof(results[i][1])]); 
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

            /* clear cell color */
            gtk_custom_table_set_cell_color_enable(nb_tab_boxoffice, 1, i, 
                FALSE);
            gtk_custom_table_set_cell_color_enable(nb_tab_boxoffice, 2, i, 
                FALSE);
 
            /* find imdb ratings in other tables */
            int index1 = gtk_custom_table_get_indexof(nb_tab_mymovies, 
                results[i][1]);
            int index2 = gtk_custom_table_get_indexof(nb_tab_top250, 
                results[i][1]);
            int index3 = gtk_custom_table_get_indexof(nb_tab_bot100, 
                results[i][1]);
            int index4 = gtk_custom_table_get_indexof(nb_tab_lists, 
                results[i][1]);
            
            /* copy them into boxoffice table */
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

    /* create dialog widgets */
    GtkAdjustment *adj = (GtkAdjustment*)gtk_adjustment_new(5, 0, 120, 0, 0, 0);
    GtkWidget *pbar = gtk_progress_bar_new_with_adjustment(adj);
    GtkWidget *label = gtk_label_new("Download new lists?\n");

    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), "Waiting..");

    /* add widgets to dialog */
    gtk_container_add(GTK_CONTAINER(content), label);
    gtk_container_add(GTK_CONTAINER(content), pbar);

    gtk_container_set_border_width(GTK_CONTAINER(content->parent), 20);
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), APP_ICON, NULL);

    gtk_widget_show_all(GTK_WIDGET(dialog));

    GThread *thread1, *thread2, *thread3;

    /* someone pressed OK.. download some files */
    if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {

        gtk_label_set_text(GTK_LABEL(label), "Downloading lists..\n");

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

            if(parse_file(CONST_TOP_SAV, CONST_TOP_CSV, pattern_top250)) {
                
                if(menu_signal_update_top()) {
                    topstat = "OK";
                }
            }
        }

        /* attempt to parse bot 100 list */
        if(dl_bot->status == DL_STATUS_OK) {

            if(parse_file(CONST_BOT_SAV, CONST_BOT_CSV, pattern_bot100)) {

                if(menu_signal_update_bot()) {
                    botstat = "OK";
                }
            }
        }

        /* attempt to parse boxoffice list */
        if(dl_box->status == DL_STATUS_OK) {

            if(parse_file(CONST_BOX_SAV, CONST_BOX_CSV, pattern_boxoffice) || 
               parse_file(CONST_BOX_SAV, CONST_BOX_CSV, pattern_boxoffice_win)) {

                if(menu_signal_update_box()) {
                    boxstat = "OK";
                }
            }
        }

        /* remove temp files */
        remove(CONST_BOT_SAV);
        remove(CONST_BOX_SAV);
        remove(CONST_TOP_SAV);

        /* free memory */
        free(dl_top);
        free(dl_bot);
        free(dl_box);

        if(current_open_file != NULL) {
            open_file(current_open_file);
        }

        /* set new statusbar message */
        char *temp = malloc(strlen(format) + strlen(topstat) + 
            strlen(botstat) + strlen(boxstat) + 1);

        sprintf(temp, format, topstat, botstat, boxstat);
        gtk_statusbar_push(GTK_STATUSBAR(status), 1, temp);

        gtk_custom_table_refresh(window);
    }
    
    gtk_widget_destroy(dialog);
}


