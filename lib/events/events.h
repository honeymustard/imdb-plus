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


#ifndef _EVENTS_
#define _EVENTS_

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

/* include external headers */
#include "../../master.h"
#include "../../widgets.h"
#include "../gtk_custom_table/gtk_custom_table.h"
#include "../download.h"
#include "../regex.h"

extern int menu_open_ratings(char *filename);
extern void set_imdb_rating(int index, int row, GtkWidget *copy, GtkWidget *paste);

/* main window events */
void menu_signal_about(GtkWidget *widget, gpointer data);
void menu_signal_open(GtkWidget *widget, gpointer data);
void menu_signal_new(GtkWidget *widget, gpointer data);
void menu_signal_update(GtkWidget *widget, gpointer data);
void menu_signal_quit(GtkWidget *widget, gpointer data);

#endif

