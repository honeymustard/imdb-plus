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


#include "colors.h"


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
    0.90,
};

/* graph foreground colors */
double graph_fg1[3] = {
    1.00,
    0.00,
    1.00,
};

double graph_fg2[3] = {
    1.00,
    0.95,
    0.00,
};

double graph_fg3[3] = {
    0.20,
    0.95,
    0.20,
};

double not_app[3] = {
    0.40,
    0.75,
    0.90,
};

