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
 * calculate widget dimensions, paint to cairo context
 * @param GtkCustomTablePrivate *table    current table
 * @param GdkEventExpose *event           expose event
 */
void gtk_custom_table_paint(GtkWidget *table, GdkEventExpose *event, 
    gboolean refresh) {

    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    /* update table dimensions for redrawing table */
    if(refresh == FALSE) {

        if(table->allocation.width < priv->table_min_width) {
            priv->table_max_width = priv->table_min_width;
        }
        else {
            priv->table_max_width = table->allocation.width;
        }

        gtk_custom_table_calc(priv);
    }

    GtkAdjustment *adjust = gtk_viewport_get_vadjustment(
        GTK_VIEWPORT(table->parent));

    gtk_adjustment_set_step_increment(adjust, 500.0);
    gtk_adjustment_set_page_increment(adjust, 500.0);

    int scroll_beg = (int)gtk_adjustment_get_value(adjust);
    int scroll_end = scroll_beg + ((int)gtk_adjustment_get_page_size(adjust));
    int scroll_tot = ((int)gtk_adjustment_get_page_size(adjust));

    int scroll_beg_row = (scroll_beg / 25);
    int scroll_end_row = (scroll_end / 25) + 1;

    scroll_beg_row = scroll_beg_row - 5;
    scroll_beg_row = scroll_beg_row < 0 ? 0 : scroll_beg_row;

    cairo_t *cr;

    /* create cairo object and draw table to specifications */
    if(refresh == TRUE) {

        priv->table_surface = cairo_image_surface_create(
            CAIRO_FORMAT_ARGB32, 
            table->allocation.width, 
            scroll_tot
        );

        cr = cairo_create(priv->table_surface);
    }
    else {
        cr = gdk_cairo_create(table->window);
    }

    int i = 0;
    int j = 0;

    char temp[10];

    cairo_set_line_width(cr, 1);

    PangoFontDescription *description = NULL;
    description = pango_font_description_from_string("Monospace 10");
    
    PangoLayout *layout = NULL;

    /* DRAW HEADER ROW */    
    if((scroll_beg_row == 0) && priv->table_has_header) {

        for(i = 0; i < priv->table_x; i++) {

            if(priv->table_column_hidden[i] == TRUE) {
                continue;
            }

            cairo_set_source_rgb(cr, 
                rgb_border[0], 
                rgb_border[1], 
                rgb_border[2]
            );

            cairo_rectangle(cr, 
                priv->table_column_offset_temp[i] + 0.5, 
                1, 
                priv->table_column_widths_temp[i], 
                priv->table_row_height - 1.5
            );

            cairo_stroke_preserve(cr);

            /* column selected background color */
            if(priv->table_sort_index == i) {

                cairo_set_source_rgb(cr, 
                    rgb_header_bold[0], 
                    rgb_header_bold[1], 
                    rgb_header_bold[2]);
            }
            /* the default background color */
            else {

                cairo_set_source_rgb(cr, 
                    rgb_header[0], 
                    rgb_header[1], 
                    rgb_header[2]);
            }

            cairo_fill(cr); 

            cairo_set_source_rgb(cr, 
                rgb_text[0], 
                rgb_text[1], 
                rgb_text[2]
            );

            /* align text */
            cairo_move_to(cr, 
                priv->table_column_offset_temp[i] + 10, 
                4
            );

            /* Create a PangoLayout, set the font and text */
            layout = pango_cairo_create_layout(cr);

            pango_layout_set_text(layout, 
                    priv->table_head->cell[i]->text, -1);

            pango_layout_set_font_description(layout, 
                description);

            pango_layout_set_width(layout, 
                (priv->table_column_widths_temp[i] - 20) * PANGO_SCALE);

            pango_layout_set_height(layout, 
                priv->table_row_height * PANGO_SCALE);

            pango_layout_set_ellipsize(layout, 
                PANGO_ELLIPSIZE_END);

            pango_layout_set_alignment(layout, 
                priv->table_cols[i]->meta->align);

            pango_cairo_show_layout(cr, layout);

            g_object_unref(layout);
        }
    }

    int offset = 0;
    int is_integer = 0;
    int modulus = 0;
    int t_height = 0;

    char *text_temp = NULL;

    double graph_step = 0;
    double graph_amount = 0;
    double graph_width = 0;

    struct table_meta *meta_cell = NULL;
    struct table_meta *meta_rows = NULL;
    struct table_meta *meta_cols = NULL;
    struct table_meta *meta_temp = NULL;

    /* only draw those columns which will be visible on window surface */
    for(i = scroll_beg_row; i < scroll_end_row && i < priv->table_y; i++) {

        /* get row meta data */
        meta_rows = priv->table_rows[i]->meta;

        for(j = 0; j < priv->table_x; j++) {

            /* skip hidden columns */
            if(priv->table_column_hidden[j] == TRUE) {
                continue;
            }

            /* get cell, col meta data */
            meta_cell = priv->table_rows[i]->cell[j]->meta;
            meta_cols = priv->table_cols[j]->meta;
            
            /* DRAW CELL BACKGROUND COLOR */

            offset = ((i + priv->table_has_header) * 
                priv->table_row_height);

            cairo_rectangle(cr, 
                priv->table_column_offset_temp[j] + 0.5, 
                offset > 0 ? offset : 1, 
                priv->table_column_widths_temp[j], 
                priv->table_row_height
            );

            cairo_set_source_rgb(cr, 
                rgb_border[0], 
                rgb_border[1], 
                rgb_border[2]
            );

            cairo_stroke_preserve(cr);

            /* draw cell background-color */
            if(meta_cell != NULL && meta_cell->has_bg_color) {

                cairo_set_source_rgb(cr, 
                    meta_cell->color[0], 
                    meta_cell->color[1], 
                    meta_cell->color[2]
                );
            }
            /* draw row background-color */
            else if(meta_rows != NULL && meta_rows->has_bg_color) {

                cairo_set_source_rgb(cr, 
                    meta_rows->color[0], 
                    meta_rows->color[1], 
                    meta_rows->color[2]
                );
            }
            /* draw col background-color */
            else if(meta_cols != NULL && meta_cols->has_bg_color) {

                cairo_set_source_rgb(cr, 
                    meta_cols->color[0], 
                    meta_cols->color[1], 
                    meta_cols->color[2]
                );
            }
            /* draw default background-color */
            else {

                modulus = i % 2;

                cairo_set_source_rgb(cr, 
                    checkers[modulus][0], 
                    checkers[modulus][modulus], 
                    checkers[modulus][2]
                );
            }

            cairo_fill(cr);

            /* FIND META WITH HIGHEST PRECEDENCE */

            /* check if data is numeric */
            is_integer = gtk_custom_table_is_integer(
                priv->table_rows[i]->cell[j]->text);

            if(meta_cell != NULL && meta_cell->graphable 
                && is_integer) {

                meta_temp = meta_cell;
            }
            else if(meta_rows != NULL && meta_rows->graphable 
                && is_integer) {

                meta_temp = meta_rows;
            }
            else if(meta_cols != NULL && meta_cols->graphable 
                && is_integer) {

                meta_temp = meta_cols;
            }

            /* DRAW CELL DATA AS GRAPH */
            if(meta_temp != NULL) {
                
                /* calculate graph size */
                graph_step = (priv->table_column_widths_temp[j] - 8) / 100.0;
                graph_amount = atoi(priv->table_rows[i]->cell[j]->text);
                graph_width = graph_amount * graph_step;

                cairo_rectangle(cr, 
                    priv->table_column_offset_temp[j] + 4, 
                    offset + 4, 
                    graph_width > 0 ? graph_width : 1,
                    priv->table_row_height - 8
                );

                cairo_set_source_rgb(cr, 
                    rgb_border[0], 
                    rgb_border[1], 
                    rgb_border[2]
                );

                cairo_stroke_preserve(cr);

                cairo_set_source_rgb(cr, 
                    meta_temp->graph[0], 
                    meta_temp->graph[1], 
                    meta_temp->graph[2]
                );

                cairo_fill(cr);
            }
            /* DRAW CELL DATA AS TEXT */
            else {

                cairo_set_source_rgb(cr, 
                    rgb_text[0], 
                    rgb_text[1], 
                    rgb_text[2]
                );

                /* align text */
                cairo_move_to(cr, 
                    priv->table_column_offset_temp[j] + 10, 
                    offset + 4
                );

                /* Create a PangoLayout, set the font and text */
                layout = pango_cairo_create_layout(cr);

                /* column is an index, show numbering */
                if(priv->table_column_index[j]) {

                    sprintf(temp, "%d", i + 1);
                    text_temp = temp;
                }
                else {
                    text_temp = priv->table_rows[i]->cell[j]->text;
                }
                
                pango_layout_set_text(layout, text_temp, -1);

                pango_layout_set_font_description(layout, 
                    description);

                pango_layout_set_width(layout, 
                    (priv->table_column_widths_temp[j] - 20) * PANGO_SCALE);

                pango_layout_set_height(layout, 
                    priv->table_row_height * PANGO_SCALE);

                pango_layout_set_ellipsize(layout, 
                    PANGO_ELLIPSIZE_END);

                pango_layout_set_alignment(layout, 
                    priv->table_cols[j]->meta->align);

                pango_cairo_show_layout(cr, layout);

                g_object_unref(layout);
            }

            meta_temp = NULL;
        }
    }

    t_height = priv->table_row_height * (priv->table_y + priv->table_has_header);


    /* DRAW FOOTER ROW */ 
    if((scroll_end_row >= priv->table_y) && priv->table_has_footer) {

        for(i = 0; i < priv->table_x; i++) {

            /* skip hidden columns */
            if(priv->table_column_hidden[i] == TRUE) {
                continue;
            }
                
            cairo_set_source_rgb(cr, 
                rgb_border[0], 
                rgb_border[1], 
                rgb_border[2]
            );

            /* draw footer background color */
            cairo_rectangle(cr, 
                priv->table_column_offset_temp[i] + 0.5, 
                t_height, 
                priv->table_column_widths_temp[i], 
                priv->table_row_height
            );

            cairo_stroke_preserve(cr);

            cairo_set_source_rgb(cr, 
                rgb_footer[0], 
                rgb_footer[1], 
                rgb_footer[2]
            );

            cairo_fill(cr); 

            cairo_set_source_rgb(cr, 
                rgb_text[0], 
                rgb_text[1], 
                rgb_text[2]
            );

            cairo_move_to(cr, 
                priv->table_column_offset_temp[i] + 10, 
                t_height + 4
            );

            /* set the font and text */
            layout = pango_cairo_create_layout(cr);

            pango_layout_set_text(layout, 
                priv->table_foot->cell[i]->text, -1);

            pango_layout_set_font_description(layout, 
                description);

            pango_layout_set_width(layout, 
                (priv->table_column_widths_temp[i] - 20) * PANGO_SCALE);

            pango_layout_set_height(layout, 
                priv->table_row_height * PANGO_SCALE);

            pango_layout_set_ellipsize(layout, 
                PANGO_ELLIPSIZE_END);

            pango_layout_set_alignment(layout, 
                priv->table_cols[i]->meta->align);

            pango_cairo_show_layout(cr, layout);

            g_object_unref(layout);
        }

        t_height += priv->table_row_height;
    }

    pango_font_description_free(description);

    /* REFRESH, draw image to avoid flicker.. */
    if(refresh == TRUE) {

        cairo_t *cr_main = gdk_cairo_create(table->window);
        cairo_set_source_surface(cr_main, priv->table_surface, 0, 0);
        cairo_paint(cr_main);
        cairo_destroy(cr_main);

        /* image is huge and not worth saving */
        cairo_surface_destroy(priv->table_surface);
    }

    cairo_destroy(cr);

    /* make sure the scrollbars are up to speed */
    gtk_widget_set_size_request(table, priv->table_min_width, t_height);
}


