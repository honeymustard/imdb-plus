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


#ifndef _UI_FILL_
#define _UI_FILL_


#include "ui/table/gtk_custom_table.h"


typedef struct movie_row {

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


void ui_fill_lists_lst(char ****results, int rows);
void ui_fill_lists_mov(char ****results, int rows);
void ui_fill_lists_cmp(GtkWidget *table1, GtkWidget *table2);

int  ui_fill_lists_box();
int  ui_fill_lists_bot();
int  ui_fill_lists_top();

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

void ui_fill_stats_mov_fill(Stats *s, int rows);
void ui_fill_stats_lst_fill(Stats *s, int rows);
void ui_fill_stats_cmp_fill(Stats *s, int rows);
void ui_fill_stats_all_fill(Stats *s, int row1, int row2, int row3);

void ui_fill_stats_avg_calc(Stats *s, int rows);
void ui_fill_stats_mov_calc(Stats *s, Movie *m, char **row);
void ui_fill_stats_lst_calc(Stats *s, Movie *m, char **row);
void ui_fill_stats_cmp_calc(Stats *s, Movie *m, int row, 
    GtkWidget *table, char *id);

enum GRAPH { CENT, SIZE };
enum STATS { VOTE, IMDB, TIME, YEAR, FLUX, ROWS };

#endif

