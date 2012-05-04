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
#define TABLE_MYMOV_COLS 6
#define TABLE_MYLST_COLS 6
#define TABLE_TP250_COLS 7
#define TABLE_BT100_COLS 7
#define TABLE_BOXOF_COLS 7


/* table column width descriptions */
int nb_tab_statistics_cols[TABLE_STATS_COLS] = {
    45, 55, 55, -1, 75, 75, 75, 75
};

int nb_tab_top250_cols[TABLE_TP250_COLS] = {
    45, 90, 90, 90, -1, 55, 65
};

int nb_tab_bot100_cols[TABLE_BT100_COLS] = {
    45, 90, 90, 90, -1, 55, 65
};

int nb_tab_boxoffice_cols[TABLE_BOXOF_COLS] = {
    45, 90, 90, 90, -1, 55, 120, 
};

int nb_tab_mymovies_cols[TABLE_MYMOV_COLS] = {
    45, 90, 90, 90, -1, 55, 
};


/* table headers */
char *nb_tab_statistics_headers[TABLE_STATS_COLS] = {
    "Vote", 
    "IMDb", 
    "Flux", 
    "Your Rating", 
    "Percent", 
    "Votes", 
    "Runtime", 
    "Year Avg", 
};

char *nb_tab_top250_headers[TABLE_TP250_COLS] = {
    "#", 
    "IMDb Rating", 
    "Your Rating", 
    "Unique ID", 
    "Title", 
    "Year", 
    "Votes", 
};

char *nb_tab_boxoffice_headers[TABLE_BOXOF_COLS] = {
    "#", 
    "IMDb Rating", 
    "Your Rating", 
    "Unique ID", 
    "Title", 
    "Year", 
    "Gross", 
};

char *nb_tab_mymovies_headers[TABLE_MYMOV_COLS] = {
    "#", 
    "IMDb Rating", 
    "Your Rating", 
    "Unique ID", 
    "Title", 
    "Year", 
};

#endif


