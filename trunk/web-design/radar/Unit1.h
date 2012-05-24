//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TOpenDialog *OpenDialog1;
        TButton *Button6;
        TButton *Button7;
        TTimer *Timer1;
        TButton *Button8;
        TButton *Button9;
        TButton *Button11;
        TButton *Button10;
        TButton *Button12;
        TTimer *Timer2;
        TButton *Button13;
        TButton *Button14;
        TButton *Button15;
        TButton *Button16;
        TButton *Button17;
        TButton *Button18;
        TListView *ListView1;
        TButton *Button19;
        TButton *Button20;
        TButton *Button21;
        TButton *Button22;
        TButton *Button23;
        TButton *Button24;
        TButton *Button25;
        TPanel *Panel1;
        TButton *Button26;
        TButton *Button27;
        TButton *Button28;
        TButton *Button29;
        TButton *Button30;
        TPanel *Panel2;
        TButton *Button31;
        TButton *Button32;
        TButton *Button33;
        TButton *Button34;
        TButton *Button35;
        TButton *Button36;
        TButton *Button37;
        TButton *Button38;
        TButton *Button39;
        TImage *Image1;
        TButton *Button40;
        TButton *Button41;
        TButton *Button42;
        TButton *Button43;
        TButton *Button44;
        TButton *Button45;
        TButton *Button46;
        TButton *Button47;
        TButton *Button48;
        TButton *Button49;
        TButton *Button50;
        TButton *Button51;
        TButton *Button52;
        TButton *Button53;
        TButton *Button54;
        TButton *Button55;
        TButton *Button56;
        TButton *Button57;
        TButton *Button58;
        TButton *Button59;
        TButton *Button60;
        TButton *Button61;
        TButton *Button62;
        TButton *Button63;
        TButton *Button64;
        TButton *Button65;
        TLabel *Label1;
        TEdit *Edit1;
        TButton *Button66;
        TButton *Button67;
        TButton *Button68;
        TButton *Button69;
        TButton *Button70;
        TButton *Button71;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button12Click(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall Button13Click(TObject *Sender);
        void __fastcall Button15Click(TObject *Sender);
        void __fastcall Button16Click(TObject *Sender);
        void __fastcall Button17Click(TObject *Sender);
        void __fastcall Button18Click(TObject *Sender);
        void __fastcall Button19Click(TObject *Sender);
        void __fastcall Button20Click(TObject *Sender);
        void __fastcall Button21Click(TObject *Sender);
        void __fastcall Button22Click(TObject *Sender);
        void __fastcall Button23Click(TObject *Sender);
        void __fastcall Button24Click(TObject *Sender);
        void __fastcall Button25Click(TObject *Sender);
        void __fastcall Button26Click(TObject *Sender);
        void __fastcall Button27Click(TObject *Sender);
        void __fastcall Button28Click(TObject *Sender);
        void __fastcall Button29Click(TObject *Sender);
        void __fastcall Button30Click(TObject *Sender);
        void __fastcall Button31Click(TObject *Sender);
        void __fastcall Button32Click(TObject *Sender);
        void __fastcall Button33Click(TObject *Sender);
        void __fastcall Button34Click(TObject *Sender);
        void __fastcall Button35Click(TObject *Sender);
        void __fastcall Button36Click(TObject *Sender);
        void __fastcall Button37Click(TObject *Sender);
        void __fastcall Button38Click(TObject *Sender);
        void __fastcall Button39Click(TObject *Sender);
        void __fastcall Button40Click(TObject *Sender);
        void __fastcall Button41Click(TObject *Sender);
        void __fastcall Button42Click(TObject *Sender);
        void __fastcall Button43Click(TObject *Sender);
        void __fastcall Button44Click(TObject *Sender);
        void __fastcall Button45Click(TObject *Sender);
        void __fastcall Button46Click(TObject *Sender);
        void __fastcall Button47Click(TObject *Sender);
        void __fastcall Button48Click(TObject *Sender);
        void __fastcall Button49Click(TObject *Sender);
        void __fastcall Button50Click(TObject *Sender);
        void __fastcall Button51Click(TObject *Sender);
        void __fastcall Button52Click(TObject *Sender);
        void __fastcall Button53Click(TObject *Sender);
        void __fastcall Button54Click(TObject *Sender);
        void __fastcall Button55Click(TObject *Sender);
        void __fastcall Button56Click(TObject *Sender);
        void __fastcall Button57Click(TObject *Sender);
        void __fastcall Button58Click(TObject *Sender);
        void __fastcall Button59Click(TObject *Sender);
        void __fastcall Button60Click(TObject *Sender);
        void __fastcall Button61Click(TObject *Sender);
        void __fastcall Button62Click(TObject *Sender);
        void __fastcall Button63Click(TObject *Sender);
        void __fastcall Button64Click(TObject *Sender);
        void __fastcall Button65Click(TObject *Sender);
        void __fastcall Button66Click(TObject *Sender);
        void __fastcall Button67Click(TObject *Sender);
        void __fastcall Button68Click(TObject *Sender);
        void __fastcall Button69Click(TObject *Sender);
        void __fastcall Button70Click(TObject *Sender);
        void __fastcall Button71Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
