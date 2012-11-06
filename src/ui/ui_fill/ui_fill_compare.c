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


#include "ui_fill.h"


void open_compare(GtkWidget *current, GtkWidget *other) {

    int i = 0;
    int j = 0;

    int row_count = 0;
    int imdb_key = 0;

    double stats[10][7];
    memset(stats, '\0', sizeof(stats));

    double vote = 0;
    double imdb = 0;
    double time = 0;
    double year = 0;
    
    double imdb_average = 0;
    double flux_average = 0;

    int index = 0;
    int graph_apex = 0;
    int year_average = 0;
    int vote_average = 0;
    int time_average = 0;

    int imdb_l = 0;
    int imdb_o = 0;
    
    char temp[100];
    char **shared = NULL;
    char *unique_id = NULL;

    double allstats[3][5];
    memset(allstats, '\0', sizeof(allstats));

    gtk_custom_table_sort(nb_tab_compare, 0, GTK_CUSTOM_TABLE_DESC);

    for(i = 0; i < gtk_custom_table_get_rows(current); i++) {
        
        unique_id = gtk_custom_table_get_cell_text(current, 3, i);

        if(gtk_custom_table_get_indexof(other, unique_id) >= 0) {
            
            gtk_custom_table_get_row(current, i, &shared);

            /* make results numeric */
            vote = atof(shared[2]);
            imdb = atof(shared[1]);
            time = atof(shared[5]);
            year = atof(shared[6]);

            imdb_l = (int)imdb;
            imdb_o = (imdb - imdb_l) * 10;

            imdb_key = imdb_o > 5 ? (int)imdb_l : (int)imdb_l - 1;

            /* add up for each rating */
            stats[imdb_key][0] += 1;
            stats[imdb_key][3] += vote;
            stats[imdb_key][4] += imdb;
            stats[imdb_key][5] += time;
            stats[imdb_key][6] += year;

            /* add up totals for vote averages */
            vote_average += vote;
            imdb_average += imdb;
            time_average += time;
            year_average += year;
            flux_average += (vote - imdb);

            row_count++;

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

            for(j = 0; j < gtk_custom_table_get_cols(current); j++) {
                free(shared[j]);
            }

            free(shared);

            shared = NULL;
        }
    }

    open_allstats(allstats[0], 3, 
        gtk_custom_table_get_rows(nb_tab_top250));
    open_allstats(allstats[1], 7, 
        gtk_custom_table_get_rows(nb_tab_bot100));
    open_allstats(allstats[2], 11, 
        gtk_custom_table_get_rows(nb_tab_boxoffice));

    for(i = 0; i < 10; i++) {

        /* find graph apex, i.e. the longest bar on screen */
        graph_apex = stats[i][0] > graph_apex ? stats[i][0]: graph_apex;
    } 

    for(i = 0, j = 10; i < 10 && j > 0; i++, j++) {

        /* calculate percentage for each rating */
        stats[i][1] = stats[i][0] != 0 ? 
            (stats[i][0] / row_count) * 100: 0; 
        /* calculate graph value from vote amounts, graph is 0-100 */
        stats[i][2] = stats[i][0] != 0 ? 
            100 / (graph_apex / stats[i][0]) : 0;
        /* calculate vote averages for each rating */
        stats[i][3] = stats[i][0] != 0 ? 
            stats[i][3] / stats[i][0] : 0;
        /* calculate imdb averages for each rating */
        stats[i][4] = stats[i][0] != 0 ? 
            stats[i][4] / stats[i][0] : 0;
        /* calculate time averages for each rating */
        stats[i][5] = stats[i][0] != 0 ? 
            stats[i][5] / stats[i][0] : 0;
        /* calculate year averages for each rating */
        stats[i][6] = stats[i][0] != 0 ? 
            stats[i][6] / stats[i][0] : 0;
    }

    double flux = 0;

    /* add statistics to widget table */
    for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {
        
        flux = stats[i][0] > 0 ? stats[i][3] - stats[i][4] : 0.00;

        /* add imdb value to table */
        sprintf(temp, "%1.2f", stats[i][4]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 0, j, 
            temp);

        /* add vote value to table */
        sprintf(temp, "%1.2f", stats[i][3]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 1, j, 
            temp);

        /* add flux value to table */
        sprintf(temp, "%+1.2f", flux);
        gtk_custom_table_set_cell_text(nb_tab_compare, 2, j, 
            temp);

        /* add graph value to table */
        sprintf(temp, "%1.0f", stats[i][2]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 3, j, 
            temp);

        /* add percent value to table */
        sprintf(temp, "%2.2f %%", stats[i][1]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 4, j, 
            temp);

        /* add votes value to table */
        sprintf(temp, "%1.0f", stats[i][0]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 5, j, 
            temp);

        /* add runtime value to table */
        sprintf(temp, "%1.2f", stats[i][5]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 6, j, 
            temp);

        /* add year value to table */
        sprintf(temp, "%1.2f", stats[i][6]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 7, j, 
            temp);

        /* add new background color to vote rating */
        int imdb_vote = (int)stats[i][4];
        int vote_vote = (int)stats[i][3];

        gtk_custom_table_set_cell_color(nb_tab_compare, 0, j, 
            colors[imdb_vote < 10 && imdb_vote > 0 ? imdb_vote - 1 : 1]);

        gtk_custom_table_set_cell_color(nb_tab_compare, 1, j, 
            colors[vote_vote < 10 && vote_vote > 0 ? vote_vote - 1 : 1]);

        /* add new background color to flux */
        gtk_custom_table_set_cell_color(nb_tab_compare, 2, j, 
            colors[flux > 0 ? 8 : 1]);
    }

    /* add statistics footer vote average */
    sprintf(temp, "%2.2f", (double)imdb_average / row_count);
    gtk_custom_table_set_foot_text(nb_tab_compare, 0, 
        temp);

    /* add statistics footer imdb average */
    sprintf(temp, "%2.2f", (double)vote_average / row_count);
    gtk_custom_table_set_foot_text(nb_tab_compare, 1, 
        temp);

    /* add statistics footer flux average */
    sprintf(temp, "%+2.2f", (double)flux_average / row_count);
    gtk_custom_table_set_foot_text(nb_tab_compare, 2, 
        temp);

    /* add statistics footer vote info */
    sprintf(temp, "%d movies intersect", row_count);
    gtk_custom_table_set_foot_text(nb_tab_compare, 3, 
        temp);

    /* add statistics footer percent total */
    gtk_custom_table_set_foot_text(nb_tab_compare, 4, 
        "100.00 %");

    /* add statistics footer votes total */
    sprintf(temp, "%d", row_count);
    gtk_custom_table_set_foot_text(nb_tab_compare, 5, 
        temp);

    /* add statistics footer runtime average */
    sprintf(temp, "%4.2f", (double)time_average / row_count);
    gtk_custom_table_set_foot_text(nb_tab_compare, 6, 
        temp);

    /* add statistics footer year average */
    sprintf(temp, "%4.2f", (double)year_average / row_count);
    gtk_custom_table_set_foot_text(nb_tab_compare, 7, 
        temp);

    gtk_custom_table_set_sortable(nb_tab_compare, TRUE);
}
