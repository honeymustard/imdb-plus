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
#include "../../main.h"
#include "../ui/ui_widgets.h"
#include "../readfile.h"
#include "../openfile.h"
#include "../download.h"
#include "../parsefile.h"
#include "../colors.h"
#include "../globals.h"
#include "../patterns.h"

/* main window events */
void menu_signal_about(GtkWidget *widget, gpointer data);
void menu_signal_open(GtkWidget *widget, gpointer data);
void menu_signal_new(GtkWidget *widget, gpointer data);
void menu_signal_update(GtkWidget *widget, gpointer data);
void menu_signal_quit(GtkWidget *widget, gpointer data);

#endif
