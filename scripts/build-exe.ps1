###############################################################################
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
###############################################################################

###############################################################
#
# Make windows exe/src builds:
#
# This script is run by Makefile. mingw32-make mingw32-build.
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
$install = $args[3].split(" ")

# long program name..
$program_name = "$program-$version"

# build directories..
$dir_build = ".\build"
$dir_build_vers = "$dir_build\$program_name"
$dir_build_vers_output = "$dir_build_vers\$program_name-win"

# temporary locations..
$tmp_srcdir = "$dir_build_vers_output\$program_name-src"
$tmp_srczip = "$dir_build_vers_output\$program_name-src.7z"


###########################################
# make build environment
###########################################

function build-env
{

    # make build directory..
    if (-not (test-path $dir_build))
    {
        new-item $dir_build -type directory | out-null
    }

    # make build version directory..
    if (-not (test-path $dir_build_vers))
    {
        new-item $dir_build_vers -type directory | out-null
    }

    # make build output directory..
    if (-not (test-path $dir_build_vers_output))
    {
        new-item $dir_build_vers_output -type directory | out-null
    }
    else 
    {
        remove-item "$dir_build_vers_output\*" -recurse -force
    }

    # Make source folder..
    new-item "$tmp_srcdir" -type directory | out-null

    return $true
}


###########################################
# make source package
###########################################

function build-src 
{
 
    # copy sources to our temp dir..
    copy-item $sources $tmp_srcdir -recurse

    # remove all non-source files..
    get-childitem $tmp_srcdir -include *.csv, *.swo, *.swp, `
        *.dll, *.o, *.d, *~, *.fuse* -recurse |
        foreach { remove-item $_.fullname -force }

    # zip entire *-win folder..
    &'7za' a -t7z $tmp_srczip "$tmp_srcdir\*"

    remove-item $tmp_srcdir -recurse -force
}


###########################################
# make executable package
###########################################

function build-exe
{

    copy-item $install $dir_build_vers_output -recurse

    # run setup script..
    iscc "$dir_build_vers_output\setup.iss" /dMyAppVersion=$version

    # build archive..
    &'7za' a -t7z "$dir_build_vers_output\$program_name-setup.7z" `
        "$dir_build_vers_output\$program_name-setup.exe"
}


###########################################
# make all targets
###########################################

if (build-env)
{
    build-src
    build-exe

    remove-item "$dir_build_vers_output\*" -exclude *.7z -recurse

    get-childitem $dir_build_vers_output

    write-host "`n$program_name.exe: build completed"
}

