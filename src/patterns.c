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


/* top250 regex pattern */
char *pattern_top250 = "<tr bgcolor=\"#.{6}\" valign\
=\"top\"><td align=\"right\"><font face=\"Arial, Helvetica,\
 sans-serif\" size=\"-1\"><b>([0-9]{1,3})\\.</b></font>\
</td><td align=\"center\"><font face=\"Arial, Helvetica, \
sans-serif\" size=\"-1\">([0-9]{1,2}\\.[0-9]{1,2})</font>\
</td><td><font face=\"Arial, Helvetica, sans-serif\" \
size=\"-1\"><a href=\"/title/(tt[0-9]{1,10})/\">(.{0,100})\
</a> \\(([0-9]{4}).{0,4}\\)</font></td><td align=\"right\">\
<font face=\"Arial, Helvetica, sans-serif\" size=\"-1\">\
(([0-9]{1,4},[0-9]{1,4}))</font></td></tr>";

/* bottom100 regex pattern */
char *pattern_bot100 = "<font face=\"Arial, Helvetica, \
sans-serif\" size=\"-1\"><b>([0-9]{1,3})\\.</b></font>\
</td><td align=\"center\"><font face=\"Arial, Helvetica, \
sans-serif\" size=\"-1\">([0-9]{1,2}\\.[0-9]{1,2})</font>\
</td><td><font face=\"Arial, Helvetica, sans-serif\" \
size=\"-1\"><a href=\"/title/(tt[0-9]{1,10})/\">(.{0,100})\
</a> \\(([0-9]{4}.{0,4})\\)</font></td><td align=\"right\">\
<font face=\"Arial, Helvetica, sans-serif\" size=\"-1\">\
(([0-9]{1,4},[0-9]{1,4}))</font></td></tr>";

/* boxoffice regex pattern */
char *pattern_boxoffice = "\
<td align=right><b>([0-9]{1,3}).</b></td>\n\
<td><a href=\"/title/(tt[0-9]{1,10})/\">(.{0,100})</a>\
 \\(([0-9]{4}).{0,2}\\)</td>\n\
<td align=right>([0-9,\\$]{1,20})</(td)>\n\
</tr>\n";

/* boxoffice regex pattern with windows line-breaks */
char *pattern_boxoffice_win = "\
<td align=right><b>([0-9]{1,3}).</b></td>\r\n\
<td><a href=\"/title/(tt[0-9]{1,10})/\">(.{0,100})</a>\
 \\(([0-9]{4}).{0,2}\\)</td>\r\n\
<td align=right>([0-9,\\$]{1,20})</(td)>\r\n\
</tr>\r\n";


