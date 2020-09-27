#ifndef DebuggerH
#define DebuggerH

#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\Menus.hpp>
#include <vcl\ComCtrls.hpp>


//----------------------------------------------------------------------------------------------------------------------

class TDEBUG : public TForm
{
  __published:
    TGroupBox *GroupBox_VarValue;
    TPanel *VAR_01;
    TPanel *VALUE_01;
    TPanel *VAR_02;
    TPanel *VAR_03;
    TPanel *VAR_04;
    TPanel *VAR_05;
    TPanel *VAR_06;
    TPanel *VAR_07;
    TPanel *VAR_08;
    TPanel *VAR_09;
    TPanel *VAR_10;
    TPanel *VAR_11;
    TPanel *VAR_12;
    TPanel *VAR_13;
    TGroupBox *GroupBox_Console;
    TPanel *VAR_14;
    TPanel *VAR_15;
    TPanel *VAR_16;
    TPanel *VAR_17;
    TPanel *VAR_18;
    TPanel *VAR_19;
    TPanel *VAR_20;
    TSpeedButton *SPDBTN_DECREASE;
    TSpeedButton *SPDBTN_INCREASE;
    TPanel *VALUE_02;
    TPanel *VALUE_03;
    TPanel *VALUE_04;
    TPanel *VALUE_05;
    TPanel *VALUE_06;
    TPanel *VALUE_07;
    TPanel *VALUE_08;
    TPanel *VALUE_09;
    TPanel *VALUE_10;
    TPanel *VALUE_11;
    TPanel *VALUE_12;
    TPanel *VALUE_13;
    TPanel *VALUE_14;
    TPanel *VALUE_15;
    TPanel *VALUE_16;
    TPanel *VALUE_17;
    TPanel *VALUE_18;
    TPanel *VALUE_19;
    TPanel *VALUE_20;
    TEdit *Konsole_Edit;
    TPopupMenu *PopupMenu_Edit;
    TMenuItem *SaveText_Edit;
    TRichEdit *Konsole_History;
    TPopupMenu *PopupMenu_RichEdit;
    TMenuItem *EraseText_REdit;
    TGroupBox *GroupBox_VarHints;
    TPanel *HELP_01;
    TPanel *HELP_02;
    TPanel *HELP_03;
    TPanel *HELP_04;
    TPanel *HELP_05;
    TSpeedButton *SPDBTN_HELP;
    TPanel *HELP_06;
    TPanel *HELP_07;
    TPanel *HELP_08;
    TPanel *HELP_09;
    TPanel *HELP_10;
    TPanel *HELP_11;
    TPanel *HELP_12;
    TPanel *HELP_13;
    TPanel *HELP_14;
    TPanel *HELP_15;
    TPanel *HELP_16;
    TPanel *HELP_17;
    TPanel *HELP_18;
    TPanel *HELP_19;
    TPanel *HELP_20;
    TGroupBox *GroupBox_Unused;
    TRadioButton *RadioButton_MF_StayTop;
    TRadioButton *RadioButton_DebuggerStayTop;
    TRadioButton *RadioButton_AllNormal;
    TBevel *Bevel_01;
    TSpeedButton *SPDBTN_INFOSAVE;
    TPanel *Panel_Statistik_1;
    TPanel *Panel_Statistik_2;
    TPanel *Panel_Statistik_3;
    TTimer *ZEIT;
    TRadioButton *RadioButton_AllTop;
    void __fastcall SPDBTN_DECREASEClick(TObject *Sender);
    void __fastcall SPDBTN_INCREASEClick(TObject *Sender);
    void __fastcall SPDBTN_HELPClick(TObject *Sender);
    void __fastcall Konsole_EditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall EraseText_REditClick(TObject *Sender);
    void __fastcall SaveText_EditClick(TObject *Sender);
    void __fastcall SPDBTN_INFOSAVEClick(TObject *Sender);
    void __fastcall ZEITTimer(TObject *Sender);
    void __fastcall RadioButton_AllNormalClick(TObject *Sender);
    void __fastcall RadioButton_DebuggerStayTopClick(TObject *Sender);
    void __fastcall RadioButton_MF_StayTopClick(TObject *Sender);
    void __fastcall RadioButton_AllTopClick(TObject *Sender);
  private:
  public:
    __fastcall TDEBUG(TComponent* Owner);
};


//----------------------------------------------------------------------------------------------------------------------

extern TDEBUG *DEBUG;


//----------------------------------------------------------------------------------------------------------------------

#endif

