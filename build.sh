#!/bin/sh

#############################################################################
#
# Copyright (C) 2011-2012  Adrian Solumsmo
# 
# imdb-plus program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# imdb-plus program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#############################################################################

######################################################
#
# Make linux deb/src builds:
#
# This script is run by Makefile. make, make build.
#
######################################################

# export credentials to match my gpg key..
DEBEMAIL="adrian.solumsmo@gmail.com"
DEBFULLNAME="Adrian Solumsmo"
export DEBEMAIL DEBFULLNAME

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

# make deb dir so not to interfere with win builds..
if [ ! -d "$1-$2-deb" ]; then
    mkdir $1-$2-deb
fi

cd $1-$2-deb

# remove existing folder if necessary..
if [ -d "$1-$2" ]; then
    rm -R $1-$2
fi

# dist tar was made by make. move it here.
mv ../../../$1-$2.tar.gz .

mkdir $1-$2
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
cp ../../../../misc/control ./debian/control
cp ../../../../misc/copyright ./debian/copyright
cp ../../../../misc/changelog ./debian/changelog
rm ./debian/README.Debian
rm ./debian/README.source
rm ./debian/docs

# build package(s)
debuild

