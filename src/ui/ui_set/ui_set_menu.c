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


#include <gdk/gdkkeysyms.h>
#include "ui/ui.h"
#include "ui/events/events.h"


void ui_set_menu() {

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
    gtk_window_add_accel_group(GTK_WINDOW(window), 
        group_file);
    gtk_window_add_accel_group(GTK_WINDOW(window), 
        group_edit);
    gtk_window_add_accel_group(GTK_WINDOW(window), 
        group_help);

    /* set accelerator groups */
    gtk_menu_set_accel_group(GTK_MENU(menu_file), 
        group_file);
    gtk_menu_set_accel_group(GTK_MENU(menu_edit), 
        group_edit);
    gtk_menu_set_accel_group(GTK_MENU(menu_help), 
        group_help);

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
    gtk_menu_append(GTK_MENU(menu_file), 
        menu_file_item_open);
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
        "activate", GTK_SIGNAL_FUNC(menu_signal_open), (gpointer)window);
    gtk_signal_connect_object(GTK_OBJECT(menu_file_item_new), 
        "activate", GTK_SIGNAL_FUNC(menu_signal_new), (gpointer)window);
    gtk_signal_connect_object(GTK_OBJECT(menu_file_item_exit), 
        "activate", GTK_SIGNAL_FUNC(menu_signal_quit), (gpointer)window);
    gtk_signal_connect_object(GTK_OBJECT(menu_edit_item_update), 
        "activate", GTK_SIGNAL_FUNC(menu_signal_update), (gpointer)window);
    gtk_signal_connect_object(GTK_OBJECT(menu_help_item_about), 
        "activate", GTK_SIGNAL_FUNC(menu_signal_about), (gpointer)window);

    /* create menu items */
    menu_file_item = gtk_menu_item_new_with_mnemonic("_File");
    menu_edit_item = gtk_menu_item_new_with_mnemonic("_Edit");
    menu_help_item = gtk_menu_item_new_with_mnemonic("_Help");

    /* add submenus to menu items */
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_file_item), 
        menu_file);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_edit_item), 
        menu_edit);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_help_item), 
        menu_help);

    /* add to main menubar */
    gtk_menu_bar_append(GTK_MENU_BAR(menubar), 
        menu_file_item);
    gtk_menu_bar_append(GTK_MENU_BAR(menubar), 
        menu_edit_item);
    gtk_menu_bar_append(GTK_MENU_BAR(menubar), 
        menu_help_item);
}

