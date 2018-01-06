//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "uCEFChromium.hpp"
#include "uCEFChromiumWindow.hpp"
#include "uCEFWindowParent.hpp"
#include "uCEFApplication.hpp"
#include <Vcl.Buttons.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdCoder.hpp>
#include <IdCoder3to4.hpp>
#include <IdCoderMIME.hpp>
#include <IdExplicitTLSClientServerBase.hpp>
#include <IdFTP.hpp>
#include <IdThreadComponent.hpp>
//---------------------------------------------------------------------------
#define CEF_POPUPCREATED    	WM_APP + 0x100
#define CEF_DESTROYTAB          WM_APP + 0x101
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *PanelTopMain;
	TPageControl *PageControl1;
	TEdit *EditURL;
	TSpeedButton *SpeedButtonGoBack;
	TSpeedButton *SpeedButtonGoForward;
	TSpeedButton *SpeedButtonGo;
	TPanel *PanelForward;
	TPanel *PanelURL;
	TPanel *PanelGo;
	TPanel *PanelBackward;
	TMemo *MemoDBG;
	TButton *ButtonExitBrowser;
	TButton *ButtonAddTabBrowser;
	TPageControl *PageControl2;
	TTabSheet *TabSheet1;
	TButton *ButtonCloseQuery;
	TStatusBar *StatusBar1;
	TPanel *PanelTab;
	TButton *ButtonFixMe;

	void __fastcall GoClick(TObject *Sender);
	void __fastcall EditURLKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EditURLKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall SpeedButtonGoClick(TObject *Sender);
	void __fastcall SpeedButtonGoBackClick(TObject *Sender);
	void __fastcall SpeedButtonGoForwardClick(TObject *Sender);
	void __fastcall ButtonExitBrowserClick(TObject *Sender);
	void __fastcall ButtonAddTabBrowserClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall ButtonCloseQueryClick(TObject *Sender);

	void __fastcall ChromiumTempAfterCreated(TObject *Sender, ICefBrowser * const browser);
	void __fastcall ChromiumTempAddressChange(TObject *Sender, ICefBrowser * const browser,
		  ICefFrame * const frame, const ustring url);
	void __fastcall ChromiumTempTitleChange(TObject *Sender, ICefBrowser * const browser,
		  const ustring title);
	void __fastcall ChromiumTempBeforePopup(TObject *Sender, ICefBrowser * const browser,
		  ICefFrame * const frame, const ustring targetUrl, const ustring targetFrameName,
		  TCefWindowOpenDisposition targetDisposition, bool userGesture,
		  TCefPopupFeatures &popupFeatures, TCefWindowInfo &windowInfo, ICefClient *&client,
		  TCefBrowserSettings &settings, bool &noJavascriptAccess, bool Result);
	void __fastcall ChromiumTempPreKeyEvent(TObject *Sender, ICefBrowser * const browser,
		  const PCefKeyEvent event, PMsg osEvent, bool isKeyboardShortcut,
		  bool Result);
	void __fastcall ChromiumTempLoadEnd(TObject *Sender, ICefBrowser * const browser,
		  ICefFrame * const frame, int httpStatusCode);
	void __fastcall ChromiumTempConsoleMessage(TObject *Sender, ICefBrowser * const browser,
		  const ustring message, const ustring source, int line,
		  bool Result);
	void __fastcall ButtonFixMeClick(TObject *Sender);

public:
	MESSAGE void __fastcall PopupCreatedMsg(Winapi::Messages::TMessage &aMessage);
	MESSAGE void __fastcall DestroyTabMsg(Winapi::Messages::TMessage &aMessage);
	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(CEF_AFTERCREATED, TMessage, PopupCreatedMsg);
		VCL_MESSAGE_HANDLER(CEF_DESTROYTAB, TMessage, DestroyTabMsg);
	END_MESSAGE_MAP(TForm)

private:	// User declarations
	void __fastcall AddTab(UnicodeString URL);
	void __fastcall ExitBrowser(TObject *Sender);
	bool __fastcall GetPageIndex(TObject *Sender, int *PageIndex);
	bool __fastcall SearchWindow(int PageIndex, TChromiumWindow **window);
	void __fastcall AppException(TObject *Sender, Exception *E);

private:
	void __fastcall dumpcode(unsigned char *buff, int len);

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
