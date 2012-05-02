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

#include <stdlib.h>
#include <curl/curl.h>
#include "download.h"


/**
 * download web pages from internet..
 * @param char *url       url to read from
 * @param char *saveas    name of file to save as
 * @return                NULL
 */
void *download(void *download) {

    CURL *curl;
    CURLcode curl_res;

    struct download *down = (struct download *)download;
    down->status = DL_STATUS_NB;
    
    FILE *tmp = fopen(down->saveas, "w");

    if(tmp == NULL) {
        return NULL;
    }

    curl = curl_easy_init();

    if(curl) {

        curl_easy_setopt(curl, CURLOPT_URL, down->url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, tmp);
        
        curl_res = curl_easy_perform(curl);

        if(curl_res == 0) {
            down->status = DL_STATUS_OK;
        }

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &down->http_code);
        curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &down->length);

        fclose(tmp);
        curl_easy_cleanup(curl);

    }

    return NULL;
}

