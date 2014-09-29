/***********************************************************************
 *
 * Copyright (C) 2011-2014  Adrian Solumsmo
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
#include "ui/table/gtk_custom_table.h"
#include "io/readfile.h"
#include "io/openfile.h"
#include "io/download.h"
#include "io/parsefile.h"
#include "io/patterns.h"


/* update lists from internet */
void menu_signal_update(gpointer data) {

    GtkWidget *dialog, *content;

    dialog = gtk_dialog_new_with_buttons(
        "Update Lists", 
        GTK_WINDOW(gtk_widget_get_parent(mwin->main)), 
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
    GtkWidget *pbar = gtk_progress_bar_new();
    GtkWidget *label = gtk_label_new("Download new lists?\n");

    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), "Waiting..");
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pbar), 0.1);

    /* add widgets to dialog */
    gtk_container_add(GTK_CONTAINER(content), label);
    gtk_container_add(GTK_CONTAINER(content), pbar);

    gtk_container_set_border_width(GTK_CONTAINER(gtk_widget_get_parent(content)), 20);
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), APP_ICON, NULL);

    gtk_widget_show_all(GTK_WIDGET(dialog));

    GThread *thread1, *thread2, *thread3;

    /* pressed OK.. download some files */
    if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {

        gtk_label_set_text(GTK_LABEL(label), "Downloading lists..\n");

        /* begin thread 1 */
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), "Top 250");

        while(gtk_events_pending()) gtk_main_iteration();

        /* download top250 list */
        Download *dl_top = malloc(sizeof(Download));
        dl_top->url = globals_get(CONST_TOP_URL);
        dl_top->saveas = globals_get(CONST_TOP_TMP);

        thread1 = g_thread_new("thread1", &download, dl_top);

        if(thread1 == 0) {
            g_warning("can't create the thread");
        }

        g_thread_join(thread1);

        /* begin thread 2 */
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), "Bottom 100");
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pbar), 0.33);

        while(gtk_events_pending()) gtk_main_iteration();

        /* download bottom100 list */
        Download *dl_bot = malloc(sizeof(Download));
        dl_bot->url = globals_get(CONST_BOT_URL);
        dl_bot->saveas = globals_get(CONST_BOT_TMP);

        thread2 = g_thread_new("thread2", &download, dl_bot);

        if (thread2 == 0) {
            g_warning("can't create the thread");
        }

        g_thread_join(thread2);

        /* begin thread 3 */
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), "All-time Boxoffice");
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pbar), 0.66);

        while(gtk_events_pending()) gtk_main_iteration();

        /* download boxoffice list */
        Download *dl_box = malloc(sizeof(Download));
        dl_box->url = globals_get(CONST_BOX_URL);
        dl_box->saveas = globals_get(CONST_BOX_TMP);

        thread3 = g_thread_new("thread3", &download, dl_box);

        if(thread3 == 0) {
            g_warning("can't create the thread");
        }

        g_thread_join(thread3);

        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), "Finished");
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pbar), 1.0);

        while(gtk_events_pending()) gtk_main_iteration();

        /* all threads have finished, do something with results */
        char *topstat = "ERR";
        char *botstat = "ERR";
        char *boxstat = "ERR";

        char *format = "DL Stats: Top 250: %s | Bottom 100: %s | Boxoffice: %s";

        /* attempt to parse top 250 list */
        if(dl_top->status == DL_STATUS_OK) {

            if(parse_file(globals_get(CONST_TOP_TMP), 
                globals_get(CONST_TOP_CSV), pattern_top) || 
                parse_file(globals_get(CONST_TOP_TMP), 
                globals_get(CONST_TOP_CSV), pattern_top_win)) {
                
                if(ui_fill_lists_top_update()) {

                    topstat = "OK";
                }
            }
        }

        /* attempt to parse bot 100 list */
        if(dl_bot->status == DL_STATUS_OK) {

            if(parse_file(globals_get(CONST_BOT_TMP), 
                globals_get(CONST_BOT_CSV), pattern_bot) || 
                parse_file(globals_get(CONST_BOT_TMP), 
                globals_get(CONST_BOT_CSV), pattern_bot_win)) {

                if(ui_fill_lists_bot_update()) {
                    botstat = "OK";
                }
            }
        }

        /* attempt to parse boxoffice list */
        if(dl_box->status == DL_STATUS_OK) {

            if(parse_file(globals_get(CONST_BOX_TMP), 
                globals_get(CONST_BOX_CSV), pattern_box) || 
                parse_file(globals_get(CONST_BOX_TMP), 
                globals_get(CONST_BOX_CSV), pattern_box_win)) {
                
                /* add extra column to boxoffice file */
                int index = 0;

                ResultList *list = readfile_new();
                
                if(readfile(list, globals_get(CONST_BOX_CSV))) {

                    GtkWidget *box = nb_lists_box_tab->table;

                    FILE *fp_out = fopen(globals_get(CONST_BOX_CSV), "wb");
                    
                    int i = 0;
                    int j = 0;

                    for(i = 0; i < list->rows; i++) {

                        for(j = 0; j < list->cols; j++) {

                            fprintf(fp_out, "\"%s\",", list->results[i][j]);
                        }

                        /* new list might be a different size */
                        index = gtk_custom_table_get_indexof(box, 
                            list->results[i][1]);

                        if(index >= 0) {
                            fprintf(fp_out, "\"%s\"\n", 
                                gtk_custom_table_get_cell_text(box, 1, index));
                        }
                        else {
                            fprintf(fp_out, "\"%s\"\n", "0.0");
                        }
                    }

                    fclose(fp_out);

                    if(ui_fill_lists_box_update()) {

                        nb_lists_box_tab->has_changed = 1;
                        boxstat = "OK";
                    }
                }

                readfile_free(list);
            }
        }

        /* remove temp files */
        remove(globals_get(CONST_BOT_TMP));
        remove(globals_get(CONST_BOX_TMP));
        remove(globals_get(CONST_TOP_TMP));

        /* free memory */
        free(dl_top);
        free(dl_bot);
        free(dl_box);

        /* re-open files to update other tabs */
        open_file(nb_lists_mov_tab, globals_get(CONST_OPEN_MOV));
        open_file(nb_lists_lst_tab, globals_get(CONST_OPEN_LST));

        /* set new statusbar message */
        char *temp = malloc(strlen(format) + strlen(topstat) + 
            strlen(botstat) + strlen(boxstat) + 1);

        sprintf(temp, format, topstat, botstat, boxstat);
        gtk_statusbar_push(GTK_STATUSBAR(mwin->stat), 1, temp);

        gtk_custom_table_refresh(mwin->main);
    }
    
    gtk_widget_destroy(dialog);
}

