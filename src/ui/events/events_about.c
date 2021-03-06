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


#include "main.h"
#include "ui/globals/globals.h"
#include "ui/widgets/widgets.h"


/* credits aka self-praise */
const char *APP_AUTH[2] = {
    APP_MAIL,
    NULL,
};

/* default license */
const char *APP_LICN = "\
\n" APP_COPY "\n\
\n\
This program is free software: you can redistribute it and/or modify\n\
it under the terms of the GNU General Public License as published by\n\
the Free Software Foundation, either version 3 of the License, or\n\
(at your option) any later version.\n\
\n\
This program is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
GNU General Public License for more details.\n\
\n\
You should have received a copy of the GNU General Public License\n\
along with this program.  If not, see <http://www.gnu.org/licenses/>.\n";


/**
 * displays an about dialog on menu event..
 */
void menu_signal_about(gpointer data) {
    
    GtkWidget *dialog = gtk_about_dialog_new();

    /* show some interesting factoids */
    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), 
        APP_NAME);
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), 
        globals_get(CONST_VERSION)); 
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

