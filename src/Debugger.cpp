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

#include "Code.cpp"

#include "BWPT.h"
#include "Debugger.h"

#pragma resource "*.dfm"


//----------------------------------------------------------------------------------------------------------------------

TDEBUG *DEBUG;

char Datum[128], Uhrzeit[128];

TStringList *DebugList;
TStringList *KonsoleList;
FILE *KillDebugList;
FILE *KillKonsoleList;

int SavedTXT, CNSCommands;
int Sec, Min, Hr;



//----------------------------------------------------------------------------------------------------------------------

__fastcall TDEBUG::TDEBUG (TComponent* Owner): TForm (Owner) {
  randomize();
  tzset();

  DebugList   = new TStringList();
  KonsoleList = new TStringList();

  Application->HintPause = 0;
  Application->HintColor = clYellow;
}



//----------------------------------------------------------------------------------------------------------------------

void __fastcall TDEBUG::SPDBTN_HELPClick (TObject *Sender) {
  Application->MessageBox("(c) 1998-2006 Christian Oellers \n\nCode-Zeilen: 144189 \nProgramm-Version: 1.0","Debugger - Informationen",0+64);
}


//----------------------------------------------------------------------------------------------------------------------

void __fastcall TDEBUG::SPDBTN_DECREASEClick (TObject *Sender) {
  ClientHeight = 500;
  ClientWidth  = 500;

  GroupBox_Console->Height = 121;
  Konsole_History->Height  = 58;
  Konsole_Edit->Top        = 83;

  MessageBeep(MB_OK);
}


void __fastcall TDEBUG::SPDBTN_INCREASEClick (TObject *Sender) {
  ClientHeight = 600;
  ClientWidth  = 800;

  GroupBox_Console->Height = 221;
  Konsole_History->Height  = 155;
  Konsole_Edit->Top        = 180;

  MessageBeep(MB_OK);
}



//----------------------------------------------------------------------------------------------------------------------

void __fastcall TDEBUG::SPDBTN_INFOSAVEClick (TObject *Sender) {
  KillKonsoleList = fopen("Konsole.txt", "w");

  for (int i = 0; i < 100; i++) {
    fprintf(KillKonsoleList,"\n");
  }

  fclose(KillKonsoleList);


  KonsoleList->LoadFromFile("Konsole.txt");
  KonsoleList->Text = Konsole_History->Text;
  KonsoleList->SaveToFile("Konsole.txt");


  // Save variable table

  KillDebugList = fopen("Debugger.txt", "w");

  for (int i = 0; i < 100; i++) {
    fprintf(KillDebugList, "\n");
  }

  fclose(KillDebugList);


  DebugList->LoadFromFile("Debugger.txt");

  DebugList->Strings[0]  =  "#------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#";
  DebugList->Strings[1]  =  "# VARIABLENBELEGUNGSTABELLE ";
  DebugList->Strings[2]  =  "";
  DebugList->Strings[3]  =  "";
  DebugList->Strings[4]  =  "Name      |    Wert      |    Kurzinfo";
  DebugList->Strings[5]  =  "";
  DebugList->Strings[6]  =  String(VAR_01->Caption)+"    |    "+String(VALUE_01->Caption)+"    |    "+String(HELP_01->Caption);
  DebugList->Strings[7]  =  String(VAR_02->Caption)+"    |    "+String(VALUE_02->Caption)+"    |    "+String(HELP_02->Caption);
  DebugList->Strings[8]  =  String(VAR_03->Caption)+"    |    "+String(VALUE_03->Caption)+"    |    "+String(HELP_03->Caption);
  DebugList->Strings[9]  =  String(VAR_04->Caption)+"    |    "+String(VALUE_04->Caption)+"    |    "+String(HELP_04->Caption);
  DebugList->Strings[10] =  String(VAR_05->Caption)+"    |    "+String(VALUE_05->Caption)+"    |    "+String(HELP_05->Caption);
  DebugList->Strings[11] =  String(VAR_06->Caption)+"    |    "+String(VALUE_06->Caption)+"    |    "+String(HELP_06->Caption);
  DebugList->Strings[12] =  String(VAR_07->Caption)+"    |    "+String(VALUE_07->Caption)+"    |    "+String(HELP_07->Caption);
  DebugList->Strings[13] =  String(VAR_08->Caption)+"    |    "+String(VALUE_08->Caption)+"    |    "+String(HELP_08->Caption);
  DebugList->Strings[14] =  String(VAR_09->Caption)+"    |    "+String(VALUE_09->Caption)+"    |    "+String(HELP_09->Caption);
  DebugList->Strings[15] =  String(VAR_10->Caption)+"    |    "+String(VALUE_10->Caption)+"    |    "+String(HELP_10->Caption);
  DebugList->Strings[16] =  String(VAR_11->Caption)+"    |    "+String(VALUE_11->Caption)+"    |    "+String(HELP_11->Caption);
  DebugList->Strings[17] =  String(VAR_12->Caption)+"    |    "+String(VALUE_12->Caption)+"    |    "+String(HELP_12->Caption);
  DebugList->Strings[18] =  String(VAR_13->Caption)+"    |    "+String(VALUE_13->Caption)+"    |    "+String(HELP_13->Caption);
  DebugList->Strings[19] =  String(VAR_14->Caption)+"    |    "+String(VALUE_14->Caption)+"    |    "+String(HELP_14->Caption);
  DebugList->Strings[20] =  String(VAR_15->Caption)+"    |    "+String(VALUE_15->Caption)+"    |    "+String(HELP_15->Caption);
  DebugList->Strings[21] =  String(VAR_16->Caption)+"    |    "+String(VALUE_16->Caption)+"    |    "+String(HELP_16->Caption);
  DebugList->Strings[22] =  String(VAR_17->Caption)+"    |    "+String(VALUE_17->Caption)+"    |    "+String(HELP_17->Caption);
  DebugList->Strings[23] =  String(VAR_18->Caption)+"    |    "+String(VALUE_18->Caption)+"    |    "+String(HELP_18->Caption);
  DebugList->Strings[24] =  String(VAR_19->Caption)+"    |    "+String(VALUE_19->Caption)+"    |    "+String(HELP_19->Caption);
  DebugList->Strings[25] =  String(VAR_20->Caption)+"    |    "+String(VALUE_20->Caption)+"    |    "+String(HELP_20->Caption);
  DebugList->Strings[26] =  "";
  DebugList->Strings[27] =  "#------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------#";
  DebugList->Strings[28] =  "";
  DebugList->Strings[29] =  "";
  DebugList->Strings[30] =  "Datum: " + String(_strdate(Datum)) + " | Uhrzeit: " + String(_strtime(Uhrzeit));

  DebugList->SaveToFile("Debugger.txt");


  SavedTXT++;


  Panel_Statistik_1->Caption = "Gespeicherte Debug-Texte insgesamt: " + String(SavedTXT);

  MessageBeep(MB_OK);

  Application->MessageBox("Informationen abgespeichert: \n\n'Debugger.txt' \n'Konsole.txt' \n\nHinweis: \nErneutes Speichern überschreibt \nalle aktuell gespeicherten Daten !", "Debugger - Daten gespeichert", 0+64);
}


