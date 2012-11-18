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
#include "../../colors.h"
#include "../../main.h"


/* add values to allstats tab */
void open_allstats(double allstats[5], int row, int rows) {

    char temp[100];

    double vote_avg = allstats[1] / allstats[0];
    double imdb_avg = allstats[2] / allstats[0];
    double flux_avg = vote_avg - imdb_avg;

    /* reset background colors */
    gtk_custom_table_set_cell_color_enable(nb_tab_allstats, 0, row, 
        FALSE);
    gtk_custom_table_set_cell_color_enable(nb_tab_allstats, 1, row, 
        FALSE);
    gtk_custom_table_set_cell_color_enable(nb_tab_allstats, 2, row, 
        FALSE);

    /* set second column, imdb */
    if(imdb_avg > 0) {

        sprintf(temp, "%1.2f", imdb_avg);

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

    /* set first column, vote */
    if(vote_avg > 0.0) {

        sprintf(temp, "%1.2f", vote_avg);

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
    if(allstats[1] > 0 && allstats[2] > 0) {

        sprintf(temp, flux_avg == 0 ? "%1.2f" : "%+1.2f", flux_avg);

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

    sprintf(temp, "%d", (int)allstats[0] > 0 ? 
        (int)(100.0 / (rows / allstats[0])) : 0);
    gtk_custom_table_set_cell_text(nb_tab_allstats, 3, row, 
        temp);

    sprintf(temp, "%1.2f %%", (int)allstats[0] > 0 ? 
        allstats[0] / (rows / 100.0) : 0.0);
    gtk_custom_table_set_cell_text(nb_tab_allstats, 5, row, 
        temp);

    sprintf(temp, "%d/%d", (int)allstats[0], rows);
    gtk_custom_table_set_cell_text(nb_tab_allstats, 6, row, 
        temp);

    sprintf(temp, "%1.2f", (int)allstats[0] > 0 ?
        allstats[3] / allstats[0] : 0.0);
    gtk_custom_table_set_cell_text(nb_tab_allstats, 7, row, 
        temp);

    sprintf(temp, "%1.2f", (int)allstats[0] > 0 ? 
        allstats[4] / allstats[0] : 0.0);
    gtk_custom_table_set_cell_text(nb_tab_allstats, 8, row, 
        temp);

    int imdb = (int)imdb_avg;
    int vote = (int)vote_avg;

    if(imdb_avg > 0.0) {
        gtk_custom_table_set_cell_color(nb_tab_allstats, 0, row, 
            colors[imdb < 10 && imdb > 0 ? imdb - 1 : 1]);
    }

    if(vote_avg > 0.0) {
        gtk_custom_table_set_cell_color(nb_tab_allstats, 1, row, 
            colors[vote < 10 && vote > 0 ? vote - 1 : 1 ]);
    }

    if(allstats[1] > 0.0 && allstats[2] > 0.0) {
        gtk_custom_table_set_cell_color(nb_tab_allstats, 2, row, 
            colors[flux_avg > 0 ? 8 : 1]);
    }

    int cent = allstats[0] / (rows / 100.0);

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


