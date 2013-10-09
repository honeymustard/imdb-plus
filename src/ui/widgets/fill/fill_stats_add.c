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


#include <stdlib.h>
#include <string.h>
#include "ui/widgets/widgets.h"
#include "ui/widgets/fill/fill.h"
#include "ui/table/gtk_custom_table.h"


/**
 * sanitize the values of a movie entry
 * @param Movie *m    movie in which to sanitize
 */
static void ui_fill_add_clip(Movie *m) {

    m->vote = m->vote >= 1 && m->vote <= 10 ? m->vote: 0;
    m->imdb = m->imdb >= 0.0 && m->imdb <= 10.0 ? m->imdb: 0.0;
    m->time = m->time >= 0.0 ? m->time : 0.0;
    m->year = m->year >= 1800.0 && m->year <= 2200.0 ? m->year : 0.0;
}


/**
 * add a movie entry to a stats object at key
 * @param Stats *s    current stats object
 * @param Movie *m    movie entry object to be added
 * @param int k       the key indice to use..
 */
static void ui_fill_add_stat(Stats *s, Movie *m, int k) {

    if(k < 0) return;

    /* add up averages */
    s->stats_amt[k][VOTE] += m->vote;
    s->stats_amt[k][IMDB] += m->imdb;
    s->stats_amt[k][TIME] += m->time;
    s->stats_amt[k][YEAR] += m->year;
    s->stats_amt[k][FLUX] += (m->vote - m->imdb);

    /* add up non-null counts */
    s->stats_cnt[k][VOTE] += m->vote > 0 ? 1 : 0;
    s->stats_cnt[k][IMDB] += m->imdb > 0 ? 1 : 0;
    s->stats_cnt[k][TIME] += m->time > 0 ? 1 : 0;
    s->stats_cnt[k][YEAR] += m->year > 0 ? 1 : 0;
    s->stats_cnt[k][FLUX] += m->vote > 0 && m->imdb > 0 ? 1 : 0;
    s->stats_cnt[k][ROWS] += 1;

    /* add up totals */
    s->total_amt[VOTE] += m->vote;
    s->total_amt[IMDB] += m->imdb;
    s->total_amt[TIME] += m->time;
    s->total_amt[YEAR] += m->year;
    s->total_amt[FLUX] += (m->vote - m->imdb);

    /* add up non-null counts */
    s->total_cnt[VOTE] += m->vote > 0 ? 1 : 0;
    s->total_cnt[IMDB] += m->imdb > 0 ? 1 : 0;
    s->total_cnt[TIME] += m->time > 0 ? 1 : 0;
    s->total_cnt[YEAR] += m->year > 0 ? 1 : 0;
    s->total_cnt[FLUX] += m->vote > 0 && m->imdb > 0 ? 1 : 0;
    s->total_cnt[ROWS] += 1;
}


/**
 * add a movie entry to a stats object if present in top-lists
 * @param Stats *s    current stats object
 * @param Movie *m    movie entry object to be added
 */
static void ui_fill_add_list(Stats *s, Movie *m) {

    int lists[3];

    lists[0] = gtk_custom_table_get_indexof(nb_lists_top_tab->table, 
        m->id_str) >= 0;
    lists[1] = gtk_custom_table_get_indexof(nb_lists_bot_tab->table, 
        m->id_str) >= 0;
    lists[2] = gtk_custom_table_get_indexof(nb_lists_box_tab->table, 
        m->id_str) >= 0;

    int i = 0;

    for(i = 0; i < 3; i++) {

        if(lists[i] == 0) continue;
    
        s->lists_amt[i][VOTE] += m->vote;
        s->lists_amt[i][IMDB] += m->imdb;
        s->lists_amt[i][TIME] += m->time;
        s->lists_amt[i][YEAR] += m->year;
        s->lists_amt[i][FLUX] += (m->vote - m->imdb);

        s->lists_cnt[i][VOTE] += m->vote > 0 ? 1 : 0;
        s->lists_cnt[i][IMDB] += m->imdb > 0 ? 1 : 0;
        s->lists_cnt[i][TIME] += m->time > 0 ? 1 : 0;
        s->lists_cnt[i][YEAR] += m->year > 0 ? 1 : 0;
        s->lists_cnt[i][FLUX] += m->vote > 0 && m->imdb > 0 ? 1 : 0;
        s->lists_cnt[i][ROWS] += 1;
    }
}


/**
 * copy movie values into string equivalents
 * @param Movie *m    current movie object
 */
void ui_fill_add_copy(Movie *m) {

    sprintf(m->vote_str, "%d", (int)m->vote);
    sprintf(m->imdb_str, "%1.1f", m->imdb);
    sprintf(m->time_str, "%d", (int)m->time);
    sprintf(m->year_str, "%d", (int)m->year);
}

/**
 * fill a stats object with movie values using vote as a key
 * @param Stats *s    current stats object
 * @param Movie *m    current movie object
 */
void ui_fill_add_vote(Stats *s, Movie *m) {

    ui_fill_add_clip(m);
    ui_fill_add_copy(m);
    ui_fill_add_stat(s, m, m->vote - 1);
    ui_fill_add_list(s, m);
}

/**
 * fill a stats object with movie values using imdb as a key
 * @param Stats *s    current stats object
 * @param Movie *m    current movie object
 */
void ui_fill_add_imdb(Stats *s, Movie *m) {

    ui_fill_add_clip(m);
    ui_fill_add_copy(m);
    ui_fill_add_stat(s, m, m->imdb == 10.0 ? 9 : (int)m->imdb - 1);
    ui_fill_add_list(s, m);
}

