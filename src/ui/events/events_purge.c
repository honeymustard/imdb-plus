/***********************************************************************
 *
 * Copyright (C) 2011-2014  Adrian Solumsmo
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/


#include "ui/globals/globals.h"
#include "ui/widgets/widgets.h"
#include "ui/widgets/fill/fill.h"
#include "ui/table/gtk_custom_table.h"


/* purge top files from disk and reset lists */
void menu_signal_purge(gpointer data) {
    
    /* delete files */
    remove(globals_get(CONST_TOP_CSV));
    remove(globals_get(CONST_BOT_CSV));
    remove(globals_get(CONST_BOX_CSV));

    ui_fill_lists_top_update();
    ui_fill_lists_bot_update();
    ui_fill_lists_box_update();
    ui_fill_stats_all_update();

    gtk_statusbar_push(GTK_STATUSBAR(mwin->stat), 1, 
        "Downloaded lists have been purged");

    gtk_custom_table_refresh(mwin->main);
}

