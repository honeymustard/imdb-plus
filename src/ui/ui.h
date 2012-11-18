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

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <stdlib.h>
#include <string.h>
#include "events/events.h"
#include "table/gtk_custom_table.h"

#define TEXT_FONT "sans 10"

#define TABLE_STATS_COLS 8
#define TABLE_MYMOV_COLS 7
#define TABLE_LSTST_COLS 8
#define TABLE_MYLST_COLS 7
#define TABLE_COMPR_COLS 8
#define TABLE_TP250_COLS 7
#define TABLE_BT100_COLS 7
#define TABLE_BOXOF_COLS 7
#define TABLE_ALLST_COLS 9

#define ROSETTE       DIR_ICON "rosette_red.png"

#define AWARD_GOLD    DIR_ICON "award_gold.png"
#define AWARD_SILVER  DIR_ICON "award_silver.png"
#define AWARD_BRONZE  DIR_ICON "award_bronze.png"
#define RIBBON_GOLD   DIR_ICON "rosette_gold.png"
#define RIBBON_SILVER DIR_ICON "rosette_silver.png"
#define RIBBON_BRONZE DIR_ICON "rosette_bronze.png"

void ui_set_init();
void ui_set_headers();
void ui_set_meta();
void ui_set_tables();
void ui_set_tabs();
void ui_set_menu();
void ui_set_destroy();

int nb_tab_statistics_cols[TABLE_STATS_COLS];
int nb_tab_mymovies_cols[TABLE_MYMOV_COLS];
int nb_tab_lists_stats_cols[TABLE_LSTST_COLS];
int nb_tab_mylists_cols[TABLE_MYLST_COLS];
int nb_tab_compare_cols[TABLE_COMPR_COLS];
int nb_tab_top250_cols[TABLE_TP250_COLS];
int nb_tab_bot100_cols[TABLE_BT100_COLS];
int nb_tab_boxoffice_cols[TABLE_BOXOF_COLS];
int nb_tab_allstats_cols[TABLE_ALLST_COLS];

char *nb_tab_statistics_headers[TABLE_STATS_COLS];
char *nb_tab_mymovies_headers[TABLE_MYMOV_COLS];
char *nb_tab_lists_stats_headers[TABLE_LSTST_COLS];
char *nb_tab_mylists_headers[TABLE_MYLST_COLS];
char *nb_tab_top250_headers[TABLE_TP250_COLS];
char *nb_tab_bot100_headers[TABLE_BT100_COLS];
char *nb_tab_boxoffice_headers[TABLE_BOXOF_COLS];
char *nb_tab_allstats_headers[TABLE_ALLST_COLS];

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

