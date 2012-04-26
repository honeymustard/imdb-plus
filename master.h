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

#ifndef MASTER 
#define MASTER
    
    /* project started december 27th 2011 */
    #define APP_NAME "imdb-plus"
    #define APP_VERS "0.0.5"
    #define APP_ADDR "/usr/share/"APP_NAME
    #define APP_ICON "./res/graphics/imdb-plus.png"
    #define APP_TITL APP_NAME " " APP_VERS
    #define APP_COPY "Copyright (C) 2011-2012 Adrian Solumsmo"
    #define APP_DESC APP_NAME " is a statistical extension application for IMDB"
    #define APP_HOME "https://sourceforge.net/projects/imdb-plus/"

    /* url constants */
    #define CONST_BOX "http://akas.imdb.com/boxoffice/alltimegross?region=world-wide"
    #define CONST_TOP "http://akas.imdb.com/chart/top"
    #define CONST_BOT "http://akas.imdb.com/chart/bottom"
    #define CONST_URL "http://akas.imdb.com/list/export?list_id=ratings&author_id=ur"

    /* path constants */
    #define CONST_PREFIX "./res/data/" 
    #define CONST_TOP_SAV CONST_PREFIX"top250.html"
    #define CONST_TOP_CSV CONST_PREFIX"top250.csv"
    #define CONST_BOT_SAV CONST_PREFIX"bottom100.html"
    #define CONST_BOT_CSV CONST_PREFIX"bottom100.csv"
    #define CONST_BOX_SAV CONST_PREFIX"boxoffice.html"
    #define CONST_BOX_CSV CONST_PREFIX"boxoffice.csv" 
    
    /* credits */
    const char *APP_AUTH[4] = {
        "Adrian Solumsmo <adrian.solumsmo@gmail.com>",
        "Thanks to the GnuWin32 project (PCRE)",
        "Thanks to Martin Pool (natcmpsort)",
        NULL,
    };

    const char *APP_LICN = "\
Copyright (C) imdb-plus  Adrian Solumsmo\n\
\n\
imdb-plus program is free software: you can redistribute it and/or modify\n\
it under the terms of the GNU General Public License as published by\n\
the Free Software Foundation, either version 3 of the License, or\n\
(at your option) any later version.\n\
\n\
imdb-plus program is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
GNU General Public License for more details.\n\
\n\
You should have received a copy of the GNU General Public License\n\
along with this program.  If not, see <http://www.gnu.org/licenses/>.";


    /* solid green to solid red */
    double colors[10][3] = {
        {1.00, 0.00, 0.00}, 
        {1.00, 0.15, 0.00}, 
        {1.00, 0.35, 0.00}, 
        {1.00, 0.55, 0.00}, 
        {1.00, 0.75, 0.00}, 
        {1.00, 0.95, 0.00}, 
        {0.85, 1.00, 0.00}, 
        {0.65, 1.00, 0.00}, 
        {0.35, 1.00, 0.00}, 
        {0.00, 1.00, 0.00}, 
    };

    double graph_bg[3] = {
        0.90, 
        0.90, 
        1.00,
    };


#endif

