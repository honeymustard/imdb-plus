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


#include "ui/ui.h"
#include "ui/table/gtk_custom_table.h"


void ui_set_meta() {

    /* set primary columns to enable quick searches */
    gtk_custom_table_set_column_prime(nb_lists_mov_tab, 3, 
        TRUE);
    gtk_custom_table_set_column_prime(nb_lists_lst_tab, 3, 
        TRUE);
    gtk_custom_table_set_column_prime(nb_lists_cmp_tab, 3, 
        TRUE);
    gtk_custom_table_set_column_prime(nb_lists_top_tab, 3, 
        TRUE);
    gtk_custom_table_set_column_prime(nb_lists_bot_tab, 3, 
        TRUE);
    gtk_custom_table_set_column_prime(nb_lists_box_tab, 3, 
        TRUE);

    /* mark a column as being a graph */
    gtk_custom_table_set_column_graph(nb_stats_mov_tab, 3, 
        TRUE);
    gtk_custom_table_set_column_graph(nb_stats_lst_tab, 3, 
        TRUE);
    gtk_custom_table_set_column_graph(nb_stats_cmp_tab, 3, 
        TRUE);
    gtk_custom_table_set_column_graph(nb_stats_all_tab, 3, 
        TRUE);

    /* set automatic column numbering */
    gtk_custom_table_set_column_index(nb_lists_mov_tab, 0, 
        TRUE);
    gtk_custom_table_set_column_index(nb_lists_lst_tab, 0, 
        TRUE);
    gtk_custom_table_set_column_index(nb_lists_cmp_tab, 0, 
        TRUE);

    /* override default font */
    gtk_custom_table_set_foot_cell_font(nb_stats_mov_tab, 3, 
        TEXT_FONT); 
    gtk_custom_table_set_foot_cell_font(nb_stats_lst_tab, 3, 
        TEXT_FONT); 
    gtk_custom_table_set_foot_cell_font(nb_stats_cmp_tab, 3, 
        TEXT_FONT); 
 
    /* set font alignments */
    gtk_custom_table_set_column_alignment(nb_stats_mov_tab, 3, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_stats_lst_tab, 3, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_stats_cmp_tab, 3, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_stats_all_tab, 3, 
        PANGO_ALIGN_LEFT);

    gtk_custom_table_set_column_alignment(nb_lists_mov_tab, 4, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_lists_lst_tab, 4, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_lists_cmp_tab, 4, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_lists_top_tab, 4, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_lists_bot_tab, 4, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_lists_box_tab, 4, 
        PANGO_ALIGN_LEFT);
}

