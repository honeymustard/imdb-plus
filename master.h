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


/* project started december 27th 2011 */

#ifndef _MASTER_
#define _MASTER_

/* set icon path */
#ifdef INSTALL
    #define IMG_DIR "/usr/share/pixmaps/" 
#else
    #define IMG_DIR "./share/icons/" 
#endif

/* application */
#define APP_NAME "imdb-plus"
#define APP_ICON IMG_DIR "imdb-plus.png"
#define APP_DIRE ".imdb-plus"
#define APP_TITL APP_NAME " " APP_VERS
#define APP_COPY "Copyright \xc2\xa9 2011-2012 Adrian Solumsmo"
#define APP_DESC APP_NAME " is a statistical extension application for IMDB"
#define APP_HOME "https://github.com/honeymustard/imdb-plus"

/* constants */
#define CONST_HOME    0x01
#define CONST_TOP_TMP 0x02
#define CONST_TOP_CSV 0x03
#define CONST_TOP_URL 0x04
#define CONST_BOT_TMP 0x05
#define CONST_BOT_CSV 0x06
#define CONST_BOT_URL 0x07
#define CONST_BOX_TMP 0x08
#define CONST_BOX_CSV 0x09
#define CONST_BOX_URL 0x10
#define CONST_RAT_URL 0x11 

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

