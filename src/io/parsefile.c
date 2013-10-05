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
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "io/parsefile.h"


/**
 * parse 'filename' with 'pattern' to 'out_file'..
 * @param char *filename    source filename..
 * @param char *out_file    output filename..
 * @param char *pattern     pattern to use for regex matching..
 * @return                  1 on success, else 0
 */
int parse_file(char *filename, char *out_file, char *pattern) {

    FILE *fp = fopen(filename, "rb");

    if(fp == NULL) {
        return 0;
    }

    /* buffer entire *filename file */
    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = malloc((int)len + 1);
    memset(buffer, '\0', len+1);

    const char *p = buffer;
    fread(buffer, 1, len, fp);

    fclose(fp);

    regex_t re;
    regmatch_t match[10];
    memset(match, '\0', sizeof(regmatch_t) * 10);
     
    /* compile regular expression pattern */
    if(regcomp(&re, pattern, REG_EXTENDED) != 0) {
        return 0;
    }

    int i = 0;
    int j = 0;

    /* open temporary output file */
    char *ext_temp = ".tmp";
    char *out_temp = malloc(strlen(out_file) + strlen(ext_temp) + 1);

    strcpy(out_temp, out_file);
    strcat(out_temp, ext_temp);

    FILE *out_file_tmp = fopen(out_temp, "wb");
    
    if(out_file_tmp == NULL) {
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
            fprintf(out_file_tmp, array[(j == (re.re_nsub - 1))], 
                match[j].rm_eo - match[j].rm_so, &p[match[j].rm_so]);
        }

        p += match[0].rm_eo;
    }

    /* close out_file and free memory */
    fclose(out_file_tmp);

    free(buffer);
    regfree(&re);

    /* if there were results, remove old .csv and replace with new */
    if(i > 1) {

        remove(out_file);
        rename(out_temp, out_file);

        return i;
    }

    /* no results, remove tmp file */
    remove(out_temp);

    return 0;    
}

