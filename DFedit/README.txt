Comments and questions to keith.brewer.08(at)gmail.com.


These are the source files for Dragon Force Edit v2.31! 

DFedit is a Win32 GUI based application. It's goal is to edit the save files for the Sega Saturn game Dragon Force. Specifically, it works on the file that is created when running the game through the Sega Saturn Emulator known as SSF with the "hook backup library" option checked. 

Normally named files do what they indicate. Files that include "TabWndCtrls" in their name are the files that control all of the GUI elements on that particular tab of the interface. 

To try the program, click on DFedit_app_with_sample_file.7z on github, then click "View Raw". This should download a 7zip archive of the release exe plus a sample file to use the program with.

The codebase currently stands at 32 source files with 11,039 lines of code (code + code and comments). It was written in the Code::Blocks IDE. It was built using the TDM version of the MinGW compiler. As long as you include the following library files (for the Win32 elements) in your linker settings, this project should build just fine. 

\lib\libcomctl32.a
\lib\libgdi32.a
\lib\libcomdlg32.a

The path before \lib\ is whatever your root folder for MinGW is. 




This program is a product of my efforts to keep my C and C++ knowledge fresh between school terms, to learn GUI programming - in this case Win32, and to make something that is actually practical instead of just random book exercises. This code was written completely by hand. No MFC or Visual-anything, just raw hand-rolled Win32. 

Since this program is the product of a personal learning exercise, you should understand that it is a bit lacking in some areas, which I am fully aware of.

Some of these things are that I take dynamic memory allocation success for granted, though there isn't actually a lot of this going on. Some areas of the code have lots of comments, other areas are thin on comments or lacking. I don't have file description comment blocks at the top of every file. The C++ classes use public data - this is something I am already going through and making private as a side project. Some of the classes may be a tad too dependent on other classes. There are also other minor things missing like being able to tab through the controls on a page or use keyboard shortcuts. 

But remember that this was a personal GUI learning exercise for me - the focus was on learning the API and creating the program. Going forward, I have, and will, return to more strict and acceptable practices.