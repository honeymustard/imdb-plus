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


/* open a ratings/list file from dialog */
void menu_signal_open(GtkWidget *widget, gpointer data) {

    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new(
        "Open File", 
        GTK_WINDOW(widget), 
        GTK_FILE_CHOOSER_ACTION_OPEN,
        GTK_STOCK_CANCEL, 
        GTK_RESPONSE_CANCEL,
        GTK_STOCK_OPEN, 
        GTK_RESPONSE_OK,
        NULL);

    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), 
        get_global(CONST_DOWN));

    /* set position and icon */
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), APP_ICON, NULL);

    /* run filechooser dialog */
    if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {

        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        
        char *stat = malloc(25 + strlen(filename));

        /* attempt to open ratings file */
        if(open_file(filename)) {
            sprintf(stat, "Opened file: %s", filename);
        }
        else {
            sprintf(stat, "Unable to open: %s", filename);
        }

        gtk_statusbar_push(GTK_STATUSBAR(status), 1, stat);

        free(stat);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

