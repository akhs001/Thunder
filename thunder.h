#pragma once
#include <iostream>
#include <map>
#include <Windows.h>
#include <thread>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

//The thunder Extension for C++ console Applications is Created By Thanos Athanasiadis
//SAE Student 2020. This extension provide a lot of functions to help you Build console 
//applications easy and with a lot of functionality(see the list bellow)
//****FUNCTIONALITIES****
//Change text color
//Change Background color
//Mouse Handling
//Keyboard Handling
//Change console title
//Change console size
//Change Text size
//Change cursor position
//This extension is absolutely FREE and you can use it as you want or extend it even more.


using namespace std;
/// <summary>
/// Color enum for the text
/// </summary>
enum class COLOR { DARKBLUE=1 , GREEN=2 , LIGHTBLUE=3 , RED=4 , PINK=5 , MUSTARD=6 , WHITE=7 , GREY=8 , 
					BLUE=9 , LIGHTGREEN=10 , LIGHTRED=12 , LIGHTPINK=13 , LIGHTYELLOW=14 , DEFAULT=15 };

/// <summary>
/// COlor enum for the Backgound
/// </summary>
enum class BG_COLOR { YELLOW , GREEN , CORAL_RED, BLUE  , FUCSIA ,BEIGE ,WHITE , GRAY , PURPLE , RED , AQUA , ORANGE };

/// <summary>
/// Enum for return type of the MessageBox
/// </summary>
enum class MSG_BOX_RETURN { OK= 1 , CANCEL =2 };

/// <summary>
/// Enum for the Mouse Click
/// </summary>
enum class _MOUSE_INPUT {NONE , L_CLICK, R_CLICK };


namespace thunder
{
	//Initialize !!!USE THIS FIRST!!!
	void _Init();												//Initialize of Thunder extension

	//Variable Functions
	static map<string, string> vars;							//The map for holding the variables
	int _getI(string name);										//Get a variable and convert it to Integer
	void _del(string name);										//Delete a variable
	string _get (string name);									//Get a variable as a string 
	void _set(string name ,string value);						//Set a variable


	//LOG functions
	void _AddText(string text);									//Show text but not change line
	void _Log(int msg);											//Show text with default color
	void _Log(string msg);										//Show text with default color
	void _Log(int msg , COLOR color);							//Show text with color
	void _Log(string msg , COLOR color);						//Show text with color
	void _DebugLog(string msg);									//Show a Debug message
	MSG_BOX_RETURN  _MsgBox(string msg, string caption);		//Show a message Box

	//Color functions
	void _Color(COLOR color);									//Change the text Color
	void _BGColor(BG_COLOR color);								//Change the Background color

	//Input functions
	_MOUSE_INPUT _GetMouse();									//The key pressed on mouse
	char _GetKey();												//The key pressed on keyboard
	COORD _GetMousePos();										//The mouse position

	//Console functions
	void _Wait();												//Wait until the user pressed any button
	void _Clear();												//Clear the console
	void _Title(string title);									//Change the console title
	void _Size(unsigned int width ,unsigned int height);		//change the console size
	void _GotoPos(short x, short y);							//Change console cursor position
	void _SetPixeSize(int size);	
	void _HideCursor(bool flag);//Change the Font size

	//File Handling
	void _CreateFile(string name);
	bool _IsFileExist(string name);
	vector<string> _ReadFile(string name);
	void _WriteToFile(string name, string data);
	void _AppendFile(string name, string data);
	
};


//Enable the Input for the console
DWORD mode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
//COnsole Handler
HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
//Console Window
HWND con = GetConsoleWindow();
//Input Handler
HANDLE handleIn = GetStdHandle(STD_INPUT_HANDLE);
//Mouse position Var
COORD mousePOS;
//**Used for the input**
INPUT_RECORD rec;
DWORD numRead;



/// <summary>
/// Change text color
/// </summary>
/// <param name="color"> : Color of text</param>
void thunder::_Color(COLOR color)
{
	SetConsoleTextAttribute(hconsole, (WORD)color);
}

/// <summary>
/// Throw a message at the Output panel (Debug)
/// </summary>
/// <param name="msg"> : message to throw</param>
void thunder::_DebugLog(string msg)
{
	_Color(COLOR::GREEN);
	char buffer[100];
	sprintf_s(buffer, msg.c_str());
	OutputDebugStringA(buffer);
}

/// <summary>
/// Print Text to the console.This Function will leave a lineSpace after
/// </summary>
/// <param name="msg"> :the message to be print</param>
void thunder::_Log(string msg)
{
	cout << msg << endl;
}

