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


#ifndef _WIDGETS_
#define _WIDGETS_


#include <gtk/gtk.h>


typedef struct MainWindow {
    
    GtkWidget *main; 
    GtkWidget *stat; 
    GtkWidget *vbox; 
    GtkWidget *hbox; 
    GtkWidget *note;

    /* menu hierarchy */
    GtkWidget *menu, 
      *menu_file, 
        *menu_file_item, 
          *menu_file_item_open,
          *menu_file_item_compare,
          *menu_file_item_space,
          *menu_file_item_exit,
      *menu_edit, 
        *menu_edit_item, 
          *menu_edit_item_update, 
          *menu_edit_item_purge, 
      *menu_help,
        *menu_help_item, 
          *menu_help_item_about;

} MainWindow;

MainWindow *mwin;

typedef enum { TAB_TYPE_NONE, TAB_TYPE_MOV, TAB_TYPE_LST } ListType;

typedef struct NotebookTab {

    int is_open;
    int has_changed;
    ListType type;
    GtkWidget *vbox; 
    GtkWidget *scroll; 
    GtkWidget *view; 
    GtkWidget *table; 

} NotebookTab;


/* all notebook tabs */
NotebookTab *nb_stats_mov_tab;
NotebookTab *nb_stats_lst_tab;
NotebookTab *nb_stats_cmp_tab;
NotebookTab *nb_stats_all_tab;
NotebookTab *nb_lists_mov_tab;
NotebookTab *nb_lists_lst_tab;
NotebookTab *nb_lists_cmp_tab;
NotebookTab *nb_lists_top_tab;
NotebookTab *nb_lists_bot_tab;
NotebookTab *nb_lists_box_tab;

#endif

