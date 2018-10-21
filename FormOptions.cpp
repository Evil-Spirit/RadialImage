//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormOptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::shColorMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ColorDialog1->Color = shColor->Brush->Color;
	if (ColorDialog1->Execute()) {
		shColor->Brush->Color = ColorDialog1->Color;
	}
}
//---------------------------------------------------------------------------

