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


#include <stdlib.h>
#include <curl/curl.h>
#include "io/download.h"


/**
 * download web pages from internet..
 * @param char *url       url to read from
 * @param char *saveas    name of file to save as
 * @return                NULL
 */
void *download(void *download) {

    CURL *curl;
    CURLcode curl_res;

    Download *down = (Download *)download;

    /* set default status to failed */
    down->status = DL_STATUS_NB;
    
    FILE *tmp = fopen(down->saveas, "w");

    if(tmp == NULL) {
        return NULL;
    }

    curl = curl_easy_init();

    if(curl) {

        /* set english headers */
        struct curl_slist *head = NULL;
     
        head = curl_slist_append(head, "Accept-Charset: iso-8859-2");
        head = curl_slist_append(head, "Accept-Language: en");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, head);
        curl_easy_setopt(curl, CURLOPT_URL, down->url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, tmp);

        curl_res = curl_easy_perform(curl);

        /* we've downloaded something, set status ok */
        if(curl_res == 0) {

            down->status = DL_STATUS_OK;
        }

        /* add http-code and size of file to download struct */
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &down->http_code);
        curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &down->length);

        fclose(tmp);

        curl_easy_cleanup(curl);
        curl_slist_free_all(head);
    }

    return NULL;
}

