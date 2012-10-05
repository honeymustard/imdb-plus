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


# Main program variables..
EXECUTE = imdb-plus
VERSION = 0.0.6
OBJECTS = main.o readfile.o openfile.o parsefile.o download.o \
          patterns.o colors.o strnatcmp.o 
SOURCES = *.c *.h Makefile COPYING TODO *.md *.iss *.rc
FOLDERS = lib res misc share scripts
CFLAGS  = -c -Wall
LDFLAGS = -Wl,--as-needed
WINDOWS = -mwindows

# Other libs..
OBJECTS += $(patsubst %.c, %.o, $(wildcard ./lib/gtk_custom_table/*.c))
OBJECTS += $(patsubst %.c, %.o, $(wildcard ./lib/events/*.c))

# Install paths..
DIR_USR = $(DESTDIR)/usr
DIR_BIN = $(DESTDIR)/usr/bin
DIR_SHR = $(DESTDIR)/usr/share
DIR_APP = $(DESTDIR)/usr/share/applications
DIR_PIX = $(DESTDIR)/usr/share/pixmaps
DIR_MAN = $(DESTDIR)/usr/share/man
DIR_MNP = $(DESTDIR)/usr/share/man/man1
DIR_EXE = $(DESTDIR)/usr/share/$(EXECUTE)
DIR_DAT = $(DESTDIR)/usr/share/$(EXECUTE)/res

###############################################################################
# Standard linux build..
#
###############################################################################

# Standard make for install..
.PHONY : all
all: CURL = -lcurl
all: GTK2 = `pkg-config --cflags --libs gtk+-2.0`
all: CFLAGS += -O2 $(GTK2) $(CURL) -DINSTALL
all: $(OBJECTS)
	gcc $(LDFLAGS) -o $(EXECUTE) $(OBJECTS) $(GTK2) $(CURL) -lgthread-2.0

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
	-@test -d $(DIR_EXE) || mkdir -p $(DIR_EXE)
	-@test -d $(DIR_DAT) || mkdir -p $(DIR_DAT)
	-@cp -R ./res/graphics $(DIR_DAT)
	-@cp ./misc/$(EXECUTE).desktop $(DIR_APP)
	-@cp ./misc/$(EXECUTE).1.gz $(DIR_MNP)
	-@cp ./res/graphics/$(EXECUTE).png $(DIR_PIX)
	-@cp $(EXECUTE) $(DIR_BIN)
	-@chmod a+rwx $(DIR_DAT)
	-@echo "$(EXECUTE) was installed successfully"

# Make uninstall..
.PHONY : uninstall
uninstall:
	-@rm -f /usr/share/man/man1/$(EXECUTE).1.gz
	-@rm -f /usr/share/applications/$(EXECUTE).desktop
	-@rm -f /usr/share/pixmaps/$(EXECUTE).png
	-@rm -f -R /usr/share/$(EXECUTE)
	-@rm -f /usr/bin/$(EXECUTE)
	-@echo "$(EXECUTE) uninstalled successfully"

# Make run-in-place debug..
.PHONY : debug
debug: CURL = -lcurl
debug: GTK2 = `pkg-config --cflags --libs gtk+-2.0`
debug: CFLAGS += -g $(GTK2) $(CURL)
debug: $(OBJECTS)
	gcc $(LDFLAGS) -o $(EXECUTE) $(OBJECTS) $(GTK2) $(CURL) -lgthread-2.0

# Make clean..
.PHONY : dist-clean
dist-clean:
	-@rm -Rf ./build/$(EXECUTE)-$(VERSION)/$(EXECUTE)-$(VERSION)-deb
	-@rm -Rf ./build/$(EXECUTE)-$(VERSION)/$(EXECUTE)-$(VERSION)-rpm

# Make dist archive..
.PHONY : dist
dist:
	cd misc && gzip -f -c $(EXECUTE).1 > $(EXECUTE).1.gz && cd ..
	-@test -d $(EXECUTE)-$(VERSION) || mkdir -p $(EXECUTE)-$(VERSION)
	cp -R $(SOURCES) $(FOLDERS) -t $(EXECUTE)-$(VERSION)
	tar -zcf $(EXECUTE)-$(VERSION).tar.gz \
    --exclude='*.csv' \
    --exclude='*.swo' \
    --exclude='*.swp' \
    --exclude='*.dll' \
    --exclude='*.o' \
    --exclude='*~' \
    --exclude='*.fuse' \
    $(EXECUTE)-$(VERSION)
	rm -Rf $(EXECUTE)-$(VERSION)

# Make build..
.PHONY : build
build:
	@echo "Choose a specific linux build.."
	@echo "- make build-deb (for DEB based distros)"
	@echo "- make build-rpm (for RPM based distros)"

# Make .DEB package..
.PHONY : build-deb
build-deb: dist
build-deb:
	sh ./scripts/build-deb.sh $(EXECUTE) $(VERSION) build-deb

# Make .RPM package..
.PHONY : build-rpm
build-rpm: dist
build-rpm:
	sh ./scripts/build-rpm.sh $(EXECUTE) $(VERSION) build-rpm

# Make clean..
.PHONY : clean
clean:
	-@rm $(OBJECTS) $(EXECUTE) 2>/dev/null && \
    echo "it's clean" || \
    echo "it's already clean"


###############################################################################
# Windows specific stuff, required packages: 
#
# gnuwin32 pcre 
# libcurl 
# gtk+
#
# Required .dll's to run program:
#
# pcre3.dll, libucrl.dll, GTK\*.dll
#
# Command line invocation:
#
# mingw32-make mingw32
# mingw32-make mingw32-debug
# mingw32-make mingw32-clean
# mingw32-make mingw32-build
#
###############################################################################

# Requires local copy of pcre3.dll..
windows: PCRE = -I"C:\MinGW\GnuWin32\include" \
                -I"C:\MinGW\GnuWin32\bin" \
                -L"C:\MinGW\GnuWin32\lib" \
                -lpcre

# Requires local copy of libcurl.dll..
windows: CURL = -I"C:\MinGW\curl\include" \
                -I"C:\MinGW\curl\bin" \
                -L"C:\MinGW\curl\lib" \
                -lcurl

# Result from "pkg-config --libs --cflags gtk+-win32-2.0" in GTK\bin
windows: GTK2 = -mms-bitfields \
                -IC:/GTK+/include/gtk-2.0 \
                -IC:/GTK+/lib/gtk-2.0/include \
                -IC:/GTK+/include/atk-1.0 \
                -IC:/GTK+/include/cairo \
                -IC:/GTK+/include/gdk-pixbuf-2.0 \
                -IC:/GTK+/include/pango-1.0 \
                -IC:/GTK+/include/glib-2.0 \
                -IC:/GTK+/lib/glib-2.0/include \
                -IC:/GTK+/include \
                -IC:/GTK+/include/freetype2 \
                -IC:/GTK+/include/libpng14 \
                -LC:/GTK+/lib \
                -lgtk-win32-2.0 \
                -lgdk-win32-2.0 \
                -latk-1.0 \
                -lgio-2.0 \
                -lpangowin32-1.0 \
                -lgdi32 \
                -lpangocairo-1.0 \
                -lgdk_pixbuf-2.0 \
                -lpango-1.0 \
                -lcairo \
                -lgobject-2.0 \
                -lgmodule-2.0 \
                -lgthread-2.0 \
                -lglib-2.0 \
                -lintl


# MinGW convenience..
.PHONY : windows
windows: CFLAGS += $(GTK2) $(CURL) $(PCRE)
windows: OBJECTS += resfile.o
windows: resfile.o $(OBJECTS)
	gcc $(LDFLAGS) -o $(EXECUTE) $(OBJECTS) $(GTK2) $(CURL) $(PCRE) $(WINDOWS)

# MinGW run-in-place build..
.PHONY : mingw32
mingw32: CFLAGS += -O2 
mingw32: windows

# MinGW debug build..
.PHONY : mingw32-debug
mingw32-debug: WINDOWS = 
mingw32-debug: CFLAGS += -g
mingw32-debug: windows

# MinGW clean, remove o's exe's..
.PHONY : mingw32-clean
mingw32-clean:
	del *.o lib\events\*.o lib\gtk_custom_table\*.o $(EXECUTE).exe

# MinGW build requires that powershell & 7zip (7za.exe) are in PATH..
.PHONY : mingw32-build
mingw32-build: mingw32
mingw32-build:
	powershell -command "& {Set-ExecutionPolicy RemoteSigned}"
	powershell -command "& .\scripts\build-exe.ps1 \
		$(EXECUTE) $(VERSION) '$(SOURCES)' '$(FOLDERS)' build-win"


###############################################################################
# Project files..
#
###############################################################################

main.o: main.c master.h tables.h widgets.h lib/events/events.h
	gcc $(CFLAGS) main.c -DAPP_VERS=\"$(VERSION)\"

readfile.o: lib/readfile.c lib/readfile.h
	gcc $(CFLAGS) lib/readfile.c

openfile.o: lib/openfile.c lib/openfile.h
	gcc $(CFLAGS) lib/openfile.c

parsefile.o: lib/parsefile.c lib/parsefile.h
	gcc $(CFLAGS) lib/parsefile.c

download.o: lib/download.c lib/download.h
	gcc $(CFLAGS) lib/download.c

patterns.o: lib/patterns.c lib/patterns.h
	gcc $(CFLAGS) lib/patterns.c

colors.o: lib/colors.c lib/colors.h
	gcc $(CFLAGS) lib/colors.c

strnatcmp.o: lib/gtk_custom_table/strnatcmp/strnatcmp.c lib/gtk_custom_table/strnatcmp/strnatcmp.h
	gcc $(CFLAGS) lib/gtk_custom_table/strnatcmp/strnatcmp.c

gtk_custom_table_%.o: gtk_custom_table_%.c lib/gtk_custom_table/gtk_custom_table.h
	gcc $(CFLAGS) $< -o $@

event_%.o: event_%.c lib/events/events.h
	gcc $(CFLAGS) $< -o $@ -DAPP_VERS=\"$(VERSION)\"

resfile.o:
	windres -o resfile.o resources.rc

