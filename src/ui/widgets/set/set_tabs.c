/***********************************************************************
 *
 * Copyright (C) 2011-2013  Adrian Solumsmo
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


#include "ui/widgets/widgets.h"
#include "ui/widgets/set/set.h"


/* minor convenience function for tab-creation */
static void ui_set_make(char *title, NotebookTab *tab) {

    tab->is_open = 0;
    tab->type = TAB_TYPE_NONE;
    tab->vbox = gtk_vbox_new(FALSE, 0);
    tab->scroll = gtk_scrolled_window_new(NULL, NULL);
    tab->view = gtk_viewport_new(NULL, NULL);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(tab->scroll), 
        GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(tab->view), tab->table);
    gtk_viewport_set_shadow_type(GTK_VIEWPORT(tab->view), GTK_SHADOW_NONE);
    gtk_container_add(GTK_CONTAINER(tab->scroll), tab->view); 
    gtk_box_pack_start(GTK_BOX(tab->vbox), tab->scroll, TRUE, TRUE, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(mwin->note), tab->vbox, 
        gtk_label_new(title));
}


void ui_set_tabs() {

    ui_set_make(NAME_STATS_MOV, nb_stats_mov_tab); 
    ui_set_make(NAME_LISTS_MOV, nb_lists_mov_tab); 
    ui_set_make(NAME_STATS_LST, nb_stats_lst_tab); 
    ui_set_make(NAME_LISTS_LST, nb_lists_lst_tab); 
    ui_set_make(NAME_STATS_CMP, nb_stats_cmp_tab); 
    ui_set_make(NAME_LISTS_CMP, nb_lists_cmp_tab); 
    ui_set_make(NAME_LISTS_TOP, nb_lists_top_tab); 
    ui_set_make(NAME_LISTS_BOT, nb_lists_bot_tab); 
    ui_set_make(NAME_LISTS_BOX, nb_lists_box_tab); 
    ui_set_make(NAME_STATS_ALL, nb_stats_all_tab);
}

