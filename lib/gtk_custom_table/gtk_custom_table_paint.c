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


double checkers[2][3] = {
    {1.00, 1.00, 1.00}, 
    {0.90, 0.90, 0.90}, 
};


/**
 * calculate widget dimensions, paint to cairo context
 * @param GtkCustomTablePrivate *table    current table
 * @param GdkEventExpose *event           expose event
 */
void gtk_custom_table_paint(GtkWidget *table, GdkEventExpose *event, gboolean refresh) {

    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    /* update table dimensions for redrawing table */
    if(refresh == FALSE) {

        priv->table_max_width = table->allocation.width < priv->table_min_width ? 
            priv->table_min_width: table->allocation.width;

        gtk_custom_table_calc(priv);
    }

    GtkAdjustment *adjust = gtk_viewport_get_vadjustment(GTK_VIEWPORT(table->parent));
    gtk_adjustment_set_step_increment(adjust, 300.0);
    gtk_adjustment_set_page_increment(adjust, 300.0);

    int scroll_beg = (int)gtk_adjustment_get_value(adjust);
    int scroll_end = scroll_beg + ((int)gtk_adjustment_get_page_size(adjust));
    int scroll_tot = ((int)gtk_adjustment_get_page_size(adjust));

    int scroll_beg_row = scroll_beg / 25;
    int scroll_end_row = scroll_end / 25;

    scroll_beg_row = scroll_beg_row - 5;
    scroll_beg_row = scroll_beg_row < 0 ? 0 : scroll_beg_row;

    cairo_t *cr;

    /* create cairo object and draw table to specifications */
    if(refresh == TRUE) {

        priv->table_surface = cairo_image_surface_create(
            CAIRO_FORMAT_ARGB32, table->allocation.width, scroll_tot);

        cr = cairo_create(priv->table_surface);
    }
    else {
        cr = gdk_cairo_create(table->window);
    }

    int table_width = priv->table_column_offset_temp[priv->table_x];
 
    /* set font */
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
        CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 12.0);

    int i = 0;
    int j = 0;

    char temp[10];

    cairo_set_line_width(cr, 1);

    /* draw header row */    
    if((scroll_beg_row == 0) && priv->table_has_header) {

        /* draw horizontal lines in header.. */
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 1.0);
        cairo_move_to(cr, 1, 1); 
        cairo_line_to(cr, table_width, 1);
        cairo_stroke(cr);

        /* draw row background color */
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_rectangle(cr, 1, 1, 
            table_width - 1, priv->table_row_height - 1.5);
        cairo_stroke_preserve(cr);
        cairo_fill(cr);

        for(i = 0; i < priv->table_x; i++) {

            if(priv->table_column_hidden[i] == TRUE) {
                continue;
            }

            /* add a darker background for currently sorted-by column */
            if(priv->table_sort_index == i) {

                cairo_set_source_rgb(cr, 0, 0, 0);
                cairo_rectangle(cr, priv->table_column_offset_temp[i] + 0.5, 1, 
                    priv->table_column_widths_temp[i], priv->table_row_height - 1.5);
                cairo_stroke_preserve(cr);
                cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);
                cairo_fill(cr); 
            }
            /* add default background color */
            else {
                
                cairo_set_source_rgb(cr, 0, 0, 0);
                cairo_rectangle(cr, priv->table_column_offset_temp[i] + 0.5, 1, 
                    priv->table_column_widths_temp[i], priv->table_row_height - 1.5);
                cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
                cairo_fill(cr); 
            }

            cairo_set_source_rgb(cr, 0, 0, 0);
            cairo_move_to(cr, 10.0 + priv->table_column_offset_temp[i], 16);
            cairo_show_text(cr, priv->table_head[i]->text);
        }
    }

    struct table_meta *meta = NULL;

    /* only draw those columns which will be visible on window surface */
    for(i = scroll_beg_row; i < scroll_end_row && i < priv->table_y; i++) {

        cairo_set_line_width(cr, 1);

        for(j = 0; j < priv->table_x; j++) {

            /* skip hidden columns */
            if(priv->table_column_hidden[j] == TRUE) {
                continue;
            }

            /* check for cell meta data */
            meta = priv->table_rows[i]->cell[j]->meta;

            /* draw cell background-color */
            if(meta != NULL && meta->has_bg_color) {

                cairo_set_source_rgb(cr, meta->color[0], meta->color[1], 
                    meta->color[2]);
            }
            else {
                cairo_set_source_rgb(cr, checkers[i%2][0], checkers[i%2][i%2], 
                    checkers[i%2][2]);
            }

            /* draw cell background color */
            cairo_rectangle(cr, 
                priv->table_column_offset_temp[j], 
                ((i + priv->table_has_header) * priv->table_row_height), 
                priv->table_column_widths_temp[j], 
                priv->table_row_height
            );

            cairo_fill(cr);

            /* check column for meta data */
            meta = priv->table_cols[j]->meta;

            /* draw cell data as graph */
            if(meta != NULL && meta->graphable) {

                /* use column meta background if applicable */
                if(meta->has_bg_color) {

                    cairo_set_source_rgb(cr, meta->color[0], meta->color[1], 
                        meta->color[2]);

                    /* draw cell background color */
                    cairo_rectangle(cr, 
                        priv->table_column_offset_temp[j], 
                        ((i + priv->table_has_header) * priv->table_row_height), 
                        priv->table_column_widths_temp[j], 
                        priv->table_row_height
                    );

                    cairo_fill(cr);
                }

                cairo_set_source_rgb(cr, 0, 0, 0);

                double graph_width = (priv->table_column_widths_temp[j] / 100.0) * 
                    (atoi(priv->table_rows[i]->cell[j]->text));

                cairo_rectangle(cr, 
                    priv->table_column_offset_temp[j] + 4, 
                    ((i + priv->table_has_header) * priv->table_row_height) + 4, 
                    graph_width > 12 ? graph_width - 8 : 0,
                    priv->table_row_height - 8
                );

                cairo_stroke_preserve(cr);

                cairo_set_source_rgb(cr, 
                    meta->graph[0], 
                    meta->graph[1], 
                    meta->graph[2]);

                cairo_fill(cr);
            }
            /* write text to cell if applicable */
            else {

                cairo_set_source_rgb(cr, 0, 0, 0);

                cairo_move_to(cr, 10.0 + priv->table_column_offset_temp[j], 
                    ((i + priv->table_has_header) * 
                    priv->table_row_height) + 16);

                if(priv->table_column_index[j]) {

                    sprintf(temp, "%d.", i + 1);
                    cairo_show_text(cr, temp);
                }
                else {
                    cairo_show_text(cr, priv->table_rows[i]->cell[j]->text);
                }
            }
        }

        /* draw horizontal lines.. */
        int temp_height = (((i+1) + priv->table_has_header) * priv->table_row_height);

        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 0.5);
        cairo_move_to(cr, 1, temp_height); 
        cairo_line_to(cr, table_width, temp_height);
        cairo_stroke(cr);
    }

    int table_height = priv->table_row_height * 
        (priv->table_y + priv->table_has_header);

    /* draw footer row */    
    if((scroll_end_row >= priv->table_y) && priv->table_has_footer) {

        /* draw horizontal lines in footer.. */
        int temp_height = ((((priv->table_y + 1 + priv->table_has_header)) * 
            priv->table_row_height) + 0.5);

        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 1.0);
        cairo_move_to(cr, 1, temp_height); 
        cairo_line_to(cr, table_width, temp_height);
        cairo_stroke(cr);

        /* draw footer background color */
        cairo_rectangle(cr, 1, table_height, table_width - 1, 
            priv->table_row_height);
        cairo_stroke_preserve(cr);
        cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
        cairo_fill(cr);

        for(i = 0; i < priv->table_x; i++) {

            /* skip hidden columns */
            if(priv->table_column_hidden[i] == TRUE) {
                continue;
            }
                
            /* draw footer background color */
            cairo_set_source_rgb(cr, 0, 0, 0);
            cairo_rectangle(cr, priv->table_column_offset_temp[i] + 0.5, table_height, 
                priv->table_column_widths_temp[i], priv->table_row_height - 1.5);
            cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
            cairo_fill(cr); 

            cairo_set_source_rgb(cr, 0, 0, 0);
            cairo_move_to(cr, 10.0 + priv->table_column_offset_temp[i], 
                16 + table_height);
            cairo_show_text(cr, priv->table_foot[i]->text);
        }

        table_height += priv->table_row_height;
    }

    /* draw borders */
    cairo_set_source_rgb(cr, 0, 0, 0);

    for(i = 0; i <= priv->table_x; i++) {

        /* skip hidden columns */
        if(i < priv->table_x && priv->table_column_hidden[i] == TRUE) {
            continue;
        }

        cairo_move_to(cr, priv->table_column_offset_temp[i] + 0.5, 0);
        cairo_line_to(cr, priv->table_column_offset_temp[i] + 0.5, 
            scroll_beg + (scroll_tot > table_height ? table_height: scroll_tot));
        cairo_stroke(cr);
    }

    /* just a refresh, draw image to avoid flicker.. */
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
    gtk_widget_set_size_request(table, priv->table_min_width, table_height);
}


