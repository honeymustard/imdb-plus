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
#include <sys/stat.h>
#include <sys/types.h>
#include "main.h"
#include "ui/globals/globals.h"
#include "io/paths.h"


/**
 * make home directory, downloads directory therein..
 * @param char **path    empty string pointer..
 * @param char **down    empty string pointer..
 */
void make_paths(char **path, char **down) {

    /* create home directory */
    #ifdef WINDOWS

        #define _WIN32_IE 0x0500
    
        #include "windows.h"
        #include "Shlobj.h"

        TCHAR home[MAX_PATH];

        SHGetFolderPath(0, CSIDL_APPDATA, 0, 
            SHGFP_TYPE_CURRENT, home);

    #endif
    #ifdef LINUX

        char *home = getenv("HOME");

    #endif

    /* create home directory */
    *path = malloc(strlen(home) + strlen(APP_FOLD) + 3);

    strcpy(*path, home);
    strcat(*path, "/");
    strcat(*path, APP_FOLD);
    strcat(*path, "/");

    /* create downloads directory */
    *down = malloc(strlen(*path) + strlen(APP_DOWN) + 3);

    strcpy(*down, *path);
    strcat(*down, APP_DOWN);
    strcat(*down, "/");

    #ifdef WINDOWS

        CreateDirectory(*path, NULL);
        CreateDirectory(*down, NULL);

    #endif
    #ifdef LINUX

        mkdir(*path, S_IRWXU);
        mkdir(*down, S_IRWXU);

    #endif
}


/**
 * append path to home directory to all filenames..
 * @param char *path    path to home directory..
 */
void make_filenames(char *path) {

    /* path constants */
    char *top_tmp = malloc(strlen(path) + strlen(TOP_TMP) + 1);
    char *top_csv = malloc(strlen(path) + strlen(TOP_CSV) + 1);
    char *bot_tmp = malloc(strlen(path) + strlen(BOT_TMP) + 1);
    char *bot_csv = malloc(strlen(path) + strlen(BOT_CSV) + 1);
    char *box_tmp = malloc(strlen(path) + strlen(BOX_TMP) + 1);
    char *box_csv = malloc(strlen(path) + strlen(BOX_CSV) + 1);

    /* make paths to home directory */
    strcpy(top_tmp, path);
    strcpy(top_csv, path);
    strcpy(bot_tmp, path);
    strcpy(bot_csv, path);
    strcpy(box_tmp, path);
    strcpy(box_csv, path);

    strcat(top_tmp, TOP_TMP);
    strcat(top_csv, TOP_CSV);
    strcat(bot_tmp, BOT_TMP);
    strcat(bot_csv, BOT_CSV);
    strcat(box_tmp, BOX_TMP);
    strcat(box_csv, BOX_CSV);

    /* set global paths */
    globals_set(CONST_TOP_TMP, top_tmp);
    globals_set(CONST_TOP_CSV, top_csv);
    globals_set(CONST_TOP_URL, TOP_URL);
    globals_set(CONST_BOT_TMP, bot_tmp);
    globals_set(CONST_BOT_CSV, bot_csv);
    globals_set(CONST_BOT_URL, BOT_URL);
    globals_set(CONST_BOX_TMP, box_tmp);
    globals_set(CONST_BOX_CSV, box_csv);
    globals_set(CONST_BOX_URL, BOX_URL);
    globals_set(CONST_RAT_URL, RAT_URL);

    free(top_tmp);
    free(top_csv);
    free(bot_tmp);
    free(bot_csv);
    free(box_tmp);
    free(box_csv);
}

