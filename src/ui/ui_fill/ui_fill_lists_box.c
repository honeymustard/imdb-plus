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


#include "globals.h"
#include "ui/ui.h"
#include "ui/env/colors.h"
#include "ui/table/gtk_custom_table.h"
#include "io/readfile.h"


static double find_entry(GtkWidget *table, char *string) {
 
    int index = gtk_custom_table_get_indexof(table, string);

    if(index >= 0) 
        return atof(gtk_custom_table_get_cell_text(table, 1, index));
    else 
        return 0;
}


static double find_rating(char *string) {

    double n = 0;

    if (n <= 0) n = find_entry(nb_tab_mymovies, string);
    if (n <= 0) n = find_entry(nb_tab_top250, string);
    if (n <= 0) n = find_entry(nb_tab_bot100, string);
    if (n <= 0) n = find_entry(nb_tab_lists, string);

    return n > 0 ? n : 0;
}


void ui_fill_lists_box_empty() {

    int i = 0;
    char temp[50];

    for(i = 0; i < 50; i++) {

        sprintf(temp, "%d", i+1);
        gtk_custom_table_set_cell_text(nb_tab_boxoffice, 0, i, 
            temp);
        gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, 
            "0.0");
        gtk_custom_table_set_cell_text(nb_tab_boxoffice, 2, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_boxoffice, 3, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_tab_boxoffice, 4, i, 
            "N/A");
        gtk_custom_table_set_cell_text(nb_tab_boxoffice, 5, i, 
            "0");
        gtk_custom_table_set_cell_text(nb_tab_boxoffice, 6, i, 
            "$0");
    }
}


int ui_fill_lists_box() {

    int i = 0;

    int cols = 0;
    int rows = 0;
    
    char temp[50];
    char ***results = NULL;
    
    if(read_file(get_global(CONST_BOX_CSV), &cols, &rows, &results) 
        && cols == 6) {

        /* update boxoffice tab size */
        gtk_custom_table_resize(nb_tab_boxoffice, -1, rows);

        for(i = 0; i < rows; i++) {

            double imdb = strtod(results[i][5], NULL);
            double year = strtol(results[i][3], NULL, 10);

            imdb = imdb >= 0 && imdb <= 10 ? imdb : 0;
            year = year > 1800 && year < 2200 ? year : 0;

            sprintf(temp, "%d", i + 1);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 0, i, 
                temp);
            sprintf(temp, "%1.2f", imdb);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, 
                temp);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 2, i, 
                "0");
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 3, i, 
                results[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 4, i, 
                results[i][2]);
            sprintf(temp, "%d", (int)year);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 5, i, 
                temp);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 6, i, 
                results[i][4]);

            /* get imdb ratings from other tables */
            double n = find_rating(results[i][1]);
            n = n > 0 ? n : imdb;

            sprintf(temp, "%1.1f", n);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, 
                temp);

            /* set cell colors */
            gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, i, 
                n <= 0 ? not_app : colors[(int)n - 1]);
            gtk_custom_table_set_cell_color(nb_tab_boxoffice, 2, i, not_app);
        }

        free_memory(results, cols, rows);

        gtk_custom_table_set_sortable(nb_tab_boxoffice, TRUE);
        gtk_custom_table_sort(nb_tab_boxoffice, 0, GTK_CUSTOM_TABLE_ASC);
        gtk_custom_table_set_column_font(nb_tab_boxoffice, 4, TEXT_FONT); 

        return 1;
    }

    ui_fill_lists_box_empty();

    return 0;
}

