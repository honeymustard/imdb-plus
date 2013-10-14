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



/* simple basename: full filename - foldername -> buffer */
static void file_basename(char *filename, char *folder, char **buffer) {

    int i = 0;
    int j = 0;

    *buffer = malloc((strlen(filename) - strlen(folder)) + 1);

    for(i = strlen(folder) + 1, j = 0; i < strlen(filename); ++i, j++) {
        (*buffer)[j] = filename[i];
    }

    (*buffer)[j] = '\0';
}


/* chop filename down to length and place it in a buffer */
static void file_truncate(char *filename, char **buffer, int length) {

    *buffer = malloc(length + 1);

    strncpy(*buffer, filename, length);

    if(strlen(filename) > length) {
        (*buffer)[length--] = '\0';
        (*buffer)[length--] = '.';
        (*buffer)[length--] = '.';
        (*buffer)[length--] = '.';
    }
}


/* prefix a filename and place it in a buffer */
static void file_prefixer(char *filename, char *prefix, char **buffer) {

    *buffer = malloc(strlen(filename) + strlen(prefix) + 1);

    strcpy(*buffer, prefix);
    strcat(*buffer, filename);
}


/* open a ratings/list file from dialog */
void menu_signal_open(gpointer data) {

    NotebookTab *tab = (NotebookTab *)data;

    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new(
        "Open File", 
        GTK_WINDOW(mwin->main->parent), 
        GTK_FILE_CHOOSER_ACTION_OPEN,
        GTK_STOCK_CANCEL, 
        GTK_RESPONSE_CANCEL,
        GTK_STOCK_OPEN, 
        GTK_RESPONSE_OK,
        NULL);

    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), 
        globals_get(CONST_DOWN));

    /* set a new file filter to limit types */
    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "*.csv");
    gtk_file_filter_add_pattern(filter, "*.csv");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    /* set position and icon */
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), APP_ICON, NULL);

    /* run filechooser dialog */
    if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {

        GtkFileChooser *fc = GTK_FILE_CHOOSER(dialog);

        char *filename = gtk_file_chooser_get_filename(fc);
        char *foldername = gtk_file_chooser_get_current_folder(fc);

        char *file_base = NULL;
        char *file_tabs = NULL;
        char *file_stat = NULL;

        /* standard basename of filename */
        file_basename(filename, foldername, &file_base);
        globals_set(CONST_OPEN_BASENAME, file_base);

        /* standard basename of filename with ellipsis */
        file_truncate(file_base, &file_tabs, 15);
        globals_set(CONST_OPEN_TABSNAME, file_tabs);

        /* standard basename of filename prefixed with Stat */
        file_prefixer(file_tabs, "Stats: ", &file_stat);
        globals_set(CONST_OPEN_STATNAME, file_stat);

        free(file_base);
        free(file_tabs);
        free(file_stat);
       
        char *stat_tmp = malloc(25 + strlen(filename));

        /* attempt to open ratings file */
        if(open_file(tab, filename)) {

            sprintf(stat_tmp, "Opened file: %s", filename);
        }
        else {

            sprintf(stat_tmp, "Unable to open: %s", filename);
        }

        gtk_statusbar_push(GTK_STATUSBAR(mwin->stat), 1, stat_tmp);

        free(stat_tmp);
        free(filename);
    }

    gtk_widget_destroy(dialog);
}

