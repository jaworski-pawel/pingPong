//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x = -4;
int y = -2;

int pickups = 0;
int player1Points = 0;
int player2Points = 0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerBallTimer(TObject *Sender)
{
    ball->Left += x;
    ball->Top += y;
    //upper reflection
    if (ball->Top <= background->Top)
    {
        y = -y;
    }
    //bottom reflection
    if (ball->Top + ball->Height >= background->Height)
    {
        y = -y;
    }
    //loss
    if (ball->Left <= background->Left)
    {
        sndPlaySound("snd/applause.wav",SND_ASYNC);
        TimerBall->Enabled = false;
        ball->Visible = false;
        player2Points ++;
        info->Caption = " Punkt dla gracza 2 -> \n Iloœæ odbiæ: " + IntToStr(pickups) +
                        "\nWynik: " + IntToStr(player1Points) + ":" + IntToStr(player2Points);
        info->Left = background->Width/2 - info->Width/2;
        info->Visible = true;
        nextRound->Left = background->Width/2 - nextRound->Width/2;
        nextRound->Visible = true;
        newGame->Left = background->Width/2 - newGame->Width/2;
        newGame->Visible = true;
        Form1->BorderStyle = bsSizeable;
    }
    //pickup
    else if (ball->Top > paddle1->Top - ball->Height/2 &&
            ball->Top < paddle1->Top + paddle1->Height - ball->Height/2 &&
            ball->Left < paddle1->Left + paddle1->Width)
    {
        if (x < 0)
        {
            sndPlaySound("snd/player1sound.wav",SND_ASYNC);
            x = -x;
            pickups++;
            if (pickups%5 == 0)
            {
                x++;
                if (y < 0)
                {
                    y--;
                }
                else
                {
                    y++;
                }
            }
        }
        //acceleration
        if (ball->Top > paddle1->Top + paddle1->Height/3 - ball->Height/2 &&
            ball->Top < paddle1->Top + 2*paddle1->Height/3 - ball->Height/2)
        {
            x += 2;
        }
    }
    //loss
    if (ball->Left + ball->Width >= background->Width)
    {
        sndPlaySound("snd/applause.wav",SND_ASYNC);
        TimerBall->Enabled = false;
        ball->Visible = false;
        player1Points++;
        info->Caption = "<- Punkt dla gracza 1 \n Iloœæ odbiæ: " + IntToStr(pickups) +
                        "\nWynik: " + IntToStr(player1Points) + ":" + IntToStr(player2Points);
        info->Left = background->Width/2 - info->Width/2;
        info->Visible = true;
        nextRound->Left = background->Width/2 - nextRound->Width/2;
        nextRound->Visible = true;
        newGame->Left = background->Width/2 - newGame->Width/2;
        newGame->Visible = true;
        Form1->BorderStyle = bsSizeable;
    }
    //pickup
    else if (ball->Top > paddle2->Top - ball->Height/2 &&
            ball->Top < paddle2->Top + paddle2->Height - ball->Height/2 &&
            ball->Left + ball->Width > paddle2->Left)
    {
        if (x > 0)
        {
            sndPlaySound("snd/player2sound.wav",SND_ASYNC);
            x = -x;
            pickups++;
            if (pickups%5 == 0)
            {
                x--;
                if (y < 0)
                {
                    y--;
                }
                else
                {
                    y++;
                }
            }
        }
        //acceleration
        if (ball->Top > paddle2->Top + paddle2->Height/3 - ball->Height/2 &&
            ball->Top < paddle2->Top + 2*paddle2->Height/3 - ball->Height/2)
        {
            x -= 2;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerPaddle1UpTimer(TObject *Sender)
{
    if (paddle1->Top > 10)
    {
        paddle1->Top -= 10;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerPaddle1DownTimer(TObject *Sender)
{
    if (paddle1->Top + paddle1->Height < background->Height - 10)
    {
        paddle1->Top += 10;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if ((Key == 'a') || (Key == 'A'))
    {
        TimerPaddle1Up->Enabled = true;
    }

    if ((Key == 'z') || (Key == 'Z'))
    {
        TimerPaddle1Down->Enabled = true;
    }

    if (Key == VK_UP)
    {
        TimerPaddle2Up->Enabled = true;
    }

    if (Key == VK_DOWN)
    {
        TimerPaddle2Down->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if ((Key == 'a') || (Key == 'A'))
    {
        TimerPaddle1Up->Enabled = false;
    }

    if ((Key == 'z') || (Key == 'Z'))
    {
        TimerPaddle1Down->Enabled = false;
    }

    if (Key == VK_UP)
    {
        TimerPaddle2Up->Enabled = false;
    }

    if (Key == VK_DOWN)
    {
        TimerPaddle2Down->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerPaddle2UpTimer(TObject *Sender)
{
    if (paddle2->Top > 10)
    {
        paddle2->Top -= 10;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerPaddle2DownTimer(TObject *Sender)
{
    if (paddle2->Top + paddle2->Height < background->Height - 10)
    {
        paddle2->Top += 10;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::nextRoundClick(TObject *Sender)
{
    x = -4;
    y = -2;
    pickups = 0;
    ball->Visible = true;
    info->Visible = false;
    nextRound->Visible = false;
    newGame->Visible = false;
    paddle1->Left = background->Left + 20;
    paddle2->Left = background->Width - 20 - paddle2->Width;
    ball->Left = background->Width/2;
    ball->Top = background->Height/2;
    paddle1->Top = background->Height/2 - paddle1->Height/2;
    paddle2->Top = background->Height/2 - paddle2->Height/2;
    TimerBall->Enabled = true;
    Form1->BorderStyle = bsDialog;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	ShowMessage(" Witaj w grze Ping Pong.\n\n Lewy gracz steruje wciskaj¹c klawisze A oraz Z.\n Prawy gracz steruje wciskaj¹c strza³ki do góry i w dó³.\n Kiedy odbijesz pi³kê na œrodku paletki, wówczas zmienisz jej k¹t odbicia i pi³ka przyœpieszy.\n Im d³u¿ej odbijasz, tym pi³ka szybciej  przemieszcza siê.\n W przerwie miêdzy rundami mo¿esz zmieniæ rozmiar pola gry.\n");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::newGameClick(TObject *Sender)
{
    player1Points = 0;
    player2Points = 0;
    nextRoundClick(Sender);
}
//---------------------------------------------------------------------------

