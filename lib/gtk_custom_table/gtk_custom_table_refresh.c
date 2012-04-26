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
 * force repaint of table widget if already realized
 * @param GtkWidget *table    table widget to refresh
 */
void gtk_custom_table_refresh(GtkWidget *table) {

    /* table might not yet have been exposed */
    if(GTK_WIDGET_REALIZED(table)) {

        gtk_custom_table_paint(table, NULL, TRUE);
    }
}

