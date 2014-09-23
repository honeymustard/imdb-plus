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


#include "io/patterns.h"


/* top250 regex pattern */
char *pattern_top = "\r\
  <td class=\"titleColumn\">\r\
    <span name=\"ir\" data-value=\"([0-9.]{1,12})\">.{0,5}</span>\r\
    <a href=\"/title/(tt[0-9]{1,10})/.{0,50}\"\r\
title=\".{0,100}\".{0,5}>(.{0,100})</a>\r\
    <span name=\"rd\" data-value=\".{0,20}\" class=\"secondaryInfo\">\\(([0-9]{4})\\)</span>\r\
  </td>\r\
  <td class=\"ratingColumn\">\r\
    <strong name=\"nv\" data-value=\"(([0-9]{1,12}))\" title=\".{0,100}\">.{0,5}</strong>\r\
  </td>";

/* top250 regex pattern with windows line-breaks */
char *pattern_top_win = "\r\n\
  <td class=\"titleColumn\">\r\n\
    <span name=\"ir\" data-value=\"([0-9.]{1,12})\">.{0,5}</span>\r\n\
    <a href=\"/title/(tt[0-9]{1,10})/.{0,50}\"\r\n\
title=\".{0,100}\".{0,5}>(.{0,100})</a>\r\n\
    <span name=\"rd\" data-value=\".{0,20}\" class=\"secondaryInfo\">\\(([0-9]{4})\\)</span>\r\n\
  </td>\r\n\
  <td class=\"ratingColumn\">\r\n\
    <strong name=\"nv\" data-value=\"(([0-9]{1,12}))\" title=\".{0,100}\">.{0,5}</strong>\r\n\
  </td>";

/* bottom100 regex pattern */
char *pattern_bot = "\r\
  <td class=\"titleColumn\">\r\
    <span name=\"ir\" data-value=\"([0-9.]{1,12})\">.{0,5}</span>\r\
    <a href=\"/title/(tt[0-9]{1,10})/.{0,50}\"\r\
title=\".{0,100}\".{0,5}>(.{0,100})</a>\r\
    <span name=\"rd\" data-value=\".{0,20}\" class=\"secondaryInfo\">\\(([0-9]{4})\\)</span>\r\
  </td>\r\
  <td class=\"ratingColumn\">\r\
    <strong name=\"nv\" data-value=\"(([0-9]{1,12}))\" title=\".{0,100}\">.{0,5}</strong>\r\
  </td>";

/* bottom100 regex pattern with windows line-breaks */
char *pattern_bot_win = "\r\n\
  <td class=\"titleColumn\">\r\n\
    <span name=\"ir\" data-value=\"([0-9.]{1,12})\">.{0,5}</span>\r\n\
    <a href=\"/title/(tt[0-9]{1,10})/.{0,50}\"\r\n\
title=\".{0,100}\".{0,5}>(.{0,100})</a>\r\n\
    <span name=\"rd\" data-value=\".{0,20}\" class=\"secondaryInfo\">\\(([0-9]{4})\\)</span>\r\n\
  </td>\r\n\
  <td class=\"ratingColumn\">\r\n\
    <strong name=\"nv\" data-value=\"(([0-9]{1,12}))\" title=\".{0,100}\">.{0,5}</strong>\r\n\
  </td>";

/* boxoffice regex pattern */
char *pattern_box = "\
<td align=right><b>([0-9]{1,3}).</b></td>\n\
<td><a href=\"/title/(tt[0-9]{1,10})/\">(.{0,100})</a>\
 \\(([0-9]{4}).{0,2}\\)</td>\n\
<td align=right>([0-9,\\$]{1,20})</(td)>\n\
</tr>\n";

/* boxoffice regex pattern with windows line-breaks */
char *pattern_box_win = "\
<td align=right><b>([0-9]{1,3}).</b></td>\r\n\
<td><a href=\"/title/(tt[0-9]{1,10})/\">(.{0,100})</a>\
 \\(([0-9]{4}).{0,2}\\)</td>\r\n\
<td align=right>([0-9,\\$]{1,20})</(td)>\r\n\
</tr>\r\n";

