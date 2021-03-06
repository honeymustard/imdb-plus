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


#include <gdk/gdkkeysyms.h>
#include "ui/widgets/widgets.h"
#include "ui/events/events.h"


static GtkAccelGroup *ui_set_menu_item(GtkWidget **menu, GtkWidget **item, 
    char *name) {

    *item = gtk_menu_item_new_with_mnemonic(name);
    *menu = gtk_menu_new();

    GtkAccelGroup *group = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(mwin->main), group);
    gtk_menu_set_accel_group(GTK_MENU(*menu), group);

    return group;
}


void ui_set_menu() {

    mwin->menu = gtk_menu_bar_new();

    GtkAccelGroup *group_file = ui_set_menu_item(&(mwin->menu_file), 
        &(mwin->menu_file_item), "_File");
    GtkAccelGroup *group_edit = ui_set_menu_item(&(mwin->menu_edit), 
        &(mwin->menu_edit_item), "_Edit");
    GtkAccelGroup *group_help = ui_set_menu_item(&(mwin->menu_help), 
        &(mwin->menu_help_item), "_Help");

    /* create submenu items */
    mwin->menu_file_item_open = gtk_menu_item_new_with_mnemonic("_Open");
    mwin->menu_file_item_compare = gtk_menu_item_new_with_mnemonic("_Compare To");
    mwin->menu_file_item_exit = gtk_menu_item_new_with_mnemonic("_Exit");
    mwin->menu_file_item_space = gtk_separator_menu_item_new();
    mwin->menu_edit_item_update = gtk_menu_item_new_with_mnemonic("_Update");
    mwin->menu_edit_item_purge = gtk_menu_item_new_with_mnemonic("_Purge Lists");
    mwin->menu_help_item_about = gtk_menu_item_new_with_mnemonic("_About");

    /* add accelerator keys to menu */
    gtk_widget_add_accelerator(mwin->menu_file_item_open, "activate", 
        group_file, GDK_KEY_O, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(mwin->menu_file_item_compare, "activate", 
        group_file, GDK_KEY_L, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(mwin->menu_file_item_exit, "activate", 
        group_file, GDK_KEY_Q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(mwin->menu_edit_item_update, "activate", 
        group_edit, GDK_KEY_U, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(mwin->menu_edit_item_purge, "activate", 
        group_edit, GDK_KEY_P, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(mwin->menu_help_item_about, "activate", 
        group_help, GDK_KEY_A, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

    /* append menu items to menus */
    gtk_menu_shell_append(GTK_MENU_SHELL(mwin->menu_file), mwin->menu_file_item_open);
    gtk_menu_shell_append(GTK_MENU_SHELL(mwin->menu_file), mwin->menu_file_item_compare);
    gtk_menu_shell_append(GTK_MENU_SHELL(mwin->menu_file), mwin->menu_file_item_space);
    gtk_menu_shell_append(GTK_MENU_SHELL(mwin->menu_file), mwin->menu_file_item_exit);
    gtk_menu_shell_append(GTK_MENU_SHELL(mwin->menu_edit), mwin->menu_edit_item_update);
    gtk_menu_shell_append(GTK_MENU_SHELL(mwin->menu_edit), mwin->menu_edit_item_purge);
    gtk_menu_shell_append(GTK_MENU_SHELL(mwin->menu_help), mwin->menu_help_item_about);

    /* attach callback functions to menu-items */
    g_signal_connect_swapped(G_OBJECT(mwin->menu_file_item_open), 
        "activate", G_CALLBACK(menu_signal_open), (gpointer)nb_lists_mov_tab);
    g_signal_connect_swapped(G_OBJECT(mwin->menu_file_item_compare), 
        "activate", G_CALLBACK(menu_signal_open), (gpointer)nb_lists_lst_tab);
    g_signal_connect_swapped(G_OBJECT(mwin->menu_file_item_exit), 
        "activate", G_CALLBACK(menu_signal_quit), (gpointer)mwin->main);
    g_signal_connect_swapped(G_OBJECT(mwin->menu_edit_item_update), 
        "activate", G_CALLBACK(menu_signal_update), (gpointer)mwin->main);
    g_signal_connect_swapped(G_OBJECT(mwin->menu_edit_item_purge), 
        "activate", G_CALLBACK(menu_signal_purge), (gpointer)mwin->main);
    g_signal_connect_swapped(G_OBJECT(mwin->menu_help_item_about), 
        "activate", G_CALLBACK(menu_signal_about), (gpointer)mwin->main);

    /* add submenus to menu items */
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mwin->menu_file_item), 
        mwin->menu_file);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mwin->menu_edit_item), 
        mwin->menu_edit);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mwin->menu_help_item), 
        mwin->menu_help);

    /* add to main menubar */
    gtk_menu_shell_append(GTK_MENU_SHELL(mwin->menu), mwin->menu_file_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(mwin->menu), mwin->menu_edit_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(mwin->menu), mwin->menu_help_item);
}

