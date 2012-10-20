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


#include "colors.h"
#include "openfile.h"
#include "readfile.h"
#include "globals.h"
#include "gtk_custom_table/gtk_custom_table.h"
#include "ui/ui_widgets.h"


int has_open_movies = 0;
int has_open_lists = 0;


/* add values to allstats tab */
void set_allstats(double allstats[5], int row, int rows) {

    char temp[100];

    double vote_avg = allstats[1] / allstats[0] ;
    double imdb_avg = allstats[2] / allstats[0];
    double flux_avg = vote_avg - imdb_avg;

    /* reset background colors */
    gtk_custom_table_set_cell_color_enable(nb_tab_allstats, 0, row, 
        FALSE);
    gtk_custom_table_set_cell_color_enable(nb_tab_allstats, 1, row, 
        FALSE);
    gtk_custom_table_set_cell_color_enable(nb_tab_allstats, 2, row, 
        FALSE);

    /* set first column, vote */
    if(vote_avg > 0.0) {

        sprintf(temp, "%1.2f", vote_avg);

        gtk_custom_table_set_cell_alignment(nb_tab_allstats, 0, row, 
            PANGO_ALIGN_RIGHT);
    }
    else {

        strcpy(temp, "N/A");

        gtk_custom_table_set_cell_color(nb_tab_allstats, 0, row, 
            not_app);
        gtk_custom_table_set_cell_alignment(nb_tab_allstats, 0, row, 
            PANGO_ALIGN_CENTER);
    }

    gtk_custom_table_set_cell_text(nb_tab_allstats, 0, row, 
        temp);

    /* set second column, imdb */
    if(imdb_avg > 0.0) {
        sprintf(temp, "%1.2f", imdb_avg);

        gtk_custom_table_set_cell_alignment(nb_tab_allstats, 1, row, 
            PANGO_ALIGN_RIGHT);
    }
    else {

        strcpy(temp, "N/A");

        gtk_custom_table_set_cell_color(nb_tab_allstats, 1, row, 
            not_app);
        gtk_custom_table_set_cell_alignment(nb_tab_allstats, 1, row, 
            PANGO_ALIGN_CENTER);
    }

    gtk_custom_table_set_cell_text(nb_tab_allstats, 1, row, 
        temp);

    /* set third column, flux */
    if(allstats[1] > 0.0 && allstats[2] > 0.0) {

        sprintf(temp, "%+1.2f", flux_avg);

        gtk_custom_table_set_cell_alignment(nb_tab_allstats, 2, row, 
            PANGO_ALIGN_RIGHT);
    }
    else {

        strcpy(temp, "N/A");

        gtk_custom_table_set_cell_color(nb_tab_allstats, 2, row, 
            not_app);
        gtk_custom_table_set_cell_alignment(nb_tab_allstats, 2, row, 
            PANGO_ALIGN_CENTER);
    }

    gtk_custom_table_set_cell_text(nb_tab_allstats, 2, row, 
        temp);

    sprintf(temp, "%d", (int)allstats[0] > 0 ? 
        (int)(100.0 / (rows / allstats[0])) : 0);
    gtk_custom_table_set_cell_text(nb_tab_allstats, 3, row, 
        temp);

    sprintf(temp, "%1.2f %%", (int)allstats[0] > 0 ? 
        allstats[0] / (rows / 100.0) : 0.0);
    gtk_custom_table_set_cell_text(nb_tab_allstats, 4, row, 
        temp);

    sprintf(temp, "%d/%d", (int)allstats[0], rows);
    gtk_custom_table_set_cell_text(nb_tab_allstats, 5, row, 
        temp);

    sprintf(temp, "%1.2f", (int)allstats[0] > 0 ?
        allstats[3] / allstats[0] : 0.0);
    gtk_custom_table_set_cell_text(nb_tab_allstats, 6, row, 
        temp);

    sprintf(temp, "%1.2f", (int)allstats[0] > 0 ? 
        allstats[4] / allstats[0] : 0.0);
    gtk_custom_table_set_cell_text(nb_tab_allstats, 7, row, 
        temp);

    int vote = (int)vote_avg;
    int imdb = (int)imdb_avg;
    int flux = (int)flux_avg;

    if(vote_avg > 0.0) {
        gtk_custom_table_set_cell_color(nb_tab_allstats, 0, row, 
            colors[vote < 10 && vote > 0 ? vote - 1 : 1 ]);
    }

    if(imdb_avg > 0.0) {
        gtk_custom_table_set_cell_color(nb_tab_allstats, 1, row, 
            colors[imdb < 10 && imdb > 0 ? imdb - 1 : 1]);
    }

    if(allstats[1] > 0.0 && allstats[2] > 0.0) {
        gtk_custom_table_set_cell_color(nb_tab_allstats, 2, row, 
            colors[flux > 0 ? 8 : 1]);
    }
}


