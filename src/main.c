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


#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "main.h"
#include "ui/globals/globals.h"
#include "ui/widgets/widgets.h"
#include "ui/widgets/set/set.h"
#include "io/paths.h"


/**
 * main program entry point
 */
int main(int argc, char *argv[]) {

    g_thread_init(NULL);
    gtk_init(&argc, &argv);

    /* set version global */
    set_global(CONST_VERSION, VERSION);

    /* set paths */
    char *path = NULL;
    char *down = NULL;

    make_paths(&path, &down);
    make_filenames(path);

    set_global(CONST_HOME, path);
    set_global(CONST_DOWN, down);

    free(path);
    free(down);

    /* set default ui */
    ui_set_init();

    /* init gtk main */
    gdk_threads_enter();
    gtk_main();
    gdk_threads_leave();

    return 0;
}

