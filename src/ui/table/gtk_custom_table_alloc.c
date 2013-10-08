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


#include "gtk_custom_table.h"


/**
 * create a new custom table and setup default variables
 * @param GtkWidget *table     current table widget
 * @param int column_widths    array of column widths
 */
void gtk_custom_table_alloc(GtkWidget *table, int column_widths[]) {

    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    int rows_h = priv->table_y;
    int head_h = priv->table_has_header;
    int foot_h = priv->table_has_footer;

    int height = (rows_h + head_h + foot_h) * priv->table_row_height;

    gtk_widget_set_size_request(table, -1, height);

    int cols = priv->table_x;
    int rows = priv->table_y;

    int i = 0;
    int j = 0;
    int k = 0;

    int indices = cols * sizeof(int);

    priv->table_column_widths = malloc(indices);
    priv->table_column_index = malloc(indices);
    priv->table_column_hidden = malloc(indices);

    priv->table_column_widths_temp = malloc(indices);
    priv->table_column_offset_temp = malloc(indices + sizeof(int));

    /* setup cells, rows and columns */
    priv->table_cols = malloc(sizeof(TableCols *) * cols); 
    priv->table_rows = malloc(sizeof(TableRows *) * rows); 
    priv->table_cell = malloc(sizeof(TableCell *) * (rows * cols)); 

    int cell = 0;

    for(i = 0; i < (rows * cols); i++) {

        /* create new table cell */
        priv->table_cell[i] = malloc(sizeof(TableCell));
        priv->table_cell[i]->text = NULL;
        priv->table_cell[i]->meta = malloc(sizeof(TableMeta));
        priv->table_cell[i]->meta->font = NULL;
        priv->table_cell[i]->meta->bg_image = NULL;
        priv->table_cell[i]->meta->align = PANGO_ALIGN_NONE;
        priv->table_cell[i]->meta->format = FORMAT_NONE;
        priv->table_cell[i]->meta->graphable = FALSE;
        priv->table_cell[i]->meta->has_format = FALSE;
        priv->table_cell[i]->meta->has_bg_color = FALSE;
        priv->table_cell[i]->meta->has_bg_image = FALSE;

        for(k = 0; k < 3; k++) {
            priv->table_cell[i]->meta->graph[k] = rgb_graph[k];
            priv->table_cell[i]->meta->color[k] = rgb_cell[k];
        }
    }

    for(i = 0; i < rows; i++) {

        priv->table_rows[i] = malloc(sizeof(TableRows));
        priv->table_rows[i]->meta = malloc(sizeof(TableMeta));
        priv->table_rows[i]->meta->font = NULL;
        priv->table_rows[i]->meta->bg_image = NULL;
        priv->table_rows[i]->meta->align = PANGO_ALIGN_NONE;
        priv->table_rows[i]->meta->format = FORMAT_NONE;
        priv->table_rows[i]->meta->graphable = FALSE;
        priv->table_rows[i]->meta->has_format = FALSE;
        priv->table_rows[i]->meta->has_bg_color = FALSE;
        priv->table_rows[i]->meta->has_bg_image = FALSE;

        priv->table_rows[i]->row_genesis = i;

        for(k = 0; k < 3; k++) {
            priv->table_rows[i]->meta->graph[k] = rgb_graph[k];
            priv->table_rows[i]->meta->color[k] = rgb_cell[k];
        }

        priv->table_rows[i]->cell = malloc(sizeof(TableCell *) * cols);
        priv->table_rows[i]->priv = priv;

        for(j = 0; j < cols; j++, cell++) {
            priv->table_rows[i]->cell[j] = priv->table_cell[cell];
        }
    }

    cell = 0;

    for(i = 0; i < cols; i++) {

        priv->table_cols[i] = malloc(sizeof(TableCols));
        priv->table_cols[i]->meta = malloc(sizeof(TableMeta));
        priv->table_cols[i]->meta->font = PANGO_DEFAULT_FONT;
        priv->table_cols[i]->meta->bg_image = NULL;
        priv->table_cols[i]->meta->align = PANGO_ALIGN_RIGHT;
        priv->table_cols[i]->meta->format = FORMAT_NONE;
        priv->table_cols[i]->meta->graphable = FALSE;
        priv->table_cols[i]->meta->has_format = FALSE;
        priv->table_cols[i]->meta->has_bg_color = FALSE;
        priv->table_cols[i]->meta->has_bg_image = FALSE;

        for(k = 0; k < 3; k++) {
            priv->table_cols[i]->meta->graph[k] = rgb_graph[k];
            priv->table_cols[i]->meta->color[k] = rgb_cell[k];
        }

        priv->table_cols[i]->cell = malloc(sizeof(TableCell *) * rows);

        for(j = 0; j < rows; j++, cell++) {
            priv->table_cols[i]->cell[j] = priv->table_cell[cell % priv->table_x];
        }

        priv->table_column_widths[i] = column_widths[i];
        priv->table_column_index[i] = FALSE;
        priv->table_column_hidden[i] = FALSE;
        priv->table_column_widths_temp[i] = 0;
        priv->table_column_offset_temp[i] = 0;
    }

    priv->table_column_offset_temp[cols] = 0;
}


