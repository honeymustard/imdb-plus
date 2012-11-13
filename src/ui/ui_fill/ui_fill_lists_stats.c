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


void open_list_stats(char ****results, int rows) {

    double stats[STATS_Y][STATS_X];
    double total[TOTAL_Y][TOTAL_X];

    memset(stats, 0, sizeof(stats));
    memset(total, 0, sizeof(total));

    ui_fill_stats(results, rows, stats, total, STATS_L);

    gtk_custom_table_sort(nb_tab_lists_stats, 0, 
        GTK_CUSTOM_TABLE_DESC);

    int i = 0;
    int j = 0;

    char temp[100];

    /* add statistics to widget table */
    for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {

        /* add imdb value to table */
        sprintf(temp, "%1.2f", stats[i][IMDB_AVG]);
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 0, j, 
            temp);
        
        /* add graph value to table */
        sprintf(temp, "%1.0f", stats[i][GRAPH_WIDTH]);
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 3, j, 
            temp);

        /* add percent value to table */
        sprintf(temp, "%2.2f %%", stats[i][PERCENTAGE]);
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 4, j, 
            temp);

        /* add votes value to table */
        sprintf(temp, "%1.0f", stats[i][VOTES]);
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 5, j, 
            temp);

        /* add runtime value to table */
        sprintf(temp, "%1.2f", stats[i][TIME_AVG]);
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 6, j, 
            temp);

        /* add year value to table */
        sprintf(temp, "%1.2f", stats[i][YEAR_AVG]);
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 7, j, 
            temp);

        /* add new background color to vote rating */
        gtk_custom_table_set_cell_color(nb_tab_lists_stats, 0, j, 
            colors[(int)stats[i][IMDB_AVG] > 0 ? 
                (int)stats[i][IMDB_AVG] - 1 : 0]);
    }

    /* add statistics footer vote average */
    sprintf(temp, "%2.2f", total[IMDB_TOT][0] / total[IMDB_TOT][1]);
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 0, 
        temp);

    /* add statistics footer vote info */
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 3, 
        get_global(CONST_OPEN_L));

    /* add statistics footer percent total */
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 4, 
        "100.00 %");

    /* add statistics footer votes total */
    sprintf(temp, "%d", rows - 1);
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 5, 
        temp);

    /* add statistics footer runtime average */
    sprintf(temp, "%4.2f", total[TIME_TOT][0] / total[TIME_TOT][1]);
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 6, 
        temp);

    /* add statistics footer year average */
    sprintf(temp, "%4.2f", total[YEAR_TOT][0] / total[YEAR_TOT][1]);
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 7, 
        temp);

    gtk_custom_table_set_sortable(nb_tab_lists_stats, TRUE);
}

