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


#ifndef _UI_FILL_
#define _UI_FILL_

#include "../ui.h"

int menu_signal_update_box();
int menu_signal_update_bot();
int menu_signal_update_top();

void open_allstats(double allstats[5], int row, int rows);
void open_compare(GtkWidget *current, GtkWidget *other);
void open_list(char ****results, int rows);
void open_movies(char ****results, int rows);
void open_movie_stats(char ****results, int rows, char *filename);
void open_list_stats(char ****results, int rows, char *filename);

#endif

