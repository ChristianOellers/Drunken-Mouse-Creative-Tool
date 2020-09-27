#ifndef BWPTH
#define BWPTH

#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Buttons.hpp>


//----------------------------------------------------------------------------------------------------------------------

class TMF : public TForm {
  __published:
    TTimer *DEBUG_POPUP;
    TTimer *CHAOS;
    TScrollBar *ScrollBar_Interval;
    TLabel *Label1;
    TScrollBar *ScrollBar_Blur;
    TLabel *Label2;
    TRichEdit *RichEdit;
    TButton *Button_About;
    TPanel *Panel;
    TLabel *Label3;
    TScrollBar *ScrollBar_Rnd;
    TBitBtn *BitButton_Start;
    TBitBtn *BitButton_RND;
    void __fastcall DEBUG_POPUPTimer(TObject *Sender);
    void __fastcall CHAOSTimer(TObject *Sender);
    void __fastcall Button_AboutClick(TObject *Sender);
    void __fastcall ScrollBar_IntervalChange(TObject *Sender);
    void __fastcall ScrollBar_BlurChange(TObject *Sender);
    void __fastcall ScrollBar_RndChange(TObject *Sender);
    void __fastcall BitButton_StartClick(TObject *Sender);
    void __fastcall BitButton_RNDClick(TObject *Sender);
    void __fastcall ScrollBar_IntervalKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall ScrollBar_BlurKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall ScrollBar_RndKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  private:
  public:
    __fastcall TMF(TComponent* Owner);
};


//----------------------------------------------------------------------------------------------------------------------

extern TMF *MF;


//----------------------------------------------------------------------------------------------------------------------

#endif

