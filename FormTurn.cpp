//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------

#include "FormTurn.h"
#include "FormMain.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

bool change = true;

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
	sectors = 0;
    angle = 0;
}

//---------------------------------------------------------------------------

int TForm3::getSectors() const {
	return sectors;
}

//---------------------------------------------------------------------------

int TForm3::getAngle() const {
	return angle;
}

//---------------------------------------------------------------------------

void __fastcall TForm3::Edit1Change(TObject *Sender)
{
	if (change == false) return;
	sectors = atoi(Edit1->Text.c_str());

    sectors = sectors % Form1->radial.getCount();
    
    float angle_per_sector = 360.0f / float(Form1->radial.getCount());
    angle = ceil(sectors * angle_per_sector);

    //Edit1->Text = IntToStr(sectors);
    change = false;
    Edit2->Text = IntToStr(angle);
    change = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edit2Change(TObject *Sender)
{
	if (change == false) return;
	angle = atoi(Edit2->Text.c_str());

    angle = angle % 360;
    
    float sectors_per_angle = float(Form1->radial.getCount()) / 360.0f;
    sectors = floor(angle * sectors_per_angle);

    change = false;
    Edit1->Text = IntToStr(sectors);
    change = true;
    //Edit2->Text = IntToStr(angle);
}
//---------------------------------------------------------------------------

