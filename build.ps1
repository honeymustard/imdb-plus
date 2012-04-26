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

###########################################
# powershell build-script for imdb-plus
#
# @param program-name
# @param program-version
# 
# @usage .\build.ps1 name version [--nogui]
#
###########################################
# required program(s): 
#
# powershell.exe  : iwith admin privileges
# 7za.exe         : 7-zip cmdline version in path
# ISCC.exe        : Inno Setup 5 version in path
#
###########################################
#
# @written by     : Adrian Solumsmo
# @email          : adrian.solumsmo@gmail.com
#
###########################################

if ($args.length -lt 2)
{
    write-output "build.ps1: expected 2 arguments. ex. .\build.ps1 'program-name' 'version'"
    exit
}

if (!(test-path "$($args[0]).exe")) 
{
    write-output "build.ps1: expected .exe file. have you buildt project?"
    exit
}


###########################################
# create build environment
###########################################

$program = $args[0]
$version = $args[1]
$bname = "$($args[0])-$($args[1])"
$builddir = ".\build\$($bname)"
$copydir = ".\build\$($bname)\$($bname)"


# make build/copy directory if necessary..
if (!(test-path -path $builddir))
{
    new-item $builddir -type directory | out-null
}
else 
{
    remove-item "$($builddir)\*" -recurse -force
}

new-item $copydir -type directory | out-null



# load winforms assemblies..
[reflection.assembly]::loadwithpartialname("system.windows.forms") | out-null


# build ready to run archive..
function build-runable
{

    # copy main program files..
    $newdir = "$($copydir)\run"
    new-item $newdir -type directory | out-null

    copy-item *.dll, "$($program).exe", *.txt $newdir

    new-item "$($newdir)\lib" -type directory | out-null

    # recursively copy required dirs..
    copy-item lib\gtk-2.0 "$($newdir)\lib" -recurse
    copy-item res $newdir -recurse
    copy-item share $newdir -recurse

    # remove any lingering data files..
    remove-item "$($newdir)\res\data\*" -recurse -force

    # build archive using 7-zip command line utility (7za must be in PATH)
    &'7za' a -t7z "$($builddir)\$($bname)-win32.7z" "$($newdir)\*"

    remove-item $newdir -recurse -force
}


# build project source code archive..
function build-source
{

    $newdir = "$($copydir)\source"
    new-item $newdir -type directory | out-null

    copy-item *c, *.h, *.rc, *.ps1, *.iss, Makefile $newdir

    # recursively copy required dirs..
    copy-item lib $newdir -recurse
    copy-item res $newdir -recurse
    copy-item share $newdir -recurse

    # remove any lingering data files..
    remove-item "$($newdir)\res\data\*" -recurse -force
    remove-item "$($newdir)\lib\gtk-2.0" -recurse -force


    # remove .swp, .swo and temp ~ and binary files..
    get-childitem $newdir -include *.swp, *.swo, *~ -recurse |
        foreach-object {remove-item $_.fullname -force}

    copy-item *c, *.h, *.rc, *.ps1, *.iss, Makefile $newdir

    $var = $null

    # build archive using 7-zip command line utility (7za must be in PATH)
    &'7za' a -t7z "$($builddir)\$($bname)-win32-src.7z" "$($newdir)\*"

    remove-item $newdir -recurse -force
}


# build project auto installing archive..
function build-installer
{

    $newdir = "$($copydir)\installer"
    new-item $newdir -type directory | out-null

    copy-item setup.iss, *.ico, *.txt, *.dll, "$($program).exe" $newdir

    new-item "$($newdir)\lib" -type directory | out-null

    # recursively copy required dirs..
    copy-item lib\gtk-2.0 "$($newdir)\lib" -recurse
    copy-item res $newdir -recurse
    copy-item share $newdir -recurse

    # remove any lingering data files..
    remove-item "$($newdir)\res\data\*" -recurse -force
    remove-item "$($newdir)\lib\gtk-2.0" -recurse -force

    iscc "$($newdir)\setup.iss" /dMyAppVersion=$($version)

    # build archive using 7-zip command line utility (7za must be in PATH)
    &'7za' a -t7z "$($builddir)\$($bname)-win32-installer.7z" `
        "$($builddir)\$($bname)\$($bname)-setup.exe"

    remove-item "$($builddir)\$($bname)\$($bname)-setup.exe" -force

    remove-item $newdir -recurse -force

}


# build project based on checkbox values..
function build-project
{
    $button2.enabled = $false

    $selected = 0

    # check for checkboxes..
    for($i = 0; $i -lt 3; $i++)
    {
        if($check[$i].checked)
        {
            $rtextbox.text += "selected: " + $options[$i] + "`n"
            $selected++
        }
    }

    # at least one option was selected..
    if($selected -gt 0)
    {

        # run selected build(s)..
        if($check[0].checked)
        {

            build-runable | foreach-object {$rtextbox.text += "$($_)`n"}
        }

        if($check[1].checked)
        {

            build-source | foreach-object {$rtextbox.text += "$($_)`n"}

        }

        if($check[2].checked)
        {

            build-source | foreach-object {$rtextbox.text += "$($_)`n"}
        }    


        # remove temporary build directory..
        remove-item "$($builddir)\$($bname)" -recurse -force

        # view contents of builddir..
        get-childitem $builddir

    }
    else
    {
        $rtextbox.text += "You need to select one mode`n"
    }

    $button2.enabled = $true
}



###########################################
# Run buildscript without gui..
###########################################

if(($args.length -eq 3) -and ($args[2] -eq "--nogui"))
{

    # build all targets..
    build-runable
    build-source
    build-installer

    remove-item "$($builddir)\$($bname)" -recurse -force

    # view contents of builddir..
    get-childitem $builddir

    exit
}



###########################################
# Run buildscript with gui..
###########################################

$options = @(
        "runnable package", 
        "source package", 
        "auto-installer package"
        )

$form = new-object windows.forms.form

$form.text = "BUILD:"

$label = new-object windows.forms.label
$label.location = new-object drawing.point 10, 5 
$label.size = new-object drawing.point 200, 25
$label.text = "Select which targets to build:"

$form.controls.add($label)

$check = @()

for($i = 0; $i -lt 3; $i++)
{
    $check += ,(new-object windows.forms.checkbox)
    $check[$i].location = new-object drawing.point 10, (($i * 25) + 40)
    $check[$i].size = new-object drawing.point 15, 15
    $check[$i].checked = $true

    $label = new-object windows.forms.label
    $label.location = new-object drawing.point 30, (($i * 25) + 40)
    $label.size = new-object drawing.point 300, 25
    $label.text = $options[$i]

    $form.controls.add($check[$i])
    $form.controls.add($label)
}

$rtextbox = new-object windows.forms.richtextbox
$rtextbox.location = new-object drawing.point 10, (($i++ * 25) + 40)
$rtextbox.size = new-object drawing.point 600, 180
$rtextbox.readonly = $true
$rtextbox.text = "Ready to build project..`n"

$form.controls.add($rtextbox)

$button1 = new-object windows.forms.button
$button1.location = new-object drawing.point 10, (($i * 25) + 40 + 160)
$button1.size = new-object drawing.point 60, 25
$button1.text = "close"
$button1.add_click({$form.close()})

$button2 = new-object windows.forms.button
$button2.location = new-object drawing.point 75, (($i++ * 25) + 40 + 160)
$button2.size = new-object drawing.point 60, 25
$button2.text = "build"
$button2.add_click({build-project})

$form.controls.add($button1)
$form.controls.add($button2)

$form.size = new-object drawing.point 635, 370

$form.showdialog()


