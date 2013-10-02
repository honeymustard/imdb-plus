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

###############################################################
#
# Make windows exe/src builds:
#
# This script is run by Makefile: mingw32-make mingw32-build
#
###############################################################


# make sure script is run from toplevel makefile only..
if [ $# -lt 4 ]; then
    echo "Error: Script expected more arguments!"
    exit
fi

if [ "$4" != "build-win" ]; then
    echo "Error: Script should be run by toplevel Makefile!"
    exit
fi

# variables from makefile..
PROGRAM=$1
VERSION=$2
INSTALL=$3

# long-form program name..
PROGRAM="$PROGRAM-$VERSION"

# build directory..
DIR_BUILD="build/$PROGRAM/$PROGRAM-win"

# make environment
[ -d $DIR_BUILD ] || mkdir -p $DIR_BUILD

if [ ! -d $DIR_BUILD ]; then
    echo "Error: build directory couldn't be created"
    exit
fi

rm -Rf "$DIR_BUILD/*"

# move source package
mv "$PROGRAM.tar.gz" $DIR_BUILD

# copy install files
cp -R $INSTALL $DIR_BUILD

# run setup script..
iscc "$DIR_BUILD/setup.iss" /dMyAppVersion=$VERSION

cd $DIR_BUILD && tar -czf "$PROGRAM-setup.tar.gz" "$PROGRAM-setup.exe" && cd -

find $DIR_BUILD/* ! -name "*.tar.gz" -delete

echo "$PROGRAM.exe: build completed"

