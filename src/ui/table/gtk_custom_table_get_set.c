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
 * add text to a table's footer or header, based on type..
 * @param GtkWidget *table    current table
 * @param int col             column index
 * @param char *text          text to be added
 * @param char *type          type is either 'header' or 'footer'
 */
void gtk_custom_table_set_head_foot_text(GtkWidget *table, int col, 
        char *text, char *type) {
    
    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    /* detect table overflow */
    if(col >= priv->table_x) {
        g_error("table overflow");
    }

    struct table_rows *table_row;

    /* type is header */
    if(strcmp(type, "header") == 0) {
        table_row = priv->table_head; 
        priv->table_has_header = 1;
    }
    /* type is footer */
    else {
        table_row = priv->table_foot; 
        priv->table_has_footer = 1;
    }

    /* free old text as needed */
    if(table_row->cell[col]->text != NULL) {
        free(table_row->cell[col]->text);
    }

    /* malloc and copy new text to cell */
    table_row->cell[col]->text = malloc(strlen(text) + 1);      
    strcpy(table_row->cell[col]->text, text);
}


/**
 * get the index of a string of text in a table.. 
 * @param GtkWidget *table    table widget in which to search..
 * @param char *text          text to be searched for
 * @return                    returns index on success, else -1
 */
int gtk_custom_table_get_indexof(GtkWidget *table, char *text) {

    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    /* check if table is primed */
    if(!priv->table_has_primary) {
        g_error("table does not have a primary index");
    }

    gtk_custom_table_tree_get_recurse(priv, priv->table_tree, text, 
        priv->table_col_primary);

    int index = GTK_CUSTOM_TABLE_GET_PRIVATE(table)->table_tree_index;
    priv->table_tree_index = -1;

    return index; 
}


/**
 * write text to cell indicated by row and col
 * @param GtkWidget *table    current working table
 * @param int col             col to write to
 * @param int row             row to write to
 * @param *char text          text to be written
 */
void gtk_custom_table_set_cell_text(GtkWidget *table, int col, int row, 
    char *text) {

    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    /* we can't allow this.. */
    if(text == NULL) {
        g_error("add to cell, text was null!");
    }

    /* detect table overflow, crash and burn */
    if((col >= priv->table_x) || (row >= priv->table_y)) {
        g_error("table overflow");
    }

    /* when adding text to the same cell twice, free memory */
    if(priv->table_rows[row]->cell[col]->text != NULL) {
        free(priv->table_rows[row]->cell[col]->text);
    }

    priv->table_rows[row]->cell[col]->text = malloc(strlen(text) + 1); 
    strcpy(priv->table_rows[row]->cell[col]->text, text);

    /* add values in primary index column to binary tree */
    if((col == priv->table_col_primary) && priv->table_has_primary) {

        /* head node is null, take care of it */
        if(priv->table_tree == NULL) {

            priv->table_tree = malloc(sizeof (struct table_tree));
            priv->table_tree->data = priv->table_rows[row];
            priv->table_tree->left = NULL;
            priv->table_tree->right = NULL;
        }
        /* add all following nodes as such.. */
        else {

            gtk_custom_table_tree_add(priv->table_tree, 
                priv->table_rows[row], col);
        }
    }
}


/**
 * set background-image to specific cell..
 * @param GtkWidget *table    current table
 * @param int col             column 
 * @param int row             row
 * @param char *filename      image filename
 */
void gtk_custom_table_set_cell_bg_image(GtkWidget *table, int col, int row, 
    char *filename) {

    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    priv->table_rows[row]->cell[col]->meta->bg_image = filename;
    priv->table_rows[row]->cell[col]->meta->has_bg_image = TRUE;
}


/**
 * mark a column as graphable.. i.e. integers will show up as graph..
 * @param GtkWidget *table    current table
 * @param int col             column 
 * @param gboolean value      turn on or off
 */
void gtk_custom_table_set_column_graph(GtkWidget *table, int col, 
    gboolean value) {
 
    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    priv->table_cols[col]->meta->graphable = value;
}


/**
 * add foreground-color to a all graphs in a column..
 * @param GtkWidget *table    current working table
 * @param int col             column 
 * @param double rgb[]        array of colors for graph
 */
