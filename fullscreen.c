// Switch a console window to full screen or windowed mode.
//
// License: MIT / X11
// Copyright (c) 2009 by James K. Lawless
// jimbo@radiks.net http://www.radiks.net/~jimbo
// http://www.mailsend-online.com
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

#include <windows.h>
#include <stdio.h>
#include <string.h>

void *getConsoleFunction(char *name);

BOOL (WINAPI *doSetConsoleDisplayMode)(HANDLE hConsoleOutput,DWORD dwFlags, void *coord);
void syntax();

int main(int argc,char **argv) {
   HANDLE hCon;
   int mode;
   
   if(argc<2) {
      syntax();
      return 1;
   }

   if(!stricmp(argv[1],"-f"))
      mode=1;
   else
   if(!stricmp(argv[1],"-w"))
      mode=2;
   else {
      syntax();
      return 1;
   }
   
   hCon=GetStdHandle(STD_OUTPUT_HANDLE);
   
   doSetConsoleDisplayMode=getConsoleFunction("SetConsoleDisplayMode");

   if(doSetConsoleDisplayMode==NULL) {
      fprintf(stderr,"Sorry! fullscreen.exe is incompatible with this version of Windows.");
      return 1;
   }   
   (*doSetConsoleDisplayMode)(hCon,mode,NULL);

   return 0;
}

void *getConsoleFunction(char *name) {
   static HMODULE kernel32=(HMODULE)0xffffffff;
   if(kernel32==0)
      return NULL;
   if(kernel32==(HMODULE)0xffffffff) {
      kernel32=LoadLibrary("kernel32.dll");
      if(kernel32==0)
         return 0;         
   }
   return GetProcAddress(kernel32,name);
}

void syntax() {
   fprintf(stderr,"fullscreen - Change console window to full screen or windowed mode\n");
   fprintf(stderr,"by Jim Lawless\n\n");
   fprintf(stderr,"Syntax:\n\tfullscreen -f\n");
   fprintf(stderr,"or\n");
   fprintf(stderr,"\tfullscreen -w\n\n");
   fprintf(stderr,"Where -f will force the console window into full-screen mode\nand -w will force the console window into windowed mode.\n");
   fprintf(stderr,"\nSee:\nhttp://www.mailsend-online.com/blog/?p=81\nfor usage instructions and C source code.\n");
}
