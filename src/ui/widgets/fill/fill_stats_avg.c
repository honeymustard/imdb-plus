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


#include "ui/widgets/widgets.h"
#include "ui/widgets/fill/fill.h"


/**
 * calculate all valid averages for a stats object
 * @param Stats *s    current stats object
 * @param int rows    number of rows in table
 */
void ui_fill_stats_avg(Stats *s) {

    int i = 0;
    int g = 0;

    /* find graph width */
    for(i = 0; i < 10; i++) {
        g = s->stats_cnt[i][ROWS] > g ? s->stats_cnt[i][ROWS]: g;
    }

    /* calculate averages */
    for(i = 0; i < 10; i++) {

        s->graph[i][CENT] = s->stats_cnt[i][ROWS] > 0 ? 
            (s->stats_cnt[i][ROWS] / s->total_cnt[ROWS]) * 100: 0; 
        s->graph[i][SIZE] = s->stats_cnt[i][ROWS] > 0 ? 
            100 / (g / s->stats_cnt[i][ROWS]) : 0;

        s->stats[i][VOTE] = s->stats_cnt[i][VOTE] > 0 ? 
            s->stats_amt[i][VOTE] / s->stats_cnt[i][VOTE] : 0;
        s->stats[i][IMDB] = s->stats_cnt[i][IMDB] > 0 ? 
            s->stats_amt[i][IMDB] / s->stats_cnt[i][IMDB] : 0;
        s->stats[i][TIME] = s->stats_cnt[i][TIME] > 0 ? 
            s->stats_amt[i][TIME] / s->stats_cnt[i][TIME] : 0;
        s->stats[i][YEAR] = s->stats_cnt[i][YEAR] > 0 ? 
            s->stats_amt[i][YEAR] / s->stats_cnt[i][YEAR] : 0;
        s->stats[i][FLUX] = s->stats_cnt[i][FLUX] > 0 ? 
            s->stats_amt[i][FLUX] / s->stats_cnt[i][FLUX] : 0;
    }

    for(i = 0; i < 3; i++) {

        s->lists[i][VOTE] = s->lists_cnt[i][VOTE] > 0 ? 
            s->lists_amt[i][VOTE] / s->lists_cnt[i][VOTE] : 0;
        s->lists[i][IMDB] = s->lists_cnt[i][IMDB] > 0 ? 
            s->lists_amt[i][IMDB] / s->lists_cnt[i][IMDB] : 0;
        s->lists[i][TIME] = s->lists_cnt[i][TIME] > 0 ? 
            s->lists_amt[i][TIME] / s->lists_cnt[i][TIME] : 0;
        s->lists[i][YEAR] = s->lists_cnt[i][YEAR] > 0 ? 
            s->lists_amt[i][YEAR] / s->lists_cnt[i][YEAR] : 0;
        s->lists[i][FLUX] = s->lists_cnt[i][FLUX] > 0 ? 
            s->lists_amt[i][FLUX] / s->lists_cnt[i][FLUX] : 0;
    }

    s->total[VOTE] = s->total_cnt[VOTE] > 0 ? 
        s->total_amt[VOTE] / s->total_cnt[VOTE] : 0;
    s->total[IMDB] = s->total_cnt[IMDB] > 0 ? 
        s->total_amt[IMDB] / s->total_cnt[IMDB] : 0;
    s->total[TIME] = s->total_cnt[TIME] > 0 ? 
        s->total_amt[TIME] / s->total_cnt[TIME] : 0;
    s->total[YEAR] = s->total_cnt[YEAR] > 0 ? 
        s->total_amt[YEAR] / s->total_cnt[YEAR] : 0;
    s->total[FLUX] = s->total_cnt[FLUX] > 0 ? 
        s->total_amt[FLUX] / s->total_cnt[FLUX] : 0;
    s->total[ROWS] = s->total_cnt[ROWS];
}

