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


void ui_fill_stats_lst_empty() {
    
    int i = 0;

    for(i = 0; i < 10; i++) {

        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 0, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 1, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 2, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 3, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 4, i, 
            "0.00 %");
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 5, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 6, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 7, i, 
            "0.00");

        /* set cell colors */
        gtk_custom_table_set_cell_color(nb_tab_lists_stats, 3, i, 
            graph_bg);
    }
    
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 0, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 1, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 2, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 3, 
        "");
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 4, 
        "0.00 %");
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 5, 
        "0");
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 6, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 7, 
        "0.00");

    gtk_custom_table_set_graph_color_col(nb_tab_lists_stats, 3, 
        graph_fg2);
}


void ui_fill_stats_lst_fill(Stats *s, int rows) {

    gtk_custom_table_sort(nb_tab_lists_stats, 0, 
        GTK_CUSTOM_TABLE_DESC);

    int i = 0;
    int j = 0;

    char temp[100];

    for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {

        /* add imdb value to table */
        double imdb = s->stats[i][IMDB] > 0 ?  
            s->stats[i][IMDB] : i + 1;

        sprintf(temp, "%1.2f", imdb);
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 0, j, 
            temp);
        
        /* add graph value to table */
        sprintf(temp, "%1.0f", s->graph[i][SIZE]);
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 3, j, 
            temp);

        /* add percent value to table */
        sprintf(temp, "%2.2f %%", s->graph[i][CENT]);
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 4, j, 
            temp);

        /* add votes value to table */
        sprintf(temp, "%1.0f", s->stats_cnt[i][IMDB]);
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 5, j, 
            temp);

        /* add runtime value to table */
        sprintf(temp, "%1.2f", s->stats[i][TIME]);
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 6, j, 
            temp);

        /* add year value to table */
        sprintf(temp, "%1.2f", s->stats[i][YEAR]);
        gtk_custom_table_set_cell_text(nb_tab_lists_stats, 7, j, 
            temp);

        /* add new background color to vote rating */
        double fraction = imdb - (int)imdb;

        gtk_custom_table_set_cell_color(nb_tab_lists_stats, 0, j, 
            colors[(int)(fraction > 0.5 ? imdb + fraction : imdb) - 1]);
    }

    /* add statistics footer vote average */
    sprintf(temp, "%2.2f", s->total[IMDB]);
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
    sprintf(temp, "%4.2f", s->total[TIME]);
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 6, 
        temp);

    /* add statistics footer year average */
    sprintf(temp, "%4.2f", s->total[YEAR]);
    gtk_custom_table_set_foot_text(nb_tab_lists_stats, 7, 
        temp);

    gtk_custom_table_set_sortable(nb_tab_lists_stats, TRUE);
}

