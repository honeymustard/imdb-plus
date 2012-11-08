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


#include "ui.h"


void ui_set_destroy() {

    /* write boxoffice values back to file */ 
    FILE *fp_out = fopen(get_global(CONST_BOX_CSV), "wb");
    
    int i = 0;
    int j = 0;

    int cols = gtk_custom_table_get_cols(nb_tab_boxoffice);
    int rows = gtk_custom_table_get_rows(nb_tab_boxoffice);

    for(i = 0; i < rows; i++) {

        char **results = NULL;
        gtk_custom_table_get_row(nb_tab_boxoffice, i, &results);

        for(j = 0; j < cols; j++) {

            if(j == 1 || j == 2) {
                continue;
            }

            fprintf(fp_out, "\"%s\",", results[j]);
        }

        fprintf(fp_out, "\"%s\"\n", results[1]);

        /* free temporary memory */
        for(j = 0; j < cols; j++) {
            free(results[j]);
        }

        free(results);
    }

    fclose(fp_out);

    /* free table memory explicitly */
    gtk_custom_table_free(nb_tab_statistics);
    gtk_custom_table_free(nb_tab_mymovies);
    gtk_custom_table_free(nb_tab_lists_stats);
    gtk_custom_table_free(nb_tab_lists);
    gtk_custom_table_free(nb_tab_compare);
    gtk_custom_table_free(nb_tab_top250);
    gtk_custom_table_free(nb_tab_bot100);
    gtk_custom_table_free(nb_tab_boxoffice);
}

