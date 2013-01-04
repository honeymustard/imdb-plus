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


#include "main.h"
#include "ui/ui.h"
#include "ui/ui_fill/ui_fill.h"
#include "ui/ui_set/ui_set.h"
#include "ui/env/colors.h"
#include "ui/table/gtk_custom_table.h"


#define ROSETTE DIR_ICON "rosette_red.png"


void ui_fill_stats_all_empty() {

    int i = 0;
    int j = 0;

    /* set all statistics table values */
    for(i = 0; i < 12; i++) {

        /* set allstats headers */
        if((i % 4) == 0) {

            for(j = 0; j < TABLE_ALLST_COLS; j++) {

                gtk_custom_table_set_cell_text(nb_tab_allstats, j, i, 
                    nb_tab_allstats_headers[j]);

                gtk_custom_table_set_row_color(nb_tab_allstats, i, 
                    rgb_header);
            }
        }
        else {

            gtk_custom_table_set_cell_text(nb_tab_allstats, 0, i, 
                "0.00");
            gtk_custom_table_set_cell_text(nb_tab_allstats, 1, i, 
                "0.00");
            gtk_custom_table_set_cell_text(nb_tab_allstats, 2, i, 
                "0.00");
            gtk_custom_table_set_cell_text(nb_tab_allstats, 3, i, 
                "0");
            gtk_custom_table_set_cell_text(nb_tab_allstats, 4, i, 
                "");
            gtk_custom_table_set_cell_text(nb_tab_allstats, 5, i, 
                "0.00 %");
            gtk_custom_table_set_cell_text(nb_tab_allstats, 6, i, 
                "0 / 0");
            gtk_custom_table_set_cell_text(nb_tab_allstats, 7, i, 
                "0.00");
            gtk_custom_table_set_cell_text(nb_tab_allstats, 8, i, 
                "0.00");

            /* set cell colors */
            gtk_custom_table_set_cell_color(nb_tab_allstats, 3, i, 
                graph_bg);

            double rank[] = {0.85, 0.20, 0.30};

            /* set cell colors */
            gtk_custom_table_set_cell_color(nb_tab_allstats, 4, i, 
                rank);
        }

        if((i % 4) == 1) {
            gtk_custom_table_set_graph_color_cell(nb_tab_allstats, 3, i, 
                graph_fg1);
        }

        if((i % 4) == 2) {
            gtk_custom_table_set_graph_color_cell(nb_tab_allstats, 3, i, 
                graph_fg2);
        }

        if((i % 4) == 3) {
            gtk_custom_table_set_graph_color_cell(nb_tab_allstats, 3, i, 
                graph_fg3);
        }
    } 

    gtk_custom_table_set_cell_text(nb_tab_allstats, 3, 0, 
        "Top 250");
    gtk_custom_table_set_cell_text(nb_tab_allstats, 3, 4, 
        "Bottom 100");
    gtk_custom_table_set_cell_text(nb_tab_allstats, 3, 8, 
        "Box Office");

    gtk_custom_table_set_cell_bg_image(nb_tab_allstats, 4, 0, 
        ROSETTE);
    gtk_custom_table_set_cell_bg_image(nb_tab_allstats, 4, 4, 
        ROSETTE);
    gtk_custom_table_set_cell_bg_image(nb_tab_allstats, 4, 8, 
        ROSETTE);
}


void ui_fill_stats_all_fill(Stats *s, int rows, int key, int row) {

    char temp[100];

    /* reset background colors */
    gtk_custom_table_set_cell_color_enable(nb_tab_allstats, 0, row, 
        FALSE);
    gtk_custom_table_set_cell_color_enable(nb_tab_allstats, 1, row, 
        FALSE);
    gtk_custom_table_set_cell_color_enable(nb_tab_allstats, 2, row, 
        FALSE);

    /* set first column, imdb */
    if(s->lists[key][IMDB] > 0) {

        sprintf(temp, "%1.2f", s->lists[key][IMDB]);

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

    /* set second column, vote */
    if(s->lists[key][VOTE] > 0) {

        sprintf(temp, "%1.2f", s->lists[key][VOTE]);

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
    if(s->lists[key][IMDB] > 0 && s->lists[key][VOTE] > 0) {

        sprintf(temp, s->lists[key][FLUX] == 0 ? "%1.2f" : "%+1.2f", 
            s->lists[key][FLUX]);

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

    /* set graph width */
    sprintf(temp, "%d", (int)s->lists_cnt[key][ROWS] > 0 ? 
        (int)(100.0 / (rows / s->lists_cnt[key][ROWS])) : 0);
    gtk_custom_table_set_cell_text(nb_tab_allstats, 3, row, 
        temp);

    /* set percentage */
    sprintf(temp, "%1.2f %%", (int)s->lists_cnt[key][ROWS] > 0 ? 
        s->lists_cnt[key][ROWS] / (rows / 100.0) : 0.0);
    gtk_custom_table_set_cell_text(nb_tab_allstats, 5, row, 
        temp);

    /* set movies count */
    sprintf(temp, "%d/%d", (int)s->lists_cnt[key][ROWS], rows);
    gtk_custom_table_set_cell_text(nb_tab_allstats, 6, row, 
        temp);

    /* set runtime */
    sprintf(temp, "%1.2f", s->lists[key][TIME]);
    gtk_custom_table_set_cell_text(nb_tab_allstats, 7, row, 
        temp);

    /* set year */
    sprintf(temp, "%1.2f", s->lists[key][YEAR]);
    gtk_custom_table_set_cell_text(nb_tab_allstats, 8, row, 
        temp);

    int imdb = (int)s->lists[key][IMDB];
    int vote = (int)s->lists[key][VOTE];

    if(s->lists[key][IMDB] > 0) {
        gtk_custom_table_set_cell_color(nb_tab_allstats, 0, row, 
            colors[imdb < 10 && imdb > 0 ? imdb - 1 : 1]);
    }

    if(s->lists[key][VOTE] > 0) {
        gtk_custom_table_set_cell_color(nb_tab_allstats, 1, row, 
            colors[vote < 10 && vote > 0 ? vote - 1 : 1 ]);
    }

    if(s->lists[key][IMDB] > 0 && s->lists[key][VOTE] > 0) {
        gtk_custom_table_set_cell_color(nb_tab_allstats, 2, row, 
            colors[s->lists[key][FLUX] > 0 ? 8 : 1]);
    }

    int cent = s->lists_cnt[key][ROWS] / (rows / 100.0);

    char *awards[] = {
        AWARD_GOLD, 
        AWARD_SILVER, 
        AWARD_BRONZE, 
        RIBBON_GOLD, 
        RIBBON_SILVER, 
        RIBBON_BRONZE
    };

    if(cent > 0 ) {

        gtk_custom_table_set_cell_bg_image(nb_tab_allstats, 4, row, 
          cent == 100 ? awards[0] : 
          cent >= 80  ? awards[1] : 
          cent >= 60  ? awards[2] : 
          cent >= 40  ? awards[3] : 
          cent >= 20  ? awards[4] : 
          cent > 0    ? awards[5] : 
          awards[5]);
    }
}

