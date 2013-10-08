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


#ifndef _WIDGETS_
#define _WIDGETS_

#define TEXT_FONT "sans 10"

#define ROSETTE       DIR_ICON "rosette_red.png"
#define AWARD_GOLD    DIR_ICON "award_gold.png"
#define AWARD_SILVER  DIR_ICON "award_silver.png"
#define AWARD_BRONZE  DIR_ICON "award_bronze.png"
#define RIBBON_GOLD   DIR_ICON "rosette_gold.png"
#define RIBBON_SILVER DIR_ICON "rosette_silver.png"
#define RIBBON_BRONZE DIR_ICON "rosette_bronze.png"


#include <gtk/gtk.h>


GtkWidget *mwin, *stat, *vbox, *hbox, *note;

typedef struct NotebookTab {

    char *filename;
    GtkWidget *vbox; 
    GtkWidget *scroll; 
    GtkWidget *view; 
    GtkWidget *table; 

} NotebookTab;

#define NB_TABS 10

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

NotebookTab *tabs[NB_TABS];


GtkWidget *menu, 
  *menu_file, 
    *menu_file_item, 
      *menu_file_item_open,
      *menu_file_item_compare,
      *menu_file_item_new,
      *menu_file_item_space,
      *menu_file_item_exit,
  *menu_edit, 
    *menu_edit_item, 
      *menu_edit_item_update, 
  *menu_help,
    *menu_help_item, 
      *menu_help_item_about;

#endif

