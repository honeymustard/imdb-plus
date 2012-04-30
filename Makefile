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

EXECUTE = imdb-plus
VERSION = 0.0.5
OBJECTS = main.o readfile.o regex.o download.o strnatcmp.o 
SOURCES = *.c *.h Makefile COPYING TODO *.md build.ps1 *.sh *.iss *.rc
FOLDERS = lib res misc
CFLAGS  = -c -Wall
LDFLAGS = -Wl,--as-needed
WINGUI  = -mwindows


TABLE_SOURCES = $(wildcard ./lib/gtk_custom_table/*.c)
EVENT_SOURCES = $(wildcard ./lib/events/*.c)
OTHER_OBJECTS = gtk_custom_table*.o event_*.o


###############################################################################
# Standard linux build..
#
###############################################################################

all: CURL = -lcurl
all: GTK2 = `pkg-config --cflags --libs gtk+-2.0`
all: CFLAGS += -O2 $(GTK2) $(CURL) -DINSTALL
all: $(OBJECTS) GTK_CUSTOM_TABLE GTK_EVENTS
	gcc $(LDFLAGS) -o $(EXECUTE) $(OBJECTS) $(OTHER_OBJECTS) $(GTK2) $(CURL) 

install:
	-@mkdir $(DESTDIR)/usr
	-@mkdir $(DESTDIR)/usr/bin
	-@mkdir $(DESTDIR)/usr/share
	-@mkdir $(DESTDIR)/usr/share/applications
	-@mkdir $(DESTDIR)/usr/share/pixmaps
	-@mkdir $(DESTDIR)/usr/share/man
	-@mkdir $(DESTDIR)/usr/share/man/man1
	-@mkdir $(DESTDIR)/usr/share/$(EXECUTE)
	-@mkdir $(DESTDIR)/usr/share/$(EXECUTE)/res
	-@cp -R ./res/graphics $(DESTDIR)/usr/share/$(EXECUTE)/res
	-@cp ./misc/$(EXECUTE).desktop $(DESTDIR)/usr/share/applications
	-@cp ./misc/$(EXECUTE).1.gz $(DESTDIR)/usr/share/man/man1
	-@cp ./res/graphics/$(EXECUTE).png $(DESTDIR)/usr/share/pixmaps
	-@cp $(EXECUTE) $(DESTDIR)/usr/bin
	-@echo "$(EXECUTE) was installed successfully"
	chmod a+rwx $(DESTDIR)/usr/share/$(EXECUTE)/res


uninstall:
	-@rm -f /usr/share/man/man1/$(EXECUTE).1.gz
	-@rm -f /usr/share/applications/$(EXECUTE).desktop
	-@rm -f /usr/share/pixmaps/$(EXECUTE).png
	-@rm -f -R /usr/share/$(EXECUTE)
	-@rm -f /usr/bin/$(EXECUTE)
	-@echo "$(EXECUTE) uninstalled successfully"

debug: CURL = -lcurl
debug: GTK2 = `pkg-config --cflags --libs gtk+-2.0`
debug: CFLAGS += -g $(GTK2) $(CURL)
debug: $(OBJECTS) GTK_CUSTOM_TABLE GTK_EVENTS
	gcc $(LDFLAGS) -o $(EXECUTE) $(OBJECTS) $(OTHER_OBJECTS) $(GTK2) $(CURL)


.PHONY : dist-clean
dist-clean:
	-@rm -Rf ./build/$(EXECUTE)-$(VERSION)/$(EXECUTE)-$(VERSION)-deb

.PHONY : dist
dist:
	cd misc && gzip -f -c $(EXECUTE).1 > $(EXECUTE).1.gz && cd ..
	tar -zcf $(EXECUTE)-$(VERSION).tar.gz --exclude='*.csv' --exclude='*.swo' --exclude='*.swp' --exclude='*.o' --exclude='*~' $(SOURCES) $(FOLDERS)

.PHONY : build
build:
	make dist
	sh build.sh $(EXECUTE) $(VERSION)

.PHONY : clean
clean:
	-@rm *.o $(EXECUTE) 2>/dev/null && echo "it's clean" || echo "it's already clean"


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
mingw32: PCRE = -I"C:\MinGW\GnuWin32\include" \
                -I"C:\MinGW\GnuWin32\bin" \
                -L"C:\MinGW\GnuWin32\lib" \
                -lpcre

# Requires local copy of libcurl.dll..
mingw32: CURL = -I"C:\MinGW\curl\include" \
                -I"C:\MinGW\curl\bin" \
                -L"C:\MinGW\curl\lib" \
                -lcurl

# Result from "pkg-config --libs --cflags gtk+-win32-2.0" in GTK\bin
mingw32: GTK2 = -mms-bitfields \
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


# Win32 release build with MinGW..
mingw32: CFLAGS += -O2 $(GTK2) $(CURL) $(PCRE)
mingw32: resfile.o
mingw32: $(OBJECTS) GTK_CUSTOM_TABLE GTK_EVENTS
	gcc $(LDFLAGS) -o $(EXECUTE) $(OBJECTS) $(OTHER_OBJECTS) resfile.o $(GTK2) $(CURL) $(PCRE) $(WINGUI)

# Win32 debug build with MinGW..
mingw32-debug: WINGUI = 
mingw32-debug: mingw32

# MinGW clean, remove o's exe's..
mingw32-clean:
	del *.o $(EXECUTE).exe

# MinGW build requires that powershell & 7zip (7za.exe) are in PATH..
.PHONY : mingw32-build
mingw32-build:
	powershell -command "& {Set-ExecutionPolicy RemoteSigned}"
	powershell .\build.ps1 $(EXECUTE) $(VERSION) --nogui

# Compile resource file, to get a nice icon..
resfile.o:
	windres -o resfile.o resources.rc


###############################################################################
# Project files..
#
###############################################################################

main.o:
	gcc -DAPP_VERS=\"$(VERSION)\" $(CFLAGS) main.c 

readfile.o:
	gcc $(CFLAGS) lib/readfile.c

regex.o:
	gcc $(CFLAGS) lib/regex.c

download.o:
	gcc $(CFLAGS) lib/download.c

strnatcmp.o:
	gcc $(CFLAGS) lib/gtk_custom_table/strnatcmp/strnatcmp.c

.PHONY : GTK_CUSTOM_TABLE
GTK_CUSTOM_TABLE:
	gcc $(CFLAGS) $(TABLE_SOURCES)

.PHONY : GTK_EVENTS
GTK_EVENTS:
	gcc -DAPP_VERS=\"$(VERSION)\" $(CFLAGS) $(EVENT_SOURCES)

