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
#include <stdlib.h>
#include <string.h>
#include <regex.h>


/**
 * perform regex on *filename with *pattern and save to disk as .csv
 * @param char *filename    source filename..
 * @param char *out_file    output filename..
 * @param char *pattern     pattern to use for regex matching..
 * @return                  1 on success, else 0
 */
int regex_to_csv(char *filename, char *out_file, char *pattern) {

    FILE *fp = fopen(filename, "rb");

    if(fp == NULL) {
        return 0;
    }

    /* buffer entire *filename file */
    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buffer = malloc(len);
    const char *p = buffer;
    fread(buffer, 1, len, fp);

    regex_t re;
    regmatch_t match[10];
     
    /* compile regular expression pattern */
    if(regcomp(&re, pattern, REG_EXTENDED) != 0) {
        return 0;
    }

    int i = 0;
    int j = 0;

    /* open output file */
    FILE *out_file_fp = fopen(out_file, "wb");
    
    if(out_file_fp == NULL) {
        return 0;
    }

    /* file format for regex'd values */
    char *array[2] = {
        "\"%.*s\",", 
        "\"%.*s\"\n"
    };


    /* keep going while pattern has more matches */
    for(i = 0; (regexec(&re, p, re.re_nsub, match, 0) == 0); i++) {

        for(j = 1; j < re.re_nsub; j++) {

            if(match[j].rm_so == -1) {
                continue;
            }

            /* last submatch in match, add end-of-line character */
            fprintf(out_file_fp, array[(j == (re.re_nsub - 1))], 
                match[j].rm_eo - match[j].rm_so, &p[match[j].rm_so]);
        }

        p += match[0].rm_eo;
    }

    /* close fp's and free memory */
    fclose(out_file_fp);
    fclose(fp);

    free(buffer);
    regfree(&re);

    return i;    
}

