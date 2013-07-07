// Get the output color attribute for the current console window
//
// License: MIT / X11
// Copyright (c) 2010 by James K. Lawless
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

void syntax();
void *getConsoleFunction(char *name);

BOOL (WINAPI *doGetConsoleScreenBufferInfo)(HANDLE hConsoleOutput, 
   CONSOLE_SCREEN_BUFFER_INFO *inf);


int main(int argc,char **argv) {
   HANDLE hCon;
   WORD color;
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   FILE *fout;
   
   if(argc<2) {
      syntax();
      return 1;
   }
   
   hCon=GetStdHandle(STD_OUTPUT_HANDLE);
   
   doGetConsoleScreenBufferInfo=getConsoleFunction("GetConsoleScreenBufferInfo");

   if(doGetConsoleScreenBufferInfo==NULL) {
      fprintf(stderr,"Sorry! get is incompatible with this version of Windows.");
      return 1;
   }   
   if(argc==3) {
      fout=fopen(argv[2],"w");
      if(fout==NULL) {
         fprintf(stderr,"Cannot open output file %s\n",argv[2]);
         return 1;
      }
   }
   else {
      fout=stdout;
   }

   (*doGetConsoleScreenBufferInfo)(hCon,&csbi);
   color=csbi.wAttributes;
   if(!stricmp(argv[1],"-b")) {
      fprintf(fout,"%x",color>>4);
   }      
   else
   if(!stricmp(argv[1],"-f")) {
      fprintf(fout,"%x",color&0x0f);
   }
   else {
      syntax();
      if(fout!=stdout)
         fclose(fout);
      return 1;
   }
   if(fout!=stdout)
         fclose(fout);
   return 0;
}

void syntax() {
   fprintf(stderr,"getcolor - Get the current console color attribute - by Jim Lawless\n\n");
   fprintf(stderr,"Syntax:\n\tgetcolor -f [optional output filename]\n");
   fprintf(stderr,"Write foreground color digit\n\nor\n\n");
   fprintf(stderr,"\tgetcolor-b [optional output filename]\n");
   fprintf(stderr,"Write background color digit\n\n");
   fprintf(stderr,"See:\nhttp://www.mailsend-online.com/blog/?p=94\nfor usage instructions and C source code.\n");
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

