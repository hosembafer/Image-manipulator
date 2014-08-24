INSTALL = /usr/bin/install -c
INSTALLDATA = /usr/bin/install -c -D -m 644

CC = g++
CPARAMS = -o
CFLAGS = `Magick++-config --cxxflags --cppflags --ldflags --libs` `fltk-config --cxxflags --ldflags --libs`
SOURCES = src/main.cpp
EXECUTABLE = Image-manipulator

all: Image-manipulator

Image-manipulator:
	$(CC) $(CPARAMS) $(EXECUTABLE) $(SOURCES) $(CFLAGS)

install:all
	$(INSTALL) Image-manipulator /usr/bin/Image-manipulator
	$(INSTALLDATA) data/icons/Image-manipulator-32x32.png /usr/share/Image-manipulator/icons/Image-manipulator-32x32.png
	$(INSTALLDATA) data/Image-manipulator.desktop /usr/share/applications/Image-manipulator.desktop

uninstall:
	rm -rf /usr/bin/Image-manipulator
	rm -rf /usr/share/applications/Image-manipulator.desktop
	rm -rf /usr/share/Image-manipulator