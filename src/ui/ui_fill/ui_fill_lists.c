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


void open_list(char ****results, int rows) {

    int i = 0;
    int j = 0;

    gtk_custom_table_set_column_font(nb_tab_lists, 4, "sans 10"); 

    double allstats[3][5];
    memset(allstats, '\0', sizeof(allstats));

    char temp[100];

    rows = rows - 1;

    gtk_custom_table_set_sortable(nb_tab_lists_stats, TRUE);

    /* update lists tab with new data */
    gtk_custom_table_resize(nb_tab_lists, -1, rows);

    memset(allstats, '\0', sizeof(allstats)); 

    /* add text to widget table */
    for(i = 1, j = 0; i <= rows; i++, j++) {

        sprintf(temp, "%d", i);

        gtk_custom_table_set_cell_text(nb_tab_lists, 0, j, 
            temp);
        gtk_custom_table_set_cell_text(nb_tab_lists, 1, j, 
            (*results)[i][8]); 
        gtk_custom_table_set_cell_text(nb_tab_lists, 2, j, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_lists, 3, j, 
            (*results)[i][1]);
        gtk_custom_table_set_cell_text(nb_tab_lists, 4, j, 
            (*results)[i][5]);
        gtk_custom_table_set_cell_text(nb_tab_lists, 5, j, 
            (*results)[i][9]);
        gtk_custom_table_set_cell_text(nb_tab_lists, 6, j, 
            (*results)[i][10]);

        /* reset background colors */
        gtk_custom_table_set_cell_color_enable(nb_tab_lists, 1, j, 
            FALSE);
        gtk_custom_table_set_cell_color_enable(nb_tab_lists, 2, j, 
            FALSE);

        /* add new background color to rating */
        int rating = (int)atoi((*results)[i][8]);
        int rating_color = rating <= 10 && rating > 0 ? rating : 0;

        gtk_custom_table_set_cell_color(nb_tab_lists, 1, j, 
            rating_color == 0 ? not_app : colors[rating_color - 1]);

        /* add 'my rating' to lists tab if applicable */
        int index = gtk_custom_table_get_indexof(nb_tab_mymovies, 
            (*results)[i][1]);

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
            (*results)[i][1]);

        if(index >= 0) {

            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, index, 
                (*results)[i][8]);

            gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, 
                index, colors[rating_color]);
        }

        /* add to allstats tab if applicable */
        index = gtk_custom_table_get_indexof(nb_tab_top250, 
            (*results)[i][1]);

        if(index >= 0) {

            allstats[0][0] += 1;
            allstats[0][2] += atof((*results)[i][8]);
            allstats[0][3] += atof((*results)[i][9]);
            allstats[0][4] += atof((*results)[i][10]);
        }

        index = gtk_custom_table_get_indexof(nb_tab_bot100, 
            (*results)[i][1]);

        if(index >= 0) {

            allstats[1][0] += 1;
            allstats[1][2] += atof((*results)[i][8]);
            allstats[1][3] += atof((*results)[i][9]);
            allstats[1][4] += atof((*results)[i][10]);
        }

        index = gtk_custom_table_get_indexof(nb_tab_boxoffice, 
            (*results)[i][1]);

        if(index >= 0) {

            allstats[2][0] += 1;
            allstats[2][2] += atof((*results)[i][8]);
            allstats[2][3] += atof((*results)[i][9]);
            allstats[2][4] += atof((*results)[i][10]);
        }
    }

    open_allstats(allstats[0], 2, 
        gtk_custom_table_get_rows(nb_tab_top250));
    open_allstats(allstats[1], 6, 
        gtk_custom_table_get_rows(nb_tab_bot100));
    open_allstats(allstats[2], 10, 
        gtk_custom_table_get_rows(nb_tab_boxoffice));

    /* set sortable and sort by index */
    gtk_custom_table_set_sortable(nb_tab_lists, TRUE);
    gtk_custom_table_sort(nb_tab_lists, 0, GTK_CUSTOM_TABLE_ASC);
}

