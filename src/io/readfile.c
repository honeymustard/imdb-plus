/***********************************************************************
 *
 * Copyright (C) 2011-2014  Adrian Solumsmo
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
#include <ctype.h>
#include "io/readfile.h"
#include "libcsv/libcsv.h"


ResultTemp *temp = NULL;


/**
 * creates a new readfile list and returns it..
 * @return ResultList *list    new list
 */
ResultList *readfile_new() {
 
    ResultList *list = malloc(sizeof(ResultList));

    list->size = 0;
    list->rows = 0;
    list->cols = 0;
    list->results = NULL;

    return list;
}


/**
 * free memory from occupied by results..
 * @param ResultList *list    list to be freed
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

    if(list->results != NULL) {
        free(list->results);
    }

    free(list);
}


/**
 * decode all html entities in a buffer
 * @param char *src_data     source buffer with entities
 * @param int src_size       source buffer length
 * @param char *dest_data    destination buffer
 * @param int *dest_size     destination buffer length
 */
void readfile_decode(char *src_data, int src_size, char **dest_data, int *dest_size) {

    char *needle = "&#x";
    int needle_length = strlen(needle);

    int len = src_size;

    char *tmp = malloc(src_size + 1);
    strncpy(tmp, src_data, src_size + 1);

    char *temp = src_data;

    for(;;) {

        temp = strstr(temp, needle);

        if(temp == NULL) {

            *dest_data = tmp;
            *dest_size = strlen(tmp);

            return;
        }

        int tmp_len = len - strlen(temp);

        temp = temp + needle_length;
        
        if(temp[0] != '\0' && 
           temp[1] != '\0' && 
           temp[2] != '\0' && 
           temp[2] == ';') {
        
            char curr = toupper(temp[0]);
            char next = toupper(temp[1]);
            char *copy = &temp[3];
            unsigned char temp = 0;

            if(isxdigit(next)) {

                /* for conventional ascii chars */
                if(isdigit(curr)) {

                    temp = (curr - HEX_D_OFF) << 4;
                    temp |= next - HEX_D_OFF;

                    tmp[tmp_len] = temp;
                    strcpy(&tmp[tmp_len+1], copy);

                    len -= 5;
                }
                /* unicode point range A-B/0-F */
                else if((curr >= 'A' && curr <= 'B')) {

                    temp = ((curr + 10) - HEX_C_OFF) << 4;

                    if(next >= 'A' && next <= 'F') {
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

                    if(next >= 'A' && next <= 'F') {
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

                    printf("Decode: Unkown character found\n");
                }
            }
        }
    }    
}


/**
 * callback for when the parser has read a token
 * @param void *buffer    string token
 * @param size_t i        string token length
 * @param void *data      none
 */
void readfile_tok(void *buffer, size_t i, void *data) {

    int bytes = (int)i;

    /* decode expects a null terminated string */
    char *token = malloc(bytes + 1);
    strncpy(token, (char *)buffer, bytes);
    token[bytes] = '\0';

    char *clean_data = NULL;
    int clean_size = 0;

    readfile_decode(token, bytes, &clean_data, &clean_size);

    free(token);

    ResultTemp *curr = malloc(sizeof(ResultTemp));
    curr->next = NULL;
    curr->data = NULL;
    curr->size = 0;
    curr->cols = 0;
    
    /* copy string data */
    curr->data = malloc(clean_size + 1);
    strncpy(curr->data, clean_data, clean_size);
    curr->data[clean_size] = '\0';
    curr->size = clean_size;

    free(clean_data);

    if(temp == NULL) {
        temp = curr;
    }
    else {

        ResultTemp *loop = temp;

        for(;;) {

            if(loop->next == NULL) {

                loop->next = curr;
                break;
            }

            loop = loop->next;
        }
    }

    temp->cols++;
}
 

/**
 * callback for when the parser reaches the end of a line
 * @param int eol       symbol which caused eol
 * @param void *data    result-list object
 */
void readfile_eol(int eol, void *data) {

    ResultList *l = (ResultList *)data;

    if(l->results == NULL) {

        l->size = STEP_SIZE;
        l->results = malloc(sizeof(char *) * STEP_SIZE);
    }

    /* expand result-list if necessary */
    if((l->rows % STEP_SIZE) == 0) {

        l->size += STEP_SIZE;

        char *** expand = realloc(l->results, sizeof(char *) * l->size);

        if(expand) {
            l->results = expand;
        }
        else {

            printf("Error: failed to realloc temp array\n");
            exit(0);
        }
    }

    l->results[l->rows] = malloc(sizeof(char *) * temp->cols);

    l->cols = temp->cols;

    int i = 0;

    /* create a row from column data */
    for(i = 0; temp != NULL; i++) {

        l->results[l->rows][i] = malloc(temp->size + 1);
        strncpy(l->results[l->rows][i], temp->data, temp->size);
        l->results[l->rows][i][temp->size] = '\0';

        free(temp->data);

        ResultTemp *t = temp;
        temp = temp->next;
        free(t);
    }

    temp = NULL;

    l->rows++;
}


/**
 * open a file and parse it into a result list
 * @param ResultList *list    handle for saved results
 * @param char *filename      file to be opened
 * @return int                returns 1 on success, else 0
 */
int readfile(ResultList *list, char *filename) {

    struct csv_parser p;
    char buf[READ_SIZE];
    size_t bytes = 0;
    size_t retval = 0;

    if(csv_init(&p, CSV_STRICT) != 0) {

        #ifdef DEBUG

        fprintf(stderr, "Failed to initialize csv parser\n");

        #endif

        return 0;
    }

    FILE *fp = fopen(filename, "rb");
    
    if(!fp) {

        #ifdef DEBUG

        fprintf(stderr, "Failed to open %s\n", filename);

        #endif

        return 0;
    }

    while((bytes = fread(buf, 1, READ_SIZE, fp)) > 0) {

        retval = csv_parse(&p, buf, bytes, readfile_tok, readfile_eol, list);

        if(retval != bytes) {

            #ifdef DEBUG

            printf("Error: could not process file %s\n", filename);

            #endif

            fclose(fp);

            return 0;
        }
    }

    fclose(fp);

    csv_fini(&p, NULL, NULL, NULL);
    csv_free(&p);

    return 1;
}

