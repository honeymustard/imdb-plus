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
#include "ui_fill.h"
#include "../../colors.h"


void open_compare(GtkWidget *current, GtkWidget *other) {

    double stats[STATS_Y][STATS_X];
    double total[TOTAL_Y][TOTAL_X];
    double allstats[3][5];

    memset(stats, 0, sizeof(stats));
    memset(total, 0, sizeof(total));
    memset(allstats, 0, sizeof(allstats));
 
    double vote = 0;
    double imdb = 0;
    double time = 0;
    double year = 0;

    int imdb_k = 0;
    int index = 0;

    char *unique_id = NULL;

    int rows = 0;
   
    int i = 0;
    int j = 0;

    for(i = 0; i < gtk_custom_table_get_rows(current); i++, rows++) {
        
        unique_id = gtk_custom_table_get_cell_text(current, 3, i);

        if(gtk_custom_table_get_indexof(other, unique_id) >= 0) {
            
            /* make results numeric */
            vote = atof(gtk_custom_table_get_cell_text(current, 2, i));
            imdb = atof(gtk_custom_table_get_cell_text(current, 1, i));
            time = atof(gtk_custom_table_get_cell_text(current, 5, i));
            year = atof(gtk_custom_table_get_cell_text(current, 6, i));

            imdb_k = ((imdb - (int)imdb) * 10) > 5 ? 
                (int)imdb : (int)imdb > 0 ? 
                    (int)imdb - 1 : 0;

            /* add up for each rating */
            stats[imdb_k][VOTES] += 1;
            stats[imdb_k][VOTE_AVG] += vote;
            stats[imdb_k][IMDB_AVG] += imdb;
            stats[imdb_k][TIME_AVG] += time;
            stats[imdb_k][YEAR_AVG] += year;
            stats[imdb_k][FLUX_AVG] += (vote - imdb);

            stats[imdb_k][VOTE_CNT] += vote > 0 ? 1 : 0;
            stats[imdb_k][IMDB_CNT] += imdb > 0 ? 1 : 0;
            stats[imdb_k][TIME_CNT] += time > 0 ? 1 : 0;
            stats[imdb_k][YEAR_CNT] += year > 0 ? 1 : 0;
            stats[imdb_k][FLUX_CNT] += vote > 0 && imdb > 0 ? 1 : 0;

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

            /* add to allstats tab if applicable */
            index = gtk_custom_table_get_indexof(nb_tab_top250, 
                unique_id);

            if(index >= 0) {

                allstats[0][0] += 1;
                allstats[0][1] += vote;
                allstats[0][2] += imdb;
                allstats[0][3] += time;
                allstats[0][4] += year;
            }

            index = gtk_custom_table_get_indexof(nb_tab_bot100, 
                unique_id);

            if(index >= 0) {

                allstats[1][0] += 1;
                allstats[1][1] += vote;
                allstats[1][2] += imdb;
                allstats[1][3] += time;
                allstats[1][4] += year;
            }

            index = gtk_custom_table_get_indexof(nb_tab_boxoffice, 
                unique_id);

            if(index >= 0) {

                allstats[2][0] += 1;
                allstats[2][1] += vote;
                allstats[2][2] += imdb;
                allstats[2][3] += time;
                allstats[2][4] += year;
            }
        }
    }

    open_allstats(allstats[0], 3, 
        gtk_custom_table_get_rows(nb_tab_top250));
    open_allstats(allstats[1], 7, 
        gtk_custom_table_get_rows(nb_tab_bot100));
    open_allstats(allstats[2], 11, 
        gtk_custom_table_get_rows(nb_tab_boxoffice));

    ui_fill_calc(rows, stats);

    gtk_custom_table_sort(nb_tab_compare, 0, 
        GTK_CUSTOM_TABLE_DESC);

    char temp[100];

    /* add statistics to widget table */
    for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {
        
        /* add imdb value to table */
        sprintf(temp, "%1.2f", stats[i][IMDB_AVG]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 0, j, 
            temp);

        /* add vote value to table */
        sprintf(temp, "%1.2f", stats[i][VOTE_AVG]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 1, j, 
            temp);

        /* add flux value to table */
        sprintf(temp, stats[i][FLUX_AVG] == 0.0 ? 
            "%1.2f" : "%+1.2f", stats[i][FLUX_AVG]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 2, j, 
            temp);

        /* add graph value to table */
        sprintf(temp, "%1.0f", stats[i][GRAPH_WIDTH]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 3, j, 
            temp);

        /* add percent value to table */
        sprintf(temp, "%2.2f %%", stats[i][PERCENTAGE]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 4, j, 
            temp);

        /* add votes value to table */
        sprintf(temp, "%1.0f", stats[i][VOTES]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 5, j, 
            temp);

        /* add runtime value to table */
        sprintf(temp, "%1.2f", stats[i][TIME_AVG]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 6, j, 
            temp);

        /* add year value to table */
        sprintf(temp, "%1.2f", stats[i][YEAR_AVG]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 7, j, 
            temp);

        /* add new background color to vote rating */
        gtk_custom_table_set_cell_color(nb_tab_compare, 0, j, 
            colors[(int)stats[i][IMDB_AVG] < 10 && 
                (int)stats[i][IMDB_AVG] > 0 ? 
                (int)stats[i][IMDB_AVG] - 1 : 1]);

        gtk_custom_table_set_cell_color(nb_tab_compare, 1, j, 
            colors[(int)stats[i][VOTE_AVG] < 10 && 
                (int)stats[i][VOTE_AVG] > 0 ? 
                (int)stats[i][VOTE_AVG] - 1 : 1]);

        /* add new background color to flux */
        gtk_custom_table_set_cell_color(nb_tab_compare, 2, j, 
            colors[(int)stats[i][FLUX_AVG] > 0 ? 8 : 1]);
    }

    /* add statistics footer vote average */
    sprintf(temp, "%2.2f", total[VOTE_TOT][0] / total[VOTE_TOT][1]);
    gtk_custom_table_set_foot_text(nb_tab_compare, 0, 
        temp);

    /* add statistics footer imdb average */
    sprintf(temp, "%2.2f", total[IMDB_TOT][0] / total[IMDB_TOT][1]);
    gtk_custom_table_set_foot_text(nb_tab_compare, 1, 
        temp);

    /* add statistics footer flux average */
    sprintf(temp, "%+2.2f", total[FLUX_TOT][0] / total[FLUX_TOT][1]);
    gtk_custom_table_set_foot_text(nb_tab_compare, 2, 
        temp);

    /* add statistics footer vote info */
    sprintf(temp, "%d movies intersect", rows);
    gtk_custom_table_set_foot_text(nb_tab_compare, 3, 
        temp);

    /* add statistics footer percent total */
    gtk_custom_table_set_foot_text(nb_tab_compare, 4, 
        "100.00 %");

    /* add statistics footer votes total */
    sprintf(temp, "%d", rows);
    gtk_custom_table_set_foot_text(nb_tab_compare, 5, 
        temp);

    /* add statistics footer runtime average */
    sprintf(temp, "%4.2f", total[TIME_TOT][0] / total[TIME_TOT][1]);
    gtk_custom_table_set_foot_text(nb_tab_compare, 6, 
        temp);

    /* add statistics footer year average */
    sprintf(temp, "%4.2f", total[YEAR_TOT][0] / total[YEAR_TOT][1]);
    gtk_custom_table_set_foot_text(nb_tab_compare, 7, 
        temp);

    gtk_custom_table_set_sortable(nb_tab_compare, TRUE);
}

