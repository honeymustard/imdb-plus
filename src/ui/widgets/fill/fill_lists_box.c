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


#include "ui/globals/globals.h"
#include "ui/widgets/widgets.h"
#include "ui/env/colors.h"
#include "ui/table/gtk_custom_table.h"
#include "io/readfile.h"


static double find_entry(NotebookTab *tab, char *string) {
 
    int index = gtk_custom_table_get_indexof(tab->table, string);

    if(index >= 0) 
        return atof(gtk_custom_table_get_cell_text(tab->table, 1, index));
    else 
        return 0;
}


static double find_rating(char *string) {

    double n = 0;

    if (n <= 0) n = find_entry(nb_lists_mov_tab, string);
    if (n <= 0) n = find_entry(nb_lists_top_tab, string);
    if (n <= 0) n = find_entry(nb_lists_lst_tab, string);
    if (n <= 0) n = find_entry(nb_lists_bot_tab, string);

    return n > 0 ? n : 0;
}


void ui_fill_lists_box_empty() {

    int i = 0;
    char temp[50];

    for(i = 0; i < 50; i++) {

        sprintf(temp, "%d", i+1);
        gtk_custom_table_set_cell_text(nb_lists_box_tab->table, 0, i, 
            temp);
        gtk_custom_table_set_cell_text(nb_lists_box_tab->table, 1, i, 
            "0.0");
        gtk_custom_table_set_cell_text(nb_lists_box_tab->table, 2, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_lists_box_tab->table, 3, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_lists_box_tab->table, 4, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_lists_box_tab->table, 5, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_lists_box_tab->table, 6, i, 
            "$0");
    }
}


void ui_fill_lists_box(ResultList *list, NotebookTab *tab) {

    int i = 0;
    char temp[50];

    gtk_custom_table_resize(tab->table, -1, list->rows);

    for(i = 0; i < list->rows; i++) {

        double imdb = strtod(list->results[i][5], NULL);
        double year = strtol(list->results[i][3], NULL, 10);

        imdb = imdb >= 0 && imdb <= 10 ? imdb : 0;
        year = year > 1800 && year < 2200 ? year : 0;

        sprintf(temp, "%d", i + 1);
        gtk_custom_table_set_cell_text(tab->table, 0, i, 
            temp);
        sprintf(temp, "%1.2f", imdb);
        gtk_custom_table_set_cell_text(tab->table, 1, i, 
            temp);
        gtk_custom_table_set_cell_text(tab->table, 2, i, 
            "0");
        gtk_custom_table_set_cell_text(tab->table, 3, i, 
            list->results[i][1]);
        gtk_custom_table_set_cell_text(tab->table, 4, i, 
            list->results[i][2]);
        sprintf(temp, "%d", (int)year);
        gtk_custom_table_set_cell_text(tab->table, 5, i, 
            temp);
        gtk_custom_table_set_cell_text(tab->table, 6, i, 
            list->results[i][4]);

        /* get imdb ratings from other tables */
        double n = find_rating(list->results[i][1]);
        n = n > 0 ? n : imdb;

        sprintf(temp, "%1.1f", n);
        gtk_custom_table_set_cell_text(tab->table, 1, i, 
            temp);

        /* set cell colors */
        gtk_custom_table_set_cell_color(tab->table, 1, i, 
            n <= 0 ? not_app : colors[(int)n - 1]);
        gtk_custom_table_set_cell_color(tab->table, 2, i, not_app);
    }

    gtk_custom_table_set_sortable(tab->table, TRUE);
    gtk_custom_table_sort(tab->table, 0, GTK_CUSTOM_TABLE_ASC);
    gtk_custom_table_set_column_font(tab->table, 4, TEXT_FONT); 
}


int ui_fill_lists_box_update() {

    ResultList *list = calloc(1, sizeof(ResultList));
    
    if(readfile(list, get_global(CONST_BOX_CSV)) 
        && list->cols == 6) {
        
        ui_fill_lists_box(list, nb_lists_box_tab);

        readfile_free(list);

        return 1;
    }

    free(list);

    ui_fill_lists_box_empty();

    return 0;
}

