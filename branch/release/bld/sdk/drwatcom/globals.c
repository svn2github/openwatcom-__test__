/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
*
****************************************************************************/


#include "wdebug.h"
#include "drwatcom.h"

interrupt_struct        IntData;
WORD                    DeadTask;
TASKENTRY               DTTaskEntry;
MODULEENTRY             DTModuleEntry;
HWND                    MainWindow;
WORD                    CharSizeX,CharSizeY;
HANDLE                  Instance;
char                    *AppName;
DWORD                   WindowsFlags;
loginfo                 LogInfo;
dumpany                 DumpAny;
HANDLE                  ProgramTask;
int                     MinAddrSpaces;
BOOL                    WDebug386 = FALSE;
HWND                    DumpDialogHwnd;
BOOL                    WasFault;
BOOL                    IsWin32App;
WORD                    Win32CS;
DWORD                   Win32InitialEIP;
WORD                    Win32DS;
BOOL                    FaultHandlerEntered;
BOOL                    StatShowSymbols=TRUE;
char                    DebuggerOpts[128];
int                     DumpHow;
BOOL                    AlwaysRespondToDebugInChar;
BOOL                    AlertOnWarnings;
LBoxHdl                 *ListBox;
