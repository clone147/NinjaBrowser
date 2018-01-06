# NinjaBrowser

NinjaBrowser is an open source project created by AmesianX to embed Chromium-based browsers in applications made with C++ Builder.

NinjaBrowser is based on CEF4Delphi made by Salvador Díaz Fau.(CEF4Delphi based on DCEF3 made by Henri Gourvest).

NinjaBrowser uses CEF 3.3239.1723.g071d1c1 which includes Chromium 63.0.3239.132. 

The CEF3 binaries used by NinjaBrowser(and CEF4Delphi) are available for download at spotify :

  32bit -> http://opensource.spotify.com/cefbuilds/cef_binary_3.3239.1723.g071d1c1_windows32.tar.bz2
  
  64bit -> http://opensource.spotify.com/cefbuilds/cef_binary_3.3239.1723.g071d1c1_windows64.tar.bz2

First, Create a "cef" directory in the executable directory.

Unpack the CEF3 archive. After decompressing, copy all the files in the "Release" (or "Debug")

and "Resources" folders to the "cef" folder.

For more information about CEF4Delphi visit :

  https://github.com/salvadordf/CEF4Delphi
  https://www.briskbard.com/index.php?lang=en&pageid=cef

Forum :
  https://www.briskbard.com/forum

Comment:
  NinjaBrowser was developed and tested on C++ Builder 10.2.2 Tokyo and it has been tested.
  The CEF4Delphi folder included in this github has been modified in only one line
  in the original version. ("CEF4Delphi\source\uCEFChromium.pas")
  Check the first line of the OnBeforePopup function.
  (Result value was changed from False to True. You can open the window with a new tab.)