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

// check the state of the Scroll Lock or Caps Lock keys.  Return a
// 1 if the requested key is active/on.

#include <windows.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib,"user32.lib")

int main(int argc,char **argv) {
   int i,key;
   if(argc<2) {
      fprintf(stderr,"Syntax:\n\t%s -scroll\nor\n\t%s -caps\n",
         argv[0],argv[0]);
      return 1;
   }
   if(!stricmp(argv[1],"-scroll"))
      key=VK_SCROLL;
   else
      key=VK_CAPITAL;
   return (GetKeyState(key)&1);
}
