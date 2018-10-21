//---------------------------------------------------------------------------

#ifndef FormOptionsH
#define FormOptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TCSpinEdit *seLights;
	TCSpinEdit *seSectors;
	TLabel *Label1;
	TLabel *Label2;
	TGroupBox *GroupBox2;
	TLabel *Label3;
	TCSpinEdit *seHole;
	TLabel *Label4;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TGroupBox *GroupBox3;
	TCheckBox *cbEditEnable;
	TGroupBox *GroupBox4;
	TShape *shColor;
	TColorDialog *ColorDialog1;
	void __fastcall shColorMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
