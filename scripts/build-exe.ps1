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

###############################################################
#
# Make windows exe/src builds:
#
# This script is run by Makefile. mingw32-make mingw32-build.
#
###############################################################

###############################################################
# required programs that must be in path
#
# powershell.exe  : with admin privileges
# 7za.exe         : 7-zip cmdline version
# ISCC.exe        : InnoSetup 5
#
###############################################################


# make sure script is run from toplevel makefile only..
if ($args.length -lt 5)
{
    write-output "Error: Script expected more arguments!"
    exit
}

if ($args[4] -ne "build-win")
{
    write-output "Error: Script should be run by toplevel Makefile!"
    exit
}


# variables from makefile..
$program = $args[0]
$version = $args[1]
$sources = $args[2].split(" ")
$folders = $args[3].split(" ")

# temporary locations..
$tmpdir = ".\$($program)-$($version)-win"
$tmpzip = ".\$($program)-$($version)-win.7z"

$execute = "$($program)-$($version)"
$builddir = ".\build\$($execute)"
$copydir = ".\build\$($execute)\$($execute)-exe"
$instdir = "$($copydir)\installer"


###########################################
# make source package
###########################################

function build-src 
{

    # Make dist folder..
    if (test-path -path $tmpdir) 
    { 
        remove-item $tmpdir -recurse -force
    }
    else {
        new-item $tmpdir -type directory | out-null
    }

    # copy sources and folders to our temp dir..
    copy-item $sources $tmpdir -recurse
    copy-item $folders $tmpdir -recurse

    # remove all non-source files..
    get-childitem $tmpdir -include *.csv, *.swo, *.swp, `
        *.dll, *.o, *~, *.fuse -recurse |
        foreach-object { remove-item $_.fullname -force }

    # remove existing archive is necessary..
    if (test-path -path $tmpzip) 
    {
        remove-item $tmpzip -force 
    }

    # zip entire *-win folder..
    &'7za' a -t7z $tmpzip $tmpdir

    remove-item $tmpdir -recurse -force
}


###########################################
# make build environment
###########################################

function build-env
{

    # make build directory..
    if (!(test-path -path $builddir))
    {
        new-item $builddir -type directory | out-null
    }

    # make copy directory..
    if (!(test-path -path $copydir))
    {
        new-item $copydir -type directory | out-null
    }
    else 
    {
        remove-item "$($copydir)\*" -recurse -force
    }

    new-item $instdir -type directory | out-null
}


###########################################
# make executable package
###########################################

function build-exe
{

    # extract source package..
    &'7za' x $tmpzip "-o$($instdir)"
    move-item "$($instdir)\$($execute)-win\*" $instdir
    remove-item "$($instdir)\$($execute)-win" -force

    # copy relevant binaries..
    copy-item "$($program).exe" $instdir
    copy-item "lib\gtk-2.0" "$($instdir)\lib" -recurse -force
    copy-item res $instdir -recurse -force
    copy-item *.dll $instdir -recurse -force

    # run setup script..
    iscc "$($instdir)\setup.iss" /dMyAppVersion=$($version)

    # build archive..
    &'7za' a -t7z "$($copydir)\$($execute)-exe.7z" `
        "$($copydir)\$($execute)-setup.exe"

    # cleanup..
    remove-item "$($copydir)\$($execute)-setup.exe" -force
    remove-item $instdir -recurse -force
}


###########################################
# make all targets
###########################################

build-src
build-env
build-exe

copy-item $tmpzip $copydir

# view contents of builddir..
get-childitem $copydir

write-output "$($execute).exe: build completed"

