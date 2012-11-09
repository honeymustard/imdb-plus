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


#include "../ui.h"


/* parse new boxoffice list */
int menu_signal_update_box() {

    int i = 0;

    int cols = 0;
    int rows = 0;
    
    char ***results;
    
    if(read_file(get_global(CONST_BOX_CSV), &cols, &rows, &results) 
        && cols == 6) {

        /* update boxoffice tab size */
        gtk_custom_table_resize(nb_tab_boxoffice, -1, rows);

        for(i = 0; i < gtk_custom_table_get_rows(nb_tab_boxoffice); i++) {

            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 0, i, 
                results[i][0]);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, 
                results[i][5]);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 2, i, 
                "0");
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 3, i, 
                results[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 4, i, 
                results[i][2]);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 5, i, 
                results[i][3]);
            gtk_custom_table_set_cell_text(nb_tab_boxoffice, 6, i, 
                results[i][4]);

            /* set cell colors */
            gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, i, not_app);
            gtk_custom_table_set_cell_color(nb_tab_boxoffice, 2, i, not_app);

            /* find imdb ratings in other tables */
            int index1 = gtk_custom_table_get_indexof(nb_tab_mymovies, 
                results[i][1]);
            int index2 = gtk_custom_table_get_indexof(nb_tab_top250, 
                results[i][1]);
            int index3 = gtk_custom_table_get_indexof(nb_tab_bot100, 
                results[i][1]);
            int index4 = gtk_custom_table_get_indexof(nb_tab_lists, 
                results[i][1]);
            
            /* copy them into boxoffice table */
            char *rating1 = index1 >= 0 ? 
                gtk_custom_table_get_cell_text(nb_tab_mymovies, 1, index1) : "0";
            char *rating2 = index2 >= 0 ? 
                gtk_custom_table_get_cell_text(nb_tab_top250, 1, index2) : "0";
            char *rating3 = index3 >= 0 ? 
                gtk_custom_table_get_cell_text(nb_tab_bot100, 1, index3) : "0";
            char *rating4 = index4 >= 0 ? 
                gtk_custom_table_get_cell_text(nb_tab_lists, 1, index4) : "0";

            /* translate ratings */
            int num = 0;
            int num1 = atoi(rating1);
            int num2 = atoi(rating2);
            int num3 = atoi(rating3);
            int num4 = atoi(rating4);

            /* apply first discovered value to table */
            if (num1 > 0) {
                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, 
                    rating1);

                num = num1 - 1;
            }
            else if(num2 > 0) {
                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, 
                    rating2);

                num = num2;
            }
            else if(num3 > 0) {
                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, 
                    rating3);

                num = num3;
            }
            else if(num4 > 0) {
                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, i, 
                    rating4);

                num = num4;
            }
            else {

                num = (int)atof(results[i][5]);

                if(num == 0) {
                    gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, i, 
                        not_app);
                    continue;
                }
            }

            gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, i, 
                colors[num - 1]);
        }

        free_memory(results, cols, rows);

        gtk_custom_table_set_sortable(nb_tab_boxoffice, TRUE);
        gtk_custom_table_sort(nb_tab_boxoffice, 0, GTK_CUSTOM_TABLE_ASC);
        gtk_custom_table_set_column_font(nb_tab_boxoffice, 4, TEXT_FONT); 

        return 1;
    }
    /* no boxoffice file on disk, add default values.. */
    else {

        char temp[10];

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

    return 0;
}

