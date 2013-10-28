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
#include "ui/table/gtk_custom_table.h"


void ui_set_meta() {

    /* make some aliases */
    GtkWidget *mov_s = nb_stats_mov_tab->table;
    GtkWidget *lst_s = nb_stats_lst_tab->table;
    GtkWidget *cmp_s = nb_stats_cmp_tab->table;
    GtkWidget *all_s = nb_stats_all_tab->table;
    GtkWidget *mov_l = nb_lists_mov_tab->table;
    GtkWidget *lst_l = nb_lists_lst_tab->table;
    GtkWidget *cmp_l = nb_lists_cmp_tab->table;
    GtkWidget *top_l = nb_lists_top_tab->table;
    GtkWidget *bot_l = nb_lists_bot_tab->table;
    GtkWidget *box_l = nb_lists_box_tab->table;

    /* set primary columns to enable quick searches */
    gtk_custom_table_set_column_prime(mov_l, 4, TRUE);
    gtk_custom_table_set_column_prime(lst_l, 4, TRUE);
    gtk_custom_table_set_column_prime(cmp_l, 4, TRUE);
    gtk_custom_table_set_column_prime(top_l, 4, TRUE);
    gtk_custom_table_set_column_prime(bot_l, 4, TRUE);
    gtk_custom_table_set_column_prime(box_l, 4, TRUE);

    /* mark a column as being a graph */
    gtk_custom_table_set_column_graph(mov_s, 3, TRUE);
    gtk_custom_table_set_column_graph(lst_s, 3, TRUE);
    gtk_custom_table_set_column_graph(cmp_s, 3, TRUE);
    gtk_custom_table_set_column_graph(all_s, 3, TRUE);

    /* set automatic column numbering */
    gtk_custom_table_set_column_index(mov_l, 0, TRUE);
    gtk_custom_table_set_column_index(lst_l, 0, TRUE);
    gtk_custom_table_set_column_index(cmp_l, 0, TRUE);

    /* override default font */
    gtk_custom_table_set_foot_cell_font(mov_s, 5, PANGO_CONTENT_FONT); 
    gtk_custom_table_set_foot_cell_font(lst_s, 5, PANGO_CONTENT_FONT); 
    gtk_custom_table_set_foot_cell_font(cmp_s, 5, PANGO_CONTENT_FONT); 
 
    /* set font alignments */
    gtk_custom_table_set_column_alignment(mov_s, 3, PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(lst_s, 3, PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(cmp_s, 3, PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(all_s, 3, PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(mov_l, 5, PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(lst_l, 5, PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(cmp_l, 5, PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(top_l, 5, PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(bot_l, 5, PANGO_ALIGN_LEFT);
    gtk_custom_table_set_column_alignment(box_l, 5, PANGO_ALIGN_LEFT);

    /* set sort types */
    gtk_custom_table_set_column_format(mov_s, 2, FORMAT_INTEGER_SIGNED);
    gtk_custom_table_set_column_format(lst_s, 2, FORMAT_INTEGER_SIGNED);
    gtk_custom_table_set_column_format(cmp_s, 2, FORMAT_INTEGER_SIGNED);
    gtk_custom_table_set_column_format(all_s, 2, FORMAT_INTEGER_SIGNED);
    gtk_custom_table_set_column_format(top_l, 7, FORMAT_INTEGER_UNSIGNED);
    gtk_custom_table_set_column_format(bot_l, 7, FORMAT_INTEGER_UNSIGNED);
    gtk_custom_table_set_column_format(box_l, 7, FORMAT_INTEGER_UNSIGNED);
}

