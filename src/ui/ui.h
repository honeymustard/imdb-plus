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
#include "ui_widgets.h"
#include "ui_fill/ui_fill.h"
#include "events/events.h"
#include "table/gtk_custom_table.h"
#include "../../main.h"
#include "../globals.h"
#include "../readfile.h"
#include "../openfile.h"
#include "../download.h"
#include "../parsefile.h"
#include "../colors.h"
#include "../patterns.h"

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

#endif

