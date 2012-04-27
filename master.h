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

#ifndef MASTER 
#define MASTER

#define APP_NAME "imdb-plus"

/* set alternate path for linux install */
#ifdef INSTALL
    #define CONST_PREFIX "/usr/share/"APP_NAME"/res/" 
#else
    #define CONST_PREFIX "./res/" 
#endif

#define APP_ADDR "/usr/share/"APP_NAME
#define APP_ICON CONST_PREFIX "graphics/imdb-plus.png"
#define APP_TITL APP_NAME " " APP_VERS
#define APP_COPY "Copyright \xc2\xa9 2011-2012 Adrian Solumsmo"
#define APP_DESC APP_NAME " is a statistical extension application for IMDB"
#define APP_HOME "https://github.com/honeymustard/imdb-plus"

/* url constants */
#define CONST_BOX "http://akas.imdb.com/boxoffice/alltimegross?region=world-wide"
#define CONST_TOP "http://akas.imdb.com/chart/top"
#define CONST_BOT "http://akas.imdb.com/chart/bottom"
#define CONST_URL "http://akas.imdb.com/list/export?list_id=ratings&author_id=ur"

/* path constants */
#define CONST_TOP_SAV CONST_PREFIX"top250.html"
#define CONST_TOP_CSV CONST_PREFIX"top250.csv"
#define CONST_BOT_SAV CONST_PREFIX"bottom100.html"
#define CONST_BOT_CSV CONST_PREFIX"bottom100.csv"
#define CONST_BOX_SAV CONST_PREFIX"boxoffice.html"
#define CONST_BOX_CSV CONST_PREFIX"boxoffice.csv" 


/* credits aka self-praise */
const char *APP_AUTH[3] = {
    "Adrian Solumsmo <adrian.solumsmo@gmail.com>\n",
    "Thanks to:\n\nThe GnuWin32 project (pcre)\nMartin Pool (natcmpsort)",
    NULL,
};

/* default license */
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


/* solid green to solid red, for ratings */
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


/* graph background colors */
double graph_bg[3] = {
    0.90, 
    0.90, 
    1.00,
};


#endif

