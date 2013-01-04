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


#include <stdlib.h>
#include <string.h>
#include "ui/ui.h"
#include "ui/ui_fill/ui_fill.h"
#include "ui/table/gtk_custom_table.h"


static void ui_fill_sanitize(Movie *m) {

    m->vote = m->vote >= 0.0 && m->vote <= 10.0 ? m->vote : 0.0;
    m->imdb = m->imdb >= 0.0 && m->imdb <= 10.0 ? m->imdb : 0.0;
    m->time = m->time >= 0.0 ? m->time : 0.0;
    m->year = m->year >= 1800.0 && m->year <= 2200.0 ? m->year : 0.0;
}


static int ui_fill_calckey(double imdb) {

    int imdb_k = (int)imdb;

    return ((imdb - imdb_k) * 10) > 5 ? 
             imdb_k : imdb_k > 0 ? imdb_k - 1 : 0;
}


static void ui_fill_addentry(Stats *s, Movie *m, int k) {

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


static void ui_fill_addlists(Stats *s, Movie *m, char *id) {

    int lists[3];

    lists[LST_TOP] = gtk_custom_table_get_indexof(nb_tab_top250, id) >= 0;
    lists[LST_BOT] = gtk_custom_table_get_indexof(nb_tab_bot100, id) >= 0;
    lists[LST_BOX] = gtk_custom_table_get_indexof(nb_tab_boxoffice, id) >= 0;

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


void ui_fill_stats_avg_calc(Stats *s, int rows) {

    int i = 0;
    int g = 0;

    /* find graph width */
    for(i = 0; i < 10; i++) {
        g = s->stats_cnt[i][ROWS] > g ? s->stats_cnt[i][ROWS]: g;
    }

    /* calculate averages */
    for(i = 0; i < 10; i++) {

        s->graph[i][CENT] = s->stats_cnt[i][ROWS] > 0 ? 
            (s->stats_cnt[i][ROWS] / rows) * 100: 0; 
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
}


void ui_fill_stats_all_calc(Stats *s, int row1, int row2, int row3) {

    ui_fill_stats_all_fill(s, gtk_custom_table_get_rows(nb_tab_top250), 
        LST_TOP, row1);
    ui_fill_stats_all_fill(s, gtk_custom_table_get_rows(nb_tab_bot100), 
        LST_BOT, row2);
    ui_fill_stats_all_fill(s, gtk_custom_table_get_rows(nb_tab_boxoffice), 
        LST_BOX, row3);
}


void ui_fill_stats_cmp_calc(GtkWidget *table1, GtkWidget *table2) {

    int i = 0;

    Movie *m = malloc(sizeof(Movie));
    Stats *s = malloc(sizeof(Stats));

    int total_rows = 0;
    int table_rows = gtk_custom_table_get_rows(table1);

    for(i = 0; i < table_rows; i++) {
        
        char *id = gtk_custom_table_get_cell_text(table1, 3, i);

        if(gtk_custom_table_get_indexof(table2, id) < 0) {
            continue;
        }
        
        m->vote = atof(gtk_custom_table_get_cell_text(table1, 2, i));
        m->imdb = atof(gtk_custom_table_get_cell_text(table1, 1, i));
        m->time = atof(gtk_custom_table_get_cell_text(table1, 5, i));
        m->year = atof(gtk_custom_table_get_cell_text(table1, 6, i));

        ui_fill_addentry(s, m, ui_fill_calckey(m->imdb));
        ui_fill_addlists(s, m, id);

        total_rows++;
    }
    
    ui_fill_stats_avg_calc(s, total_rows);
    ui_fill_stats_all_calc(s, 3, 7, 11);
    ui_fill_stats_cmp_fill(s, total_rows);

    free(m);
    free(s);
}


static void ui_fill_stats_calc(Stats *s, Movie *m, char **row, int key) {

    strcpy(m->id, row[1]);
    strcpy(m->title, row[5]);

    sprintf(m->vote_str, "%d", (int)m->vote);
    sprintf(m->imdb_str, "%1.1f", m->imdb);
    sprintf(m->time_str, "%d", (int)m->time);
    sprintf(m->year_str, "%d", (int)m->year);

    ui_fill_sanitize(m);
    ui_fill_addentry(s, m, key);
    ui_fill_addlists(s, m, row[1]);
}


void ui_fill_stats_mov_calc(Stats *s, Movie *m, char **row) {

    m->vote = strtol(row[8], NULL, 10);
    m->imdb = strtod(row[9], NULL);
    m->time = strtol(row[10], NULL, 10);
    m->year = strtol(row[11], NULL, 10);

    ui_fill_stats_calc(s, m, row, m->vote > 0 ? (int)m->vote - 1 : 0);
}


void ui_fill_stats_lst_calc(Stats *s, Movie *m, char **row) {

    m->vote = 0;
    m->imdb = strtod(row[8], NULL);
    m->time = strtol(row[9], NULL, 10);
    m->year = strtol(row[10], NULL, 10);
 
    ui_fill_stats_calc(s, m, row, ui_fill_calckey(m->imdb));
}
