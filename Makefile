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

# Program variables..
EXECUTE = imdb-plus
VERSION = 0.0.8
SOURCES = *.c *.h *.md Makefile COPYING
FOLDERS = src misc share scripts
WININST = lib share COPYING *.dll misc\setup.iss $(EXECUTE).exe
CFLAGS  = -c -Wall
LDFLAGS = -Wl,--as-needed


###############################################################################
# Project files..
#
###############################################################################

# Linux specific objects
ifeq ($(MAKE), make)

OBJECTS = $(patsubst %.c, %.o, $(shell find ./ -name "*.c"))

# Windows specific objects
else

OBJECTS = $(shell powershell -command \
		  "& {Get-ChildItem .\ *.c -recurse | \
		  foreach {(Resolve-Path $$_.fullname -relative) \
		  -replace \".c$$\", \".o\"} | \
		  write-host }")

OBJECTS += resfile.o

endif


###############################################################################
# Standard linux build..
#
# @usage: make | make [ debug | clean | build-[deb|rpm] | dist | [un]install ]
#
###############################################################################

# Install paths..
DIR_USR = $(DESTDIR)/usr
DIR_BIN = $(DESTDIR)/usr/bin
DIR_SHR = $(DESTDIR)/usr/share
DIR_APP = $(DESTDIR)/usr/share/applications
DIR_PIX = $(DESTDIR)/usr/share/pixmaps
DIR_MAN = $(DESTDIR)/usr/share/man
DIR_MNP = $(DESTDIR)/usr/share/man/man1

# Default for make..
.PHONY : all
all: CFLAGS += -O2 -DINSTALL
all: linux

# Make run-in-place debug..
.PHONY : debug
debug: CFLAGS += -g
debug: linux

# Faux target..
.PHONY : linux
linux: OS = LINUX
linux: CURL = -lcurl
linux: GTHREAD = -lgthread-2.0
linux: GTK2 = `pkg-config --cflags --libs gtk+-2.0`
linux: PACKAGES = $(GTK2) $(CURL) $(GTHREAD) 
linux: CFLAGS += $(PACKAGES)
linux: $(OBJECTS)
	gcc $(LDFLAGS) -o $(EXECUTE) $(OBJECTS) $(PACKAGES)

# Make install..
.PHONY : install
install: all
install:
	-@test -d $(DIR_USR) || mkdir -p $(DIR_USR)
	-@test -d $(DIR_BIN) || mkdir -p $(DIR_BIN)
	-@test -d $(DIR_SHR) || mkdir -p $(DIR_SHR)
	-@test -d $(DIR_APP) || mkdir -p $(DIR_APP)
	-@test -d $(DIR_PIX) || mkdir -p $(DIR_PIX)
	-@test -d $(DIR_MAN) || mkdir -p $(DIR_MAN)
	-@test -d $(DIR_MNP) || mkdir -p $(DIR_MNP)
	-@cp ./misc/$(EXECUTE).desktop $(DIR_APP)
	-@cd ./misc && gzip -f -c $(EXECUTE).1 > $(EXECUTE).1.gz && cd ..
	-@cp ./misc/$(EXECUTE).1.gz $(DIR_MNP)
	-@cp -R ./share/icons/imdb-plus $(DIR_PIX)
	-@cp ./share/icons/$(EXECUTE).png $(DIR_PIX)
	-@cp $(EXECUTE) $(DIR_BIN)
	-@echo "$(EXECUTE) installed successfully"

# Make uninstall..
.PHONY : uninstall
uninstall:
	-@rm -f /usr/share/man/man1/$(EXECUTE).1.gz
	-@rm -f /usr/share/applications/$(EXECUTE).desktop
	-@rm -f /usr/share/pixmaps/$(EXECUTE).png
	-@rm -f /usr/bin/$(EXECUTE)
	-@echo "$(EXECUTE) uninstalled successfully"

# Make dist archive..
.PHONY : dist
dist: CURRENT = $(EXECUTE)-$(VERSION)
dist: ARCHIVE = $(SOURCES) $(FOLDERS)
dist:
	-@cd ./misc && gzip -f -c $(EXECUTE).1 > $(EXECUTE).1.gz
	-@tar -zcf $(CURRENT).tar.gz -X ./misc/exclude $(ARCHIVE)