int open_compare(GtkWidget *current, GtkWidget *other) {

    int i = 0;
    int j = 0;

    int row_count = 0;
    int imdb_key = 0;

    double stats[10][6];
    memset(stats, '\0', sizeof(stats));

    int vote = 0;
    int imdb = 0;
    int time = 0;
    int year = 0;

    int index = 0;
    int graph_apex = 0;
    int year_average = 0;
    int vote_average = 0;
    int time_average = 0;
    double imdb_average = 0;
    double flux_average = 0;

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
            vote = atoi(shared[2]);
            imdb = atof(shared[1]);
            time = atoi(shared[5]);
            year = atoi(shared[6]);

            imdb_key = (int)imdb - 1;
            
            /* add up for each rating */
            stats[imdb_key][0] += 1;
            stats[imdb_key][3] += vote;
            stats[imdb_key][4] += time;
            stats[imdb_key][5] += year;

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

    set_allstats(allstats[0], 3, 
        gtk_custom_table_get_rows(nb_tab_top250));
    set_allstats(allstats[1], 7, 
        gtk_custom_table_get_rows(nb_tab_bot100));
    set_allstats(allstats[2], 11, 
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
        sprintf(temp, "%d", i + 1);
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
        sprintf(temp, "%1.2f", stats[i][4]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 6, j, 
            temp);

        /* add year value to table */
        sprintf(temp, "%1.2f", stats[i][5]);
        gtk_custom_table_set_cell_text(nb_tab_compare, 7, j, 
            temp);


        /* reset background colors */
        gtk_custom_table_set_cell_color_enable(nb_tab_compare, 1, j, 
            FALSE);
        gtk_custom_table_set_cell_color_enable(nb_tab_compare, 2, j, 
            FALSE);

        /* add new background color to vote rating */
        int imdb_vote = (int)stats[i][3];

        gtk_custom_table_set_cell_color(nb_tab_compare, 1, j, 
            colors[imdb_vote < 10 && imdb_vote > 0 ? imdb_vote - 1 : 1]);

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
    sprintf(temp, "%d movies intersect, average rating is %1.2f", 
        row_count, (double)vote_average / row_count);
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

    return 1;
}


/**
 * read and parse a ratings file or list..
 * @param char *filename    file to open..
 */
int open_file(char *filename) {

    int cols = 0;
    int rows = 0;

    char ***results;
            
    if(!read_file(filename, &cols, &rows, &results) || cols < 10) {
        return 0;
    }

    int i = 0;
    int j = 0;

    double stats[10][6];
    memset(stats, '\0', sizeof(stats));

    double allstats[3][5];
    memset(allstats, '\0', sizeof(allstats));

    int vote = 0;
    int imdb = 0;
    int time = 0;
    int year = 0;

    int graph_apex = 0;
    int year_average = 0;
    int vote_average = 0;
    int time_average = 0;
    double imdb_average = 0;
    double flux_average = 0;

    char temp[100];

    if(strcmp("IMDb Rating", results[0][9]) == 0) {

        set_global(CONST_OPEN_M, filename);

        /* clear associated color from lists */
        for(i = 0; i < gtk_custom_table_get_rows(nb_tab_lists); i++) {
            
            gtk_custom_table_set_cell_text(nb_tab_lists, 2, i, "0");
            gtk_custom_table_set_cell_color_enable(nb_tab_lists, 2, i, 
                FALSE);
        }

        /* clear associated color from top250 */
        for(i = 0; i < gtk_custom_table_get_rows(nb_tab_top250); i++) {
            
            gtk_custom_table_set_cell_text(nb_tab_top250, 2, i, "0");
            gtk_custom_table_set_cell_color_enable(nb_tab_top250, 2, i, 
                FALSE);
        }

        /* clear associated color from boxoffice */
        for(i = 0; i < gtk_custom_table_get_rows(nb_tab_boxoffice); i++) {
            
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 2, i, "0");
            gtk_custom_table_set_cell_color_enable(nb_tab_boxoffice, 2, i, 
                FALSE);
        }

        gtk_custom_table_sort(nb_tab_statistics, 0, GTK_CUSTOM_TABLE_DESC);

        for(i = 1; i < rows; i++) {

            /* make results numeric */
            vote = atoi(results[i][8]);
            imdb = atof(results[i][9]);
            time = atoi(results[i][10]);
            year = atoi(results[i][11]);

            /* add up for each rating */
            stats[vote - 1][0] += 1;
            stats[vote - 1][3] += imdb;
            stats[vote - 1][4] += time;
            stats[vote - 1][5] += year;

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
        sprintf(temp, "You've rated %d movies, average rating is %1.2f", 
            rows, (double)vote_average / rows);
        gtk_custom_table_set_foot_text(nb_tab_statistics, 3, 
            temp);

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

        /* update mymovies tab with new data */
        gtk_custom_table_resize(nb_tab_mymovies, -1, rows);

        memset(allstats, '\0', sizeof(allstats));

        /* add text to widget table */
        for(i = 1, j = 0; i <= rows; i++, j++) {

            sprintf(temp, "%d", i);

            gtk_custom_table_set_cell_text(nb_tab_mymovies, 0, j, 
                temp);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 1, j, 
                results[i][9]);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 2, j, 
                results[i][8]);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 3, j, 
                results[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 4, j, 
                results[i][5]);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 5, j, 
                results[i][10]);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 6, j, 
                results[i][11]);

            /* set cell colors for imdb and flux values */
            gtk_custom_table_set_cell_color(nb_tab_mymovies, 1, j, 
                colors[(int)atoi(results[i][9]) - 1]);
            gtk_custom_table_set_cell_color(nb_tab_mymovies, 2, j, 
                colors[atoi(results[i][8]) - 1]);

            /* mark rated movies on top250 list */
            int index = gtk_custom_table_get_indexof(nb_tab_top250, 
                results[i][1]);

            if(index >= 0) {

                /* add 'my rating' to top250 tab */
                gtk_custom_table_set_cell_text(nb_tab_top250, 2, 
                    index, results[i][8]);

                gtk_custom_table_set_cell_color(nb_tab_top250, 2, 
                    index, colors[atoi(results[i][8]) - 1]);
                
                allstats[0][0] += 1;
                allstats[0][1] += atof(results[i][8]);
                allstats[0][2] += atof(results[i][9]);
                allstats[0][3] += atof(results[i][10]);
                allstats[0][4] += atof(results[i][11]);
            }

            /* add 'my rating' to bottom100 tab if applicable */
            index = gtk_custom_table_get_indexof(nb_tab_bot100, 
                results[i][1]);

            if(index >= 0) {

                /* set cell values */
                gtk_custom_table_set_cell_text(nb_tab_bot100, 2, 
                    index, results[i][8]);

                gtk_custom_table_set_cell_color(nb_tab_bot100, 2, 
                    index, colors[atoi(results[i][8]) - 1]);

                allstats[1][0] += 1;
                allstats[1][1] += atof(results[i][8]);
                allstats[1][2] += atof(results[i][9]);
                allstats[1][3] += atof(results[i][10]);
                allstats[1][4] += atof(results[i][11]);
            }

            /* add 'my rating' to boxoffice tab if applicable */
            index = gtk_custom_table_get_indexof(nb_tab_boxoffice, 
                results[i][1]);

            if(index >= 0) {

                /* set cell values */
                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, 
                    index, results[i][9]);
                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 2, 
                    index, results[i][8]);

                /* set cell colors */
                gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, 
                    index, colors[atoi(results[i][9]) - 1]);
                gtk_custom_table_set_cell_color(nb_tab_boxoffice, 2, 
                    index, colors[atoi(results[i][8]) - 1]);

                allstats[2][0] += 1;
                allstats[2][1] += atof(results[i][8]);
                allstats[2][2] += atof(results[i][9]);
                allstats[2][3] += atof(results[i][10]);
                allstats[2][4] += atof(results[i][11]);
            }

            /* add 'my rating' to lists tab if applicable */
            index = gtk_custom_table_get_indexof(nb_tab_lists, 
                results[i][1]);

            if(index >= 0) {

                gtk_custom_table_set_cell_text(nb_tab_lists, 2, 
                    index, results[i][8]);
                gtk_custom_table_set_cell_color(nb_tab_lists, 2, 
                    index, colors[atoi(results[i][8]) - 1]);
            }
        }
 
        set_allstats(allstats[0], 1, 
            gtk_custom_table_get_rows(nb_tab_top250));
        set_allstats(allstats[1], 5, 
            gtk_custom_table_get_rows(nb_tab_bot100));
        set_allstats(allstats[2], 9, 
            gtk_custom_table_get_rows(nb_tab_boxoffice));

        /* set sortable and sort by index */
        gtk_custom_table_set_sortable(nb_tab_mymovies, TRUE);
        gtk_custom_table_sort(nb_tab_mymovies, 0, GTK_CUSTOM_TABLE_ASC);

        has_open_movies = 1;
    }
    else {

        set_global(CONST_OPEN_L, filename);

        gtk_custom_table_sort(nb_tab_lists_stats, 0, GTK_CUSTOM_TABLE_DESC);

        for(i = 1; i < rows; i++) {

            /* make results numeric */
            vote = atoi(results[i][8]);
            imdb = atof(results[i][8]);
            time = atoi(results[i][9]);
            year = atoi(results[i][10]);

            /* add up for each rating */
            stats[vote - 1][0] += 1;
            stats[vote - 1][3] += imdb;
            stats[vote - 1][4] += time;
            stats[vote - 1][5] += year;

            /* add up totals for vote averages */
            vote_average += vote;
            imdb_average += imdb;
            time_average += time;
            year_average += year;
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

        /* add statistics to widget table */
        for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {
            
            /* add graph value to table */
            sprintf(temp, "%1.0f", stats[i][2]);
            gtk_custom_table_set_cell_text(nb_tab_lists_stats, 3, j, 
                temp);

            /* add percent value to table */
            sprintf(temp, "%2.2f %%", stats[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_lists_stats, 4, j, 
                temp);

            /* add votes value to table */
            sprintf(temp, "%1.0f", stats[i][0]);
            gtk_custom_table_set_cell_text(nb_tab_lists_stats, 5, j, 
                temp);

            /* add runtime value to table */
            sprintf(temp, "%1.2f", stats[i][4]);
            gtk_custom_table_set_cell_text(nb_tab_lists_stats, 6, j, 
                temp);

            /* add year value to table */
            sprintf(temp, "%1.2f", stats[i][5]);
            gtk_custom_table_set_cell_text(nb_tab_lists_stats, 7, j, 
                temp);
        }

        /* add statistics footer vote average */
        sprintf(temp, "%2.2f", (double)vote_average / rows);
        gtk_custom_table_set_foot_text(nb_tab_lists_stats, 0, 
            temp);

        /* add statistics footer vote info */
        sprintf(temp, "List contains %d movies, average rating is %1.2f", 
            rows, (double)vote_average / rows);
        gtk_custom_table_set_foot_text(nb_tab_lists_stats, 3, 
            temp);

        /* add statistics footer percent total */
        gtk_custom_table_set_foot_text(nb_tab_lists_stats, 4, 
            "100.00 %");

        /* add statistics footer votes total */
        sprintf(temp, "%d", rows);
        gtk_custom_table_set_foot_text(nb_tab_lists_stats, 5, 
            temp);

        /* add statistics footer runtime average */
        sprintf(temp, "%4.2f", (double)time_average / rows);
        gtk_custom_table_set_foot_text(nb_tab_lists_stats, 6, 
            temp);

        /* add statistics footer year average */
        sprintf(temp, "%4.2f", (double)year_average / rows);
        gtk_custom_table_set_foot_text(nb_tab_lists_stats, 7, 
            temp);

        gtk_custom_table_set_sortable(nb_tab_lists_stats, TRUE);


        /* update lists tab with new data */
        gtk_custom_table_resize(nb_tab_lists, -1, (rows - 1));

        memset(allstats, '\0', sizeof(allstats)); 

        /* add text to widget table */
        for(i = 1, j = 0; i < rows; i++, j++) {

            sprintf(temp, "%d", i);

            gtk_custom_table_set_cell_text(nb_tab_lists, 0, j, 
                temp);
            gtk_custom_table_set_cell_text(nb_tab_lists, 1, j, 
                results[i][8]); 
            gtk_custom_table_set_cell_text(nb_tab_lists, 2, j, 
                "0");
            gtk_custom_table_set_cell_text(nb_tab_lists, 3, j, 
                results[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_lists, 4, j, 
                results[i][5]);
            gtk_custom_table_set_cell_text(nb_tab_lists, 5, j, 
                results[i][9]);
            gtk_custom_table_set_cell_text(nb_tab_lists, 6, j, 
                results[i][10]);

            /* add new background color to rating */
            int rating = (int)atoi(results[i][8]);
            int rating_color = rating < 10 && rating > 0 ? rating - 1 : 0;

            gtk_custom_table_set_cell_color(nb_tab_lists, 1, j, 
                colors[rating_color]);

            /* add 'my rating' to lists tab if applicable */
            int index = gtk_custom_table_get_indexof(nb_tab_mymovies, 
                results[i][1]);

            if(index >= 0) {
                
                char **table_row = NULL;

                gtk_custom_table_get_row(nb_tab_mymovies, index, &table_row);

                gtk_custom_table_set_cell_text(nb_tab_lists, 2, j, 
                    table_row[2]);

                gtk_custom_table_set_cell_color(nb_tab_lists, 2, j, 
                    colors[atoi(table_row[2]) - 1]);

                int k = 0;

                for(k = 0; k < gtk_custom_table_get_cols(nb_tab_mymovies); k++) {
                    free(table_row[k]);
                }

                free(table_row);
            }

            /* add imdb-rating to boxoffice tab if applicable */
            index = gtk_custom_table_get_indexof(nb_tab_boxoffice, 
                results[i][1]);

            if(index >= 0) {

                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, index, 
                    results[i][8]);

                gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, 
                    index, colors[rating_color]);
            }

            /* add to allstats tab if applicable */
            index = gtk_custom_table_get_indexof(nb_tab_top250, 
                results[i][1]);

            if(index >= 0) {

                allstats[0][0] += 1;
                allstats[0][2] += atof(results[i][8]);
                allstats[0][3] += atof(results[i][9]);
                allstats[0][4] += atof(results[i][10]);
            }

            index = gtk_custom_table_get_indexof(nb_tab_bot100, 
                results[i][1]);

            if(index >= 0) {

                allstats[1][0] += 1;
                allstats[1][2] += atof(results[i][8]);
                allstats[1][3] += atof(results[i][9]);
                allstats[1][4] += atof(results[i][10]);
            }

            index = gtk_custom_table_get_indexof(nb_tab_boxoffice, 
                results[i][1]);

            if(index >= 0) {

                allstats[2][0] += 1;
                allstats[2][2] += atof(results[i][8]);
                allstats[2][3] += atof(results[i][9]);
                allstats[2][4] += atof(results[i][10]);
            }

        }

        set_allstats(allstats[0], 2, 
            gtk_custom_table_get_rows(nb_tab_top250));
        set_allstats(allstats[1], 6, 
            gtk_custom_table_get_rows(nb_tab_bot100));
        set_allstats(allstats[2], 10, 
            gtk_custom_table_get_rows(nb_tab_boxoffice));

        /* set sortable and sort by index */
        gtk_custom_table_set_sortable(nb_tab_lists, TRUE);
        gtk_custom_table_sort(nb_tab_lists, 0, GTK_CUSTOM_TABLE_ASC);

        has_open_lists = 1;
    }

    free_memory(results, cols, rows);

    if(has_open_movies && has_open_lists) {
        open_compare(nb_tab_mymovies, nb_tab_lists);
    }
        
    gtk_custom_table_refresh(window);

    return 1;
}