/// <summary>
/// Print Text to the console with a Color
/// </summary>
/// <param name="msg"> : message to be print</param>
/// <param name="color"> : The color of the text</param>
void thunder::_Log(string msg, COLOR color)
{
	_Color(color);
	cout << msg << endl;
	_Color(COLOR::DEFAULT);
}

void thunder::_AddText(string text)
{
	cout << text;
}

/// <summary>
/// Print an int number to the console
/// </summary>
/// <param name="msg"> : Int number to be print</param>
void thunder::_Log(int msg)
{
	cout << msg << endl;
}

/// <summary>
/// Print an int Number to the console with Color
/// </summary>
/// <param name="msg"> :message to be print</param>
/// <param name="color"> :Color of the text</param>
void thunder::_Log(int msg, COLOR color)
{
	_Color(color);
	cout << msg << endl;
	_Color(COLOR::DEFAULT);
}

/// <summary>
/// Wait for user Input to continue
/// </summary>
void thunder::_Wait()
{
	system("pause");
}

/// <summary>
/// Set a Variable 
/// </summary>
/// <param name="name"> :Variable name</param>
/// <param name="value"> : Variable value</param>
void thunder::_set(string name, string value)
{
	vars.insert({ name , value });
}

/// <summary>
/// Delete a Variable
/// </summary>
/// <param name="name"> :Variable name to delete</param>
void thunder::_del(string name)
{
	auto it = vars.find(name);

	if (it != vars.end())
	{
		vars.erase(it);
	}

}

/// <summary>
/// Get a Variable value 
/// </summary>
/// <param name="name"> :The name of the variable to Get</param>
/// <returns></returns>
string thunder::_get(string name)
{
	auto it = vars.find(name);

	if (it != vars.end())
	{
		return it->second;
	}
	else
	{
		_Log("## Variable " + name + " is not set##");
		return "";
	}
}

/// <summary>
/// Get a variable Converted to Int ("Use this only if you know that the value is and Int type)
/// </summary>
/// <param name="name"> :Variable name to be returned</param>
/// <returns></returns>
int thunder::_getI(string name)
{
	string i = vars[name];

	return stoi(i);
}

/// <summary>
/// Resize the console window Size
/// </summary>
/// <param name="width"> :Width of the window</param>
/// <param name="height"> :Height of the window</param>
void thunder::_Size(unsigned int width, unsigned int height)
{
	RECT rect = { NULL };
	GetWindowRect(GetConsoleWindow(), &rect);

	MoveWindow(con, rect.left, rect.top, width, height, TRUE);
}

/// <summary>
/// Change COnsole cursor position
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void thunder::_GotoPos(short x, short y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(hconsole, pos);
}

void thunder::_SetPixeSize(int size)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.dwFontSize.X = size;
	cfi.dwFontSize.Y = size;
	SetCurrentConsoleFontEx(hconsole, FALSE, &cfi);
}

void thunder::_HideCursor(bool flag)
{
	CONSOLE_CURSOR_INFO info;

	GetConsoleCursorInfo(hconsole, &info);
	info.bVisible = flag;
	SetConsoleCursorInfo(hconsole, &info);
}


void thunder::_CreateFile(string name)
{
	if (name.length() > 0)
	{
		ofstream outputfile(name);

		outputfile.close();
	}
	else
	{
		_DebugLog("CREATING FILE : No name!");
	}

}

bool thunder::_IsFileExist(string name)
{
		ifstream inputfile(name);

		if (inputfile.fail())
		{
			return false;
		}
		else
		{
			return true;
		}




}


vector<string> thunder::_ReadFile(string name)
{
	vector<string> lines;
	if (!_IsFileExist(name)) { 
		_DebugLog("READ FILE : ERROR OPENING FILE");
		return lines ; }

	ifstream infile(name);
	string data;
	while (!infile.eof())
	{
		getline(infile, data);
		lines.push_back(data);
	}


	return lines;
}


void thunder::_WriteToFile(string name, string data)
{
	if (!_IsFileExist(name)) {
		_DebugLog("WRITE FILE : ERROR OPENING FILE. TRY CREATING THE FILE FIRST");
		return;
	}
	ofstream outputfile(name);

	outputfile.write(data.c_str(), data.size());

	outputfile.close();
}

void thunder::_AppendFile(string name, string data)
{
	if (!_IsFileExist(name)) {
		_DebugLog("WRITE FILE : ERROR OPENING FILE. TRY CREATING THE FILE FIRST");
		return;
	}

	fstream appfile(name , ios_base::app);

	appfile.write(data.c_str(), data.size());

	appfile.close();

}

