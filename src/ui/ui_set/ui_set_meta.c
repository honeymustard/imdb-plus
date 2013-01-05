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
    gtk_custom_table_set_column_prime(nb_tab_mymovies, 3, 
        TRUE);
    gtk_custom_table_set_column_prime(nb_tab_lists, 3, 
        TRUE);
    gtk_custom_table_set_column_prime(nb_tab_lists_cmp, 3, 
        TRUE);
    gtk_custom_table_set_column_prime(nb_tab_top250, 3, 
        TRUE);
    gtk_custom_table_set_column_prime(nb_tab_bot100, 3, 
        TRUE);
    gtk_custom_table_set_column_prime(nb_tab_boxoffice, 3, 
        TRUE);

    /* mark a column as being a graph */
    gtk_custom_table_set_column_graph(nb_tab_statistics, 3, 
        TRUE);
    gtk_custom_table_set_column_graph(nb_tab_lists_stats, 3, 
        TRUE);
    gtk_custom_table_set_column_graph(nb_tab_compare, 3, 
        TRUE);
    gtk_custom_table_set_column_graph(nb_tab_allstats, 3, 
        TRUE);

    /* set automatic column numbering */
    gtk_custom_table_set_column_index(nb_tab_mymovies, 0, 
        TRUE);
    gtk_custom_table_set_column_index(nb_tab_lists, 0, 
        TRUE);
    gtk_custom_table_set_column_index(nb_tab_lists_cmp, 0, 
        TRUE);

    /* override default font */
    gtk_custom_table_set_foot_cell_font(nb_tab_statistics, 3, 
        TEXT_FONT); 
    gtk_custom_table_set_foot_cell_font(nb_tab_lists_stats, 3, 
        TEXT_FONT); 
    gtk_custom_table_set_foot_cell_font(nb_tab_compare, 3, 
        TEXT_FONT); 
 
    /* set font alignments */
    gtk_custom_table_set_column_alignment(nb_tab_statistics, 3, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_tab_lists_stats, 3, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_tab_compare, 3, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_tab_allstats, 3, 
        PANGO_ALIGN_LEFT);

    gtk_custom_table_set_column_alignment(nb_tab_top250, 4, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_tab_bot100, 4, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_tab_boxoffice, 4, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_tab_mymovies, 4, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_tab_lists, 4, 
        PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(nb_tab_lists_cmp, 4, 
        PANGO_ALIGN_LEFT);
}

