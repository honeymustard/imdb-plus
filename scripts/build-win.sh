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


if [ $# -lt 4 ]; then
    echo "Error: Script expected more arguments!"
    exit
fi

# make sure script is run from toplevel only..
if [ "$4" != "build-win" ]; then
    echo "Error: Script should be run by toplevel Makefile!"
    exit
fi

# variables from makefile..
PROGRAM=$1-$2
VERSION=$2
INSTALL=$3

# build directory..
DIR_HOST="build/$PROGRAM/$PROGRAM-win"
DIR_TEMP="build/$PROGRAM/$PROGRAM-win/$PROGRAM"

# make environment
[ -d $DIR_HOST ] || mkdir -p $DIR_HOST

if [ ! -d $DIR_HOST ]; then
    echo "Error: build directory couldn't be created"
    exit
fi

rm -Rf "$DIR_HOST/*"

[ -d $DIR_TEMP ] || mkdir -p $DIR_TEMP

if [ ! -d $DIR_TEMP ]; then
    echo "Error: build directory couldn't be created"
    exit
fi

# move source package
mv "$PROGRAM.tar.gz" $DIR_HOST

# copy install files
cp -R $INSTALL $DIR_TEMP

# run setup script..
iscc "$DIR_TEMP/setup.iss" /dMyAppVersion=$VERSION

SETUP="$DIR_TEMP/$PROGRAM-setup.exe"

if [ ! -f $SETUP ]; then
    echo "Error: failed to create setup.exe"
    exit
fi

cp $SETUP $DIR_HOST

rm "$DIR_HOST/$PROGRAM.tar.gz"
rm -Rf $DIR_TEMP

echo "$PROGRAM.exe: build completed"

