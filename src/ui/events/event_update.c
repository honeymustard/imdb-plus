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


#include "main.h"
#include "ui/globals/globals.h"
#include "ui/widgets/widgets.h"
#include "ui/widgets/fill/fill.h"
#include "ui/table/gtk_custom_table.h"
#include "io/readfile.h"
#include "io/openfile.h"
#include "io/download.h"
#include "io/parsefile.h"
#include "io/patterns.h"


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
        dl_top->url = get_global(CONST_TOP_URL);
        dl_top->saveas = get_global(CONST_TOP_TMP);

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
        dl_bot->url = get_global(CONST_BOT_URL);
        dl_bot->saveas = get_global(CONST_BOT_TMP);

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
        dl_box->url = get_global(CONST_BOX_URL);
        dl_box->saveas = get_global(CONST_BOX_TMP);

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

            if(parse_file(get_global(CONST_TOP_TMP), 
                get_global(CONST_TOP_CSV), pattern_top250)) {
                
                if(ui_fill_lists_top_update()) {
                    topstat = "OK";
                }
            }
        }

        /* attempt to parse bot 100 list */
        if(dl_bot->status == DL_STATUS_OK) {

            if(parse_file(get_global(CONST_BOT_TMP), 
                get_global(CONST_BOT_CSV), pattern_bot100)) {

                if(ui_fill_lists_bot_update()) {
                    botstat = "OK";
                }
            }
        }

        /* attempt to parse boxoffice list */
        if(dl_box->status == DL_STATUS_OK) {

            if(parse_file(get_global(CONST_BOX_TMP), 
                get_global(CONST_BOX_CSV), pattern_boxoffice) || 
                parse_file(get_global(CONST_BOX_TMP), 
                get_global(CONST_BOX_CSV), pattern_boxoffice_win)) {
                
                /* add extra column to boxoffice file */
                int index = 0;

                ResultList *list = malloc(sizeof(ResultList));
                
                if(readfile(list, get_global(CONST_BOX_CSV))) {

                    FILE *fp_out = fopen(get_global(CONST_BOX_CSV), "wb");
                    
                    int i = 0;
                    int j = 0;

                    for(i = 0; i < list->rows; i++) {

                        for(j = 0; j < list->cols; j++) {

                            fprintf(fp_out, "\"%s\",", list->results[i][j]);
                        }

                        index = gtk_custom_table_get_indexof(nb_lists_box_tab->table, 
                            list->results[i][1]);
                            
                        if(index >= 0) {
                            fprintf(fp_out, "\"%s\"\n", 
                                gtk_custom_table_get_cell_text(nb_lists_box_tab->table, 
                                    1, index));
                        }
                        else {
                            fprintf(fp_out, "\"%s\"\n", "0.0");
                        }
                    }

                    fclose(fp_out);
                }

                free(list);
                readfile_free(list);

                if(ui_fill_lists_box_update()) {
                    boxstat = "OK";
                }
            }
        }

        /* remove temp files */
        remove(get_global(CONST_BOT_TMP));
        remove(get_global(CONST_BOX_TMP));
        remove(get_global(CONST_TOP_TMP));

        /* free memory */
        free(dl_top);
        free(dl_bot);
        free(dl_box);

        /* re-open files to update other tabs */
        /*
        char *open_movie_file = get_global(CONST_OPEN_M);
        char *open_lists_file = get_global(CONST_OPEN_L);

        if(open_movie_file != NULL) {
            openfile(open_movie_file);
        }

        if(open_lists_file != NULL) {
            openfile(open_lists_file);
        }
        */

        /* set new statusbar message */
        char *temp = malloc(strlen(format) + strlen(topstat) + 
            strlen(botstat) + strlen(boxstat) + 1);

        sprintf(temp, format, topstat, botstat, boxstat);
        gtk_statusbar_push(GTK_STATUSBAR(stat), 1, temp);

        gtk_custom_table_refresh(mwin);
    }
    
    gtk_widget_destroy(dialog);
}

