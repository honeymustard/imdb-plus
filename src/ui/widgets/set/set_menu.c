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


#include <gdk/gdkkeysyms.h>
#include "ui/widgets/widgets.h"
#include "ui/events/events.h"


static GtkAccelGroup *ui_set_menu_item(GtkWidget **menu, GtkWidget **item, 
    char *name) {

    *item = gtk_menu_item_new_with_mnemonic(name);
    *menu = gtk_menu_new();

    GtkAccelGroup *group = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(mwin), group);
    gtk_menu_set_accel_group(GTK_MENU(*menu), group);

    return group;
}


void ui_set_menu() {

    menu = gtk_menu_bar_new();

    GtkAccelGroup *group_file = ui_set_menu_item(&menu_file, 
        &menu_file_item, "_File");
    GtkAccelGroup *group_edit = ui_set_menu_item(&menu_edit, 
        &menu_edit_item, "_Edit");
    GtkAccelGroup *group_help = ui_set_menu_item(&menu_help, 
        &menu_help_item, "_Help");

    /* create submenu items */
    menu_file_item_open = gtk_menu_item_new_with_mnemonic("_Open");
    menu_file_item_compare = gtk_menu_item_new_with_mnemonic("_Compare To");
    menu_file_item_new = gtk_menu_item_new_with_mnemonic("_Download");
    menu_file_item_exit = gtk_menu_item_new_with_mnemonic("_Exit");
    menu_file_item_space = gtk_separator_menu_item_new();
    menu_edit_item_update = gtk_menu_item_new_with_mnemonic("_Update");
    menu_help_item_about = gtk_menu_item_new_with_mnemonic("_About");

    /* add accelerator keys to menu */
    gtk_widget_add_accelerator(menu_file_item_open, "activate", 
        group_file, GDK_O, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(menu_file_item_compare, "activate", 
        group_file, GDK_L, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
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
        menu_file_item_compare);
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
        "activate", GTK_SIGNAL_FUNC(menu_signal_open_mov), (gpointer)mwin);
    gtk_signal_connect_object(GTK_OBJECT(menu_file_item_compare), 
        "activate", GTK_SIGNAL_FUNC(menu_signal_open_lst), (gpointer)mwin);
    gtk_signal_connect_object(GTK_OBJECT(menu_file_item_new), 
        "activate", GTK_SIGNAL_FUNC(menu_signal_new), (gpointer)mwin);
    gtk_signal_connect_object(GTK_OBJECT(menu_file_item_exit), 
        "activate", GTK_SIGNAL_FUNC(menu_signal_quit), (gpointer)mwin);
    gtk_signal_connect_object(GTK_OBJECT(menu_edit_item_update), 
        "activate", GTK_SIGNAL_FUNC(menu_signal_update), (gpointer)mwin);
    gtk_signal_connect_object(GTK_OBJECT(menu_help_item_about), 
        "activate", GTK_SIGNAL_FUNC(menu_signal_about), (gpointer)mwin);

    /* add submenus to menu items */
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_file_item), 
        menu_file);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_edit_item), 
        menu_edit);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_help_item), 
        menu_help);

    /* add to main menubar */
    gtk_menu_bar_append(GTK_MENU_BAR(menu), 
        menu_file_item);
    gtk_menu_bar_append(GTK_MENU_BAR(menu), 
        menu_edit_item);
    gtk_menu_bar_append(GTK_MENU_BAR(menu), 
        menu_help_item);
}

