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

    gtk_init(&argc, &argv);

    globals_init();

    /* set global version and appname */
    globals_set(CONST_VERSION, VERSION);
    globals_set(CONST_APPNAME, APP_NAME " - " VERSION);

    /* set paths */
    char *path = NULL;
    char *down = NULL;

    make_paths(&path, &down);
    make_filenames(path);

    globals_set(CONST_HOME, path);
    globals_set(CONST_DOWN, down);

    free(path);
    free(down);

    /* set default ui */
    ui_set_init();

    gtk_main();

    return 0;
}

