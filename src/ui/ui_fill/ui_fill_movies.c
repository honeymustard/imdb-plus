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


void open_movies(char ****results, int rows) {
    
    int i = 0;
    int j = 0;

    gtk_custom_table_set_column_font(nb_tab_mymovies, 4, "sans 10"); 

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

    double allstats[3][5];
    memset(allstats, '\0', sizeof(allstats));

    char temp[100];

    rows = rows - 1;

    /* update mymovies tab with new data */
    gtk_custom_table_resize(nb_tab_mymovies, -1, rows);

    /* add text to widget table */
    for(i = 1, j = 0; i <= rows; i++, j++) {

        sprintf(temp, "%d", i);

        gtk_custom_table_set_cell_text(nb_tab_mymovies, 0, j, 
            temp);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 1, j, 
            (*results)[i][9]);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 2, j, 
            (*results)[i][8]);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 3, j, 
            (*results)[i][1]);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 4, j, 
            (*results)[i][5]);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 5, j, 
            (*results)[i][10]);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 6, j, 
            (*results)[i][11]);

        /* reset background colors */
        gtk_custom_table_set_cell_color_enable(nb_tab_mymovies, 1, j, 
            FALSE);
        gtk_custom_table_set_cell_color_enable(nb_tab_mymovies, 2, j, 
            FALSE);

        /* add new background color to rating */
        int rating_imdb = (int)atoi((*results)[i][9]);
        rating_imdb = rating_imdb <= 10 && rating_imdb > 0 ? rating_imdb : 0;

        int rating_vote = (int)atoi((*results)[i][8]);
        rating_vote = rating_vote <= 10 && rating_vote > 0 ? rating_vote : 0;

        /* set cell colors for imdb and flux values */
        gtk_custom_table_set_cell_color(nb_tab_mymovies, 1, j, 
            rating_imdb == 0 ? not_app : colors[rating_imdb - 1]);
        gtk_custom_table_set_cell_color(nb_tab_mymovies, 2, j, 
            rating_vote == 0 ? not_app : colors[rating_vote - 1]);

        /* mark rated movies on top250 list */
        int index = gtk_custom_table_get_indexof(nb_tab_top250, 
            (*results)[i][1]);

        if(index >= 0) {

            /* add 'my rating' to top250 tab */
            gtk_custom_table_set_cell_text(nb_tab_top250, 2, 
                index, (*results)[i][8]);

            gtk_custom_table_set_cell_color(nb_tab_top250, 2, 
                index, colors[atoi((*results)[i][8]) - 1]);
            
            allstats[0][0] += 1;
            allstats[0][1] += atof((*results)[i][8]);
            allstats[0][2] += atof((*results)[i][9]);
            allstats[0][3] += atof((*results)[i][10]);
            allstats[0][4] += atof((*results)[i][11]);
        }

        /* add 'my rating' to bottom100 tab if applicable */
        index = gtk_custom_table_get_indexof(nb_tab_bot100, 
            (*results)[i][1]);

        if(index >= 0) {

            /* set cell values */
            gtk_custom_table_set_cell_text(nb_tab_bot100, 2, 
                index, (*results)[i][8]);

            gtk_custom_table_set_cell_color(nb_tab_bot100, 2, 
                index, colors[atoi((*results)[i][8]) - 1]);

            allstats[1][0] += 1;
            allstats[1][1] += atof((*results)[i][8]);
            allstats[1][2] += atof((*results)[i][9]);
            allstats[1][3] += atof((*results)[i][10]);
            allstats[1][4] += atof((*results)[i][11]);
        }

        /* add 'my rating' to boxoffice tab if applicable */
        index = gtk_custom_table_get_indexof(nb_tab_boxoffice, 
            (*results)[i][1]);

        if(index >= 0) {

            /* set cell values */
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, 
                index, (*results)[i][9]);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 2, 
                index, (*results)[i][8]);

            /* set cell colors */
            gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, 
                index, colors[atoi((*results)[i][9]) - 1]);
            gtk_custom_table_set_cell_color(nb_tab_boxoffice, 2, 
                index, colors[atoi((*results)[i][8]) - 1]);

            allstats[2][0] += 1;
            allstats[2][1] += atof((*results)[i][8]);
            allstats[2][2] += atof((*results)[i][9]);
            allstats[2][3] += atof((*results)[i][10]);
            allstats[2][4] += atof((*results)[i][11]);
        }

        /* add 'my rating' to lists tab if applicable */
        index = gtk_custom_table_get_indexof(nb_tab_lists, 
            (*results)[i][1]);

        if(index >= 0) {

            gtk_custom_table_set_cell_text(nb_tab_lists, 2, 
                index, (*results)[i][8]);
            gtk_custom_table_set_cell_color(nb_tab_lists, 2, 
                index, colors[atoi((*results)[i][8]) - 1]);
        }
    }

    open_allstats(allstats[0], 1, 
        gtk_custom_table_get_rows(nb_tab_top250));
    open_allstats(allstats[1], 5, 
        gtk_custom_table_get_rows(nb_tab_bot100));
    open_allstats(allstats[2], 9, 
        gtk_custom_table_get_rows(nb_tab_boxoffice));

    /* set sortable and sort by index */
    gtk_custom_table_set_sortable(nb_tab_mymovies, TRUE);
    gtk_custom_table_sort(nb_tab_mymovies, 0, GTK_CUSTOM_TABLE_ASC);
}

