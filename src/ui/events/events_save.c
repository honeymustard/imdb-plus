/***********************************************************************
 *
 * Copyright (C) 2011-2013  Adrian Solumsmo
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


#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "ui/globals/globals.h"
#include "ui/widgets/widgets.h"
#include "io/openfile.h"


/* save a list from dialog */
void menu_signal_save(gpointer data) {

    char *tmpfile = globals_get(CONST_OPEN_MOV);

    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new(
        "Save File", 
        GTK_WINDOW(gtk_widget_get_parent(mwin->main)), 
        GTK_FILE_CHOOSER_ACTION_SAVE,
        GTK_STOCK_CANCEL, 
        GTK_RESPONSE_CANCEL,
        GTK_STOCK_OK, 
        GTK_RESPONSE_OK,
        NULL);

    GtkFileChooser *fc = GTK_FILE_CHOOSER(dialog);
    gtk_file_chooser_get_show_hidden(fc);
    gtk_file_chooser_set_current_folder(fc, globals_get(CONST_DOWN));
    gtk_file_chooser_set_current_name(fc, tmpfile);

    /* set position and icon */
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), APP_ICON, NULL);

    /* run filechooser dialog */
    if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {

        char *filename = gtk_file_chooser_get_filename(fc);
        char *stat_tmp = malloc(25 + strlen(filename));

        // check file-extension here..

        rename(tmpfile, filename);

        /* reopen file to reflect changes */
        if(open_file(nb_lists_mov_tab, filename)) {
            sprintf(stat_tmp, "Opened file: %s", filename);
        }
        else {
            sprintf(stat_tmp, "Unable to open: %s", filename);
        }

        gtk_statusbar_push(GTK_STATUSBAR(mwin->stat), 1, stat_tmp);

        free(stat_tmp);
        free(filename);

        /* disable saving */
        gtk_widget_set_sensitive(mwin->menu_file_item_save, FALSE);
    }

    gtk_widget_destroy(dialog);
}

