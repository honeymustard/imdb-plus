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
 * resize existing table to an arbitrary size
 * @param GtkWidget *table    table to be resized
 * @param int cols            amount of cols
 * @param int rows            amount of rows
 */
void gtk_custom_table_resize(GtkWidget *table, int cols, int rows) {

    int i = 0;

    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    /* free memory occupied by table cells */
    for(i = 0; i < (priv->table_x * priv->table_y); i++) {

        /* free meta structure */
        if(priv->table_cell[i]->meta != NULL) {
            free(priv->table_cell[i]->meta);
        }
        /* free cell text */
        if(priv->table_cell[i]->text != NULL) {
            free(priv->table_cell[i]->text);
        }

        free(priv->table_cell[i]);
    }


    /* free memory occupied by table rows */
    for(i = 0; i < priv->table_y; i++) {

        if(priv->table_rows[i]->meta != NULL) {
            free(priv->table_rows[i]->meta);
        }

        free(priv->table_rows[i]->cell);
        free(priv->table_rows[i]);
    }


    /* free memory occupied by table cols */
    for(i = 0; i < priv->table_x; i++) {

        if(priv->table_cols[i]->meta != NULL) {
            free(priv->table_cols[i]->meta);
        }

        free(priv->table_cols[i]->cell);
        free(priv->table_cols[i]);
    }

    int col_widths[priv->table_x];

    /* reuse old column widths */
    for(i = 0; i < priv->table_x; i++) {
        col_widths[i] = priv->table_column_widths[i];
    }
    
    /* free misc memory */
    free(priv->table_column_widths);
    free(priv->table_column_index);
    free(priv->table_column_hidden);
    free(priv->table_column_widths_temp);
    free(priv->table_column_offset_temp);

    /* free memory occupied by primed column */
    gtk_custom_table_tree_free(priv->table_tree);
    priv->table_tree = NULL;

    /* use existing size(s) if desired */
    if(cols >= 0) {
        priv->table_x = cols;    
    }
    /* what he said.. */
    if(rows >= 0) {
        priv->table_y = rows;
    }

    gtk_custom_table_alloc(priv, priv->table_x, priv->table_y, col_widths);
}

