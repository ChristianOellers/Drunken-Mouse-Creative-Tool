#include <vcl\vcl.h>
#include <mmsystem32.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <sys/stat.h>
#include <iostream.h>
#include <windows.h>
#include <direct.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <fcntl.h>
#include <ddraw.h>
#include <dir32.h>
#include <io32.h>
#include <time.h>
#include <bios.h>
#include <math.h>
#include <dos.h>
#pragma hdrstop


//----------------------------------------------------------------------------------------------------------------------

USEFORM("BWPT.cpp", MF);
USERES("PrototypX.res");
USEFORM("Debugger.cpp", DEBUG);


//----------------------------------------------------------------------------------------------------------------------

WINAPI WinMain (HINSTANCE, HINSTANCE, LPSTR, int) {
  randomize();
  tzset();

  try {
    Application->Initialize();

    Application->Title = "Drunken Mouse";

    Application->CreateForm(__classid(TMF), &MF);
    Application->CreateForm(__classid(TDEBUG), &DEBUG);
    Application->Run();
  }
  catch(Exception &exception) {
    Application->ShowException(&exception);
  }

  return 0;
}

