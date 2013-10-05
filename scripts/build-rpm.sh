#!/bin/sh

########################################################################
#
# Copyright (C) 2011-2013  Adrian Solumsmo
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
########################################################################


if [ $# -lt 3 ]; then
    echo "Error: Script expected more arguments!"
    exit
fi

# make sure script is run from toplevel only..
if [ "$3" != "build-rpm" ]; then 
    echo "Error: script must be run from toplevel Makefile!"
    exit
fi

PROGRAM=$1-$2
VERSION=$2
CALLDIR=$PWD

# build directory..
DIR_HOST="build/$PROGRAM/$PROGRAM-rpm"
DIR_TEMP="build/$PROGRAM/$PROGRAM-rpm/temp"

# make environment
[ -d $DIR_HOST ] || mkdir -p $DIR_HOST

if [ ! -d $DIR_HOST ]; then
    echo "Error: build directory couldn't be created"
    exit
fi

rm -Rf "$DIR_HOST/*"

# make version dir..
[ ! -d $DIR_TEMP ] || mkdir $DIR_TEMP

if [ ! -d $DIR_TEMP ]; then
    echo "Error: temp directory couldn't be created"
    exit
fi

rm -Rf "$DIR_HOST/$PROGRAM/*"

########################### remove this..
mkdir "$DIR_TEMP/BUILD"
mkdir "$DIR_TEMP/RPMS"
mkdir "$DIR_TEMP/SOURCES"
mkdir "$DIR_TEMP/SPECS"
mkdir "$DIR_TEMP/SRPMS"

#rpmdev-setuptree

# copy relevant files to build folder..
cp "$CALLDIR/misc/$1.spec" "$DIR_TEMP/SPECS"
cp "$CALLDIR/$1-$2.tar.gz" "$DIR_TEMP/SOURCES"

FILE_SPEC="$DIR_TEMP/SPECS/$1.spec"
FILE_TEMP="$DIR_TEMP/SPECS/$1.temp"

# copy version number into spec..
sed "s/X\.X\.X/$2/" < $FILE_SPEC > $FILE_TEMP
cat $FILE_TEMP > $FILE_SPEC && rm $FILE_TEMP

# Check RPM spec with lint..
if [ `rpmlint $FILE_SPEC | grep -c E:` -gt 0 ]; then
    echo "rpmlint exited with Error!"
    exit
fi

rpmbuild -ba $FILE_SPEC --define "_topdir $CALLDIR"
 
# clean/make LOGS directory..
[ ! -d "$DIR_TEMP/LOGS" ] || mkdir "$DIR_TEMP/LOGS"

if [ ! -d "$DIR_TEMP/LOGS" ]; then
    echo "Error: logs directory couldn't be created"
    exit
fi

rm -R "$DIR_TEMP/LOGS/*"


# Check RPM source with mock..
`mock -r fedora-17-x86_64 --rebuild "$DIR_TEMP/SRPMS/*.src.rpm" --resultdir="$DIR_TEMP/LOGS"`

if [ `cat "$DIR_TEMP/LOGS/state.log" | grep -c "Finish: run"` -eq 0 ]; then
    echo "Mock exited with Error!"
    exit
fi

# copy relevant rpm's..
cp "$DIR_TEMP/RPMS/x86_64/*.rpm" $DIR_HOST
cp "$DIR_TEMP/SRPMS/*.rpm" $DIR_HOST

rm -Rf $DIR_TEMP

echo "$PROGRAM.rpm: build completed"

