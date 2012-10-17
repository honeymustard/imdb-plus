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


#ifndef _TABLES_
#define _TABLES_

#define TABLE_STATS_COLS 8
#define TABLE_MYMOV_COLS 7
#define TABLE_LSTST_COLS 8
#define TABLE_MYLST_COLS 7
#define TABLE_COMPR_COLS 8
#define TABLE_TP250_COLS 7
#define TABLE_BT100_COLS 7
#define TABLE_BOXOF_COLS 7
#define TABLE_ALLST_COLS 8


/* table column width descriptions */
int nb_tab_statistics_cols[TABLE_STATS_COLS] = {
    60, 60, 60, -1, 85, 85, 85, 85
};

int nb_tab_mymovies_cols[TABLE_MYMOV_COLS] = {
    55, 55, 55, 100, -1, 80, 55
};

int nb_tab_lists_stats_cols[TABLE_LSTST_COLS] = {
    60, 60, 60, -1, 85, 85, 85, 85
};

int nb_tab_mylists_cols[TABLE_MYLST_COLS] = {
    55, 55, 55, 100, -1, 80, 55
};

int nb_tab_compare_cols[TABLE_COMPR_COLS] = {
    60, 60, 60, -1, 85, 85, 85, 85
};

int nb_tab_top250_cols[TABLE_TP250_COLS] = {
    55, 55, 55, 100, -1, 55, 80 
};

int nb_tab_bot100_cols[TABLE_BT100_COLS] = {
    55, 55, 55, 100, -1, 55, 80
};

int nb_tab_boxoffice_cols[TABLE_BOXOF_COLS] = {
    55, 55, 55, 100, -1, 55, 140, 
};

int nb_tab_allstats_cols[TABLE_ALLST_COLS] = {
    60, 60, 60, -1, 85, 85, 85, 85
};


/* table headers */
char *nb_tab_statistics_headers[TABLE_STATS_COLS] = {
    "Vote", 
    "IMDb", 
    "Flux", 
    "Your Ratings", 
    "Percent", 
    "Movies", 
    "Runtime", 
    "Year", 
};

char *nb_tab_mymovies_headers[TABLE_MYMOV_COLS] = {
    "#", 
    "IMDb", 
    "Vote", 
    "IMDb ID", 
    "Title", 
    "Runtime", 
    "Year", 
};

char *nb_tab_lists_stats_headers[TABLE_LSTST_COLS] = {
    "IMDb", 
    "N/A", 
    "N/A", 
    "IMDb Ratings", 
    "Percent", 
    "Movies", 
    "Runtime", 
    "Year", 
};

char *nb_tab_mylists_headers[TABLE_MYLST_COLS] = {
    "#", 
    "IMDb", 
    "Vote", 
    "IMDb ID", 
    "Title", 
    "Runtime", 
    "Year", 
};

char *nb_tab_compare_headers[TABLE_COMPR_COLS] = {
    "IMDb", 
    "Vote", 
    "Flux", 
    "Intersected Ratings", 
    "Percent", 
    "Movies", 
    "Runtime", 
    "Year", 
};

char *nb_tab_top250_headers[TABLE_TP250_COLS] = {
    "#", 
    "IMDb", 
    "Vote", 
    "IMDb ID", 
    "Title", 
    "Year", 
    "Votes", 
};

char *nb_tab_bot100_headers[TABLE_BT100_COLS] = {
    "#", 
    "IMDb", 
    "Vote", 
    "Unique ID", 
    "Title", 
    "Year", 
    "Votes", 
};

char *nb_tab_boxoffice_headers[TABLE_BOXOF_COLS] = {
    "#", 
    "IMDb", 
    "Vote", 
    "IMDb ID", 
    "Title", 
    "Year", 
    "Gross", 
};

char *nb_tab_allstats_headers[TABLE_ALLST_COLS] = {
    "Vote", 
    "IMDb", 
    "Flux", 
    "Completion", 
    "Percent", 
    "Movies", 
    "Runtime", 
    "Year",
};

#endif

