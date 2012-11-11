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


void open_movies(char ****results, int rows) {
    
    int i = 0;
    int j = 0;

    /* clear associated color from lists */
    for(i = 0; i < gtk_custom_table_get_rows(nb_tab_lists); i++) {
        
        gtk_custom_table_set_cell_text(nb_tab_lists, 2, i, "0");
        gtk_custom_table_set_cell_color(nb_tab_lists, 2, i, not_app);
    }

    /* clear associated color from top250 */
    for(i = 0; i < gtk_custom_table_get_rows(nb_tab_top250); i++) {
        
        gtk_custom_table_set_cell_text(nb_tab_top250, 2, i, "0");
        gtk_custom_table_set_cell_color(nb_tab_top250, 2, i, not_app);
    }

    /* clear associated color from bot100 */
    for(i = 0; i < gtk_custom_table_get_rows(nb_tab_bot100); i++) {
        
        gtk_custom_table_set_cell_text(nb_tab_bot100, 2, i, "0");
        gtk_custom_table_set_cell_color(nb_tab_bot100, 2, i, not_app);
    }

    /* clear associated color from boxoffice */
    for(i = 0; i < gtk_custom_table_get_rows(nb_tab_boxoffice); i++) {
        
        gtk_custom_table_set_cell_text(nb_tab_boxoffice, 2, i, "0");
        gtk_custom_table_set_cell_color(nb_tab_boxoffice, 2, i, not_app);
    }

    double allstats[3][5];
    memset(allstats, 0, sizeof(allstats));

    double vote = 0;
    double imdb = 0;
    double time = 0;
    double year = 0;

    char temp[100];

    rows = rows - 1;

    /* update mymovies tab with new data */
    gtk_custom_table_resize(nb_tab_mymovies, -1, rows);

    /* add text to widget table */
    for(i = 1, j = 0; i <= rows; i++, j++) {

        /* make results numeric */
        vote = strtol((*results)[i][8], NULL, 10);
        imdb = strtod((*results)[i][9], NULL);
        time = strtol((*results)[i][10], NULL, 10);
        year = strtol((*results)[i][11], NULL, 10);

        vote = vote >= 0.0 && vote <= 10.0 ? vote : 0.0;
        imdb = imdb >= 0.0 && imdb <= 10.0 ? imdb : 0.0;
        time = time >= 0.0 ? time : 0.0;
        year = year > 1800.0 && year < 2200.0 ? year : 0.0;

        char *id = (*results)[i][1];
        char *title = (*results)[i][5];

        char str_vote[10];
        char str_imdb[10];
        char str_time[10];
        char str_year[10];

        sprintf(str_vote, "%d", (int)vote);
        sprintf(str_imdb, "%1.2f", imdb);
        sprintf(str_time, "%d", (int)time);
        sprintf(str_year, "%d", (int)year);

        /* add text to cells */
        sprintf(temp, "%d", i);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 0, j, 
            temp);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 1, j, 
            str_imdb);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 2, j, 
            str_vote);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 3, j, 
            id);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 4, j, 
            title);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 5, j, 
            str_time);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 6, j, 
            str_year);

        /* set background colors */
        gtk_custom_table_set_cell_color(nb_tab_mymovies, 1, j, not_app);
        gtk_custom_table_set_cell_color(nb_tab_mymovies, 2, j, not_app);

        /* set cell colors for imdb and vote values */
        gtk_custom_table_set_cell_color(nb_tab_mymovies, 1, j, 
            (int)imdb == 0 ? not_app : colors[(int)imdb - 1]);
        gtk_custom_table_set_cell_color(nb_tab_mymovies, 2, j, 
            (int)vote == 0 ? not_app : colors[(int)vote - 1]);

        /* mark rated movies on top250 list */
        int index = gtk_custom_table_get_indexof(nb_tab_top250, 
            id);

        if(index >= 0) {

            /* add 'my rating' to top250 tab */
            gtk_custom_table_set_cell_text(nb_tab_top250, 2, 
                index, str_vote);

            gtk_custom_table_set_cell_color(nb_tab_top250, 2, 
                index, colors[(int)vote - 1]);
            
            allstats[0][0] += 1;
            allstats[0][1] += vote;
            allstats[0][2] += imdb;
            allstats[0][3] += time;
            allstats[0][4] += year;
        }

        /* add 'my rating' to bottom100 tab if applicable */
        index = gtk_custom_table_get_indexof(nb_tab_bot100, 
            id);

        if(index >= 0) {

            /* set cell values */
            gtk_custom_table_set_cell_text(nb_tab_bot100, 2, 
                index, str_vote);

            gtk_custom_table_set_cell_color(nb_tab_bot100, 2, 
                index, colors[(int)vote - 1]);

            allstats[1][0] += 1;
            allstats[1][1] += vote;
            allstats[1][2] += imdb;
            allstats[1][3] += time;
            allstats[1][4] += year;
        }

        /* add 'my rating' to boxoffice tab if applicable */
        index = gtk_custom_table_get_indexof(nb_tab_boxoffice, 
            id);

        if(index >= 0) {

            /* set cell values */
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, 
                index, str_imdb);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 2, 
                index, str_vote);

            /* set cell colors */
            gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, 
                index, colors[(int)imdb - 1]);
            gtk_custom_table_set_cell_color(nb_tab_boxoffice, 2, 
                index, colors[(int)vote - 1]);

            allstats[2][0] += 1;
            allstats[2][1] += vote;
            allstats[2][2] += imdb;
            allstats[2][3] += time;
            allstats[2][4] += year;
        }

        /* add 'my rating' to lists tab if applicable */
        index = gtk_custom_table_get_indexof(nb_tab_lists, 
            id);

        if(index >= 0) {

            gtk_custom_table_set_cell_text(nb_tab_lists, 2, 
                index, str_vote);
            gtk_custom_table_set_cell_color(nb_tab_lists, 2, 
                index, colors[(int)vote - 1]);
        }
    }

    /* add statistical data to allstats */
    open_allstats(allstats[0], 1, 
        gtk_custom_table_get_rows(nb_tab_top250));
    open_allstats(allstats[1], 5, 
        gtk_custom_table_get_rows(nb_tab_bot100));
    open_allstats(allstats[2], 9, 
        gtk_custom_table_get_rows(nb_tab_boxoffice));

    /* set sortable and sort by index */
    gtk_custom_table_set_sortable(nb_tab_mymovies, TRUE);
    gtk_custom_table_sort(nb_tab_mymovies, 0, GTK_CUSTOM_TABLE_ASC);
    gtk_custom_table_set_column_font(nb_tab_mymovies, 4, TEXT_FONT); 
}