//----------------------------------------------------------------------------------------------------------------------

void __fastcall TDEBUG::SaveText_EditClick (TObject *Sender) {
  Konsole_Edit->Text = "";

  MessageBeep(MB_OK);
}


//----------------------------------------------------------------------------------------------------------------------

void __fastcall TDEBUG::EraseText_REditClick (TObject *Sender) {
  Konsole_History->Text = "";

  MessageBeep(MB_OK);
}


//----------------------------------------------------------------------------------------------------------------------

void __fastcall TDEBUG::ZEITTimer (TObject *Sender) {
  Sec++;

  if (Sec == 60) {
    Sec = 0;
    Min++;
  }

  if (Min == 60) {
    Min = 0;
    Hr++;
  }

  if (Hr < 10) {
    if (Min < 10) {
      if (Sec < 10) {
        Panel_Statistik_3->Caption = "Laufzeit des Debuggers: 0" + String(Hr) +":0"+ String(Min) +":0"+ String(Sec);
      }
      else {
        Panel_Statistik_3->Caption = "Laufzeit des Debuggers: 0" + String(Hr) +":0"+ String(Min) +":"+ String(Sec);
      }
    }
    else {
      Panel_Statistik_3->Caption = "Laufzeit des Debuggers: 0" + String(Hr) +":"+ String(Min) +":"+ String(Sec);
    }
  }
  else {
    Panel_Statistik_3->Caption = "Laufzeit des Debuggers: " + String(Hr) +":"+ String(Min) +":"+ String(Sec);
  }
}


//----------------------------------------------------------------------------------------------------------------------

void __fastcall TDEBUG::RadioButton_AllNormalClick (TObject *Sender) {
  DEBUG->FormStyle = fsNormal;
  MF->FormStyle    = fsNormal;
}


void __fastcall TDEBUG::RadioButton_AllTopClick (TObject *Sender) {
  DEBUG->FormStyle = fsStayOnTop;
  MF->FormStyle    = fsStayOnTop;
}


void __fastcall TDEBUG::RadioButton_DebuggerStayTopClick (TObject *Sender) {
  DEBUG->FormStyle = fsStayOnTop;
  MF->FormStyle    = fsNormal;
}


void __fastcall TDEBUG::RadioButton_MF_StayTopClick (TObject *Sender) {
  DEBUG->FormStyle = fsNormal;
  MF->FormStyle    = fsStayOnTop;
}


//----------------------------------------------------------------------------------------------------------------------

void __fastcall TDEBUG::Konsole_EditKeyDown (TObject *Sender, WORD &Key, TShiftState Shift) {
  if (Key == VK_RETURN) {
    Konsole_History->Lines->Add("> " + Konsole_Edit->Text);

    if (Konsole_Edit->Text == "_clr") {
      Konsole_History->Text = "";
    }

    if (Konsole_Edit->Text == "debugger_exit()") {
      Application->Terminate();
    }

    if (Konsole_Edit->Text != "debugger_exit()" && Konsole_Edit->Text != "_clr") {
      Konsole_History->Lines->Add("? Unbekannter Begriff.");
    }

    CNSCommands++;

    Panel_Statistik_2->Caption = "Eingegebene Konsolenbefehle insgesamt: " + String(CNSCommands);
    Konsole_Edit->Text = "";

    MessageBeep(MB_OK);
  }


  if (Key == VK_ESCAPE) {
    Konsole_Edit->Text = "";

    MessageBeep(MB_OK);
  }
}

