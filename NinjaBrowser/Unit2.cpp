//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	MemoFixMe->Clear();
	MemoFixMe->Lines->Add("This sample program has been implemented ugly.");
	MemoFixMe->Lines->Add("CEF's libcef.dll can not free memory properly");
	MemoFixMe->Lines->Add("Because ChromiumBrowser can not be released within a tab.");
	MemoFixMe->Lines->Add("It is possible outside the tab. For this tab issue,");
	MemoFixMe->Lines->Add("Windows message delivery does not work in C++ Builder.");
	MemoFixMe->Lines->Add("It seems possible in Delphi. C++ Builder has");
	MemoFixMe->Lines->Add("always had this difference with Delphi.");
	MemoFixMe->Lines->Add("The same problem occurred with the simple porting");
	MemoFixMe->Lines->Add("of the CEF4Delphi project's tabbed browser example");
	MemoFixMe->Lines->Add("to C++ Builder.");
	MemoFixMe->Lines->Add("There are also the most serious problems.");
	MemoFixMe->Lines->Add("If you try to scroll randomly in a web browser");
	MemoFixMe->Lines->Add("the program crashes in libcef.dll.");
	MemoFixMe->Lines->Add("I hope someone solves this bug.");
	MemoFixMe->Lines->Add("It seems to be a serious bug.");
	MemoFixMe->Lines->Add("This issue has not been solved for many years");
	MemoFixMe->Lines->Add("in the past since Delphi's CEF project started.");
	MemoFixMe->Lines->Add("You can not use the browser at all.");
	MemoFixMe->Lines->Add("I am very desperate.");
	MemoFixMe->Lines->Add("The original purpose of this NinjaBrowser was");
	MemoFixMe->Lines->Add("to create a web proxy with Javascript Injectable.");
	MemoFixMe->Lines->Add("(just like a Monkey JavaScript Style)");
	MemoFixMe->Lines->Add("This insecure crash problem of CEF seems to be");
	MemoFixMe->Lines->Add("the same in QT.");
	MemoFixMe->Lines->Add("");
	MemoFixMe->Lines->Add(" - This is a complaint by Chicken House Owner in Hell-Chosun. -");
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ButtonCloseClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

