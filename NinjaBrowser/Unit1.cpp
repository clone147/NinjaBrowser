/*
//---------------------------------------------------------------------------
// The NinjaBrowser has been programmed by AmesianX in powerhacker.net.
//---------------------------------------------------------------------------
// The original purpose of this NinjaBrowser was to create a web proxy
// with Javascript Injectable.(Monkey JavaScript Style)

// <NinjaBrowser's Function Keys>
//
// Alt+T(New Tab) and Alt+W(Close Tab), Alt+Q(Close Tab)
// Alt+2(Moving Left Tab), Alt+2(Moving Right Tab)
// Alt+D(Selecting Input URL)
//
//
// <\CEF4Delphi\source\uCEFChromium.pas>
//
// You need to modify this uCEFChromium.pas file.
// If it is already installed, reinstall the component.
//
// function TChromium.doOnBeforePopup(const browser         : ICefBrowser;
// 								   const frame              : ICefFrame;
// 								   const targetUrl          : ustring;
// 								   const targetFrameName    : ustring;
// 										 targetDisposition  : TCefWindowOpenDisposition;
// 										 userGesture        : Boolean;
// 								   var   popupFeatures      : TCefPopupFeatures;
// 								   var   windowInfo         : TCefWindowInfo;
// 								   var   client             : ICefClient;
// 								   var   settings           : TCefBrowserSettings;
// 								   var   noJavascriptAccess : Boolean): Boolean;
// begin
//   Result := True;  // You have to modify this part to "True" From "False".
//                    // You can open a tab in a new window.
//
// if Assigned(FOnBeforePopup) then
//   FOnBeforePopup(Self, browser, frame, targetUrl, targetFrameName,
//				   targetDisposition, userGesture, popupFeatures, windowInfo, client,
//				   settings, noJavascriptAccess, Result);
// end;
*/

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "uCEFChromium"
#pragma link "uCEFChromiumWindow"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
void __fastcall TForm1::AppException(TObject *Sender, Exception *E)
{
	MemoDBG->Lines->Add("Message: "  + E->Message);
	ExitProcess(0);
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Application->OnException = AppException;

	MemoDBG->Clear();

	AddTab("http://google.com");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonCloseQueryClick(TObject *Sender)
{
	if (PageControl1->PageCount == 1 || PageControl1->TabIndex == 0) {
		ExitProcess(0);
	}

	ButtonCloseQuery->Enabled = false;

	TChromiumWindow *window = NULL;

	for (int i = 1; i < PageControl1->PageCount; i++)
	{
		SearchWindow(i, &window);
		if (window != NULL && window->ChromiumBrowser->IsLoading)
		{
			window->ChromiumBrowser->StopLoad();
			StatusBar1->Panels->Items[0]->Text = "Loading stopped / Try again if you want to close tab";
			ButtonCloseQuery->Enabled = true;
			return;
		}
	}

	window = reinterpret_cast<TChromiumWindow *>(PageControl1->ActivePage->Tag);
	window->ChromiumBrowser->SetFocus(false);
	window->Perform(WM_KILLFOCUS, 0, 0);

	int PageIndex = PageControl1->TabIndex;

	if (PageIndex == (PageControl1->PageCount - 1)) {
		if (PageIndex > 0)
			PageIndex--;
	}

	// [Fix Me]

	// This is programming code that does not work properly.
	try {
		window->ChromiumBrowser->Free();
	} catch(const Exception &e) {
		MemoDBG->Lines->Add("Message: " + e.Message);
	}

	// This is programming code that does not work properly.
	try {
		window->Free();
	} catch(const Exception &e) {
		MemoDBG->Lines->Add("Message: " + e.Message);
	}

	// This will cause an access error, but the tab will be removed properly.
	try {
		PageControl1->Pages[PageControl1->TabIndex]->Free();
	} catch(const Exception &e) {
		MemoDBG->Lines->Add("Message: " + e.Message);
	}

	PageControl1->TabIndex = PageIndex;
	PageControl1->Pages[PageControl1->TabIndex]->UpdateControlState();

	window = reinterpret_cast<TChromiumWindow *>(PageControl1->Pages[PageControl1->TabIndex]->Tag);
	EditURL->Text = window->ChromiumBrowser->Browser->MainFrame->Url;
	window->ChromiumBrowser->SetFocus(true);

	StatusBar1->Panels->Items[0]->Text = "";
	ButtonCloseQuery->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	CanClose = false;

	if (ButtonCloseQuery->Enabled)
	    ButtonCloseQueryClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::dumpcode(unsigned char *buff, int len)
{
	AnsiString output, dump;

	int i;

	for (i = 0; i < len; i++)
	{
		if (i % 16 == 0)
        {
			output.sprintf("0x%08X ", &buff[i]);
			dump += output;
		}

		output.sprintf("%02X ", buff[i]);
		dump += output;

		if (i % 16 - 15 == 0)
		{
			int j;

			dump += "  ";
			for (j = i - 15; j <= i; j++)
			{
				if (isprint(buff[j]))
				{
					output.sprintf("%C", buff[j]);
					dump += output;
				}
				else
				{
					dump += ".";
				}
			}
			dump += "\r\n";
		}
	}

	if (i % 16 != 0)
	{
		int j;
		int spaces = (len - i + 16 - i % 16) * 3 + 2;
		for (j = 0; j < spaces; j++)
		{
			dump += " ";
		}
		for (j = i - i % 16; j < len; j++)
		{
			if (isprint(buff[j]))
			{
				output.sprintf("%C", buff[j]);
				dump += output;
            }
            else
			{
                dump += ".";
            }
		}
	}

	dump += "\r\n\r\n";

	MemoDBG->Lines->Add(dump);
}
//---------------------------------------------------------------------------
bool __fastcall TForm1::SearchWindow(int PageIndex, TChromiumWindow **window)
{
	int i, j;
	TControl *TempControl;
	TTabSheet *TempSheet;

	bool res = false;
	*window = NULL;

	if (PageIndex >= 0 && PageIndex < PageControl1->PageCount)
	{
		TempSheet = PageControl1->Pages[PageIndex];
		i = 0;
		j = TempSheet->ControlCount;

		do {
			TempControl = TempSheet->Controls[i];

			if (TempControl != NULL && TempControl->ClassNameIs("TChromiumWindow"))
			{
				*window = reinterpret_cast<TChromiumWindow *>(TempControl);
				res = true;
			}
			else {
				i++;
			}
		}
		while (i < j && !res);
	}

	return res;
}
//---------------------------------------------------------------------------
bool __fastcall TForm1::GetPageIndex(TObject *Sender, int *PageIndex)
{
	bool res = false;
	*PageIndex = -1;

	if ((Sender != NULL) &&
		 Sender->ClassNameIs("TChromiumWindow") &&
		 reinterpret_cast<TComponent *>(Sender)->Owner != NULL &&
		 reinterpret_cast<TComponent *>(Sender)->Owner->ClassNameIs("TTabSheet"))
	{
		*PageIndex = reinterpret_cast<TTabSheet *>(reinterpret_cast<TComponent *>(Sender)->Owner)->PageIndex;
		res = true;
	}

	return res;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumTempAddressChange(TObject *Sender, ICefBrowser * const browser,
		  ICefFrame * const frame, const ustring url)
{
	if (!EditURL->Focused())
	{
		TChromiumWindow *window = reinterpret_cast<TChromiumWindow *>(PageControl1->ActivePage->Tag);
		if (window->ChromiumBrowser->Browser != NULL)
			EditURL->Text = window->ChromiumBrowser->Browser->MainFrame->Url;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PageControl1Change(TObject *Sender)
{
	if (PageControl1->ActivePage->Tag)
	{
		TChromiumWindow *window = reinterpret_cast<TChromiumWindow *>(PageControl1->ActivePage->Tag);

		if (window->ChromiumBrowser->Browser != NULL)
		{
			if (window->ChromiumBrowser->Browser->MainFrame->Url == "data:text/html,chromewebdata" ||
				window->ChromiumBrowser->Browser->MainFrame->Url == "about:blank")
			{
				window->ChromiumBrowser->Browser->Reload();
			}

			TTabSheet *tab = reinterpret_cast<TTabSheet *>(window->ChromiumBrowser->Tag);

			if (tab->PageIndex == PageControl1->TabIndex && !EditURL->Focused())
				EditURL->Text = window->ChromiumBrowser->DocumentURL;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumTempTitleChange(TObject *Sender, ICefBrowser * const browser,
		  const ustring title)
{
	TTabSheet *tab = reinterpret_cast<TTabSheet *>(reinterpret_cast<TChromium *>(Sender)->Tag);

	if (title.Length() > 10)
	{
		UnicodeString retitle = title.SubString(1, 10);
		tab->Caption = retitle + "...";
	}
	else
	{
		tab->Caption = title;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumTempBeforePopup(TObject *Sender, ICefBrowser * const browser,
		  ICefFrame * const frame, const ustring targetUrl, const ustring targetFrameName,
		  TCefWindowOpenDisposition targetDisposition, bool userGesture,
          TCefPopupFeatures &popupFeatures, TCefWindowInfo &windowInfo, ICefClient *&client,
		  TCefBrowserSettings &settings, bool &noJavascriptAccess, bool Result)
{
	windowInfo.windowless_rendering_enabled = true;
	AddTab(targetUrl);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditURLKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == vkReturn)
	{
		TTabSheet *tab = PageControl1->ActivePage;
		TChromiumWindow *window = reinterpret_cast<TChromiumWindow *>(tab->Tag);
		window->LoadURL(EditURL->Text);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonAddTabBrowserClick(TObject *Sender)
{
	ButtonAddTabBrowser->Enabled = false;

	StatusBar1->Panels->Items[0]->Text = "Loading..";

	UnicodeString *URL = reinterpret_cast<UnicodeString *>(Sender);

	TTabSheet *tab = new TTabSheet(PageControl1);
	tab->Caption = "New Tab";
	tab->PageControl = PageControl1;

	TChromiumWindow *window = new TChromiumWindow(tab);
	window->Parent = tab;
	window->Color = clWhite;
	window->Align = alClient;

	tab->Tag = reinterpret_cast<int>(window);
	if (!(*URL).IsEmpty()) tab->Hint = *URL;
	window->ChromiumBrowser->Tag = reinterpret_cast<int>(tab);
	window->OnAfterCreated = (TNotifyEvent)&ChromiumTempAfterCreated;
	window->ChromiumBrowser->OnAddressChange = (TOnAddressChange)&ChromiumTempAddressChange;
	window->ChromiumBrowser->OnTitleChange = (TOnTitleChange)&ChromiumTempTitleChange;
	window->ChromiumBrowser->OnBeforePopup = (TOnBeforePopup)&ChromiumTempBeforePopup;
	window->ChromiumBrowser->OnPreKeyEvent = (TOnPreKeyEvent)&ChromiumTempPreKeyEvent;
	window->ChromiumBrowser->OnConsoleMessage = (TOnConsoleMessage)&ChromiumTempConsoleMessage;
	window->ChromiumBrowser->OnLoadEnd = (TOnLoadEnd)&ChromiumTempLoadEnd;
	// window->ChromiumBrowser->Options->WindowlessFrameRate = 60;
	window->CreateBrowser();

	StatusBar1->Panels->Items[0]->Text = "";
	ButtonAddTabBrowser->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonExitBrowserClick(TObject *Sender)
{
	if (PageControl1->PageCount == 1 || PageControl1->TabIndex == 0) {
		return;
	}

	ButtonExitBrowser->Enabled = false;

	TChromiumWindow *window = NULL;

	for (int i = 1; i < PageControl1->PageCount; i++)
	{
		SearchWindow(i, &window);
		if (window != NULL && window->ChromiumBrowser->IsLoading)
		{
			window->ChromiumBrowser->StopLoad();
			StatusBar1->Panels->Items[0]->Text = "Loading stopped / Try again if you want to close tab";
			ButtonExitBrowser->Enabled = true;
			return;
		}
	}

	window = reinterpret_cast<TChromiumWindow *>(PageControl1->ActivePage->Tag);
	window->ChromiumBrowser->SetFocus(false);
	window->Perform(WM_KILLFOCUS, 0, 0);

	int PageIndex = PageControl1->TabIndex;

	if (PageIndex == (PageControl1->PageCount - 1)) {
		if (PageIndex > 0)
			PageIndex--;
	}


	// [Fix Me]

	// This is programming code that does not work properly.
	try {
		window->ChromiumBrowser->Free();
	} catch(const Exception &e) {
		MemoDBG->Lines->Add("Message: " + e.Message);
	}

	// This is programming code that does not work properly.
	try {
		window->Free();
	} catch(const Exception &e) {
		MemoDBG->Lines->Add("Message: " + e.Message);
	}

	// This will cause an access error, but the tab will be removed properly.
	try {
		PageControl1->Pages[PageControl1->TabIndex]->Free();
	} catch(const Exception &e) {
		MemoDBG->Lines->Add("Message: " + e.Message);
	}

	PageControl1->TabIndex = PageIndex;
	PageControl1->Pages[PageControl1->TabIndex]->UpdateControlState();

	window = reinterpret_cast<TChromiumWindow *>(PageControl1->Pages[PageControl1->TabIndex]->Tag);
	EditURL->Text = window->ChromiumBrowser->Browser->MainFrame->Url;
	window->ChromiumBrowser->SetFocus(true);

	StatusBar1->Panels->Items[0]->Text = "";
	ButtonExitBrowser->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PopupCreatedMsg(TMessage &Message)
{
	TChromiumWindow *TempWindow = NULL;

	if (SearchWindow(Message.WParam, &TempWindow))
	{
		if (TempWindow != NULL)
			TempWindow->UpdateSize();
	}

	PageControl1->TabIndex = Message.WParam;
	
	TChromiumWindow *window = reinterpret_cast<TChromiumWindow *>(PageControl1->Pages[Message.WParam]->Tag);
	window->LoadURL(PageControl1->Pages[Message.WParam]->Hint);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DestroyTabMsg(TMessage &Message)
{
	Form1->Perform(WM_SETFOCUS, 0, 0);
	ExitBrowser(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumTempAfterCreated(TObject *Sender, ICefBrowser *const browser)
{
	int TempPageIndex;

	if (GetPageIndex(Sender, &TempPageIndex)) {
		PostMessage(Handle, CEF_AFTERCREATED, TempPageIndex, 0);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ExitBrowser(TObject *Sender)
{
	if (ButtonExitBrowser->Enabled)
		ButtonExitBrowserClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AddTab(UnicodeString URL)
{
	if (ButtonAddTabBrowser->Enabled)
		ButtonAddTabBrowserClick(reinterpret_cast<TObject *>(&URL));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumTempPreKeyEvent(TObject *Sender, ICefBrowser * const browser,
		  const PCefKeyEvent event, PMsg osEvent, bool isKeyboardShortcut,
		  bool Result)
{
	#define KEY_VK_2     0x32
	#define KEY_VK_3     0x33
	#define KEY_VK_D     0x44
	#define KEY_VK_E     0x45
	#define KEY_VK_F     0x46
	#define KEY_VK_G     0x47
	#define KEY_VK_Q     0x51
	#define KEY_VK_S     0x53
	#define KEY_VK_T     0x54
	#define KEY_VK_W     0x57
	#define KEY_VK_F5    0x74

	if (event->kind == KEYEVENT_RAWKEYDOWN)
	{
		switch (event->windows_key_code)
		{
			case KEY_VK_F5:
			{
				browser->Reload();
				break;
			}

			case KEY_VK_D:
			{
				if (event->modifiers & EVENTFLAG_ALT_DOWN)
				{
					Form1->Perform(WM_SETFOCUS, 0, 0);
					EditURL->SetFocus();
					EditURL->SelectAll();
				}

				break;
			}

			case KEY_VK_T:
			{
				if (event->modifiers & EVENTFLAG_ALT_DOWN)
				{
					AddTab("http://google.com");
				}

				break;
			}

			case KEY_VK_W:
			case KEY_VK_Q:
			{
				if (event->modifiers & EVENTFLAG_ALT_DOWN)
				{
					PostMessage(Handle, CEF_DESTROYTAB, PageControl1->TabIndex, 0);
                    // ExitBrowser(Sender);
				}

				break;
			}

			case KEY_VK_2:
			{
				if (event->modifiers & EVENTFLAG_ALT_DOWN)
				{
					PageControl1->SelectNextPage(false, true);

					TChromiumWindow *window = reinterpret_cast<TChromiumWindow *>(PageControl1->ActivePage->Tag);
					window->ChromiumBrowser->SetFocus(true);

					EditURL->SelectAll();

					break;
				}
			}

			case KEY_VK_3:
			{
				if (event->modifiers & EVENTFLAG_ALT_DOWN)
				{
					PageControl1->SelectNextPage(true, true);

					TChromiumWindow *window = reinterpret_cast<TChromiumWindow *>(PageControl1->ActivePage->Tag);
					window->ChromiumBrowser->SetFocus(true);

					EditURL->SelectAll();

					break;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditURLKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if ((Key == 'd' || Key == 'D') && Shift.Contains(ssAlt))
	{
		EditURL->SetFocus();
		EditURL->SelectAll();
	}

	if ((Key == '2') && Shift.Contains(ssAlt))
	{
		PageControl1->SelectNextPage(false, true);

		TChromium *chrome = reinterpret_cast<TChromium *>(PageControl1->ActivePage->Tag);
		chrome->SetFocus(true);

		EditURL->SelectAll();
	}

	if ((Key == '3') && Shift.Contains(ssAlt))
	{
		PageControl1->SelectNextPage(true, true);

		TChromium *chrome = reinterpret_cast<TChromium *>(PageControl1->ActivePage->Tag);
		chrome->SetFocus(true);

		EditURL->SelectAll();
	}

	if ((Key == 't' || Key == 'T') && Shift.Contains(ssAlt))
	{
		AddTab("http://google.com");
	}

	if ((Key == 'w' || Key == 'W') && Shift.Contains(ssAlt))
	{
		Form1->Perform(WM_SETFOCUS, 0, 0);
		ExitBrowser(Sender);
	}

	if ((Key == 'q' || Key == 'Q') && Shift.Contains(ssAlt))
	{
		Form1->Perform(WM_SETFOCUS, 0, 0);
		ExitBrowser(Sender);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if ((Key == 'd' || Key == 'D') && Shift.Contains(ssAlt))
	{
		EditURL->SetFocus();
		EditURL->SelectAll();
	}

	if ((Key == '2') && Shift.Contains(ssAlt))
	{
		PageControl1->SelectNextPage(false, true);

		TChromiumWindow *chrome = reinterpret_cast<TChromiumWindow *>(PageControl1->ActivePage->Tag);
		chrome->ChromiumBrowser->SetFocus(true);

		EditURL->SelectAll();
	}

	if ((Key == '3') && Shift.Contains(ssAlt))
	{
		PageControl1->SelectNextPage(true, true);

		TChromiumWindow *chrome = reinterpret_cast<TChromiumWindow *>(PageControl1->ActivePage->Tag);
		chrome->ChromiumBrowser->SetFocus(true);

		EditURL->SelectAll();
	}

	if ((Key == 't' || Key == 'T') && Shift.Contains(ssAlt))
	{
		AddTab("http://google.com");
	}

	if ((Key == 'w' || Key == 'W') && Shift.Contains(ssAlt))
	{
		Form1->Perform(WM_SETFOCUS, 0, 0);
		ExitBrowser(Sender);
	}

	if ((Key == 'q' || Key == 'Q') && Shift.Contains(ssAlt))
	{
		Form1->Perform(WM_SETFOCUS, 0, 0);
		ExitBrowser(Sender);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumTempLoadEnd(TObject *Sender, ICefBrowser * const browser,
		  ICefFrame * const frame, int httpStatusCode)
{
	UnicodeString javascript = "";

	// frame->ExecuteJavaScript("window.close = function() {\r\n"
	// 						 "    // Do Not Edit Code Here..\r\n"
	//						 "    console.log('[IoCtlNinjaBrowser:OnClose]');\r\n"
	//						 "};", "", 0);

	frame->ExecuteJavaScript(javascript, "", 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::GoClick(TObject *Sender)
{
	AddTab(EditURL->Text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButtonGoClick(TObject *Sender)
{
	if (PageControl1->ActivePage->Tag)
	{
		TChromiumWindow *chrome = reinterpret_cast<TChromiumWindow *>(PageControl1->ActivePage->Tag);
		chrome->ChromiumBrowser->LoadURL(EditURL->Text);
		EditURL->SetFocus();
		EditURL->SelectAll();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButtonGoBackClick(TObject *Sender)
{
	if (PageControl1->ActivePage->Tag)
	{
		TChromiumWindow *chrome = reinterpret_cast<TChromiumWindow *>(PageControl1->ActivePage->Tag);
		chrome->ChromiumBrowser->GoBack();
		EditURL->SetFocus();
		EditURL->SelectAll();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButtonGoForwardClick(TObject *Sender)
{
	if (PageControl1->ActivePage->Tag)
	{
		TChromiumWindow *chrome = reinterpret_cast<TChromiumWindow *>(PageControl1->ActivePage->Tag);
		chrome->ChromiumBrowser->GoForward();
		EditURL->SetFocus();
		EditURL->SelectAll();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChromiumTempConsoleMessage(TObject *Sender, ICefBrowser * const browser,
          const ustring message, const ustring source, int line,
		  bool Result)
{
	if (message.Pos("[IoCtlNinjaBrowser:OnClose]") > 0)
	{
		ExitBrowser(Sender);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonFixMeClick(TObject *Sender)
{
    Form2->Show();
}
//---------------------------------------------------------------------------

