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


#ifndef _UI_
#define _UI_

#define TEXT_FONT "sans 10"

#define ROSETTE       DIR_ICON "rosette_red.png"
#define AWARD_GOLD    DIR_ICON "award_gold.png"
#define AWARD_SILVER  DIR_ICON "award_silver.png"
#define AWARD_BRONZE  DIR_ICON "award_bronze.png"
#define RIBBON_GOLD   DIR_ICON "rosette_gold.png"
#define RIBBON_SILVER DIR_ICON "rosette_silver.png"
#define RIBBON_BRONZE DIR_ICON "rosette_bronze.png"

#include <gtk/gtk.h>

/* widget hierarchy */
GtkWidget *window, *stat, *vbox, *hbox;

/* tabs hierarchy */
GtkWidget *nb, 

    *nb_stats_mov_vbox, 
        *nb_stats_mov_scroll, 
            *nb_stats_mov_view, 
                *nb_stats_mov_tab, 
    *nb_stats_lst_vbox, 
        *nb_stats_lst_scroll, 
            *nb_stats_lst_view, 
                *nb_stats_lst_tab, 
    *nb_stats_cmp_vbox, 
        *nb_stats_cmp_scroll, 
            *nb_stats_cmp_view, 
                *nb_stats_cmp_tab, 
    *nb_stats_all_vbox, 
        *nb_stats_all_scroll, 
            *nb_stats_all_view, 
                *nb_stats_all_tab, 
    *nb_lists_mov_vbox, 
        *nb_lists_mov_scroll, 
            *nb_lists_mov_view, 
                *nb_lists_mov_tab,
    *nb_lists_lst_vbox, 
        *nb_lists_lst_scroll, 
            *nb_lists_lst_view, 
                *nb_lists_lst_tab, 
    *nb_lists_cmp_vbox, 
        *nb_lists_cmp_scroll, 
            *nb_lists_cmp_view, 
                *nb_lists_cmp_tab, 
    *nb_lists_top_vbox, 
        *nb_lists_top_scroll, 
            *nb_lists_top_view, 
                *nb_lists_top_tab, 
    *nb_lists_bot_vbox, 
        *nb_lists_bot_scroll, 
            *nb_lists_bot_view, 
                *nb_lists_bot_tab, 
    *nb_lists_box_vbox, 
        *nb_lists_box_scroll, 
            *nb_lists_box_view, 
                *nb_lists_box_tab;


/* menubar hierarchy */
GtkWidget *menubar, 
    *menu_file, 
        *menu_file_item, 
            *menu_file_item_open,
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

