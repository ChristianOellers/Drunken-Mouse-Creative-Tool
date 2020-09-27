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

#include "BWPT.h"
#include "Debugger.h"

#include "Code.cpp"

#pragma resource "*.dfm"


//----------------------------------------------------------------------------------------------------------------------

TMF *MF;


//----------------------------------------------------------------------------------------------------------------------

__fastcall TMF::TMF (TComponent* Owner) : TForm (Owner) {
  randomize();
  tzset();

  Application->HintPause = 0;
  Application->HintColor = RGB(255, 245, 175);

  Blur = 1;
  Panel->Caption = "Active Settings: " + String(ScrollBar_Interval->Position) +" / "+ String(ScrollBar_Blur->Position) +" / "+ String(ScrollBar_Rnd->Position);
}


//----------------------------------------------------------------------------------------------------------------------

void __fastcall TMF::DEBUG_POPUPTimer (TObject *Sender) {
  MF->Show();

  DEBUG_POPUP->Enabled = false;
}


//----------------------------------------------------------------------------------------------------------------------

void __fastcall TMF::Button_AboutClick (TObject *Sender) {
  Application->MessageBox("Copyright: \nChristian Oellers \n\nVersion: 1.6 \nLast Update: Sun, Aug. 06-2006 \n\nBeta-Testing: Danny G.", "About ...", 0+64);
}


//----------------------------------------------------------------------------------------------------------------------

void __fastcall TMF::BitButton_StartClick (TObject *Sender) {
  MessageBeep(1);

  if (CHAOS->Enabled == true) {
    CHAOS->Enabled = false;
    BitButton_Start->Caption = "<<  Start Timer  >>";
    goto End;
  }

  if (CHAOS->Enabled == false) {
    CHAOS->Enabled = true;
    BitButton_Start->Caption = "<<  Stop Timer  >>";
  }

  End:;
}


//----------------------------------------------------------------------------------------------------------------------

void __fastcall TMF::BitButton_RNDClick (TObject *Sender) {
  if (RND == false) {
    RND = true;
    BitButton_RND->Caption = "Normalize !";
    goto End;
  }

  if (RND == true) {
    RND = false;
    BitButton_RND->Caption = "Randomize !";
  }

  End:;
}


//----------------------------------------------------------------------------------------------------------------------

void __fastcall TMF::CHAOSTimer (TObject *Sender) {
  CHAOS->Interval = ScrollBar_Interval->Position;

  if (RND == false) {
    Blur = ScrollBar_Blur->Position;
  }

  if (RND == true) {
    for (int i = 0; i < 10; i++) {
      RNDZufall = random(ScrollBar_Rnd->Position);
    }

    Blur = ScrollBar_Blur->Position + RNDZufall;
  }


  GetCursorPos(&Mouse);

  for (int i = 0; i < 8; i++) {
    Zufall = rand() % 8;
  }

  switch(Zufall) {
    case 1: //++
      Mouse.x -= Blur;
      Mouse.y -= Blur;
    break;
    case 2: //--
      Mouse.x += Blur;
      Mouse.y += Blur;
    break;
    case 3: //+-
      Mouse.x += Blur;
      Mouse.y -= Blur;
    break;
       case 4: //-+
      Mouse.x -= Blur;
      Mouse.y += Blur;
    break;
       case 5: //-x
      Mouse.x -= Blur;
    break;
       case 6: //-y
      Mouse.y -= Blur;
    break;
       case 7: //+x
      Mouse.x += Blur;
    break;
       case 8: //+y
      Mouse.y += Blur;
    break;
    default:
    break;
  }

  SetCursorPos(Mouse.x,Mouse.y);
}


//----------------------------------------------------------------------------------------------------------------------

void __fastcall TMF::ScrollBar_IntervalChange (TObject *Sender) {
  ScrollBar_Interval->Hint = String(ScrollBar_Interval->Position);

  Panel->Caption = "Active Settings: " + String(ScrollBar_Interval->Position) +" / "+ String(ScrollBar_Blur->Position) +" / "+ String(ScrollBar_Rnd->Position);
}


void __fastcall TMF::ScrollBar_BlurChange (TObject *Sender) {
  ScrollBar_Blur->Hint = String(ScrollBar_Blur->Position);

  Panel->Caption = "Active Settings: " + String(ScrollBar_Interval->Position) +" / "+ String(ScrollBar_Blur->Position) +" / "+ String(ScrollBar_Rnd->Position);
}


void __fastcall TMF::ScrollBar_RndChange (TObject *Sender) {
  ScrollBar_Rnd->Hint = String(ScrollBar_Rnd->Position);

  Panel->Caption = "Active Settings: " + String(ScrollBar_Interval->Position) +" / "+ String(ScrollBar_Blur->Position) +" / "+ String(ScrollBar_Rnd->Position);
}


//----------------------------------------------------------------------------------------------------------------------

void __fastcall TMF::ScrollBar_IntervalKeyDown (TObject *Sender, WORD &Key, TShiftState Shift) {
  if (Key == VK_UP) {
    ScrollBar_Interval->Position = 5000;
    Key = VK_RIGHT;
  }

  if (Key == VK_DOWN) {
    ScrollBar_Interval->Position = 1;
    Key = VK_LEFT;
  }

  ScrollBar_Interval->Hint = String(ScrollBar_Interval->Position);

  Panel->Caption = "Active Settings: " + String(ScrollBar_Interval->Position) +" / "+ String(ScrollBar_Blur->Position) +" / "+ String(ScrollBar_Rnd->Position);
}


void __fastcall TMF::ScrollBar_BlurKeyDown (TObject *Sender, WORD &Key, TShiftState Shift) {
  if (Key == VK_UP) {
    ScrollBar_Blur->Position = 100;
    Key = VK_RIGHT;
  }

  if (Key == VK_DOWN) {
    ScrollBar_Blur->Position = 1;
    Key = VK_LEFT;
  }

  ScrollBar_Blur->Hint = String(ScrollBar_Blur->Position);

  Panel->Caption = "Active Settings: " + String(ScrollBar_Interval->Position) +" / "+ String(ScrollBar_Blur->Position) +" / "+ String(ScrollBar_Rnd->Position);
}


void __fastcall TMF::ScrollBar_RndKeyDown (TObject *Sender, WORD &Key, TShiftState Shift) {
  if (Key == VK_UP) {
    ScrollBar_Rnd->Position = 100;
    Key = VK_RIGHT;
  }

  if (Key == VK_DOWN) {
    ScrollBar_Rnd->Position = 1;
    Key = VK_LEFT;
  }

  ScrollBar_Rnd->Hint = String(ScrollBar_Rnd->Position);

  Panel->Caption = "Active Settings: " + String(ScrollBar_Interval->Position) +" / "+ String(ScrollBar_Blur->Position) +" / "+ String(ScrollBar_Rnd->Position);
}

