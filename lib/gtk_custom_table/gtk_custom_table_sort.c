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
 * comparision callback function for table sorting
 * @param const void *cmp1    pointer to comparable 1
 * @param const void *cmp2    pointer to comparable 2
 * @return                    see: strcmp
 */
int gtk_custom_table_compare(const void *cmp1, const void *cmp2) {

    struct table_rows *row1 = *(((struct table_rows **)cmp1));
    struct table_rows *row2 = *(((struct table_rows **)cmp2));

    char *x = row1->cell[row1->priv->table_sort_index]->text;
    char *y = row2->cell[row2->priv->table_sort_index]->text;

    /* natural sort is confused by monetary value strings of unequal length */
    if(x[0] == '$' && y[0] == '$') {

        if(strlen(x) != strlen(y)) { 

            if(row1->priv->table_sort_order == GTK_CUSTOM_TABLE_ASC) {
                return strcmp(y, x);
            }

            return strcmp(x, y);
        }
    }

    /* use natural sort comparison */
    if(row1->priv->table_sort_order == GTK_CUSTOM_TABLE_ASC) {
        return strnatcmp(x, y);
    }
    else {
        return strnatcmp(y, x);    
    }
}


/**
 * sort an existing table using qsort..
 * @param GtkWidget *table    current table widget
 * @param int col             sort table by contents of table[col]
 * @param int orit            sort orientation, desc, asc or inverse
 */
void gtk_custom_table_sort(GtkWidget *table, int col, int orient) {

    GtkCustomTablePrivate *priv;
    priv = GTK_CUSTOM_TABLE_GET_PRIVATE(table);

    /* only sort if table is sortable */
    if(priv->table_is_sortable == FALSE) {
        return; 
    }

    /* set next table sort order */
    priv->table_sort_index = col;
    priv->table_sort_order = orient == -1 ? !priv->table_sort_order : orient;

    /* perform qsort on table cells array */
    qsort((void *)priv->table_rows, priv->table_y, 
        sizeof(struct table_rows *), gtk_custom_table_compare);

    int i = 0;

    /* reset row index, so that binary search can find them */
    for(i = 0; i < priv->table_y; i++) {

        priv->table_rows[i]->row = i;
    }
}

