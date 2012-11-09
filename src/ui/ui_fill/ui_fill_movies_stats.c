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


void open_movie_stats(char ****results, int rows, char *filename) {

    int i = 0;
    int j = 0;

    double stats[10][6];
    memset(stats, '\0', sizeof(stats));

    double vote = 0;
    double imdb = 0;
    double time = 0;
    double year = 0;

    double imdb_average = 0;
    double flux_average = 0;

    int graph_apex = 0;
    int year_average = 0;
    int vote_average = 0;
    int time_average = 0;

    char temp[100];
    
    gtk_custom_table_sort(nb_tab_statistics, 0, GTK_CUSTOM_TABLE_DESC);

    for(i = 1; i < rows; i++) {

        /* make results numeric */
        vote = atof((*results)[i][8]);
        imdb = atof((*results)[i][9]);
        time = atof((*results)[i][10]);
        year = atof((*results)[i][11]);

        /* add up for each rating */
        stats[(int)vote - 1][0] += 1;
        stats[(int)vote - 1][3] += imdb;
        stats[(int)vote - 1][4] += time;
        stats[(int)vote - 1][5] += year;

        /* add up totals for vote averages */
        vote_average += vote;
        imdb_average += imdb;
        time_average += time;
        year_average += year;
        flux_average += (vote - imdb);
    }

    for(i = 0; i < 10; i++) {

        /* find graph apex, i.e. the longest bar on screen */
        graph_apex = stats[i][0] > graph_apex ? stats[i][0]: graph_apex;
    } 

    rows = rows - 1;

    for(i = 0, j = 10; i < 10 && j > 0; i++, j++) {

        /* calculate percentage for each rating */
        stats[i][1] = stats[i][0] != 0 ? 
            (stats[i][0] / rows) * 100: 0; 
        /* calculate graph value from vote amounts, graph is 0-100 */
        stats[i][2] = stats[i][0] != 0 ? 
            100 / (graph_apex / stats[i][0]) : 0;
        /* calculate imdb averages for each rating */
        stats[i][3] = stats[i][0] != 0 ? 
            stats[i][3] / stats[i][0] : 0;
        /* calculate time averages for each rating */
        stats[i][4] = stats[i][0] != 0 ? 
            stats[i][4] / stats[i][0] : 0;
        /* calculate year averages for each rating */
        stats[i][5] = stats[i][0] != 0 ? 
            stats[i][5] / stats[i][0] : 0;
    }

    double flux = 0;

    /* add statistics to widget table */
    for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {
        
        flux = stats[i][0] > 0 ? (i + 1) - stats[i][3] : 0.00;

        /* add imdb value to table */
        sprintf(temp, "%1.2f", stats[i][3]);
        gtk_custom_table_set_cell_text(nb_tab_statistics, 1, j, 
            temp);

        /* add flux value to table */
        sprintf(temp, "%+1.2f", flux);
        gtk_custom_table_set_cell_text(nb_tab_statistics, 2, j, 
            temp);

        /* add graph value to table */
        sprintf(temp, "%1.0f", stats[i][2]);
        gtk_custom_table_set_cell_text(nb_tab_statistics, 3, j, 
            temp);

        /* add percent value to table */
        sprintf(temp, "%2.2f %%", stats[i][1]);
        gtk_custom_table_set_cell_text(nb_tab_statistics, 4, j, 
            temp);

        /* add votes value to table */
        sprintf(temp, "%1.0f", stats[i][0]);
        gtk_custom_table_set_cell_text(nb_tab_statistics, 5, j, 
            temp);

        /* add runtime value to table */
        sprintf(temp, "%1.2f", stats[i][4]);
        gtk_custom_table_set_cell_text(nb_tab_statistics, 6, j, 
            temp);

        /* add year value to table */
        sprintf(temp, "%1.2f", stats[i][5]);
        gtk_custom_table_set_cell_text(nb_tab_statistics, 7, j, 
            temp);

        /* reset background colors */
        gtk_custom_table_set_cell_color_enable(nb_tab_statistics, 1, j, 
            FALSE);
        gtk_custom_table_set_cell_color_enable(nb_tab_statistics, 2, j, 
            FALSE);

        /* add new background color to imdb rating */
        int imdb_vote = (int)stats[i][3];

        gtk_custom_table_set_cell_color(nb_tab_statistics, 1, j, 
            colors[imdb_vote < 10 && imdb_vote > 0 ? imdb_vote - 1 : 1]);

        /* add new background color to flux */
        gtk_custom_table_set_cell_color(nb_tab_statistics, 2, j, 
            colors[flux > 0 ? 8 : 1]);
    }

    /* add statistics footer vote average */
    sprintf(temp, "%2.2f", (double)vote_average / rows);
    gtk_custom_table_set_foot_text(nb_tab_statistics, 0, 
        temp);

    /* add statistics footer imdb average */
    sprintf(temp, "%2.2f", (double)imdb_average / rows);
    gtk_custom_table_set_foot_text(nb_tab_statistics, 1, 
        temp);

    /* add statistics footer flux average */
    sprintf(temp, "%+2.2f", (double)flux_average / rows);
    gtk_custom_table_set_foot_text(nb_tab_statistics, 2, 
        temp);

    /* add statistics footer vote info */
    gtk_custom_table_set_foot_text(nb_tab_statistics, 3, 
        filename);

    /* add statistics footer percent total */
    gtk_custom_table_set_foot_text(nb_tab_statistics, 4, 
        "100.00 %");

    /* add statistics footer votes total */
    sprintf(temp, "%d", rows);
    gtk_custom_table_set_foot_text(nb_tab_statistics, 5, 
        temp);

    /* add statistics footer runtime average */
    sprintf(temp, "%4.2f", (double)time_average / rows);
    gtk_custom_table_set_foot_text(nb_tab_statistics, 6, 
        temp);

    /* add statistics footer year average */
    sprintf(temp, "%4.2f", (double)year_average / rows);
    gtk_custom_table_set_foot_text(nb_tab_statistics, 7, 
        temp);

    gtk_custom_table_set_sortable(nb_tab_statistics, TRUE);
}