void gtk_custom_table_set_graph_color_col(GtkWidget *table, int col,  
        double rgb[]) {

    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    int i = 0;

    for(i = 0; i < 3; i++) {
        priv->table_cols[col]->meta->graph[i] = rgb[i];
    }

    priv->table_cols[col]->meta->graphable = TRUE;
}


/**
 * add foreground-color to a graph in a specific cell..
 * @param GtkWidget *table    current working table
 * @param int col             column 
 * @param int row             row
 * @param double rgb[]        array of colors for graph
 */
void gtk_custom_table_set_graph_color_cell(GtkWidget *table, int col,  
        int row, double rgb[]) {

    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    int i = 0;

    for(i = 0; i < 3; i++) {
        priv->table_rows[row]->cell[col]->meta->graph[i] = rgb[i];
    }

    priv->table_rows[row]->cell[col]->meta->graphable = TRUE;
}


/**
 * add a background-color to specific table row..
 * @param GtkWidget *table    current working table
 * @param int row             row
 * @param double rgb[]        array of colors for graph
 */
void gtk_custom_table_set_row_color(GtkWidget *table, int row, 
        double rgb[]) {

    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    int i = 0;

    for(i = 0; i < 3; i++) {
        priv->table_rows[row]->meta->color[i] = rgb[i];
    }

    priv->table_rows[row]->meta->has_bg_color = TRUE;
}


/**
 * add a background-color to specific table cell..
 * @param GtkWidget *table    current working table
 * @param int col             column 
 * @param int row             row
 * @param double rgb[]        array of colors for graph
 */
void gtk_custom_table_set_cell_color(GtkWidget *table, int col, int row, 
        double rgb[]) {

    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);
    
    int i = 0;

    for(i = 0; i < 3; i++) {
        priv->table_rows[row]->cell[col]->meta->color[i] = rgb[i];
    }

    priv->table_rows[row]->cell[col]->meta->has_bg_color = TRUE;
}


/**
 * enable or disable table cell background color..
 * @param GtkWidget *table    current table
 * @param int col             cell x index
 * @param int row             cell y index
 * gboolean value             value, true or false
 */
void gtk_custom_table_set_cell_color_enable(GtkWidget *table, int col, int row, 
        gboolean value) {

    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    struct table_meta *meta = priv->table_rows[row]->cell[col]->meta;

    meta->has_bg_color = value;
}


/**
 * get a specific table row as a char * array of text values..
 * @param GtkWidget *table     current table
 * @param int index            row index
 * @param char ***container    container which equals NULL..
 */
void gtk_custom_table_get_row(GtkWidget *table, int index, char ***container) {
    
    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    if(index >= priv->table_y) {
        g_error("can't get row, index out of bounds");    
    }

    *container = malloc(sizeof(char *) * priv->table_x);

    int i = 0;

    for(i = 0; i < priv->table_x; i++) {

        (*container)[i] = malloc(strlen(priv->table_rows[index]->cell[i]->text) + 1);
        strcpy((*container)[i], priv->table_rows[index]->cell[i]->text);
    }
}


/**
 * get the text value of a specific table cell..
 * @param GtkWidget *table    current table
 * @param int col             col value
 * @param int row             row value
 */
char* gtk_custom_table_get_cell_text(GtkWidget *table, int col, int row) {
    
    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    if(row >= priv->table_y || col >= priv->table_x) {
        g_error("can't get cell, coordinates were out of bounds");    
    }

    return priv->table_rows[row]->cell[col]->text;
}


int gtk_custom_table_get_rows(GtkWidget *table) {

    return GTK_CUSTOM_TABLE_GET_PRIVATE(table)->table_y;   
}

int gtk_custom_table_get_cols(GtkWidget *table) {

    return GTK_CUSTOM_TABLE_GET_PRIVATE(table)->table_x;
}

void gtk_custom_table_set_column_prime(GtkWidget *table, int col, gboolean value) {

    GTK_CUSTOM_TABLE_GET_PRIVATE(table)->table_has_primary = value;
    GTK_CUSTOM_TABLE_GET_PRIVATE(table)->table_col_primary = col;
}

