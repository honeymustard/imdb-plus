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

rpmdev-setuptree

# copy relevant files to build folder..
cp ./misc/$1.spec ~/rpmbuild/SPECS
cp ./$1-$2.tar.gz ~/rpmbuild/SOURCES

# copy version number into spec..
sed "s/X\.X\.X/$2/" <~/rpmbuild/SPECS/$1.spec >~/rpmbuild/SPECS/$1.tmp
cat ~/rpmbuild/SPECS/$1.tmp > ~/rpmbuild/SPECS/$1.spec && rm ~/rpmbuild/SPECS/$1.tmp

cd ~/rpmbuild/SPECS

# Check RPM spec with lint..
if [ `rpmlint $1.spec | grep -c E:` -gt 0 ]; then
    echo "rpmlint exited with Error!"
    exit
fi

rpmbuild -ba $1.spec

cd - 

cd ~/rpmbuild

# clean/make LOGS directory..
if [ -d LOGS ]; then
    rm -rf ./LOGS
fi

mkdir LOGS

# Check RPM source with mock..
`mock -r fedora-17-x86_64 --rebuild ./SRPMS/*.src.rpm --resultdir=./LOGS`

if [ `cat ./LOGS/state.log | grep -c "Finish: run"` -eq 0 ]; then
    echo "Mock exited with Error!"
    exit
fi

cd - 

# make build directory if not available..
if [ ! -d "build" ]; then
    mkdir "build"
fi

cd ./build

# make version directory if not available..
if [ ! -d "$1-$2" ]; then
    mkdir $1-$2
fi

cd ./$1-$2

# clean/make dist directory if applicable..
if [ -d "$1-$2-rpm" ]; then
    rm -rf $1-$2-rpm
fi

mkdir $1-$2-rpm

cd $1-$2-rpm

# copy relevant rpm's..
cp ~/rpmbuild/RPMS/x86_64/*.rpm .
cp ~/rpmbuild/SRPMS/*.rpm .

rm -rf ~/rpmbuild

echo "$1-$2.rpm: build completed"

