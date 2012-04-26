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
 * @param int cols               amount of table columns
 * @param int rows               amount of table rows
 * @param int min_width          minimun width of the table
 * @param int min_height         minimum height of the table
 * @return GtkWidget *table      returns newly created table widget
 */
GtkWidget * gtk_custom_table_new(int cols, int rows, int min_width, int min_height, 
    int column_widths[]) {
    
    GtkWidget *table = g_object_new(GTK_TYPE_CUSTOM_TABLE, NULL);

    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    priv->table_surface = NULL;
    priv->table_min_width = min_width;
    priv->table_row_height = 25;
    priv->table_has_primary = 0;
    priv->table_has_header = 0;
    priv->table_has_footer = 0;
    priv->table_scroll_lock = 0;
    priv->table_tree = NULL;
    priv->table_sort_index = 0;
    priv->table_sort_order = 0;
    priv->table_tree_index = -1;
    priv->table_is_sortable = FALSE;
    priv->table_col_primary = 2;

    /* create header/footer */
    priv->table_head = malloc(sizeof (struct table_cell *) * cols); 
    priv->table_foot = malloc(sizeof (struct table_cell *) * cols); 

    int i = 0;

    for(i = 0; i < cols; i++) {

        /* create new table cell */
        priv->table_head[i] = malloc(sizeof (struct table_cell));
        priv->table_head[i]->text = NULL;
        priv->table_head[i]->meta = NULL;
        
        priv->table_foot[i] = malloc(sizeof (struct table_cell));
        priv->table_foot[i]->text = NULL;
        priv->table_foot[i]->meta = NULL;
    }

    gtk_custom_table_alloc(priv, cols, rows, column_widths);

    return table;
}

