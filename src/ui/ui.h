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
GtkWidget *window, *status, *vbox, *hbox;

/* tabs hierarchy */
GtkWidget *nb, 
    *nb_tab_statistics_vbox, 
        *nb_statistics_scroll, 
            *nb_statistics_view, 
                *nb_tab_statistics, 
    *nb_tab_mymovies_vbox, 
        *nb_mymovies_scroll, 
            *nb_mymovies_view, 
                *nb_tab_mymovies,
    *nb_tab_lists_stats_vbox, 
        *nb_lists_stats_scroll, 
            *nb_lists_stats_view, 
                *nb_tab_lists_stats, 
    *nb_tab_lists_vbox, 
        *nb_lists_scroll, 
            *nb_lists_view, 
                *nb_tab_lists, 
    *nb_tab_compare_vbox, 
        *nb_compare_scroll, 
            *nb_compare_view, 
                *nb_tab_compare, 
    *nb_tab_lists_cmp_vbox, 
        *nb_lists_cmp_scroll, 
            *nb_lists_cmp_view, 
                *nb_tab_lists_cmp, 
    *nb_tab_top250_vbox, 
        *nb_top250_scroll, 
            *nb_top250_view, 
                *nb_tab_top250, 
    *nb_tab_bot100_vbox, 
        *nb_bot100_scroll, 
            *nb_bot100_view, 
                *nb_tab_bot100, 
    *nb_tab_boxoffice_vbox, 
        *nb_boxoffice_scroll, 
            *nb_boxoffice_view, 
                *nb_tab_boxoffice, 
    *nb_tab_allstats_vbox, 
        *nb_allstats_scroll, 
            *nb_allstats_view, 
                *nb_tab_allstats;

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

