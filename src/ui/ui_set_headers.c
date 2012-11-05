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


#include "ui.h"


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
    "MyMovies / MyLists Comparison", 
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
    "IMDb ID", 
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
    "IMDb", 
    "Vote", 
    "Flux", 
    "Completion", 
    "Percent", 
    "Movies", 
    "Runtime", 
    "Year",
};


void ui_set_headers() {

    int i = 0;

    /* set statistics headers */
    for(i = 0; i < TABLE_STATS_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_statistics, i, 
            nb_tab_statistics_headers[i]);
    }

    /* set my-movies headers */
    for(i = 0; i < TABLE_MYMOV_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_mymovies, i, 
            nb_tab_mymovies_headers[i]);
    }
    /* set lists stats headers */
    for(i = 0; i < TABLE_LSTST_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_lists_stats, i, 
            nb_tab_lists_stats_headers[i]);
    }

    /* set my-lists headers */
    for(i = 0; i < TABLE_MYLST_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_lists, i, 
            nb_tab_mylists_headers[i]);
    }

    /* set compare headers */
    for(i = 0; i < TABLE_COMPR_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_compare, i, 
            nb_tab_compare_headers[i]);
    }

    /* set top 250 headers */
    for(i = 0; i < TABLE_TP250_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_top250, i, 
            nb_tab_top250_headers[i]);
    }

    /* set bottom 100 headers */
    for(i = 0; i < TABLE_BT100_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_bot100, i, 
            nb_tab_bot100_headers[i]);
    }

    /* set boxoffice headers */
    for(i = 0; i < TABLE_BOXOF_COLS; i++) {
        gtk_custom_table_set_head_text(nb_tab_boxoffice, i, 
            nb_tab_boxoffice_headers[i]);
    }
}

