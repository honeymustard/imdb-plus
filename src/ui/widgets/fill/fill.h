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


#ifndef _FILL_
#define _FILL_


#include "io/readfile.h"


#define TOP_COLS 6
#define TOP_ROWS 250
#define BOT_COLS 6
#define BOT_ROWS 100
#define BOX_COLS 6


typedef struct movie {

    char id_str[50];
    char name_str[200];
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


typedef struct state {
    
    int tab1_vcol;
    int tab2_vcol;
    Stats *stats;
    NotebookTab *tab1;
    NotebookTab *tab2;
    NotebookTab *tab3;
    NotebookTab *stat;

} State;

/* fill tabs with new data */
int  ui_fill_lists_box_update();
int  ui_fill_lists_bot_update();
int  ui_fill_lists_top_update();
void ui_fill_lists_lst(State *state, ResultList *list);
void ui_fill_lists_mov(State *state, ResultList *list);
void ui_fill_lists_cmp(State *state);
void ui_fill_lists_top(ResultList *list);
void ui_fill_lists_bot(ResultList *list);
void ui_fill_lists_box(ResultList *list);
void ui_fill_stats_mov(State *state);
void ui_fill_stats_lst(State *state);
void ui_fill_stats_cmp(State *state);
void ui_fill_stats_avg(Stats *stats);
void ui_fill_stats_all(State *state, int rows[]);

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

/* fill tabs with data from other tabs */
void ui_fill_lists_lst_add(State *state);
void ui_fill_lists_mov_add(State *state);
void ui_fill_lists_cmp_add(State *state);
void ui_fill_lists_box_add(ResultList *list);

/* fill stats object with data */
void ui_fill_stats_mov_add(Stats *stats, Movie *m);
void ui_fill_stats_lst_add(Stats *stats, Movie *m);

enum GRAPH { CENT, SIZE };
enum STATS { VOTE, IMDB, TIME, YEAR, FLUX, ROWS };

#endif

