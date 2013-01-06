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

            for(j = 0; j < COLS_STATS_ALL; j++) {

                gtk_custom_table_set_cell_text(nb_stats_all_tab, j, i, 
                    nb_stats_all_headers[j]);

                gtk_custom_table_set_row_color(nb_stats_all_tab, i, 
                    rgb_header);
            }
        }
        else {

            gtk_custom_table_set_cell_text(nb_stats_all_tab, 0, i, 
                "0.00");
            gtk_custom_table_set_cell_text(nb_stats_all_tab, 1, i, 
                "0.00");
            gtk_custom_table_set_cell_text(nb_stats_all_tab, 2, i, 
                "0.00");
            gtk_custom_table_set_cell_text(nb_stats_all_tab, 3, i, 
                "0");
            gtk_custom_table_set_cell_text(nb_stats_all_tab, 4, i, 
                "");
            gtk_custom_table_set_cell_text(nb_stats_all_tab, 5, i, 
                "0.00 %");
            gtk_custom_table_set_cell_text(nb_stats_all_tab, 6, i, 
                "0 / 0");
            gtk_custom_table_set_cell_text(nb_stats_all_tab, 7, i, 
                "0.00");
            gtk_custom_table_set_cell_text(nb_stats_all_tab, 8, i, 
                "0.00");

            /* set cell colors */
            gtk_custom_table_set_cell_color(nb_stats_all_tab, 3, i, 
                graph_bg);

            double rank[] = {0.85, 0.20, 0.30};

            /* set cell colors */
            gtk_custom_table_set_cell_color(nb_stats_all_tab, 4, i, 
                rank);
        }

        if((i % 4) == 1) {
            gtk_custom_table_set_graph_color_cell(nb_stats_all_tab, 3, i, 
                graph_fg1);
        }

        if((i % 4) == 2) {
            gtk_custom_table_set_graph_color_cell(nb_stats_all_tab, 3, i, 
                graph_fg2);
        }

        if((i % 4) == 3) {
            gtk_custom_table_set_graph_color_cell(nb_stats_all_tab, 3, i, 
                graph_fg3);
        }
    } 

    gtk_custom_table_set_cell_text(nb_stats_all_tab, 3, 0, 
        "Top 250");
    gtk_custom_table_set_cell_text(nb_stats_all_tab, 3, 4, 
        "Bottom 100");
    gtk_custom_table_set_cell_text(nb_stats_all_tab, 3, 8, 
        "Box Office");

    gtk_custom_table_set_cell_bg_image(nb_stats_all_tab, 4, 0, 
        ROSETTE);
    gtk_custom_table_set_cell_bg_image(nb_stats_all_tab, 4, 4, 
        ROSETTE);
    gtk_custom_table_set_cell_bg_image(nb_stats_all_tab, 4, 8, 
        ROSETTE);
}


