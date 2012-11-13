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


#include "../ui.h"


void fill_sanitize(double *v, double *i, double *t, double *y) {

    *v = *v >= 0.0 && *v <= 10.0 ? 
        *v : 0.0;
    *i = *i >= 0.0 && *i <= 10.0 ? 
        *i : 0.0;
    *t = *t >= 0.0 ? 
        *t : 0.0;
    *y = *y >= 1800.0 && *y <= 2200.0 ? 
        *y : 0.0;
}


void ui_fill_stats(char ****results, int rows, double stats[][STATS_X], 
    double total[][TOTAL_X], int type) {

    int i = 0;

    double vote = 0;
    double imdb = 0;
    double time = 0;
    double year = 0;

    int imdb_k = 0;

    for(i = 1; i < rows; i++) {

        /* make results numeric */
        if(type == STATS_M) {

            vote = strtol((*results)[i][8], NULL, 10);
            imdb = strtod((*results)[i][9], NULL);
            time = strtol((*results)[i][10], NULL, 10);
            year = strtol((*results)[i][11], NULL, 10);

            imdb_k = (int)vote - 1;
        }
        else {

            imdb = strtod((*results)[i][8], NULL);
            time = strtol((*results)[i][9], NULL, 10);
            year = strtol((*results)[i][10], NULL, 10);

            imdb_k = ((imdb - (int)imdb) * 10) > 5 ? 
                (int)imdb : (int)imdb - 1;
        }

        fill_sanitize(&vote, &imdb, &time, &year);

        /* add up for each rating */
        stats[imdb_k][VOTES] += 1;
        stats[imdb_k][IMDB_AVG] += imdb;
        stats[imdb_k][TIME_AVG] += time;
        stats[imdb_k][YEAR_AVG] += year;
        stats[imdb_k][FLUX_AVG] += (vote - imdb);

        /* add up totals */
        total[VOTE_TOT][0] += vote;
        total[IMDB_TOT][0] += imdb;
        total[TIME_TOT][0] += time;
        total[YEAR_TOT][0] += year;
        total[FLUX_TOT][0] += (vote - imdb);

        total[VOTE_TOT][1] += vote > 0.0 ? 1 : 0;
        total[IMDB_TOT][1] += imdb > 0.0 ? 1 : 0;
        total[TIME_TOT][1] += time > 0.0 ? 1 : 0;
        total[YEAR_TOT][1] += year > 0.0 ? 1 : 0;
        total[FLUX_TOT][1] += vote > 0.0 ? 1 : 0;
    }

    int graph = 0;

    /* find graph width */
    for(i = 0; i < 10; i++) {

        graph = stats[i][VOTES] > graph ? 
            stats[i][VOTES]: graph;
    }

    for(i = 0; i < 10; i++) {

        /* calculate percentage */
        stats[i][PERCENTAGE] = stats[i][VOTES] != 0.0 ? 
            (stats[i][VOTES] / rows) * 100: 0; 
        /* calculate graph width */
        stats[i][GRAPH_WIDTH] = stats[i][VOTES] != 0.0 ? 
            100 / (graph / stats[i][VOTES]) : 0;
        /* calculate imdb average */
        stats[i][IMDB_AVG] = stats[i][VOTES] != 0.0 ? 
            stats[i][IMDB_AVG] / stats[i][VOTES] : 0;
        /* calculate flux average */
        stats[i][FLUX_AVG] = stats[i][VOTES] != 0.0 ? 
            stats[i][FLUX_AVG] / stats[i][VOTES] : 0;
        /* calculate time average */
        stats[i][TIME_AVG] = stats[i][VOTES] != 0.0 ? 
            stats[i][TIME_AVG] / stats[i][VOTES] : 0;
        /* calculate year average */
        stats[i][YEAR_AVG] = stats[i][VOTES] != 0.0 ? 
            stats[i][YEAR_AVG] / stats[i][VOTES] : 0;
    }
}

