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


#include "../ui.h"


GtkAdjustment *adj;
GtkWidget *pbar, *label, *entry;

/* download new ratings file response handler */
void menu_signal_new_response(GtkWidget *dialog, int response, gpointer *data) {

    /* destroy dialog on these events */
    if((response == GTK_RESPONSE_CANCEL) || 
       (response == GTK_RESPONSE_DELETE_EVENT)) {
        gtk_widget_destroy(dialog);
        return;
    }

    /* copy entered text */
    char entered[100];
    strcpy(entered, gtk_entry_get_text(GTK_ENTRY(entry)));

    /* number should presumably be larger or smaller than this */
    int enter_len = strlen(entered);

    /* check input for length */
    if(enter_len <= 6 || enter_len >= 20) {
        gtk_label_set_text(GTK_LABEL(label), 
            "Text should be 6 to 20 digits..\n");
        return;
    }

    /* download from this url.. */
    char load[100];
    strcpy(load, get_global(CONST_RAT_URL));
    strcat(load, entered);

    /* save to this path.. */
    char save[100];
    strcpy(save, get_global(CONST_DOWN));
    strcat(save, entered);
    strcat(save, ".csv");

    /* set this progressbar message */
    char pbar_text[50];
    strcpy(pbar_text, "Downloading: ");
    strcat(pbar_text, entered);
    strcat(pbar_text, ".csv..");

    gtk_label_set_text(GTK_LABEL(label), "Downloading ratings..\n");
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

    char *temp = NULL;
    char *stat = NULL;
    char *info = NULL;

    int adjustment = 0;

    int opened_file = 0;

    /* attempt to open fresh ratings */
    if(dl->status == DL_STATUS_OK && (opened_file = open_file(save))) {

        info = "finished";
        adjustment = 120;

        stat = "DL OK: Opened ratings file: ";

        temp = malloc(strlen(stat) + strlen(save) + 1);
        strcpy(temp, stat),
        strcat(temp, save);
    }
    else {

        info = "failed..";
        adjustment = 5;
              
        remove(save);

        /* download failed, could not download file */
        if(dl->status == DL_STATUS_NB) {

            stat = "DL ERR: Unable to download file";

            temp = malloc(strlen(stat) + 1);
            strcpy(temp, stat);
        }
        /* download succeeded, but with an error code */
        else if(dl->http_code > 0) {

            stat = "DL ERR: Unable to download file: ";

            char error[20];
            sprintf(error, "%ld", dl->http_code);

            temp = malloc(strlen(stat) + strlen(error) + 1);
            strcpy(temp, stat);
            strcat(temp, error);
        }
        /* download succeeded, but could not open ratings */
        else if(!opened_file) {

            stat = "DL ERR: Unable to open file: ";

            temp = malloc(strlen(stat) + strlen(save) + 1);
            strcpy(temp, stat);
            strcpy(temp, save);
        }
        /* download succeeded, but an unknown error occured */
        else {

            stat = "DL ERR: Unknown error";

            temp = malloc(strlen(stat) + 1);
            strcpy(temp, stat);
        }
    }

    /* set progressbar text and adjustment accordingly */
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), info);
    gtk_adjustment_set_value(adj, adjustment);

    /* push and update statusbar */
    gtk_statusbar_push(GTK_STATUSBAR(status), 1, temp);
    while(gtk_events_pending()) gtk_main_iteration();

    free(temp);
    free(dl);

    gtk_widget_destroy(dialog);
}


/* open new ratings download dialog */
void menu_signal_new(GtkWidget *widget, gpointer data) {
    
    GtkWidget *dialog = gtk_dialog_new_with_buttons(
        "Download Ratings", 
        GTK_WINDOW(widget->parent), 
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
        GTK_STOCK_OK, 
        GTK_RESPONSE_OK, 
        GTK_STOCK_CANCEL, 
        GTK_RESPONSE_CANCEL, 
        NULL
    );
    
    adj = (GtkAdjustment*)gtk_adjustment_new(5, 0, 120, 0, 0, 0);
    GtkWidget *vbox = gtk_vbox_new(FALSE, 5);

    pbar = gtk_progress_bar_new_with_adjustment(adj);
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar), "Waiting..");

    label = gtk_label_new("Enter IMDb ID i.e. 4854451\n");

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    entry = gtk_entry_new();

    gtk_container_add(GTK_CONTAINER(content), label);

    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), pbar, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(content), vbox);
    
    g_signal_connect(dialog, "response", 
        G_CALLBACK(menu_signal_new_response), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(content->parent), 20);
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), APP_ICON, NULL);
    gtk_widget_show_all(GTK_WIDGET(dialog));

    gtk_dialog_run(GTK_DIALOG(dialog));
}


