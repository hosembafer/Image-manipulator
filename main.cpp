// g++ arguments
// g++ `Magick++-config --cxxflags --cppflags` `fltk-config --cxxflags --ldflags`  -o "%e" "%f" `Magick++-config --ldflags --libs`

#include <map>
#include <iostream>
#include <Magick++.h>
#include <sys/utsname.h>

#include <stdio.h>
#include <stdlib.h>

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Window.H>
#include <FL/fl_message.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_File_Chooser.H>

using namespace std;

Fl_Window *win;
Fl_Int_Input *inputWidth;
Fl_Int_Input *inputHeight;

Fl_Button *buttonChooseIn;
Fl_Button *buttonChooseOut;
Fl_Button *buttonProceed;

map <int, string> imgChooseList;
string saveFolderPath;
string wh;
string outTmpFilePath;


void init();
void getChooseImages(Fl_Widget* event, void*);
void getChooseSaveFolder(Fl_Widget* event, void*);
void proceed(Fl_Widget* event, void*);
int prepare();

const char* strtoupper(string str);
string strLastSplit(string path, string delimiter);
int imageExtExists(string path);
string getFileNameFromPath(string *path);


int main()
{
	init();
	
	return Fl::run();
}

void init()
{
	win = new Fl_Window(600, 400, "Big Image Manipulator");
	win->begin();
		inputWidth = new Fl_Int_Input(70, 10, 100, 40, "Width: ");
		inputHeight = new Fl_Int_Input(70, 60, 100, 40, "Height: ");
		
		buttonChooseIn = new Fl_Button(310, 10, 180, 30, "Choose Images: ");
		buttonChooseOut = new Fl_Button(310, 60, 180, 30, "Save folder: ");
		
		buttonProceed = new Fl_Button(480, 350, 100, 30, "Proceed");
	win->end();
	
	buttonChooseIn->callback(getChooseImages);
	buttonChooseOut->callback(getChooseSaveFolder);
	
	buttonProceed->callback(proceed);
	
	win->show();
}

void getChooseImages(Fl_Widget *event, void*)
{
	Fl_File_Chooser chooser(
		".",
		"*",
		Fl_File_Chooser::MULTI,
		"Choose images for manipulation"
	);
	
	chooser.show();
	
	while(chooser.shown())
		Fl::wait();
	
	if(chooser.count() > 0)
	{
		int i;
		for(i = 0; i < chooser.count(); i++)
		{
			imgChooseList[i] = chooser.value(i+1);
		}
	}
}

void getChooseSaveFolder(Fl_Widget *event, void*)
{
	Fl_File_Chooser chooser(
		".",
		"*",
		Fl_File_Chooser::DIRECTORY,
		"Choose folder for save result"
	);
	
	chooser.show();
	
	while(chooser.shown())
		Fl::wait();
	
	if(chooser.value() != NULL)
	{
		saveFolderPath = chooser.value();
	}
	cout << saveFolderPath << endl;
}

const char* strtoupper(string str)
{
	for(int i = 0; i < str.size(); i++)
		str[i] = toupper(str[i]);
	return str.c_str();
}

string strLastSplit(string path, string delimiter)
{
	unsigned int pos = 0;
	while((pos = path.find(delimiter)) != string::npos)
		path.erase(0, pos + delimiter.length());
	return path;
}

int imageExtExists(string path)
{
	string tmp = strtoupper(strLastSplit(path, "."));
	if(tmp == "JPG" || tmp == "JPEG" || tmp == "GIF" || tmp == "PNG")
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

string getFileNameFromPath(string *path)
{
	
	return "qwerty";
}

int prepare()
{
	if(atoi(inputWidth->value()) > 0 && atoi(inputHeight->value()) > 0 && saveFolderPath != "" && imgChooseList.size() > 0)
	{
		wh = inputWidth->value();
		wh += "x";
		wh += inputHeight->value();
		
		return 1;
	}
	
	return 0;
}

void proceed(Fl_Widget *event, void*)
{
	if(prepare())
	{
		int i;
		string filePath;
		Magick::Image image;
		for(i = 0; i < imgChooseList.size(); i++)
		{
			cout << "[" << (i+1) << " of " << imgChooseList.size() << "] ";
			filePath = imgChooseList[i];
			if(imageExtExists(filePath))
			{
				outTmpFilePath = "";
				outTmpFilePath += saveFolderPath;
				outTmpFilePath += strLastSplit(filePath, "/");
				
				image.read(filePath);
				image.resize(wh);
				image.write(outTmpFilePath);
				
				
				cout
					<< imgChooseList[i] << " -> " << outTmpFilePath
					<< " "
					<< wh
					<< endl;
			}
			else
			{
				cout << "Not valid image extension." << endl;
			}
		}
		
		cout << "Proceed end." << endl;
	}
}