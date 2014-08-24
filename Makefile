INSTALL = /usr/bin/install -c
INSTALLDATA = /usr/bin/install -c -D -m 644

CC = gcc
CPARAMS = -o

CFLAGS = `pkg-config --cflags --libs gtk+-3.0`
SOURCES = src/main.c
EXECUTABLE = Image-manipulator

all: Image-manipulator

unmake:
	rm -rf Image-manipulator

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