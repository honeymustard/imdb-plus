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

########################################################
#
# Make linux deb/src builds:
#
# This script is run by Makefile. make build-deb.
#
########################################################


# export credentials to match gpg key..
DEBEMAIL="adrian.solumsmo@gmail.com"
DEBFULLNAME="Adrian Solumsmo"
export DEBEMAIL DEBFULLNAME

# make sure script is run from toplevel only..
if [ "$3" != "build-deb" ]; then 
    echo "Error: script must be run from toplevel Makefile!"
    exit
fi

# make build directory if not available..
if [ ! -d "build" ]; then
    mkdir "build"
fi
   
cd ./build 

# make new folder to suit program-version..
if [ ! -d "$1-$2" ]; then
    mkdir $1-$2
fi

cd ./$1-$2

# make deb dir so not to interfere with other builds..
if [ ! -d "$1-$2-deb" ]; then
    mkdir $1-$2-deb
fi

cd $1-$2-deb
rm -Rf ./*

# make version dir..
if [ ! -d "$1-$2" ]; then
    mkdir $1-$2
fi

# dist tar was made by make. move it here.
mv ../../../$1-$2.tar.gz .

cd $1-$2

# extract that bad-boy.. zing.
tar -zxf ../$1-$2.tar.gz 

# do dh_make to setup deb package structure..
dh_make --single --copyright gpl3 -f ../$1-$2.tar.gz

# remove example files..
cd ./debian
rm *.ex *EX
cd ..

# copy pre-made relevant files from top dir..
cp ../../../../misc/changelog ./debian/changelog

# copy version number into changelog..
sed "s/imdb-plus (X\.X\.X-1)/imdb-plus ($2-1)/" <./debian/changelog >./debian/clog
cat ./debian/clog > ./debian/changelog && rm ./debian/clog

cp ../../../../misc/control ./debian/control
cp ../../../../misc/copyright ./debian/copyright
cp ../../../../misc/rules ./debian/rules
rm ./debian/README.Debian
rm ./debian/README.source
rm ./debian/docs

# build packages
debuild

# do some cleaning..
cd ..
rm -Rf ./$1-$2

echo "$1-$2.deb: build completed"

