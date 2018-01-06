//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "Unit1.h"
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", Form2);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		GlobalCEFApp = new TCefApplication();
		GlobalCEFApp->CheckCEFFiles = true;
		GlobalCEFApp->FrameworkDirPath = "cef";
		GlobalCEFApp->ResourcesDirPath = "cef";
		GlobalCEFApp->LocalesDirPath = "cef\\locales";
		GlobalCEFApp->Cache = "cef\\cache";
		GlobalCEFApp->Cookies = "cef\\cookies";
		GlobalCEFApp->UserDataPath = "cef\\User Data";
		GlobalCEFApp->DeleteCache = true;
		GlobalCEFApp->DeleteCookies = true;
		GlobalCEFApp->FlashEnabled = true;
		GlobalCEFApp->EnableSpeechInput = true;
		GlobalCEFApp->EnableMediaStream = true;
		GlobalCEFApp->FastUnload = true;
		GlobalCEFApp->NoSandbox = true;
		GlobalCEFApp->SingleProcess = true;
		GlobalCEFApp->Locale = "ko";

		if(GlobalCEFApp->StartMainProcess())
		{
			Application->Initialize();
			Application->MainFormOnTaskBar = true;
			Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TForm2), &Form2);
		Application->Run();
		}
		GlobalCEFApp->~TCefApplication();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
