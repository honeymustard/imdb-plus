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

    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    int t_cols = cols >= 0 ? cols : priv->table_x;
    int t_rows = rows >= 0 ? rows : priv->table_y;

    int t_copy_cols = t_cols > priv->table_x ? priv->table_x : t_cols;
    int t_copy_rows = t_rows > priv->table_y ? priv->table_y : t_rows;
    int t_copy_cell = t_copy_cols * t_copy_rows;

    /* copy table meta-data */
    struct table_meta **table_cols = malloc(sizeof(struct table_meta *) * t_copy_cols); 
    struct table_meta **table_rows = malloc(sizeof(struct table_meta *) * t_copy_rows); 
    struct table_meta **table_cell = malloc(sizeof(struct table_meta *) * t_copy_cell); 

    int i = 0;
    int j = 0;
    int k = 0;

    struct table_meta *meta = NULL;

    for(i = 0; i < t_copy_rows; i++) {
        
        table_rows[i] = malloc(sizeof(struct table_meta));
        
        meta = priv->table_rows[i]->meta;

        for(j = 0; j < 3; j++) {

            table_rows[i]->color[j] = meta->color[j];
            table_rows[i]->graph[j] = meta->graph[j];
        }

        table_rows[i]->graphable = meta->graphable;
        table_rows[i]->has_bg_color = meta->has_bg_color;
        table_rows[i]->align = meta->align;
        table_rows[i]->font = meta->font;
    }

    for(i = 0; i < t_copy_cols; i++) {

        table_cols[i] = malloc(sizeof(struct table_meta));

        meta = priv->table_cols[i]->meta;

        for(j = 0; j < 3; j++) {

            table_cols[i]->color[j] = meta->color[j];
            table_cols[i]->graph[j] = meta->graph[j];
        }

        table_cols[i]->graphable = meta->graphable;
        table_cols[i]->has_bg_color = meta->has_bg_color;
        table_cols[i]->align = meta->align;
        table_cols[i]->font = meta->font;
    }

    int cell = 0;

    for(i = 0; i < t_copy_rows; i++) {
        
        for(j = 0; j < priv->table_x; j++) {

            /* table might've shrunk */
            if(j >= t_cols) {
                continue;
            }

            table_cell[cell] = malloc(sizeof(struct table_meta));

            meta = priv->table_rows[i]->cell[j]->meta;

            for(k = 0; k < 3; k++) {

                table_cell[cell]->color[k] = meta->color[k];
                table_cell[cell]->graph[k] = meta->graph[k];
            }

            table_cell[cell]->graphable = meta->graphable;
            table_cell[cell]->has_bg_color = meta->has_bg_color;
            table_cell[cell]->align = meta->align;
            table_cell[cell]->font = meta->font;

            cell++;
        }
    }

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

    int col_widths[t_cols];

    for(i = 0; i < t_cols; i++) {
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

    priv->table_x = t_cols;
    priv->table_y = t_rows;

    gtk_custom_table_alloc(priv, priv->table_x, priv->table_y, col_widths);

    /* put saved meta-data back into table */
    for(i = 0; i < t_copy_rows; i++) {
        
        meta = priv->table_rows[i]->meta;

        for(j = 0; j < 3; j++) {

            meta->color[j] = table_rows[i]->color[j];
            meta->graph[j] = table_rows[i]->graph[j];
        }

        meta->graphable = table_rows[i]->graphable;
        meta->has_bg_color = table_rows[i]->has_bg_color;
        meta->align = table_rows[i]->align;
        meta->font = table_rows[i]->font;

        free(table_rows[i]);
    }

    free(table_rows);

    for(i = 0; i < t_copy_cols; i++) {

        meta = priv->table_cols[i]->meta;

        for(j = 0; j < 3; j++) {

            meta->color[j] = table_cols[i]->color[j];
            meta->graph[j] = table_cols[i]->graph[j];
        }

        meta->graphable = table_cols[i]->graphable;
        meta->has_bg_color = table_cols[i]->has_bg_color;
        meta->align = table_cols[i]->align;
        meta->font = table_cols[i]->font;

        free(table_cols[i]);
    }

    free(table_cols);

    for(i = 0; i < t_copy_cell; i++) {
        
        meta = priv->table_cell[i]->meta;

        for(j = 0; j < 3; j++) {

            meta->color[j] = table_cell[i]->color[j];
            meta->graph[j] = table_cell[i]->graph[j];
        }

        meta->graphable = table_cell[i]->graphable;
        meta->has_bg_color = table_cell[i]->has_bg_color;
        meta->align = table_cell[i]->align;
        meta->font = table_cell[i]->font;

        free(table_cell[i]);
    }

    free(table_cell);
}

