CC = g++
CPARAMS = -o
CFLAGS = `Magick++-config --cxxflags --cppflags --ldflags --libs` `fltk-config --cxxflags --ldflags --libs`
SOURCES = src/main.cpp
EXECUTABLE = Image-manipulator

all: Image-manipulator

Image-manipulator:
	$(CC) $(CPARAMS) $(EXECUTABLE) $(SOURCES) $(CFLAGS)