/// <summary>
/// Change the Background color of the console window
/// </summary>
/// <param name="color"> : Color of type BGColor</param>
void thunder::_BGColor(BG_COLOR color)
{
	switch (color)
	{
	case BG_COLOR::GREEN:
		system("color A2");
		break;
	case BG_COLOR::CORAL_RED:
		system("color C2");
		break;
	case BG_COLOR::BLUE:
		system("color ");
		break;
	case BG_COLOR::FUCSIA:
		system("color D2");
		break;
	case BG_COLOR::BEIGE:
		system("color E2");
		break;
	case BG_COLOR::WHITE:
		system("color 7F");
		break;
	case BG_COLOR::GRAY:
		system("color 81");
		break;
	case BG_COLOR::PURPLE:
		system("color D5");
		break;
	case BG_COLOR::AQUA:
		system("color 3B");
		break;
	case BG_COLOR::ORANGE:
		system("color 6C");
		break;
	}

}

/// <summary>
/// Change the title of the console window
/// </summary>
/// <param name="title"> : Title of the window </param>
void thunder::_Title(string title)
{
	SetConsoleTitleA(title.c_str());
}

/// <summary>
/// Clear the console
/// </summary>
void thunder::_Clear()
{
	COORD startPos = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(hconsole, &screen);
	FillConsoleOutputCharacterA(hconsole, ' ', screen.dwSize.X * screen.dwSize.Y, startPos, &written);
	SetConsoleCursorPosition(hconsole, mousePOS);
}

/// <summary>
/// Initialize the Thunder Extension
/// </summary>
void thunder::_Init()
{
	DWORD fdwMode = ENABLE_EXTENDED_FLAGS;
	SetConsoleMode(handleIn, fdwMode);

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(handleIn, fdwMode);


}

/// <summary>
/// Show a message Box
/// </summary>
/// <param name="msg"></param>
/// <param name="caption"></param>
/// <returns></returns>
MSG_BOX_RETURN thunder::_MsgBox(string msg, string caption)
{
	return static_cast<MSG_BOX_RETURN>(MessageBoxA(con, msg.c_str(), caption.c_str(), 1));

}

/// <summary>
/// Get the mouse Input
/// </summary>
/// <returns> Return a mouseInput Left or Right</returns>
_MOUSE_INPUT thunder::_GetMouse()
{
	//Get the number of Events so the function is not wait for input(BLOCK)
	DWORD numEvents = 0;
	GetNumberOfConsoleInputEvents(handleIn, &numEvents);


	if (numEvents > 0)	//If we have an event then get it
	{
		ReadConsoleInput(handleIn,
			&rec,
			1,
			&numRead);
	}
	Sleep(50);
	////If its not a keyboard Event dont continue
	if (rec.EventType == KEY_EVENT) { return _MOUSE_INPUT::NONE; }

	////Store the mouse position
	mousePOS = rec.Event.MouseEvent.dwMousePosition;

	switch (rec.EventType)	//Check if the event is Mouse event
	{
	case MOUSE_EVENT:

		switch (rec.Event.MouseEvent.dwButtonState)	//Check what button is pressed
		{
		case FROM_LEFT_1ST_BUTTON_PRESSED:
			return _MOUSE_INPUT::L_CLICK;
			break;
		case RIGHTMOST_BUTTON_PRESSED:
			return _MOUSE_INPUT::R_CLICK;
			break;
		}
		return _MOUSE_INPUT::NONE;
	}
	return _MOUSE_INPUT::NONE;
}

/// <summary>
/// Get the key pressed By keyboard and return the string 
/// Because I return the string this is not be able to return keys such as
/// Left shift or Alt or Enter.but later I will fix that as well
/// </summary>
/// <returns></returns>
char thunder::_GetKey()
{
	DWORD numEvents = 0;
	GetNumberOfConsoleInputEvents(handleIn, &numEvents);

	if (numEvents > 0)	//If we have an event then get it
	{
		ReadConsoleInput(handleIn,
			&rec,
			numEvents,
			&numRead);
	}
	Sleep(50);
	//If its not a keyboard Event dont continue
	if (rec.EventType == MOUSE_EVENT) { return NULL; }

	switch (rec.EventType)
	{
	case KEY_EVENT:
		//COnvert char to string
		if (rec.Event.KeyEvent.bKeyDown)
		{
			char key = rec.Event.KeyEvent.uChar.AsciiChar;
			return key;
		}
	}
	return NULL;
}

COORD thunder::_GetMousePos()
{
	return mousePOS;
}