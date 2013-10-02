/***********************************************************************
 *
 * Copyright (C) 2011-2013  Adrian Solumsmo
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/


#include "ui/widgets/widgets.h"
#include "ui/widgets/fill/fill.h"
#include "ui/env/colors.h"
#include "ui/table/gtk_custom_table.h"


void ui_fill_stats_cmp_empty() {

    int i = 0;
    int j = 0;
    
    char temp[10];

    for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {

        sprintf(temp, "%d", (j + 1));

        gtk_custom_table_set_cell_text(nb_stats_cmp_tab->table, 0, i, 
            temp);
        gtk_custom_table_set_cell_text(nb_stats_cmp_tab->table, 1, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_stats_cmp_tab->table, 2, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_stats_cmp_tab->table, 3, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_stats_cmp_tab->table, 4, i, 
            "0.00 %");
        gtk_custom_table_set_cell_text(nb_stats_cmp_tab->table, 5, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_stats_cmp_tab->table, 6, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_stats_cmp_tab->table, 7, i, 
            "0.00");

        /* set cell colors */
        gtk_custom_table_set_cell_color(nb_stats_cmp_tab->table, 0, i, 
            colors[j]);
        gtk_custom_table_set_cell_color(nb_stats_cmp_tab->table, 3, i, 
            graph_bg);
    }
    
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 0, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 1, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 2, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 3, 
        "");
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 4, 
        "0.00 %");
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 5, 
        "0");
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 6, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 7, 
        "0.00");

    gtk_custom_table_set_graph_color_col(nb_stats_cmp_tab->table, 3, 
        graph_fg3);
}


void ui_fill_stats_cmp(Stats *s) {

    gtk_custom_table_sort(nb_stats_cmp_tab->table, 0, 
        GTK_CUSTOM_TABLE_DESC);

    int i = 0;
    int j = 0;

    char temp[100];

    for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {
        
        /* add imdb value to table */
        double imdb = s->stats[i][IMDB] > 0 ?  
            s->stats[i][IMDB] : i;

        sprintf(temp, "%1.2f", imdb);
        gtk_custom_table_set_cell_text(nb_stats_cmp_tab->table, 1, j, 
            temp);

        /* add flux value to table */
        sprintf(temp, s->stats[i][FLUX] == 0.0 ? 
            "%1.2f" : "%+1.2f", s->stats[i][FLUX]);
        gtk_custom_table_set_cell_text(nb_stats_cmp_tab->table, 2, j, 
            temp);

        /* add graph value to table */
        sprintf(temp, "%1.0f", s->graph[i][SIZE]);
        gtk_custom_table_set_cell_text(nb_stats_cmp_tab->table, 3, j, 
            temp);

        /* add percent value to table */
        sprintf(temp, "%2.2f %%", s->graph[i][CENT]);
        gtk_custom_table_set_cell_text(nb_stats_cmp_tab->table, 4, j, 
            temp);

        /* add votes value to table */
        sprintf(temp, "%1.0f", s->stats_cnt[i][ROWS]);
        gtk_custom_table_set_cell_text(nb_stats_cmp_tab->table, 5, j, 
            temp);

        /* add runtime value to table */
        sprintf(temp, "%1.2f", s->stats[i][TIME]);
        gtk_custom_table_set_cell_text(nb_stats_cmp_tab->table, 6, j, 
            temp);

        /* add year value to table */
        sprintf(temp, "%1.2f", s->stats[i][YEAR]);
        gtk_custom_table_set_cell_text(nb_stats_cmp_tab->table, 7, j, 
            temp);

        gtk_custom_table_set_cell_color(nb_stats_cmp_tab->table, 1, j, 
            colors[(int)imdb]);

        /* add new background color to flux */
        gtk_custom_table_set_cell_color(nb_stats_cmp_tab->table, 2, j, 
            colors[s->stats[i][FLUX] > 0 ? 8 : 1]);
    }

    /* add statistics footer vote average */
    sprintf(temp, "%2.2f", s->total[VOTE]);
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 0, 
        temp);

    /* add statistics footer imdb average */
    sprintf(temp, "%2.2f", s->total[IMDB]);
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 1, 
        temp);

    /* add statistics footer flux average */
    sprintf(temp, "%+2.2f", s->total[FLUX]);
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 2, 
        temp);

    /* add statistics footer vote info */
    sprintf(temp, "%d movies intersect", (int)s->total[ROWS]);
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 3, 
        temp);

    /* add statistics footer percent total */
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 4, 
        "100.00 %");

    /* add statistics footer votes total */
    sprintf(temp, "%d", (int)s->total[ROWS]);
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 5, 
        temp);

    /* add statistics footer runtime average */
    sprintf(temp, "%4.2f", s->total[TIME]);
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 6, 
        temp);

    /* add statistics footer year average */
    sprintf(temp, "%4.2f", s->total[YEAR]);
    gtk_custom_table_set_foot_text(nb_stats_cmp_tab->table, 7, 
        temp);

    gtk_custom_table_set_sortable(nb_stats_cmp_tab->table, TRUE);
}

