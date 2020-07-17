#include<iostream>
#include "thunder.h"
#include <Windows.h>
#include <string>
#include <vector>

#define ENUM_TO_STRING(ENUM) string(#ENUM)

using namespace thunder;

int main()
{
    _Init();
    _Title("Thanos is The king");
    _SetPixeSize(20);
    _Size(600, 600);
    _HideCursor(false);

    string filename = "text.txt";

    _AppendFile(filename, "\nThis is added text");

    vector<string> lines;
    if(_IsFileExist(filename))
    {
        lines = _ReadFile(filename);
        
        for (string line : lines)
        {
            _Log(line);
        }
    }
 

    //Game loop
    while (true)
    {
        //***DRAWING***
    if (_GetMouse() == _MOUSE_INPUT::L_CLICK)
    {
        _Color(COLOR::GREEN);
        _GotoPos(_GetMousePos().X, _GetMousePos().Y);
        _Log("o");
    }
    }


    return 0;
}


//CODE SNIPPETS

        //***Print the mouse position ***
        //Game code here
        //if (_GetMouse() == _MOUSE_INPUT::L_CLICK)
        //{
        //    GotoPos(_GetMousePos().X, _GetMousePos().Y);
        //    _Log("Left Click at Pos " + to_string( _GetMousePos().X) + ":" + to_string( _GetMousePos().Y));
        //}
        //else if (_GetMouse() == _MOUSE_INPUT::R_CLICK)
        //{
        //    GotoPos(_GetMousePos().X, _GetMousePos().Y);
        //    _Log("Right Click at Pos " + to_string(_GetMousePos().X) + ":" + to_string(_GetMousePos().Y));
        //}
        //else if (_GetKey() != "")
        //{
        //    string key = _GetKey();
        //    _Log("You pressed " + key);
        //}

    
        //***DRAWING***
        //if (_GetMouse() == _MOUSE_INPUT::L_CLICK)
        //{
        //    _GotoPos(_GetMousePos().X, _GetMousePos().Y);
        //    _Log("o");
        //}


        //***Keyboard Button handling***
        //Check if ENTER is pressed
        //Ascii code for ENTER is 13

        //if (_GetKey() == 13)
        //{
        //    _Log("yOU PRressed Enter");
        //}