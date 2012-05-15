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


#ifndef __GTKCUSTOMTABLE_H__
#define __GTKCUSTOMTABLE_H__

    #include <cairo.h>
    #include <gtk/gtk.h>
    #include <string.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <unistd.h>
    #include "strnatcmp/strnatcmp.h"

    typedef struct _GtkCustomTable GtkCustomTable;
    typedef struct _GtkCustomTableClass GtkCustomTableClass;
    typedef struct _GtkCustomTablePrivate GtkCustomTablePrivate;

    /* structure for per instance public, data */
    struct _GtkCustomTable {
        
        GtkDrawingArea parent;
    };

    /* structure for all widget instances */
    struct _GtkCustomTableClass {
        
        GtkDrawingAreaClass parent_class;  
    };

    /* per instance structure for cell meta data */
    struct table_meta {

        double color[3];
        double graph[3];
        gboolean graphable;
        gboolean has_bg_color;
    };

    struct table_cell {

        char *text;
        struct table_meta *meta;
    };

    struct table_cols {

        struct table_meta *meta;
        struct table_cell **cell;
    };

    struct table_rows {

        GtkCustomTablePrivate *priv;

        int row;
        struct table_meta *meta;
        struct table_cell **cell;
    };

    struct table_tree {

        struct table_rows *data;
        struct table_tree *left;
        struct table_tree *right;
    };

    /* structure for per instance private data */
    struct _GtkCustomTablePrivate {

        gboolean table_is_sortable;
        cairo_surface_t *table_surface;

        int table_x;
        int table_y;
        int table_tree_index;
        int table_sort_index;
        int table_sort_order;
        int table_has_header;
        int table_has_footer;
        int table_has_primary;
        int table_col_primary;
        int table_min_width;
        int table_max_width;
        int table_min_height;
        int table_max_height;
        int table_row_height;
        int table_scroll_lock;

        int *table_column_widths;
        int *table_column_index;
        int *table_column_hidden;
        int *table_column_widths_temp;
        int *table_column_offset_temp;

        struct table_tree *table_tree;

        struct table_cols **table_cols;
        struct table_rows **table_rows;
        struct table_cell **table_cell;
        struct table_cell **table_head;
        struct table_cell **table_foot;
        // should be table_row..
    };

    #define GTK_CUSTOM_TABLE_ASC 0
    #define GTK_CUSTOM_TABLE_DESC 1
    #define GTK_CUSTOM_TABLE_INVERT -1

    #define GTK_TYPE_CUSTOM_TABLE             (gtk_custom_table_get_type ())
    #define GTK_CUSTOM_TABLE(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CUSTOM_TABLE, GtkCustomTable))
    #define GTK_CUSTOM_TABLE_CLASS(obj)       (G_TYPE_CHECK_CLASS_CAST ((obj), GTK_CUSTOM_TABLE,  GtkCustomTableClass))
    #define GTK_IS_CUSTOM_TABLE(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CUSTOM_TABLE))
    #define GTK_IS_CUSTOM_TABLE_CLASS(obj)    (G_TYPE_CHECK_CLASS_TYPE ((obj), GTK_TYPE_CUSTOM_TABLE))
    #define GTK_CUSTOM_TABLE_GET_CLASS        (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CUSTOM_TABLE, GtkCustomTableClass))
    #define GTK_CUSTOM_TABLE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), GTK_TYPE_CUSTOM_TABLE, GtkCustomTablePrivate))


    /* important, required for casting */
    GtkType gtk_custom_table_get_type(void);


    /* widget private functions */
    void gtk_custom_table_resize(GtkWidget *table, int cols, int rows);
    void gtk_custom_table_calc(GtkCustomTablePrivate *table);
    void gtk_custom_table_paint(GtkWidget *table, GdkEventExpose *event, 
        gboolean refresh);
    void gtk_custom_table_tree_free(struct table_tree *tree);
    void gtk_custom_table_tree_get_recurse(GtkCustomTablePrivate *priv, 
        struct table_tree *tree, char *value, int col);
    void gtk_custom_table_tree_add(struct table_tree *tree, 
        struct table_rows *data, int primary);
    void gtk_custom_table_alloc(GtkCustomTablePrivate *priv, int cols, 
        int rows, int column_widths[]);
    
    /* widget event functions */
    gboolean gtk_custom_table_clicked(GtkWidget *table, 
        GdkEventMotion *event);
    gboolean gtk_custom_table_mouse_released(GtkWidget *table, 
        GdkEventButton *event);
    gboolean gtk_custom_table_expose(GtkWidget *table, 
        GdkEventExpose *event);


    /* widget public functions */
    GtkWidget * gtk_custom_table_new(int rows, int cols, int min_width, int min_height, 
        int column_widths[]);
    void gtk_custom_table_refresh(GtkWidget *table);
    void gtk_custom_table_sort(GtkWidget *table, int col, int orientation);
    void gtk_custom_table_resize(GtkWidget *table, int cols, int rows);

    /* public getters and setters */
    void gtk_custom_table_set_cell_color(GtkWidget *table, int col, int row, 
        double rgb[]);
    void gtk_custom_table_set_graph_color(GtkWidget *table, int col, int row, 
        double rgb[]);
    void gtk_custom_table_set_column_index(GtkWidget *table, int col, gboolean value);
    void gtk_custom_table_set_column_shade(GtkWidget *table, int col, gboolean value);
    void gtk_custom_table_set_column_prime(GtkWidget *table, int col, gboolean value);
    void gtk_custom_table_set_column_graph(GtkWidget *table, int col, gboolean value); 
    void gtk_custom_table_set_sortable(GtkWidget *table, gboolean truth);
    void gtk_custom_table_set_cell_text(GtkWidget *table, int col, int row, char *text);
    void gtk_custom_table_set_head_text(GtkWidget *table, int col, char *text);
    void gtk_custom_table_set_foot_text(GtkWidget *table, int col, char *text);
    void gtk_custom_table_get_row(GtkWidget *table, int index, char **container);
    int gtk_custom_table_get_rows(GtkWidget *table);
    int gtk_custom_table_get_cols(GtkWidget *table);
    int gtk_custom_table_get_indexof(GtkWidget *table, char *value);
    int gtk_custom_table_set_cell_color_enable(GtkWidget *table, int col, int row, 
        gboolean value);
    char* gtk_custom_table_get_cell_value(GtkWidget *table, int col, int row);


#endif /* __GTKCUSTOMTABLE_H__*/

