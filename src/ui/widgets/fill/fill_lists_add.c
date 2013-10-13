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
#include "ui/widgets/fill/fill.h"
#include "ui/env/colors.h"
#include "ui/table/gtk_custom_table.h"


/**
 * exchange ratings with other lists
 * @param State *state    current state object
 */
void ui_fill_lists_mov_add(State *state) {

    /* make some aliases */
    GtkWidget *table1 = state->tab1->table;
    GtkWidget *table2 = state->tab2->table;
    GtkWidget *top = nb_lists_top_tab->table;
    GtkWidget *bot = nb_lists_bot_tab->table;
    GtkWidget *box = nb_lists_box_tab->table;
    
    int col1 = state->tab1_vcol;
    int col2 = state->tab2_vcol;

    int i = 0;
    int j = 0;

    /* clear associated color from top250 */
    for(i = 0; i < gtk_custom_table_get_rows(top); i++) {
        
        gtk_custom_table_set_cell_text(top, col1, i, "0");
        gtk_custom_table_set_cell_color(top, col1, i, not_app);
    }

    /* clear associated color from bot100 */
    for(i = 0; i < gtk_custom_table_get_rows(bot); i++) {
        
        gtk_custom_table_set_cell_text(bot, col1, i, "0");
        gtk_custom_table_set_cell_color(bot, col1, i, not_app);
    }

    /* clear associated color from boxoffice */
    for(i = 0; i < gtk_custom_table_get_rows(box); i++) {
        
        gtk_custom_table_set_cell_text(box, col1, i, "0");
        gtk_custom_table_set_cell_color(box, col1, i, not_app);
    }

    /* clear associated color from other list */
    for(i = 0; i < gtk_custom_table_get_rows(table2); i++) {

        gtk_custom_table_set_cell_text(table2, col1, i, "0");
        gtk_custom_table_set_cell_color(table2, col1, i, not_app);
    }

    for(i = 0; i < gtk_custom_table_get_rows(table1); i++) {

        char *imdb_str = gtk_custom_table_get_cell_text(table1, 1, i);
        char *vote_str = gtk_custom_table_get_cell_text(table1, col1, i);
        char *id = gtk_custom_table_get_cell_text(table1, 4, i);

        int imdb = atoi(imdb_str);
        int vote = atoi(vote_str);

        int imdb_col = imdb > 0 ? imdb - 1 : 0;
        int vote_col = vote > 0 ? vote - 1 : 0;

        /* add rating to top250 tab */
        if((j = gtk_custom_table_get_indexof(top, id)) >= 0) {

            gtk_custom_table_set_cell_text(top, col1, j, vote_str);
            gtk_custom_table_set_cell_color(top, col1, j, colors[vote_col]);
        }

        /* add rating to bottom100 tab  */
        if((j = gtk_custom_table_get_indexof(bot, id)) >= 0) {

            gtk_custom_table_set_cell_text(bot, col1, j, vote_str);
            gtk_custom_table_set_cell_color(bot, col1, j, colors[vote_col]);
        }

        /* add rating, imdb-rating to boxoffice */
        if((j = gtk_custom_table_get_indexof(box, id)) >= 0) {

            gtk_custom_table_set_cell_text(box, 1, j, imdb_str);
            gtk_custom_table_set_cell_text(box, col1, j, vote_str);
            gtk_custom_table_set_cell_color(box, 1, j, colors[imdb_col]);
            gtk_custom_table_set_cell_color(box, col1, j, colors[vote_col]);
        }

        /* add other rating to this tab and vice versa */
        if((j = gtk_custom_table_get_indexof(table2, id)) >= 0) {

            char *rating = (gtk_custom_table_get_cell_text(table2, col2, j));
            int vote_col2 = atoi(rating);

            gtk_custom_table_set_cell_text(table1, col2, i, rating);
            gtk_custom_table_set_cell_color(table1, col2, i, 
                vote_col2 > 0 ? colors[vote_col2 - 1] : not_app);

            gtk_custom_table_set_cell_text(table2, col1, j, vote_str);
            gtk_custom_table_set_cell_color(table2, col1, j, 
                vote_col > 0 ? colors[vote_col] : not_app);
        }
    }
}


/**
 * exchange ratings with other lists
 * @param State *state    current state object
 */
