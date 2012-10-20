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


void ui_set_align() {
 
    gtk_custom_table_set_column_alignment(nb_tab_statistics, 1, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_statistics, 2, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_statistics, 4, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_statistics, 5, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_statistics, 6, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_statistics, 7, 
        PANGO_ALIGN_RIGHT);

    gtk_custom_table_set_column_alignment(nb_tab_lists_stats, 1, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_lists_stats, 2, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_lists_stats, 4, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_lists_stats, 5, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_lists_stats, 6, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_lists_stats, 7, 
        PANGO_ALIGN_RIGHT);

    gtk_custom_table_set_column_alignment(nb_tab_compare, 1, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_compare, 2, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_compare, 4, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_compare, 5, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_compare, 6, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_compare, 7, 
        PANGO_ALIGN_RIGHT);

    gtk_custom_table_set_column_alignment(nb_tab_allstats, 0, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_allstats, 1, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_allstats, 2, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_allstats, 4, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_allstats, 5, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_allstats, 6, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_allstats, 7, 
        PANGO_ALIGN_RIGHT);

    gtk_custom_table_set_column_alignment(nb_tab_top250, 0, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_top250, 1, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_top250, 2, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_top250, 3, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_top250, 5, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_top250, 6, 
        PANGO_ALIGN_RIGHT);

    gtk_custom_table_set_column_alignment(nb_tab_bot100, 0, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_bot100, 1, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_bot100, 2, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_bot100, 3, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_bot100, 5, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_bot100, 6, 
        PANGO_ALIGN_RIGHT);

    gtk_custom_table_set_column_alignment(nb_tab_boxoffice, 0, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_boxoffice, 1, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_boxoffice, 2, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_boxoffice, 3, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_boxoffice, 5, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_boxoffice, 6, 
        PANGO_ALIGN_RIGHT);

    gtk_custom_table_set_column_alignment(nb_tab_mymovies, 0, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_mymovies, 1, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_mymovies, 2, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_mymovies, 3, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_mymovies, 5, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_mymovies, 6, 
        PANGO_ALIGN_RIGHT);

    gtk_custom_table_set_column_alignment(nb_tab_lists, 0, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_lists, 1, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_lists, 2, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_lists, 3, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_lists, 5, 
        PANGO_ALIGN_RIGHT);
    gtk_custom_table_set_column_alignment(nb_tab_lists, 6, 
        PANGO_ALIGN_RIGHT);
}
