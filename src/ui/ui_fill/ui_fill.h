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

int menu_signal_update_box();
int menu_signal_update_bot();
int menu_signal_update_top();

void open_allstats(double allstats[5], int row, int rows);
void open_compare(GtkWidget *current, GtkWidget *other);
void open_list(char ****results, int rows);
void open_movies(char ****results, int rows);
void open_movie_stats(char ****results, int rows);
void open_list_stats(char ****results, int rows);

#define STATS_M 1
#define STATS_L 0
#define STATS_Y 10
#define STATS_X 8
#define TOTAL_Y 5
#define TOTAL_X 2

void fill_sanitize(double *v, double *i, double *t, double *y);
void ui_fill_stats(char ****results, int rows, double stats[][STATS_X], 
    double total[][TOTAL_X], int type);

enum STATS {

    VOTES, 
    PERCENTAGE, 
    GRAPH_WIDTH, 
    VOTE_AVG, 
    IMDB_AVG, 
    FLUX_AVG, 
    TIME_AVG, 
    YEAR_AVG
};

enum TOTAL {

    VOTE_TOT, 
    IMDB_TOT, 
    TIME_TOT, 
    YEAR_TOT, 
    FLUX_TOT
};

#endif

