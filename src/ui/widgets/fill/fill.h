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


#ifndef _FILL_
#define _FILL_


#include "io/readfile.h"

#define TYPE_MOV 0
#define TYPE_LST 1

typedef struct movie {

    char id[50];
    char title[200];
    char vote_str[10];
    char imdb_str[10];
    char time_str[10];
    char year_str[10];

    double vote;
    double imdb;
    double time;
    double year;

} Movie;


typedef struct stats {

    double graph[10][2];
    double stats[10][6];
    double total[6];
    double lists[3][6];

    double stats_amt[10][5];
    double stats_cnt[10][6];
    double total_amt[5];
    double total_cnt[6];
    double lists_amt[3][5];
    double lists_cnt[3][6];

} Stats;


/* fill tabs with new data */
int  ui_fill_lists_box_update();
int  ui_fill_lists_bot_update();
int  ui_fill_lists_top_update();

//void ui_fill_lists_lst(ResultList *list, NotebookTab *tab, Stats *s);
void ui_fill_lists_mov(ResultList *list, NotebookTab *tab, 
    NotebookTab *tab_stats, int type);
void ui_fill_lists_top(ResultList *list, NotebookTab *tab);
void ui_fill_lists_bot(ResultList *list, NotebookTab *tab);
void ui_fill_lists_box(ResultList *list, NotebookTab *tab);
void ui_fill_lists_cmp(NotebookTab *tab1, NotebookTab *tab2);
void ui_fill_stats_mov(Stats *s, NotebookTab *tab);
//void ui_fill_stats_lst(Stats *s, NotebookTab *tab);
void ui_fill_stats_cmp(Stats *s);
void ui_fill_stats_all(Stats *s, int row1, int row2, int row3);

/* fill tabs with default data */
void ui_fill_lists_lst_empty();
void ui_fill_lists_mov_empty();
void ui_fill_lists_cmp_empty();
void ui_fill_lists_top_empty();
void ui_fill_lists_bot_empty();
void ui_fill_lists_box_empty();
void ui_fill_stats_lst_empty();
void ui_fill_stats_mov_empty();
void ui_fill_stats_cmp_empty();
void ui_fill_stats_all_empty();

/* fill stats object with data */
void ui_fill_stats_avg(Stats *s);
void ui_fill_stats_mov_calc(Stats *s, Movie *m, char **row);
void ui_fill_stats_lst_calc(Stats *s, Movie *m, char **row);
void ui_fill_stats_cmp_calc(Stats *s, Movie *m, int row, 
    NotebookTab *tab, char *id);

enum GRAPH { CENT, SIZE };
enum STATS { VOTE, IMDB, TIME, YEAR, FLUX, ROWS };

#endif

