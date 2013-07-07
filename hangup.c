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

// Find the first RAS connection and hang it up.

#include <stdio.h>
#include <windows.h>
#include <ras.h>

#pragma comment(lib, "rasapi32.lib")

main(int argc,char **argv)
{
	RASCONN r;
	DWORD siz,num;

	printf("Hang Up! V 2.0\nCopyright (c)  2009 by Jim Lawless\n");
	printf("(See MIT/X11 license in the source code)\n");
	r.dwSize=siz=sizeof(RASCONN);
	RasEnumConnections(&r,&siz,&num);
	if( num == 0 ) {
		printf("No connections found!  Terminating.\n");
		exit(1);
	}
	RasHangUp(r.hrasconn);
	Sleep(3000);
	printf("Done.\n");
	exit(0);
}

