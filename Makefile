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
CC      = gcc


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
		  -replace \".c$$\", \".o\"}}")

OBJECTS += resfile.o

endif


###############################################################################
# Standard linux build..
#
# @usage: make | make [ debug | clean | build-[deb|rpm] | dist | [un]install ]
#
###############################################################################

.PHONY : all debug clean linux install uninstall build build-deb build-rpm dist

# Install paths..
DIR_USR = $(DESTDIR)/usr
DIR_BIN = $(DESTDIR)/usr/bin
DIR_SHR = $(DESTDIR)/usr/share
DIR_APP = $(DESTDIR)/usr/share/applications
DIR_PIX = $(DESTDIR)/usr/share/pixmaps
DIR_MAN = $(DESTDIR)/usr/share/man
DIR_MNP = $(DESTDIR)/usr/share/man/man1

# Default for make..
all: CFLAGS += -O2 -DINSTALL
all: linux

# Make debug..
debug: CFLAGS += -g
debug: linux

# Faux target..
linux: OS = LINUX
linux: GTK2 = `pkg-config --cflags --libs gtk+-2.0`
linux: PACKAGES = $(GTK2) -lcurl -lgthread-2.0
linux: CFLAGS += $(PACKAGES)
linux: $(OBJECTS)
	gcc $(LDFLAGS) -o $(EXECUTE) $(OBJECTS) $(PACKAGES)

# Make install..
install: all
	-@test -d $(DIR_USR) || mkdir -p $(DIR_USR)
	-@test -d $(DIR_BIN) || mkdir -p $(DIR_BIN)
	-@test -d $(DIR_SHR) || mkdir -p $(DIR_SHR)
	-@test -d $(DIR_APP) || mkdir -p $(DIR_APP)
	-@test -d $(DIR_PIX) || mkdir -p $(DIR_PIX)
	-@test -d $(DIR_MAN) || mkdir -p $(DIR_MAN)
	-@test -d $(DIR_MNP) || mkdir -p $(DIR_MNP)
	-@cp ./misc/$(EXECUTE).desktop $(DIR_APP)
	-@cd ./misc && gzip -f -c $(EXECUTE).1 > $(EXECUTE).1.gz
	-@cp ./misc/$(EXECUTE).1.gz $(DIR_MNP)
	-@cp -R ./share/icons/imdb-plus $(DIR_PIX)
	-@cp ./share/icons/$(EXECUTE).png $(DIR_PIX)
	-@cp $(EXECUTE) $(DIR_BIN)
	-@echo "$(EXECUTE) installed successfully"

# Make uninstall..
uninstall:
	-@rm -f /usr/share/man/man1/$(EXECUTE).1.gz
	-@rm -f /usr/share/applications/$(EXECUTE).desktop
	-@rm -f /usr/share/pixmaps/$(EXECUTE).png
	-@rm -f /usr/bin/$(EXECUTE)
	-@echo "$(EXECUTE) uninstalled successfully"

# Make dist archive..
dist: CURRENT = $(EXECUTE)-$(VERSION)
dist: ARCHIVE = $(SOURCES) $(FOLDERS)
dist:
	-@gzip -f -c ./misc/$(EXECUTE).1 > ./misc/$(EXECUTE).1.gz
	-@tar -zcf $(CURRENT).tar.gz -X ./misc/exclude $(ARCHIVE)

# Make build..
build:
	-@echo "Choose a specific linux build.."
	-@echo "- make build-deb (for DEB based distros)"
	-@echo "- make build-rpm (for RPM based distros)"

# Make .DEB package..
build-deb: dist
	-@sh ./scripts/build-deb.sh $(EXECUTE) $(VERSION) build-deb

# Make .RPM package..
build-rpm: dist
	-@sh ./scripts/build-rpm.sh $(EXECUTE) $(VERSION) build-rpm

# Make clean..
clean:
	-@rm $(EXECUTE) `find ./ -name "*.o"` 2>/dev/null && \
    echo "it's clean" || echo "it's already clean"


###############################################################################
# Required Windows packages: Powershell, MinGW, Gnuwin32 PCRE, libcurl, GTK+
#
# @usage: mingw32-make [ mingw32-[ make | debug | clean | build ] ]
#
###############################################################################

.PHONY : mingw32-make mingw32-debug mingw32-clean mingw32-build windows

# MinGW release..
mingw32-make: WINDOWS = -mwindows
mingw32-make: CFLAGS += -O2 
mingw32-make: windows

# MinGW debug..
mingw32-debug: WINDOWS = 
mingw32-debug: CFLAGS += -g
mingw32-debug: windows

# MinGW make all..
windows: OS = WINDOWS
windows: MINGW = C:\MinGW
windows: GTK2 = $(shell pkg-config.exe --libs --cflags gtk+-win32-2.0)
windows: PATHS = -I$(MINGW)\include -I$(MINGW)\bin -L$(MINGW)\lib 
windows: PACKAGES = $(PATHS) $(GTK2) -lcurl -lpcre
windows: CFLAGS += $(PACKAGES)
windows: $(OBJECTS)
	gcc $(LDFLAGS) -o $(EXECUTE) $(OBJECTS) $(PACKAGES) $(WINDOWS)

# MinGW clean..
mingw32-clean:
	-@powershell -command "& { if (test-path $(EXECUTE).exe) \
		{ remove-item $(EXECUTE).exe -force } }"
	-@powershell -command "& get-childitem .\ *.o -recurse \
		| foreach-object { remove-item $$_.fullname -force }"

# MinGW build requires Powershell, 7za (7zip cli), ISSC (Inno Setup)..
mingw32-build: mingw32-make
mingw32-build:
	-@powershell -command "& { Set-ExecutionPolicy RemoteSigned }"
	-@powershell -command "& .\scripts\build-exe.ps1 \
		$(EXECUTE) $(VERSION) '$(SOURCES)' '$(FOLDERS)' '$(WININST)' build-win"


###############################################################################
# Project targets..
#
###############################################################################

main.o: main.c main.h src/paths.h src/ui/ui.h
	$(CC) $(CFLAGS) $< -o $@ -DVERSION=\"$(VERSION)\"

%openfile.o: %openfile.c %openfile.h %readfile.h %globals.h %ui/ui.h
	$(CC) $(CFLAGS) $< -o $@

%paths.o: %paths.c %paths.h main.h
	$(CC) $(CFLAGS) $< -o $@ -D$(OS)

event_%.o: event_%.c src/ui/events/events.h
	$(CC) $(CFLAGS) $< -o $@

gtk_%.o: gtk_%.c src/ui/table/gtk_custom_table.h
	$(CC) $(CFLAGS) $< -o $@

ui_%.o: ui_%.c src/ui/ui.h src/ui/ui_fill/ui_fill.h
	$(CC) $(CFLAGS) $< -o $@

resfile.o:
	windres -o resfile.o ./misc/resources.rc

src/%.o: src/%.c src/%.h 
	$(CC) $(CFLAGS) $< -o $@

