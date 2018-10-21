//---------------------------------------------------------------------------

#ifndef FormTurnH
#define FormTurnH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn1;
	TGroupBox *GroupBox1;
	TEdit *Edit1;
	TGroupBox *GroupBox2;
	TEdit *Edit2;
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall Edit2Change(TObject *Sender);

private:	// User declarations

	int sectors;
    int angle;

public:		// User declarations
	__fastcall TForm3(TComponent* Owner);

    int getSectors() const;
    int getAngle() const;
    
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
