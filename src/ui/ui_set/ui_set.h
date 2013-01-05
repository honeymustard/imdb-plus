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


#ifndef _UI_SET_
#define _UI_SET_

void ui_set_init();
void ui_set_headers();
void ui_set_meta();
void ui_set_tabs();
void ui_set_menu();
void ui_set_destroy();

#define TABLE_STATS_COLS 8
#define TABLE_MYMOV_COLS 7
#define TABLE_LSTST_COLS 8
#define TABLE_MYLST_COLS 7
#define TABLE_COMPR_COLS 8
#define TABLE_MYCMP_COLS 7
#define TABLE_TP250_COLS 7
#define TABLE_BT100_COLS 7
#define TABLE_BOXOF_COLS 7
#define TABLE_ALLST_COLS 9

char *nb_tab_statistics_headers[TABLE_STATS_COLS];
char *nb_tab_mymovies_headers[TABLE_MYMOV_COLS];
char *nb_tab_lists_stats_headers[TABLE_LSTST_COLS];
char *nb_tab_mylists_headers[TABLE_MYLST_COLS];
char *nb_tab_compare_headers[TABLE_COMPR_COLS];
char *nb_tab_lists_cmp_headers[TABLE_MYCMP_COLS];
char *nb_tab_top250_headers[TABLE_TP250_COLS];
char *nb_tab_bot100_headers[TABLE_BT100_COLS];
char *nb_tab_boxoffice_headers[TABLE_BOXOF_COLS];
char *nb_tab_allstats_headers[TABLE_ALLST_COLS];

#endif

