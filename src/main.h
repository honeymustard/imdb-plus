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


/* project started december 27th 2011 */

#ifndef _MAIN_
#define _MAIN_

/* set icon path */
#ifdef INSTALL
    #define IMG_DIR "/usr/share/pixmaps/" 
#else
    #define IMG_DIR "./share/icons/" 
#endif

#define DIR_ICON IMG_DIR "imdb-plus/"

/* set default home */
#ifdef LINUX
    #define APP_FOLD ".imdb-plus"
#endif
#ifdef WINDOWS
    #define APP_FOLD "imdb-plus"
#endif

/* application */
#define APP_NAME "imdb-plus"
#define APP_DOWN "ratings"
#define APP_ICON IMG_DIR "imdb-plus.png"
#define APP_COPY "Copyright \xc2\xa9 2011-2012 Adrian Solumsmo"
#define APP_DESC APP_NAME " is a statistical application for movie fans"
#define APP_HOME "https://github.com/honeymustard/imdb-plus"

/* filenames */
#define TOP_TMP "top250.html"
#define TOP_CSV "top250.csv"
#define BOT_TMP "bottom100.html"
#define BOT_CSV "bottom100.csv"
#define BOX_TMP "boxoffice.html"
#define BOX_CSV "boxoffice.csv" 

/* urls */
#define BOX_URL "http://akas.imdb.com/boxoffice/alltimegross?region=world-wide"
#define TOP_URL "http://akas.imdb.com/chart/top"
#define BOT_URL "http://akas.imdb.com/chart/bottom"
#define RAT_URL "http://akas.imdb.com/list/export?list_id=ratings&author_id=ur"

#endif

