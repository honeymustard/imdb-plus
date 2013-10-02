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
# Make linux rpm/src builds:
#
# This script is run by Makefile. make build-rpm.
#
########################################################


# make sure script is run from toplevel only..
if [ "$3" != "build-rpm" ]; then 
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
if [ ! -d "$1-$2-rpm" ]; then
    mkdir $1-$2-rpm
fi

cd ./$1-$2-rpm

# make version dir..
if [ ! -d "$1-$2" ]; then
    mkdir $1-$2
fi

cd ./$1-$2

TOP_DIR=../../../..

rm -Rf ./*

mkdir "BUILD"
mkdir "RPMS"
mkdir "SOURCES"
mkdir "SPECS"
mkdir "SRPMS"

#rpmdev-setuptree

# copy relevant files to build folder..
cp $TOP_DIR/misc/$1.spec SPECS
cp $TOP_DIR/$1-$2.tar.gz SOURCES

# copy version number into spec..
sed "s/X\.X\.X/$2/" <SPECS/$1.spec >SPECS/$1.tmp
cat SPECS/$1.tmp > SPECS/$1.spec && rm SPECS/$1.tmp

CWD=$PWD

cd SPECS

# Check RPM spec with lint..
#if [ `rpmlint $1.spec | grep -c E:` -gt 0 ]; then
#    echo "rpmlint exited with Error!"
#    exit
#fi

rpmbuild -ba $1.spec --define "_topdir $CWD"
 
cd .. 

# clean/make LOGS directory..
#if [ -d LOGS ]; then
#    rm -R ./LOGS
#fi

#mkdir LOGS

# Check RPM source with mock..
#`mock -r fedora-17-x86_64 --rebuild ./SRPMS/*.src.rpm --resultdir=./LOGS`

#if [ `cat ./LOGS/state.log | grep -c "Finish: run"` -eq 0 ]; then
#    echo "Mock exited with Error!"
#    exit
#fi

# copy relevant rpm's..
cp RPMS/x86_64/*.rpm ../
cp SRPMS/*.rpm ../

cd ..

#rm -rf $1-$2

echo "$1-$2.rpm: build completed"