# Make build..
.PHONY : build
build:
	-@echo "Choose a specific linux build.."
	-@echo "- make build-deb (for DEB based distros)"
	-@echo "- make build-rpm (for RPM based distros)"

# Make .DEB package..
.PHONY : build-deb
build-deb: dist
build-deb:
	-@sh ./scripts/build-deb.sh $(EXECUTE) $(VERSION) build-deb

# Make .RPM package..
.PHONY : build-rpm
build-rpm: dist
build-rpm:
	-@sh ./scripts/build-rpm.sh $(EXECUTE) $(VERSION) build-rpm

# Make clean..
.PHONY : clean
clean:
	-@rm $(EXECUTE) `find ./ -name "*.o"` 2>/dev/null && \
    echo "it's clean" || echo "it's already clean"


###############################################################################
# Required Windows packages: Powershell, MinGW, Gnuwin32 PCRE, libcurl, GTK+
#
# @usage: mingw32-make [ mingw32-[ make | debug | clean | build ] ]
#
###############################################################################

# MinGW release build..
.PHONY : mingw32-make
mingw32-make: WINDOWS = -mwindows
mingw32-make: CFLAGS += -O2 
mingw32-make: windows

# MinGW debug build..
.PHONY : mingw32-debug
mingw32-debug: WINDOWS = 
mingw32-debug: CFLAGS += -g
mingw32-debug: windows

.PHONY : windows
windows: GNUWIN32 = C:\MinGW\GnuWin32
windows: LIBCURL  = C:\MinGW\curl

# Requires local copy of pcre3.dll..
windows: PCRE = -I"$(GNUWIN32)\include" \
                -I"$(GNUWIN32)\bin" \
                -L"$(GNUWIN32)\lib" \
                -lpcre

# Requires local copy of libcurl.dll..
windows: CURL = -I"$(LIBCURL)\include" \
                -I"$(LIBCURL)\bin" \
                -L"$(LIBCURL)\lib" \
                -lcurl

# MinGW convenience..
windows: OS = WINDOWS
windows: GTK2 = $(shell pkg-config.exe --libs --cflags gtk+-win32-2.0)
windows: PACKAGES = $(GTK2) $(CURL) $(PCRE)
windows: CFLAGS += $(PACKAGES)
windows: $(OBJECTS)
	gcc $(LDFLAGS) -o $(EXECUTE) $(OBJECTS) $(PACKAGES) $(WINDOWS)

# MinGW clean..
.PHONY : mingw32-clean
mingw32-clean:
	-@powershell -command "& { if (test-path $(EXECUTE).exe) \
		{ remove-item $(EXECUTE).exe -force } }"
	-@powershell -command "& get-childitem .\ *.o -recurse \
		| foreach-object { remove-item $$_.fullname -force }"

# MinGW build requires Powershell, 7za (7zip cli), ISSC (Inno Setup) in PATH..
.PHONY : mingw32-build
mingw32-build: mingw32-make
mingw32-build:
	-@powershell -command "& { Set-ExecutionPolicy RemoteSigned }"
	-@powershell -command "& .\scripts\build-exe.ps1 \
		$(EXECUTE) $(VERSION) '$(SOURCES)' '$(FOLDERS)' '$(WININST)' build-win"


###############################################################################
# Project targets..
#
###############################################################################

# Compile paths..
path%.o: path%.c src/paths.h main.h
	gcc $(CFLAGS) $< -o $@ -D$(OS)

# Compile ui functions..
ui_set_%.o: ui_set_%.c src/ui/ui.h src/ui/ui_widgets.h src/ui/events/events.h
	gcc $(CFLAGS) $< -o $@

# Compile ui fill functions..
ui_fill_%.o: ui_fill_%.c src/ui/ui_fill/ui_fill.h
	gcc $(CFLAGS) $< -o $@

# Compile table..
gtk_custom_table_%.o: gtk_custom_table_%.c src/ui/table/gtk_custom_table.h
	gcc $(CFLAGS) $< -o $@

# Compile events..
event_%.o: event_%.c src/ui/events/events.h
	gcc $(CFLAGS) $< -o $@

# Compile Windows resource..
resfile.o:
	windres -o resfile.o ./misc/resources.rc

# Compile default..
%.o: %.c %.h 
	gcc $(CFLAGS) $< -o $@ -DVERSION=\"$(VERSION)\"

