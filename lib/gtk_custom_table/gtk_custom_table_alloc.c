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

#include "gtk_custom_table.h"


/**
 * create a new custom table and setup default variables
 * @param GtkWidget *table    current table widget
 * @param int cols            amount of table cols
 * @param int rows            amount of table rows
 */
void gtk_custom_table_alloc(GtkCustomTablePrivate *priv, int cols, int rows, 
        int column_widths[]) {

    priv->table_x = cols;
    priv->table_y = rows;

    int i = 0;
    int j = 0;

    priv->table_column_widths = malloc(cols * sizeof(int));
    priv->table_column_index = malloc(cols * sizeof(int));
    priv->table_column_hidden = malloc(cols * sizeof(int));

    priv->table_column_widths_temp = malloc(cols * sizeof(int));
    priv->table_column_offset_temp = malloc((cols + 1) * sizeof(int));

    /* setup cells, rows and columns */
    priv->table_cols = malloc(sizeof(struct table_cols *) * cols); 
    priv->table_rows = malloc(sizeof(struct table_rows *) * rows); 
    priv->table_cell = malloc(sizeof(struct table_cell *) * (rows * cols)); 

    int cell = 0;

    for(i = 0; i < (rows * cols); i++) {

        /* create new table cell */
        priv->table_cell[i] = malloc(sizeof (struct table_cell));
        priv->table_cell[i]->text = NULL;
        priv->table_cell[i]->meta = NULL;
    }

    for(i = 0; i < rows; i++) {

        priv->table_rows[i] = malloc(sizeof (struct table_rows));
        priv->table_rows[i]->meta = NULL;
        priv->table_rows[i]->cell = malloc(sizeof (struct table_cell *) * cols);
        priv->table_rows[i]->priv = priv;

        for(j = 0; j < cols; j++) {
            priv->table_rows[i]->cell[j] = priv->table_cell[cell++];
        }
    }

    cell = 0;

    for(i = 0; i < cols; i++) {

        priv->table_cols[i] = malloc(sizeof (struct table_cols));
        priv->table_cols[i]->meta = NULL;
        priv->table_cols[i]->cell = malloc(sizeof (struct table_cell *) * rows);

        for(j = 0; j < rows; j++) {
            priv->table_cols[i]->cell[j] = priv->table_cell[cell++];
        }

        priv->table_column_widths[i] = column_widths[i];
        priv->table_column_index[i] = FALSE;
        priv->table_column_hidden[i] = FALSE;
        priv->table_column_widths_temp[i] = 0;
        priv->table_column_offset_temp[i] = 0;
    }

    priv->table_column_offset_temp[cols] = 0;
}


