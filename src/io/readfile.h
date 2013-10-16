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


#ifndef _READFILE_
#define _READFILE_

#define READ_SIZE 512
#define STEP_SIZE 256

#define HEX_D_OFF 0x30 /* ascii offset to 0,1,2.. */
#define HEX_C_OFF 0x41 /* ascii offset to A,B,C.. */

typedef struct result {

    int rows;
    int cols;
    char ***results;

} ResultList;

int  readfile(ResultList *list, char *filename);
void readfile_free(ResultList *list);

#endif

