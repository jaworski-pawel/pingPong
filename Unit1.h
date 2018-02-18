//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TShape *background;
    TImage *ball;
    TTimer *TimerBall;
    TImage *paddle1;
    TImage *paddle2;
    TTimer *TimerPaddle1Up;
    TTimer *TimerPaddle1Down;
    TTimer *TimerPaddle2Up;
    TTimer *TimerPaddle2Down;
    TLabel *info;
    TButton *nextRound;
    TButton *newGame;
    void __fastcall TimerBallTimer(TObject *Sender);
    void __fastcall TimerPaddle1UpTimer(TObject *Sender);
    void __fastcall TimerPaddle1DownTimer(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall TimerPaddle2UpTimer(TObject *Sender);
    void __fastcall TimerPaddle2DownTimer(TObject *Sender);
    void __fastcall nextRoundClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall newGameClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 