void ui_fill_stats_all_fill(Stats *s, int row1, int row2, int row3) {

    int i = 0;

    int rows[3];

    rows[0] = row1;
    rows[1] = row2;
    rows[2] = row3;

    int rows_count[3];

    rows_count[0] = gtk_custom_table_get_rows(nb_lists_top_tab);
    rows_count[1] = gtk_custom_table_get_rows(nb_lists_bot_tab);
    rows_count[2] = gtk_custom_table_get_rows(nb_lists_box_tab);

    char temp[100];

    for(i = 0; i < 3; i++) {

        /* reset background colors */
        gtk_custom_table_set_cell_color_enable(nb_stats_all_tab, 0, rows[i], 
            FALSE);
        gtk_custom_table_set_cell_color_enable(nb_stats_all_tab, 1, rows[i], 
            FALSE);
        gtk_custom_table_set_cell_color_enable(nb_stats_all_tab, 2, rows[i], 
            FALSE);

        /* set first column, vote */
        if(s->lists[i][VOTE] > 0) {

            sprintf(temp, "%1.2f", s->lists[i][VOTE]);

            gtk_custom_table_set_cell_alignment(nb_stats_all_tab, 0, rows[i], 
                PANGO_ALIGN_RIGHT);
        }
        else {

            strcpy(temp, "N/A");

            gtk_custom_table_set_cell_color(nb_stats_all_tab, 0, rows[i], 
                not_app);
            gtk_custom_table_set_cell_alignment(nb_stats_all_tab, 0, rows[i], 
                PANGO_ALIGN_CENTER);
        }

        gtk_custom_table_set_cell_text(nb_stats_all_tab, 0, rows[i], 
            temp);

        /* set second column, imdb */
        if(s->lists[i][IMDB] > 0) {

            sprintf(temp, "%1.2f", s->lists[i][IMDB]);

            gtk_custom_table_set_cell_alignment(nb_stats_all_tab, 1, rows[i], 
                PANGO_ALIGN_RIGHT);
        }
        else {

            strcpy(temp, "N/A");

            gtk_custom_table_set_cell_color(nb_stats_all_tab, 1, rows[i], 
                not_app);
            gtk_custom_table_set_cell_alignment(nb_stats_all_tab, 1, rows[i], 
                PANGO_ALIGN_CENTER);
        }

        gtk_custom_table_set_cell_text(nb_stats_all_tab, 1, rows[i], 
            temp);

        /* set third column, flux */
        if(s->lists[i][IMDB] > 0 && s->lists[i][VOTE] > 0) {

            sprintf(temp, s->lists[i][FLUX] == 0 ? "%1.2f" : "%+1.2f", 
                s->lists[i][FLUX]);

            gtk_custom_table_set_cell_alignment(nb_stats_all_tab, 2, rows[i], 
                PANGO_ALIGN_RIGHT);
        }
        else {

            strcpy(temp, "N/A");

            gtk_custom_table_set_cell_color(nb_stats_all_tab, 2, rows[i], 
                not_app);
            gtk_custom_table_set_cell_alignment(nb_stats_all_tab, 2, rows[i], 
                PANGO_ALIGN_CENTER);
        }

        gtk_custom_table_set_cell_text(nb_stats_all_tab, 2, rows[i], 
            temp);

        /* set graph width */
        sprintf(temp, "%d", (int)s->lists_cnt[i][ROWS] > 0 ? 
            (int)(100.0 / (rows_count[i] / s->lists_cnt[i][ROWS])) : 0);
        gtk_custom_table_set_cell_text(nb_stats_all_tab, 3, rows[i], 
            temp);

        /* set percentage */
        sprintf(temp, "%1.2f %%", (int)s->lists_cnt[i][ROWS] > 0 ? 
            s->lists_cnt[i][ROWS] / (rows_count[i] / 100.0) : 0.0);
        gtk_custom_table_set_cell_text(nb_stats_all_tab, 5, rows[i], 
            temp);

        /* set movies count */
        sprintf(temp, "%d/%d", (int)s->lists_cnt[i][ROWS], rows_count[i]);
        gtk_custom_table_set_cell_text(nb_stats_all_tab, 6, rows[i], 
            temp);

        /* set runtime */
        sprintf(temp, "%1.2f", s->lists[i][TIME]);
        gtk_custom_table_set_cell_text(nb_stats_all_tab, 7, rows[i], 
            temp);

        /* set year */
        sprintf(temp, "%1.2f", s->lists[i][YEAR]);
        gtk_custom_table_set_cell_text(nb_stats_all_tab, 8, rows[i], 
            temp);

        int imdb = (int)s->lists[i][IMDB];
        int vote = (int)s->lists[i][VOTE];

        /* set cell colors */
        if(s->lists[i][VOTE] > 0) {
            gtk_custom_table_set_cell_color(nb_stats_all_tab, 0, rows[i], 
                colors[vote < 10 && vote > 0 ? vote - 1 : 1 ]);
        }

        if(s->lists[i][IMDB] > 0) {
            gtk_custom_table_set_cell_color(nb_stats_all_tab, 1, rows[i], 
                colors[imdb < 10 && imdb > 0 ? imdb - 1 : 1]);
        }

        if(s->lists[i][IMDB] > 0 && s->lists[i][VOTE] > 0) {
            gtk_custom_table_set_cell_color(nb_stats_all_tab, 2, rows[i], 
                colors[s->lists[i][FLUX] > 0 ? 8 : 1]);
        }

        int cent = s->lists_cnt[i][ROWS] / (rows_count[i] / 100.0);

        char *awards[] = {
            AWARD_GOLD, 
            AWARD_SILVER, 
            AWARD_BRONZE, 
            RIBBON_GOLD, 
            RIBBON_SILVER, 
            RIBBON_BRONZE
        };

        if(cent > 0 ) {

            gtk_custom_table_set_cell_bg_image(nb_stats_all_tab, 4, rows[i], 
              cent == 100 ? awards[0] : 
              cent >= 80  ? awards[1] : 
              cent >= 60  ? awards[2] : 
              cent >= 40  ? awards[3] : 
              cent >= 20  ? awards[4] : 
              cent > 0    ? awards[5] : 
              awards[5]);
        }
    }
}