void ui_fill_lists_lst_add(State *state) {

    GtkWidget *table1 = state->tab1->table;
    GtkWidget *table2 = state->tab2->table;
    GtkWidget *top = nb_lists_top_tab->table;
    GtkWidget *bot = nb_lists_bot_tab->table;
    GtkWidget *box = nb_lists_box_tab->table;
    
    int col1 = state->tab1_vcol;
    int col2 = state->tab2_vcol;

    int i = 0;
    int j = 0;

    /* clear associated color from top250 */
    for(i = 0; i < gtk_custom_table_get_rows(top); i++) {
        
        gtk_custom_table_set_cell_text(top, col1, i, "0");
        gtk_custom_table_set_cell_color(top, col1, i, not_app);
    }

    /* clear associated color from bot100 */
    for(i = 0; i < gtk_custom_table_get_rows(bot); i++) {
        
        gtk_custom_table_set_cell_text(bot, col1, i, "0");
        gtk_custom_table_set_cell_color(bot, col1, i, not_app);
    }

    /* clear associated color from boxoffice */
    for(i = 0; i < gtk_custom_table_get_rows(box); i++) {
        
        gtk_custom_table_set_cell_text(box, col1, i, "0");
        gtk_custom_table_set_cell_color(box, col1, i, not_app);
    }

    /* clear values from other list */
    for(i = 0; i < gtk_custom_table_get_rows(table2); i++) {
        
        gtk_custom_table_set_cell_text(table2, col1, i, "0");
        gtk_custom_table_set_cell_color(table2, col1, i, not_app);
    }

    for(i = 0; i < gtk_custom_table_get_rows(table1); i++) {

        char *imdb_str = gtk_custom_table_get_cell_text(table1, 1, i);
        char *id = gtk_custom_table_get_cell_text(table1, 4, i);

        int imdb = atoi(imdb_str);
        int imdb_col = imdb > 0 ? imdb - 1 : 0;

        /* add other rating to this tab */
        if((j = gtk_custom_table_get_indexof(table2, id)) >= 0) {
            
            char *rating = gtk_custom_table_get_cell_text(table2, col2, j);
            int vote_col2 = atoi(rating);

            gtk_custom_table_set_cell_text(table1, col2, i, rating);
            gtk_custom_table_set_cell_color(table1, col2, i, 
                vote_col2 > 0 ? colors[vote_col2 - 1] : not_app);
        }

        /* add imdb-rating to boxoffice tab */
        if((j = gtk_custom_table_get_indexof(box, id)) >= 0) {

            gtk_custom_table_set_cell_text(box, 1, j, imdb_str);
            gtk_custom_table_set_cell_color(box, 1, j, colors[imdb_col]);
        }
    }
}


/**
 * exchange ratings with other lists
 * @param State *state    current state object
 */
void ui_fill_lists_cmp_add(State *state) {

    GtkWidget *table1 = state->tab1->table;

    int i = 0;

    for(i = 0; i < gtk_custom_table_get_rows(table1); i++) {

        char *imdb_str = gtk_custom_table_get_cell_text(table1, 1, i);
        char *vote_str1 = gtk_custom_table_get_cell_text(table1, 2, i);
        char *vote_str2 = gtk_custom_table_get_cell_text(table1, 3, i);

        /* set background colors */
        int imdb = atoi(imdb_str);
        int vote1 = atoi(vote_str1);
        int vote2 = atoi(vote_str2);

        gtk_custom_table_set_cell_color(table1, 1, i, 
            imdb > 0 ? colors[imdb - 1] : not_app);
        gtk_custom_table_set_cell_color(table1, 2, i, 
            vote1 > 0 ? colors[vote1 - 1] : not_app);
        gtk_custom_table_set_cell_color(table1, 3, i, 
            vote2 > 0 ? colors[vote2 - 1] : not_app);
    }
}

/*
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



void ui_fill_lists_box_add(State *state) {

        // get imdb ratings from other tables
        double n = find_rating(list->results[i][1]);
        n = n > 0 ? n : imdb;

        sprintf(temp, "%1.1f", n);
        gtk_custom_table_set_cell_text(table, 1, i, temp);

        gtk_custom_table_set_cell_color(table, 1, i, 
            n <= 0 ? not_app : colors[(int)n - 1]);

}
*/
