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


#include "events.h"


/**
 * read and parse a ratings file or list..
 * @param char *filename    file to open..
 */
int menu_open_ratings(char *filename) {

    int cols = 0;
    int rows = 0;

    char ***results;
            
    if(!read_file(filename, &cols, &rows, &results) || cols < 10) {
        return 0;
    }

    int i = 0;
    int j = 0;

    /* remove previous MyRating and associated color from lists */
    for(i = 0; i < gtk_custom_table_get_rows(nb_tab_lists); i++) {
        
        gtk_custom_table_set_cell_text(nb_tab_lists, 2, i, "0");
        gtk_custom_table_set_cell_color_enable(nb_tab_lists, 2, i, FALSE);
    }

    /* remove previous MyRating and associated color from top250 */
    for(i = 0; i < gtk_custom_table_get_rows(nb_tab_top250); i++) {
        
        gtk_custom_table_set_cell_text(nb_tab_top250, 2, i, "0");
        gtk_custom_table_set_cell_color_enable(nb_tab_top250, 2, i, FALSE);
    }

    /* remove previous MyRating and associated color from boxoffice */
    for(i = 0; i < gtk_custom_table_get_rows(nb_tab_boxoffice); i++) {
        
        gtk_custom_table_set_cell_text(nb_tab_boxoffice, 2, i, "0");
        gtk_custom_table_set_cell_color_enable(nb_tab_boxoffice, 2, i, FALSE);
    }

    char temp[100];

    if(strcmp("IMDb Rating", results[0][9]) == 0) {

        gtk_custom_table_sort(nb_tab_statistics, 0, GTK_CUSTOM_TABLE_DESC);

        double stats[10][6];
        memset(stats, '\0', sizeof(stats));

        int graph_apex = 0;
        int year_average = 0;
        int vote_average = 0;
        int time_average = 0;
        double imdb_average = 0;
        double flux_average = 0;

        for(i = 1; i < rows; i++) {

            /* add up totals per rating */
            stats[atoi(results[i][8])-1][2] += 1;
            stats[atoi(results[i][8])-1][3] += atoi(results[i][9]);
            stats[atoi(results[i][8])-1][4] += atoi(results[i][10]);
            stats[atoi(results[i][8])-1][5] += atoi(results[i][11]);

            /* add up totals for vote averages */
            vote_average += atoi(results[i][8]);
            imdb_average += atoi(results[i][9]);
            time_average += atoi(results[i][10]);
            year_average += atoi(results[i][11]);

            flux_average += atoi(results[i][8]) - atoi(results[i][9]);
        }

        for(i = 0; i < 10; i++) {

            /* find graph apex, i.e. the longest bar on screen */
            graph_apex = stats[i][2] > graph_apex ? stats[i][2]: graph_apex;
        } 

        for(i = 0, j = 10; i < 10 && j > 0; i++, j++) {
 
            /* calculate graph value from vote amounts, graph is 0-100 */
            stats[i][0] = stats[i][2] != 0 ? 100 / (graph_apex / stats[i][2]) : 0;
            /* calculate percentage for each rating */
            stats[i][1] = stats[i][2] != 0 ? (stats[i][2] / rows) * 100: 0;
            /* calculate imdb averages for each rating */
            stats[i][3] = stats[i][2] != 0 ? stats[i][3] / stats[i][2] : 0;
            /* calculate year averages for each rating */
            stats[i][4] = stats[i][2] != 0 ? stats[i][4] / stats[i][2] : 0;
            /* calculate year averages for each rating */
            stats[i][5] = stats[i][2] != 0 ? stats[i][5] / stats[i][2] : 0;
        }

        double flux = 0;

        /* add statistics to widget table */
        for(i = 0, j = 9; i < 10 && j >= 0; i++, j--) {
            
            flux = stats[i][2] > 0 ? (i + 1) - stats[i][3] : 0.00;

            sprintf(temp, "%1.2f", stats[i][3]);
            gtk_custom_table_set_cell_text(nb_tab_statistics, 1, j, temp);
            sprintf(temp, "%+1.2f", flux);
            gtk_custom_table_set_cell_text(nb_tab_statistics, 2, j, temp);
            sprintf(temp, "%1.0f", stats[i][0]);
            gtk_custom_table_set_cell_text(nb_tab_statistics, 3, j, temp);
            sprintf(temp, "%2.2f %%", stats[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_statistics, 4, j, temp);
            sprintf(temp, "%1.0f", stats[i][2]);
            gtk_custom_table_set_cell_text(nb_tab_statistics, 5, j, temp);
            sprintf(temp, "%1.2f", stats[i][4]);
            gtk_custom_table_set_cell_text(nb_tab_statistics, 6, j, temp);
            sprintf(temp, "%1.2f", stats[i][5]);
            gtk_custom_table_set_cell_text(nb_tab_statistics, 7, j, temp);

            /* make sure value falls within color range.. */
            int cell_to_color = (int)stats[i][3] - 1;

            /* reset background color */
            gtk_custom_table_set_cell_color_enable(nb_tab_statistics, 1, j, 
                FALSE);

            if(cell_to_color < 10 && cell_to_color >= 0) {
                gtk_custom_table_set_cell_color(nb_tab_statistics, 1, j, 
                    colors[(int)stats[i][3] - 1]);
            }
            else {
                gtk_custom_table_set_cell_color(nb_tab_statistics, 1, j, 
                    colors[1]);
            }

            /* reset background color */
            gtk_custom_table_set_cell_color_enable(nb_tab_statistics, 2, j, 
                FALSE);

            /* add new background color to flux */
            if(flux > 0) {
                gtk_custom_table_set_cell_color(nb_tab_statistics, 2, j, 
                    colors[8]);
            }
            else {
                 gtk_custom_table_set_cell_color(nb_tab_statistics, 2, j, 
                    colors[1]);
            }
        }

        /* add statistics footer */
        sprintf(temp, "%2.2f", (double)vote_average / (rows -1));
        gtk_custom_table_set_foot_text(nb_tab_statistics, 0, temp);
        sprintf(temp, "%2.2f", (double)imdb_average / (rows - 1));
        gtk_custom_table_set_foot_text(nb_tab_statistics, 1, temp);
        sprintf(temp, "%+2.2f", (double)flux_average / (rows - 1));
        gtk_custom_table_set_foot_text(nb_tab_statistics, 2, temp);
        sprintf(temp, "You have rated %d, on average %1.2f", 
            (rows - 1), (double)vote_average / (rows - 1));
        gtk_custom_table_set_foot_text(nb_tab_statistics, 3, temp);
        gtk_custom_table_set_foot_text(nb_tab_statistics, 4, "100.00 %");
        sprintf(temp, "%d", (rows - 1));
        gtk_custom_table_set_foot_text(nb_tab_statistics, 5, temp);
        sprintf(temp, "%4.2f", (double)time_average / (rows - 1));
        gtk_custom_table_set_foot_text(nb_tab_statistics, 6, temp);
        sprintf(temp, "%4.2f", (double)year_average / (rows - 1));
        gtk_custom_table_set_foot_text(nb_tab_statistics, 7, temp);

        gtk_custom_table_set_sortable(nb_tab_statistics, TRUE);

        /* update mymovies tab with new data */
        gtk_custom_table_resize(nb_tab_mymovies, -1, (rows - 1));

        /* add text to widget table */
        for(i = 1, j = 0; i < rows; i++, j++) {

            sprintf(temp, "%d", i);

            gtk_custom_table_set_cell_text(nb_tab_mymovies, 0, j, temp);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 1, j, results[i][9]);
            gtk_custom_table_set_cell_color(nb_tab_mymovies, 1, j, 
                colors[(int)atoi(results[i][9]) - 1]);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 2, j, results[i][8]);
            gtk_custom_table_set_cell_color(nb_tab_mymovies, 2, j, 
                colors[atoi(results[i][8]) - 1]);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 3, j, results[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 4, j, results[i][5]);
            gtk_custom_table_set_cell_text(nb_tab_mymovies, 5, j, results[i][11]);


            /* add 'my rating' to top250 tab if applicable */
            int index_top = gtk_custom_table_get_indexof(nb_tab_top250, 
                results[i][1]);

            if(index_top >= 0) {

                gtk_custom_table_set_cell_text(nb_tab_top250, 2, index_top, 
                    results[i][8]);
                gtk_custom_table_set_cell_color(nb_tab_top250, 2, index_top, 
                    colors[atoi(results[i][8]) - 1]);
            }

            /* add 'my rating' to boxoffice tab if applicable */
            int index_box = gtk_custom_table_get_indexof(nb_tab_boxoffice, 
                results[i][1]);

            if(index_box >= 0) {

                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, index_box, 
                    results[i][9]);
                gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, index_box, 
                    colors[atoi(results[i][9]) - 1]);
                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 2, index_box, 
                    results[i][8]);
                gtk_custom_table_set_cell_color(nb_tab_boxoffice, 2, index_box, 
                    colors[atoi(results[i][8]) - 1]);
            }

            /* add 'my rating' to lists tab if applicable */
            int index_lst = gtk_custom_table_get_indexof(nb_tab_lists, 
                results[i][1]);

            if(index_lst >= 0) {

                gtk_custom_table_set_cell_text(nb_tab_lists, 2, index_lst, 
                    results[i][8]);
                gtk_custom_table_set_cell_color(nb_tab_lists, 2, index_lst, 
                    colors[atoi(results[i][8]) - 1]);
            }
        }

        gtk_custom_table_set_sortable(nb_tab_mymovies, TRUE);
        gtk_custom_table_sort(nb_tab_mymovies, 0, GTK_CUSTOM_TABLE_ASC);

        free_memory(results, cols, rows);
    }
    else {

        /* update lists tab with new data */
        gtk_custom_table_resize(nb_tab_lists, -1, (rows - 1));

        /* add text to widget table */
        for(i = 1, j = 0; i < rows; i++, j++) {

            sprintf(temp, "%d", i);

            gtk_custom_table_set_cell_text(nb_tab_lists, 0, j, temp);
            gtk_custom_table_set_cell_text(nb_tab_lists, 1, j, results[i][8]); 
            gtk_custom_table_set_cell_text(nb_tab_lists, 2, j, "0");
            gtk_custom_table_set_cell_text(nb_tab_lists, 3, j, results[i][1]);
            gtk_custom_table_set_cell_text(nb_tab_lists, 4, j, results[i][5]);
            gtk_custom_table_set_cell_text(nb_tab_lists, 5, j, results[i][10]);
            
            /* make sure value falls within color range.. */
            int cell_to_color = (int)atoi(results[i][8]) - 1;

            if(cell_to_color < 10 && cell_to_color >= 0) {
                gtk_custom_table_set_cell_color(nb_tab_lists, 1, j, 
                    colors[(int)atoi(results[i][8]) - 1]);
            }

            /* add 'my rating' to lists tab if applicable */
            int index_lst = gtk_custom_table_get_indexof(nb_tab_mymovies, 
                results[i][1]);

            if(index_lst >= 0) {
                
                char *table_row[gtk_custom_table_get_rows(nb_tab_mymovies)];

                gtk_custom_table_get_row(nb_tab_mymovies, index_lst, table_row);

                gtk_custom_table_set_cell_text(nb_tab_lists, 2, j, 
                    table_row[2]);
                gtk_custom_table_set_cell_color(nb_tab_lists, 2, j, 
                    colors[atoi(table_row[2]) - 1]);
            }

            /* add imdb-rating to boxoffice tab if applicable */
            int index_box = gtk_custom_table_get_indexof(nb_tab_boxoffice, 
                results[i][8]);

            if(index_box >= 0) {

                gtk_custom_table_set_cell_text(nb_tab_boxoffice, 1, index_box, 
                    results[i][8]);

                if(cell_to_color < 10 && cell_to_color >= 0) {
                    gtk_custom_table_set_cell_color(nb_tab_boxoffice, 1, 
                        index_box, colors[(int)atoi(results[i][8]) - 1]);
                }
            }
        }

        gtk_custom_table_set_sortable(nb_tab_lists, TRUE);
        gtk_custom_table_sort(nb_tab_lists, 0, GTK_CUSTOM_TABLE_ASC);

        free_memory(results, cols, rows);
    }

    gtk_custom_table_refresh(window);

    return 1;
}

/* open a ratings/list file from dialog */
void menu_signal_open(GtkWidget *widget, gpointer data) {

    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new(
        "Open File", 
        GTK_WINDOW(widget), 
        GTK_FILE_CHOOSER_ACTION_OPEN,
        GTK_STOCK_CANCEL, 
        GTK_RESPONSE_CANCEL,
        GTK_STOCK_OPEN, 
        GTK_RESPONSE_OK,
        NULL);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), APP_ICON, NULL);

    if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {

        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        
        char *temp = NULL;
        char *stat = NULL;

        /* attempt to open ratings file */
        if(menu_open_ratings(filename)) {
            stat = "Opened ratings file: ";
        }
        else {
            stat = "Unable to open file: ";
        }

        temp = malloc(strlen(stat) + strlen(filename) + 1);
        strcpy(temp, stat),
        strcat(temp, filename);
            
        gtk_statusbar_push(GTK_STATUSBAR(status), 1, temp);

        free(temp);
    }

    gtk_widget_destroy(dialog);
}


