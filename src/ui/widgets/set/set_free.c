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


#include "ui/globals/globals.h"
#include "ui/widgets/widgets.h"
#include "ui/table/gtk_custom_table.h"


void ui_set_free() {

    gtk_custom_table_sort(nb_lists_box_tab->table, 0, GTK_CUSTOM_TABLE_ASC);

    /* write boxoffice values back to file */ 
    FILE *fp_out = fopen(globals_get(CONST_BOX_CSV), "wb");
    
    int i = 0;
    int j = 0;

    int cols = gtk_custom_table_get_cols(nb_lists_box_tab->table);
    int rows = gtk_custom_table_get_rows(nb_lists_box_tab->table);

    for(i = 0; i < rows; i++) {

        for(j = 0; j < cols; j++) {

            /* skip columns not represented in file */
            if(j == 1 || j == 2 || j == 3) {
                continue;
            }

            fprintf(fp_out, "\"%s\",", 
                gtk_custom_table_get_cell_text(nb_lists_box_tab->table, j, i));
        }

        fprintf(fp_out, "\"%s\"\n", 
            gtk_custom_table_get_cell_text(nb_lists_box_tab->table, 1, i));
    }

    fclose(fp_out);

    /* free data from tables */
    gtk_custom_table_free(nb_stats_mov_tab->table);
    gtk_custom_table_free(nb_stats_lst_tab->table);
    gtk_custom_table_free(nb_stats_cmp_tab->table);
    gtk_custom_table_free(nb_stats_all_tab->table);
    gtk_custom_table_free(nb_lists_mov_tab->table);
    gtk_custom_table_free(nb_lists_lst_tab->table);
    gtk_custom_table_free(nb_lists_cmp_tab->table);
    gtk_custom_table_free(nb_lists_top_tab->table);
    gtk_custom_table_free(nb_lists_bot_tab->table);
    gtk_custom_table_free(nb_lists_box_tab->table);
}

