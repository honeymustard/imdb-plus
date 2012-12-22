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


#include "globals.h"
#include "ui/ui.h"
#include "ui/env/colors.h"
#include "ui/ui_fill/ui_fill.h"
#include "ui/table/gtk_custom_table.h"


void open_list(char ****results, int rows) {

    int i = 0;
    int j = 0;

    double allstats[3][5];
    memset(allstats, 0, sizeof(allstats));

    double vote = 0;
    double imdb = 0;
    double time = 0;
    double year = 0;

    char temp[100];

    char str_imdb[10];
    char str_time[10];
    char str_year[10];

    /* update lists tab with new data */
    gtk_custom_table_resize(nb_tab_lists, -1, rows - 1);

    /* add text to widget table */
    for(i = 1, j = 0; i < rows; i++, j++) {

        /* make results numeric */
        imdb = strtod((*results)[i][8], NULL);
        time = strtol((*results)[i][9], NULL, 10);
        year = strtol((*results)[i][10], NULL, 10);

        fill_sanitize(&vote, &imdb, &time, &year);

        char *id = (*results)[i][1];
        char *title = (*results)[i][5];

        sprintf(str_imdb, "%1.1f", imdb);
        sprintf(str_time, "%d", (int)time);
        sprintf(str_year, "%d", (int)year);

        /* add text to cells */
        sprintf(temp, "%d", i);
        gtk_custom_table_set_cell_text(nb_tab_lists, 0, j, 
            temp);
        gtk_custom_table_set_cell_text(nb_tab_lists, 1, j, 
            str_imdb); 
        gtk_custom_table_set_cell_text(nb_tab_lists, 2, j, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_lists, 3, j, 
            id);
        gtk_custom_table_set_cell_text(nb_tab_lists, 4, j, 
            title);
        gtk_custom_table_set_cell_text(nb_tab_lists, 5, j, 
            str_time);
        gtk_custom_table_set_cell_text(nb_tab_lists, 6, j, 
            str_year);

        /* set background colors */
        gtk_custom_table_set_cell_color(nb_tab_lists, 1, j, 
            not_app);
        gtk_custom_table_set_cell_color(nb_tab_lists, 2, j, 
            not_app);

        /* set cell colors for imdb and vote values */
        gtk_custom_table_set_cell_color(nb_tab_lists, 1, j, 
            (int)imdb > 0 ? colors[(int)imdb - 1] : not_app);
        gtk_custom_table_set_cell_color(nb_tab_lists, 2, j, 
            not_app);

        /* add 'my rating' to lists tab if applicable */
        int index = gtk_custom_table_get_indexof(nb_tab_mymovies, 
            id);

        if(index >= 0) {
            
            char *rating = gtk_custom_table_get_cell_text(nb_tab_mymovies, 2, 
                index);

            /* add new background color to rating */
            gtk_custom_table_set_cell_text(nb_tab_lists, 2, j, 
                rating);

            gtk_custom_table_set_cell_color(nb_tab_lists, 2, j, 
                atoi(rating) > 0 ? colors[atoi(rating) - 1] : not_app);
        }

        /* add imdb-rating to boxoffice tab if applicable */
        index = gtk_custom_table_get_indexof(nb_tab_boxoffice, 
            id);

        if(index >= 0) {

            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, 
                index, str_imdb);

            gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, 
                index, colors[(int)imdb > 0 ? (int)imdb - 1 : 0]);
        }

        /* add to allstats tab if applicable */
        index = gtk_custom_table_get_indexof(nb_tab_top250, 
            id);

        if(index >= 0) {

            allstats[0][0] += 1;
            allstats[0][2] += imdb;
            allstats[0][3] += time;
            allstats[0][4] += year;
        }

        index = gtk_custom_table_get_indexof(nb_tab_bot100, 
            id);

        if(index >= 0) {

            allstats[1][0] += 1;
            allstats[1][2] += imdb;
            allstats[1][3] += time;
            allstats[1][4] += year;
        }

        index = gtk_custom_table_get_indexof(nb_tab_boxoffice, 
            id);

        if(index >= 0) {

            allstats[2][0] += 1;
            allstats[2][2] += imdb;
            allstats[2][3] += time;
            allstats[2][4] += year;
        }
    }

    /* add statistical data to allstats */
    open_allstats(allstats[0], 2, 
        gtk_custom_table_get_rows(nb_tab_top250));
    open_allstats(allstats[1], 6, 
        gtk_custom_table_get_rows(nb_tab_bot100));
    open_allstats(allstats[2], 10, 
        gtk_custom_table_get_rows(nb_tab_boxoffice));

    /* set sortable and sort by index */
    gtk_custom_table_set_sortable(nb_tab_lists, TRUE);
    gtk_custom_table_sort(nb_tab_lists, 0, GTK_CUSTOM_TABLE_ASC);
    gtk_custom_table_set_column_font(nb_tab_lists, 4, TEXT_FONT); 
}

