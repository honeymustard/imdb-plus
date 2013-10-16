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


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "io/readfile.h"


/**
 * free memory from occupied by results..
 * @param ResultList **list    list to be freed
 */
void readfile_free(ResultList *list) {
 
    int i = 0;
    int j = 0;

    for(i = 0; i < list->rows; i++) {

        for(j = 0; j < list->cols; j++) {

            if(list->results[i][j] != NULL) {
                free(list->results[i][j]);
            }
        }

        free(list->results[i]); 
    }

    free(list->results);
}


/* function of minor convenience */
int is_0_to_9(char byte) {
    
    return byte >= '0' && byte <= '9';
}

/* function of minor convenience */
int is_a_to_f(char byte) {
    
    return byte >= 'A' && byte <= 'F';
}

/* function of minor convenience */
int is_0_to_f(char byte) {

   return is_0_to_9(byte) || is_a_to_f(byte);
}


/**
 * decode entity in buffer at index i, return offset
 * @param char *buffer   string buffer with entity
 * @return char *        returns newly allocated string
 */
char * decode(char *buffer) {

    char *needle = "&#x";
    int length = strlen(needle);

    int len = strlen(buffer);

    char *tmp = malloc(strlen(buffer) + 1);
    strcpy(tmp, buffer);

    while(1) {

        buffer = strstr(buffer, needle);

        if(buffer == NULL) {
            free(buffer);
            return tmp;
        }

        int tmp_len = len - strlen(buffer);

        buffer = buffer + length;
        
        if(buffer[0] != '\0' && 
           buffer[1] != '\0' && 
           buffer[2] != '\0' && 
           buffer[2] == ';') {
        
            char curr = buffer[0];
            char next = buffer[1];
            char *copy = &buffer[3];
            unsigned char temp = 0;

            if(is_0_to_f(next)) {

                /* for conventional ascii chars */
                if(is_0_to_9(curr)) {

                    temp = (curr - HEX_D_OFF) << 4;
                    temp |= next - HEX_D_OFF;

                    tmp[tmp_len] = temp;
                    strcpy(&tmp[tmp_len+1], copy);

                    len -= 5;
                }
                /* unicode point range A-B/0-F */
                else if((curr >= 'A' && curr <= 'B')) {

                    temp = ((curr + 10) - HEX_C_OFF) << 4;

                    if(is_a_to_f(next)) {
                        temp |= (next + 10) - HEX_C_OFF;
                    }
                    else {
                        temp |= next - HEX_D_OFF;
                    }

                    tmp[tmp_len] = 0xC2;
                    tmp[tmp_len+1] = temp;
                    strcpy(&tmp[tmp_len+2], copy);

                    len -= 4;
                }
                /* unicode point range C-F/0-F */
                else if((curr >= 'C' && curr <= 'F')) {

                    char values[] = {8, 9, 10, 11};

                    temp = values[curr - (HEX_C_OFF + 2)] << 4;

                    if(is_a_to_f(next)) {
                        temp |= (next + 10) - HEX_C_OFF;
                    }
                    else {
                        temp |= next - HEX_D_OFF;
                    }

                    tmp[tmp_len] = 0xC3;
                    tmp[tmp_len+1] = temp;
                    strcpy(&tmp[tmp_len+2], copy);

                    len -= 4;
                }
                /* else, just add question mark */
                else {

                    tmp[tmp_len] = 0x3F;
                    strcpy(&tmp[tmp_len+1], copy);
                    len -= 5; 

                    printf(" Unkown character found\n");
                }
            }
        }
    }    
}


/**
 * parse a csv line and add values to buffer
 * @param char **container    array big enough to contain parsed values
 * @param char *buffer        line to be parsed
 * @param int cols            number of columns expected
 * @return int                returns 1
 */
int parse_line(char **container, char *buffer, int cols) {

    char *delim = "\",\"";

    int delim_len = strlen(delim);
    int total_len = strlen(buffer);

    /* clip each end of original buffer */
    char *temp = malloc(strlen(buffer));
    strncpy(temp, &buffer[1], total_len - 3);
    temp[total_len - 3] = '\0';

    /* copy back into buffer */
    strcpy(buffer, temp);

    int offset = 0;

    int i = 0;

    for(i = 0; ; i++) {
   
        temp = strstr(temp, delim);

        int offset_old = offset;

        offset = temp == NULL ? total_len : total_len - strlen(temp);

        int bytes = (offset - delim_len) - offset_old;

        if(bytes == 0) {

            container[i] = malloc(2);
            strcpy(container[i], "0");
        }
        else {
            container[i] = malloc(bytes + 1);
            strncpy(container[i], &buffer[offset_old], bytes);
            container[i][bytes] = '\0';
        }

        container[i] = decode(container[i]);

        if(temp == NULL) {
            break;
        }

        temp = temp + delim_len;
    }
    
    free(temp);

    return ++i == cols;
}


/**
 * calculate number of columns in a buffer..
 * @param char *buffer    buffered line to check..
 * @return int            returns number of columns
 */
int calc_cols(char *buffer) {

    char *needle = "\",\"";
    int length = strlen(needle);
    
    int i = 0;

    for(i = 0; ; i++) {

        buffer = strstr(buffer, needle);

        if(buffer == NULL) break;

        buffer = buffer + length;
    }

    return i+1;
}


/**
 * open a file and decore html unicode point to utf8..
 * @param ResultList *list    handle for saved results
 * @param char *filename      file to be opened
 * @return int                returns 1 on success, else 0
 */
int readfile(ResultList *list, char *filename) {

    FILE *fp = fopen(filename, "rb");
        
    if(!fp) {
        return 0;
    }

    char buffer[READ_SIZE];
    memset(buffer, '\0', READ_SIZE);

    int length = STEP_SIZE;
    char *** temp = malloc(sizeof(char *) * length);

    int cols = 0;
    int rows = 0;

    /* determine amount of lines */
    while(fgets(buffer, sizeof(buffer), fp) != NULL) {
        
        if(rows == 0) {
            cols = calc_cols(buffer);
        }

        if(cols != calc_cols(buffer)) {

            printf("Error: column widths didn't match \n");
            fclose(fp);
            return 0;
        }

        if((rows % STEP_SIZE) == 0) {

            length += STEP_SIZE;

            char *** expand = realloc(temp, sizeof(char *) * length);

            if(expand) {
                temp = expand;
            }
            else {

                printf("Error: failed to realloc temp array\n");
                exit(0);
            }
        }

        temp[rows] = malloc(sizeof(char *) * cols);

        int i = 0;

        for(i = 0; i < cols; i++) {
            temp[rows][i] = NULL;
        }

        if(!parse_line(temp[rows], buffer, cols)) {

            printf("Error: failed to parse line %d\n", rows);
            fclose(fp);
            return 0;
        }

        rows++;
    }
    
    list->rows = rows;
    list->cols = cols;

    /* copy temp results into result-list */
    list->results = malloc(sizeof(char *) * list->rows);
    memcpy(list->results, temp, sizeof(char *) * list->rows);

    fclose(fp);

    return 1;
}

