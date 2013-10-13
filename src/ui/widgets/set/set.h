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


#ifndef _SET_
#define _SET_

void ui_set_init();
void ui_set_head();
void ui_set_meta();
void ui_set_tabs();
void ui_set_menu();
void ui_set_free();

#define COLS_STATS_MOV 8
#define COLS_STATS_LST 8
#define COLS_STATS_CMP 8
#define COLS_STATS_ALL 9
#define COLS_LISTS_MOV 8
#define COLS_LISTS_LST 8
#define COLS_LISTS_CMP 8
#define COLS_LISTS_TOP 8
#define COLS_LISTS_BOT 8
#define COLS_LISTS_BOX 8

#define NAME_STATS_MOV "Stats"
#define NAME_STATS_LST "Stats"
#define NAME_STATS_CMP "Stats"
#define NAME_STATS_ALL "Stats All"
#define NAME_LISTS_MOV "My Movies"
#define NAME_LISTS_LST "My Movies"
#define NAME_LISTS_CMP "Intersect"
#define NAME_LISTS_TOP "Top 250"
#define NAME_LISTS_BOT "Bottom 100"
#define NAME_LISTS_BOX "Boxoffice"

char *nb_stats_mov_headers[COLS_STATS_MOV];
char *nb_stats_lst_headers[COLS_STATS_LST];
char *nb_stats_cmp_headers[COLS_STATS_CMP];
char *nb_stats_all_headers[COLS_STATS_ALL];
char *nb_lists_mov_headers[COLS_LISTS_MOV];
char *nb_lists_lst_headers[COLS_LISTS_LST];
char *nb_lists_cmp_headers[COLS_LISTS_CMP];
char *nb_lists_top_headers[COLS_LISTS_TOP];
char *nb_lists_bot_headers[COLS_LISTS_BOT];
char *nb_lists_box_headers[COLS_LISTS_BOX];

#endif

