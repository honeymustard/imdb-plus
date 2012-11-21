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
#include "ui/ui_set/ui_set.h"
#include "ui/ui_fill/ui_fill.h"
#include "ui/env/colors.h"
#include "ui/table/gtk_custom_table.h"


#define ROSETTE DIR_ICON "rosette_red.png"


void ui_set_tables() {
    
    int i = 0;
    int j = 0;

    char temp[10];

    /* set official lists */
    menu_signal_update_top();
    menu_signal_update_bot();
    menu_signal_update_box();

    /* set default movies and lists values */
    for(i = 0; i < 50; i++) {

        sprintf(temp, "%d", i+1);

        gtk_custom_table_set_cell_text(nb_tab_mymovies, 0, i, 
            temp);
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 1, i, 
            "0.0");
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 2, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 3, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 4, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 5, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_mymovies, 6, i, 
            "0");

        gtk_custom_table_set_cell_text(nb_tab_lists, 0, i, 
            temp);
        gtk_custom_table_set_cell_text(nb_tab_lists, 1, i, 
            "0.0");
        gtk_custom_table_set_cell_text(nb_tab_lists, 2, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_lists, 3, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_tab_lists, 4, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_tab_lists, 5, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_lists, 6, i, 
            "0");
    }

    /* set statistics table values */
    for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {

        sprintf(temp, "%d", (j + 1));

        gtk_custom_table_set_cell_text(nb_tab_statistics, 0, i, 
            temp);
        gtk_custom_table_set_cell_text(nb_tab_statistics, 1, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 2, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 3, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 4, i, 
            "0.00 %");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 5, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 6, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_tab_statistics, 7, i, 
            "0.00");

        /* set cell colors */
        gtk_custom_table_set_cell_color(nb_tab_statistics, 0, i, 
            colors[j]);
        gtk_custom_table_set_cell_color(nb_tab_statistics, 3, i, 
            graph_bg);
    }
    
    /* statistics footer */
    gtk_custom_table_set_foot_text(nb_tab_statistics, 0, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 1, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 2, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 3, 
        "");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 4, 
        "0.00 %");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 5, 
        "0");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 6, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_statistics, 7, 
        "0.00");

    gtk_custom_table_set_graph_color_col(nb_tab_statistics, 3, 
        graph_fg1);

    /* set lists statistics table values */
    for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {

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
    
    /* lists statistics footer */
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

    /* set compare statistics table values */
    for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {

        gtk_custom_table_set_cell_text(nb_tab_compare, 0, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_tab_compare, 1, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_tab_compare, 2, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_tab_compare, 3, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_compare, 4, i, 
            "0.00 %");
        gtk_custom_table_set_cell_text(nb_tab_compare, 5, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_compare, 6, i, 
            "0.00");
        gtk_custom_table_set_cell_text(nb_tab_compare, 7, i, 
            "0.00");

        /* set cell colors */
        gtk_custom_table_set_cell_color(nb_tab_compare, 3, i, 
            graph_bg);
    }
    
    /* compare statistics footer */
    gtk_custom_table_set_foot_text(nb_tab_compare, 0, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_compare, 1, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_compare, 2, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_compare, 3, 
        "");
    gtk_custom_table_set_foot_text(nb_tab_compare, 4, 
        "0.00 %");
    gtk_custom_table_set_foot_text(nb_tab_compare, 5, 
        "0");
    gtk_custom_table_set_foot_text(nb_tab_compare, 6, 
        "0.00");
    gtk_custom_table_set_foot_text(nb_tab_compare, 7, 
        "0.00");

    gtk_custom_table_set_graph_color_col(nb_tab_compare, 3, 
        graph_fg3);

    /* set all statistics table values */
    for(i = 0; i < 12; i++) {

        /* set allstats headers */
        if((i % 4) == 0) {

            for(j = 0; j < TABLE_ALLST_COLS; j++) {

                gtk_custom_table_set_cell_text(nb_tab_allstats, j, i, 
                    nb_tab_allstats_headers[j]);
                /* set row color */
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

