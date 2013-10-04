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
if [ "$3" != "build-deb" ]; then 
    echo "Error: script must be run from toplevel Makefile!"
    exit
fi

# export credentials to match gpg key..
DEBEMAIL="adrian.solumsmo@gmail.com"
DEBFULLNAME="Adrian Solumsmo"
export DEBEMAIL DEBFULLNAME

PROGRAM=$1-$2
VERSION=$2
CALLDIR=$PWD

# build directory..
DIR_HOST="build/$PROGRAM/$PROGRAM-deb"
DIR_TEMP="build/$PROGRAM/$PROGRAM-deb/$PROGRAM"

# make environment
[ -d $DIR_HOST ] || mkdir -p $DIR_HOST

if [ ! -d $DIR_HOST ]; then
    echo "Error: build directory couldn't be created"
    exit
fi

rm -Rf $DIR_HOST/*

# make temp dir..
[ -d $DIR_TEMP ] || mkdir -p $DIR_TEMP

if [ ! -d $DIR_TEMP ]; then
    echo "Error: temp directory couldn't be created"
    exit
fi

# dist tar was made by make. move it here.
mv "$PROGRAM.tar.gz" "$DIR_HOST/$1_$2.orig.tar.gz"

cd $DIR_TEMP

# extract that bad-boy.. zing.
tar -zxf "../$1_$2.orig.tar.gz"

# do dh_make to setup deb package structure..
dh_make --yes --indep --copyright gpl3

cd -

DIR_DEB="$DIR_TEMP/debian"

# remove example files..
cd $DIR_DEB && rm *.ex *EX && cd -

# copy pre-made relevant files from calldir..
cp "$CALLDIR/misc/changelog" "$DIR_DEB/changelog"

LOG_OUT="$DIR_DEB/changelog"
LOG_TMP="$DIR_DEB/changelog.tmp"

# copy version number into changelog..
sed "s/$1 (X\.X\.X-1)/$1 ($2-1)/" < $LOG_OUT > $LOG_TMP
cat $LOG_TMP > $LOG_OUT && rm $LOG_TMP

cp "$CALLDIR/misc/control" "$DIR_DEB/control"
cp "$CALLDIR/misc/copyright" "$DIR_DEB/copyright"
cp "$CALLDIR/misc/rules" "$DIR_DEB/rules"
rm "$DIR_DEB/README.Debian"
rm "$DIR_DEB/README.source"
rm "$DIR_DEB/docs"

# build packages
cd $DIR_DEB && debuild -i -us -uc -b && cd -

# do some cleaning..
rm -Rf $DIR_TEMP
cd $DIR_HOST && rm *.build *.changes && cd -

echo "$PROGRAM.deb: build completed"

