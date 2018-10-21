//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------

#include "FormMain.h"
#include <Math.hpp>
#include "FormOptions.h"
#include "FormTurn.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	editEnable = false;
	DoubleBuffered = true;
	radial.setSize(256, 32);
//	editEnable = Form2->cbEditEnable->Checked;
/*	for (int i=0; i<radial.getCount(); i++) {
		radial[i].setBit(i / 8, true);
	}*/
}
//---------------------------------------------------------------------------
/*
void TForm1::draw() {
	Image1->Picture->Bitmap->Width = Image1->Width;
	Image1->Picture->Bitmap->Height = Image1->Height;


	Image1->Canvas->Brush->Color = clBlack;
	Image1->Canvas->FillRect(Image1->Canvas->ClipRect);

	int lights = 32;
	int count = 256;

	int cx = Image1->Canvas->ClipRect.Width();
	int cy = Image1->Canvas->ClipRect.Height();

	float ratX = (float)Image2->Canvas->ClipRect.Width() / (float)Image1->Canvas->ClipRect.Width();
	float ratY = (float)Image2->Canvas->ClipRect.Height() / (float)Image1->Canvas->ClipRect.Height();

	Image1->Canvas->Brush->Color = clBlack;
	Image1->Canvas->Pen->Color = clBlue;
	Image1->Canvas->Ellipse(0, 0, cx, cy);

	for (int j=0; j<lights; j++) {
		float radX = (float)cx / 2 / (float)lights;
		float radY = (float)cy / 2 / (float)lights;
		int sx = 2;
		int sy = 2;

		for (int i=0; i<count; i++) {
			float angle = 2 * M_PI / count * i;
			int x = cos(angle) * cx / 2 / lights * (j+1) + cx / 2;
			int y = sin(angle) * cy / 2 / lights * (j+1) + cy / 2;

			TColor color = clBlack;

			if (Image2->Canvas->Pixels[int(x * ratX)][int(y *ratY)] & 0x00FF0000 > 128) {
				color = clBlue;
			}

			Image1->Canvas->Brush->Color = color;
			Image1->Canvas->Pen->Color = color;
			Image1->Canvas->Ellipse(x-sx, y-sy, x+sx, y+sy);

		}
	}
}
*/
void __fastcall TForm1::FormResize(TObject *Sender)
{
	Image1->Picture->Bitmap->Width = Image1->Width;
	Image1->Picture->Bitmap->Height = Image1->Height;
	radial.draw(Image1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N2Click(TObject *Sender)
{
	if (OpenDialog1->Execute()) {
		if (ExtractFileExt(OpenDialog1->FileName).LowerCase() == ".bmp") {
			Image2->Picture->LoadFromFile(OpenDialog1->FileName);
			radial.convert(Image2);
		} else
		if (ExtractFileExt(OpenDialog1->FileName).LowerCase() == ".bsp_old") {
			radial.convertBSP_OLD(OpenDialog1->FileName);
		} else
		if (ExtractFileExt(OpenDialog1->FileName).LowerCase() == ".bsp") {
			radial.convertBSP(OpenDialog1->FileName);
		} else
		if (ExtractFileExt(OpenDialog1->FileName).LowerCase() == ".sbp") {
			radial.loadSBP(OpenDialog1->FileName);
		}

		radial.draw(Image1);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
	if (SaveDialog1->Execute()) {

		if (ExtractFileExt(SaveDialog1->FileName).LowerCase() == ".bsp_old") {
			radial.saveBSP_OLD(SaveDialog1->FileName);
		} else 
		if (ExtractFileExt(SaveDialog1->FileName).LowerCase() == ".sbp") {
			radial.saveSBP(SaveDialog1->FileName);
		} else 
		radial.saveBSP(ChangeFileExt(SaveDialog1->FileName, ".bsp"));
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{
	MessageBox(NULL, "Radial Image Editor.\nCopyright (c) 2008, Alexei Egorov aka FadeToBlack", "About", MB_OK);
}
//---------------------------------------------------------------------------


void TForm1::draw(int X, int Y, bool state) {
	if (!editEnable) return;
	float cx = Image1->Canvas->ClipRect.Width() / 2;
	float cy = Image1->Canvas->ClipRect.Height() / 2;
	float angle = ArcTan2(Y - cy, X - cx) + M_PI * 2.5;
	if (angle > 2 * M_PI) angle = angle - 2 * M_PI;
	int index = angle / (2 * M_PI) * radial.getCount();
	float radius = cx;
	if (cy < radius) radius = cy;
	float ratio = float(radial.getHole()) / 100.0f;
	float point = sqrt((X - cx) * (X - cx) + (Y - cy) * (Y - cy));
	int light = ((point - radius * ratio) / radius / (1 - ratio) * radial.getLights());
	if (light < radial.getLights() && light >= 0) {
		radial[index].setBit(light, state);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseDown(TObject *Sender,
	  TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft) {
		draw(X, Y, true);
		radial.draw(Image1);
	}
	if (Button == mbRight) {
		draw(X, Y, false);
		radial.draw(Image1);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift,
	  int X, int Y)
{
	if (Shift.Contains(ssLeft)) {
		draw(X, Y, true);
		radial.draw(Image1);
	}
	if (Shift.Contains(ssRight)) {
		draw(X, Y, false);
		radial.draw(Image1);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Clear1Click(TObject *Sender)
{
	for (int i=0; i<radial.getCount(); i++) {
		for (int j=0; j<radial.getLights(); j++) {
			radial[i].setBit(j, false);
		}
	}
	radial.draw(Image1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Options1Click(TObject *Sender)
{

	Form2->seSectors->Value = radial.getCount();
	Form2->seLights->Value = radial.getLights();
	Form2->seHole->Value = radial.getHole();
	Form2->cbEditEnable->Checked = editEnable;
	Form2->shColor->Brush->Color = radial.getColor();

	if (Form2->ShowModal() == mrOk) {
		editEnable = Form2->cbEditEnable->Checked;
		radial.setColor(Form2->shColor->Brush->Color);

		if (Form2->seSectors->Value != radial.getCount() || Form2->seLights->Value != radial.getLights()) {
			radial.setSize(Form2->seSectors->Value, Form2->seLights->Value);
			radial.convert(Image2);
		}

		if (Form2->seHole->Value != radial.getHole()) {
			radial.setHole(Form2->seHole->Value);
			radial.convert(Image2);
		}
		radial.draw(Image1);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Negative1Click(TObject *Sender)
{
	radial.negate();
	radial.draw(Image1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Turn1Click(TObject *Sender)
{
	if (Form3->ShowModal() == mrOk) {
    	radial.turn(Form3->getSectors());
		radial.draw(Image1);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if (Key == 37) {
    	radial.turn(-1);
		radial.draw(Image1);
    } else
	if (Key == 39) {
    	radial.turn(1);
		radial.draw(Image1);
    } else
	if (Key == 38) {
    	if (radial.getHole() < 90) {
	    	radial.setHole(radial.getHole() + 1);
        }
		radial.draw(Image1);
    } else
	if (Key == 40) {
    	if (radial.getHole() > 0) {
	    	radial.setHole(radial.getHole() - 1);
        }
		radial.draw(Image1);
    }
}
//---------------------------------------------------------------------------