void gtk_custom_table_set_column_index(GtkWidget *table, int col, gboolean value) {

    GTK_CUSTOM_TABLE_GET_PRIVATE(table)->table_column_index[col] = value;
}

void gtk_custom_table_set_column_shade(GtkWidget *table, int col, gboolean value) {

    GTK_CUSTOM_TABLE_GET_PRIVATE(table)->table_column_hidden[col] = value;
}

void gtk_custom_table_set_column_alignment(GtkWidget *table, int col, 
    PangoAlignment align) {

    GTK_CUSTOM_TABLE_GET_PRIVATE(table)->table_cols[col]->meta->align = align;
}

void gtk_custom_table_set_row_alignment(GtkWidget *table, int row, 
    PangoAlignment align) {

    GTK_CUSTOM_TABLE_GET_PRIVATE(table)->table_rows[row]->meta->align = align;
}

void gtk_custom_table_set_head_row_alignment(GtkWidget *table, 
    PangoAlignment align) {

    GTK_CUSTOM_TABLE_GET_PRIVATE(table)->table_head->meta->align = align;
}

void gtk_custom_table_set_foot_row_alignment(GtkWidget *table, 
    PangoAlignment align) {

    GTK_CUSTOM_TABLE_GET_PRIVATE(table)->table_foot->meta->align = align;
}

void gtk_custom_table_set_cell_alignment(GtkWidget *table, int col, 
    int row, PangoAlignment align) {

    GtkCustomTablePrivate *priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);
    priv->table_rows[row]->cell[col]->meta->align = align;
}

void gtk_custom_table_set_foot_cell_alignment(GtkWidget *table, int col, 
    PangoAlignment align) {

    GtkCustomTablePrivate *priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);
    priv->table_foot->cell[col]->meta->align = align;
}

void gtk_custom_table_set_head_cell_alignment(GtkWidget *table, int col, 
    PangoAlignment align) {

    GtkCustomTablePrivate *priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);
    priv->table_head->cell[col]->meta->align = align;
}

void gtk_custom_table_set_sort_index(GtkWidget *table, int col) {
    
    GTK_CUSTOM_TABLE_GET_PRIVATE(table)->table_sort_index = col;
}

void gtk_custom_table_set_sortable(GtkWidget *table, gboolean value) {
 
    GTK_CUSTOM_TABLE_GET_PRIVATE(table)->table_is_sortable = value;
}

void gtk_custom_table_set_foot_text(GtkWidget *table, int col, char *text) {
    
    gtk_custom_table_set_head_foot_text(table, col, text, "footer");
}

void gtk_custom_table_set_head_text(GtkWidget *table, int col, char *text) {

    gtk_custom_table_set_head_foot_text(table, col, text, "header");
}

void gtk_custom_table_set_head_cell_font(GtkWidget *table, int col, 
    char *font) {

    GtkCustomTablePrivate *priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);
    priv->table_head->cell[col]->meta->font = font;
}

void gtk_custom_table_set_foot_cell_font(GtkWidget *table, int col, 
    char *font) {

    GtkCustomTablePrivate *priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);
    priv->table_foot->cell[col]->meta->font = font;
}

void gtk_custom_table_set_head_row_font(GtkWidget *table, char *font) {

    GtkCustomTablePrivate *priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);
    priv->table_head->meta->font = font;
}

void gtk_custom_table_set_foot_row_font(GtkWidget *table, char *font) {

    GtkCustomTablePrivate *priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);
    priv->table_foot->meta->font = font;
}

void gtk_custom_table_set_cell_font(GtkWidget *table, int col, 
    int row, char *font) {

    GtkCustomTablePrivate *priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);
    priv->table_rows[row]->cell[col]->meta->font = font;
}

void gtk_custom_table_set_row_font(GtkWidget *table, int row, 
    char *font) {

    GtkCustomTablePrivate *priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);
    priv->table_rows[row]->meta->font = font;
}

void gtk_custom_table_set_column_font(GtkWidget *table, int col, 
    char *font) {

    GtkCustomTablePrivate *priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);
    priv->table_cols[col]->meta->font = font;
}


