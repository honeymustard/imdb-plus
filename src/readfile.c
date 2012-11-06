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


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readfile.h"


/**
 * free memory from temporary char array..
 * @param char ***results    array to be freed
 * @param int cols           cols in array
 * @param int rows           rows in array
 * @return                   returns 1
 */
int free_memory(char ***results, int cols, int rows) {
 
    int i = 0;
    int j = 0;

    /* free memory occupied by results.. */
    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++) {

            if(results[i][j] != NULL) {
                free(results[i][j]);
            }
        }

        free(results[i]); 
    }

    return 1;
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
 * @param int i          start index..
 * @return               returns string offset
 */
int entities_decode(char *buffer, int i) {

    if(buffer[i++] != '&') {
        return 0; 
    }

    if(buffer[i++] != '#') {
        return 0; 
    }

    if(buffer[i++] != 'x') {
        return 0; 
    }

    if(buffer[i] != '\0' && buffer[i+1] != '\0' && buffer[i+2] == ';') {
        
        unsigned char temp = 0;

        /* for conventional ascii chars */
        if(is_0_to_9(buffer[i]) && is_0_to_f(buffer[i+1])) {

            temp = (buffer[i] - HEX_D_OFF) << 4;
            temp |= buffer[i+1] - HEX_D_OFF;

            buffer[i+2] = temp;

            return 5;
        }
        /* unicode point range A-B/0-F */
        else if((buffer[i] >= 'A' && buffer[i] <= 'B') && 
            is_0_to_f(buffer[i+1])) {

            temp = ((buffer[i] + 10) - HEX_C_OFF) << 4;

            if(is_a_to_f(buffer[i+1])) {

                temp |= (buffer[i+1] + 10) - HEX_C_OFF;
            }
            else {
                temp |= buffer[i+1] - HEX_D_OFF;
            }

            buffer[++i] = 0xC2;
            buffer[++i] = temp;

            return 4;
        }
        /* unicode point range C-F/0-F */
        else if((buffer[i] >= 'C' && buffer[i] <= 'F') && 
            is_0_to_f(buffer[i+1])) {

            char values[] = {8, 9, 10, 11};

            temp = values[buffer[i] - (HEX_C_OFF + 2)] << 4;

            if(is_a_to_f(buffer[i+1])) {

                temp |= (buffer[i+1] + 10) - HEX_C_OFF;
            }
            else {
                temp |= buffer[i+1] - HEX_D_OFF;
            }

            buffer[++i] = 0xC3;
            buffer[++i] = temp;

            return 4;
        }
         
        /* else, just add question mark */
        i += 2;
        buffer[i] = 0x3F;

        return 5;
    }    

    return 0;
}


/**
 * parse a csv line and add values to buffer
 * @param char **container    array big enough to contain parsed values
 * @param char *buffer        line to be parsed
 * @return int                returns 1
 */
int parse_line(char **container, char *buffer) {

    int i = 0;

    int values_parsed = 0;

    char temp[200];
    memset(temp, '\0', 200);

    for(i = 0; buffer[i] != '\0'; i++) {

        /* if symbol is a starting delimiter */
        if(buffer[i] == '"' && buffer[i+1] != ',') {

            /* check for null indices */
            if(buffer[++i] == '"') {
                container[values_parsed] = malloc(2);
                strcpy(container[values_parsed++], "0");
                i++;
                continue;
            }

            /* add current indice to container array */
            int temp_counter = 0;

            while(buffer[i] != '"') {

                if(buffer[i] == '&') {
                    i += entities_decode(buffer, i);
                }

                temp[temp_counter++] = buffer[i++];
            }
             
            temp[temp_counter] = '\0';

            container[values_parsed] = malloc(strlen(temp) + 1);
            strcpy(container[values_parsed++], temp);
        }
    }

    return 1;
}


/**
 * calculate number of comma separated values..
 * @param char *buffer    string to check..
 */
int calc_cols(char *buffer) {

    int i = 0;
    int j = 0;

    for(i = 0; buffer[i] != '\0'; i++) {

        if(buffer[i] != '\0' && buffer[i] == '"') {
            i++;
            if(buffer[i] != '\0' && buffer[i] == ',') {
                i++;
                if(buffer[i] != '\0' && buffer[i] == '"') {
                    i++;
                    j++;
                }
            }
        }
    }

    return ++j;
}


/**
 * open a file and decore html unicode point to utf8..
 * @param char *filename      file to be opened
 * @param int *cols           store col amount
 * @param int *rows           store row amount
 * @param char ****results    handle for saved results
 * @return                    returns 1 on success, else 0
 */
int read_file(char *filename, int *cols, int *rows, char ****results) {
        
    FILE *fp = fopen(filename, "rb");
        
    if(!fp) {
        return 0;
    }

    int i = 0;
    int j = 0;

    char buffer[512];

    /* determine amount of lines */
    while(fgets(buffer, 512, fp) != NULL) {
        
        if(*rows == 0) {
            *cols = calc_cols(buffer);
        }

        (*rows)++;
    }

    if(*cols < 2) {

        fclose(fp);
        return 0;
    }

    /* reset */
    fseek(fp, 0, SEEK_SET);

    *results = malloc(sizeof(char *) * (*rows));
    
    for(i = 0; i < (*rows); i++) {

        (*results)[i] = malloc(sizeof(char *) * (*cols));

        for(j = 0; j < (*cols); j++) {
            (*results)[i][j] = NULL;
        }
    }

    int lines = 0;

    /* copy all lines into table buffer */
    while(fgets(buffer, 512, fp) != NULL) {

        if(!parse_line((*results)[lines++], buffer)) {
            return 0;
        }
    }

    fclose(fp);

    return 1;
}

