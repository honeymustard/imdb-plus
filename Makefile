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

# Program variables..
EXECUTE = imdb-plus
VERSION = 0.1.0
PROGRAM = $(EXECUTE)-$(VERSION)
SOURCES = Makefile TODO.md README.md LICENSE src misc share scripts
WININST = *.dll lib share LICENSE misc/setup.iss $(EXECUTE).exe
CFLAGS  = -c -Wall -MMD -MP -Isrc
LDFLAGS = -Wl,--as-needed
CC      = gcc

# Program source and object files..
CCFILES = $(shell find ./src/ -name "*.c")
OBJECTS = $(patsubst %.c,%.o,$(CCFILES))
DDFILES = $(patsubst %.o,%.d,$(OBJECTS))

-include $(DDFILES)

###############################################################################
# Standard linux build..
#
# @usage: make | make [ debug | clean | build-[deb|rpm] | dist | [un]install ]
#
###############################################################################

.PHONY : all debug linux install uninstall build build-deb build-rpm

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
	$(CC) $(LDFLAGS) -o $(EXECUTE) $(OBJECTS) $(PACKAGES)

# Make install..
install: all
	-@test -d $(DIR_USR) || mkdir -p $(DIR_USR)
	-@test -d $(DIR_BIN) || mkdir -p $(DIR_BIN)
	-@test -d $(DIR_SHR) || mkdir -p $(DIR_SHR)
	-@test -d $(DIR_APP) || mkdir -p $(DIR_APP)
	-@test -d $(DIR_PIX) || mkdir -p $(DIR_PIX)
	-@test -d $(DIR_MAN) || mkdir -p $(DIR_MAN)
	-@test -d $(DIR_MNP) || mkdir -p $(DIR_MNP)
	-@gzip -f -c ./misc/$(EXECUTE).1 > ./misc/$(EXECUTE).1.gz
	-@cp ./misc/$(EXECUTE).desktop $(DIR_APP)
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

###############################################################################
# Standard windows build: 
#
# Cygwin, MinGW, Gnuwin32 PCRE, libcurl, GTK+, ISSC.exe
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

# MinGW make..
windows: OS = WINDOWS
windows: MINGW = C:\MinGW
windows: GTK2 = $(shell pkg-config.exe --libs --cflags gtk+-win32-2.0)
windows: PATHS = -I$(MINGW)\include -I$(MINGW)\bin -L$(MINGW)\lib 
windows: PACKAGES = $(PATHS) $(GTK2) -lcurl -lpcre
windows: CFLAGS += $(PACKAGES)
windows: OBJECTS += resfile.o
windows: $(OBJECTS) resfile.o
	$(CC) $(LDFLAGS) -o $(EXECUTE) $(OBJECTS) $(PACKAGES) $(WINDOWS)

# MinGW build..
mingw32-build: mingw32-make dist
	-@sh ./scripts/build-win.sh $(EXECUTE) $(VERSION) "$(WININST)" build-win

# MinGW clean..
mingw32-clean: clean

###############################################################################
# Shared targets..
#
###############################################################################

.PHONY : clean dist

dist:
	-@gzip -f -c ./misc/$(EXECUTE).1 > ./misc/$(EXECUTE).1.gz
	-@tar -zcf $(PROGRAM).tar.gz -X ./misc/exclude $(SOURCES)

clean:
	-@rm $(EXECUTE) $(OBJECTS) $(DDFILES) 2>/dev/null && \
    echo "it's clean" || echo "it's already clean"

###############################################################################
# Project targets..
#
###############################################################################

%/main.o: %/main.c
	$(CC) $(CFLAGS) $< -o $@ -DVERSION=\"$(VERSION)\"

%/paths.o: %/paths.c
	$(CC) $(CFLAGS) $< -o $@ -D$(OS)

resfile.o:
	windres -o resfile.o misc/resources.rc

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

