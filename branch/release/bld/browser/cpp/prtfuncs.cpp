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


// System includes -------------------------------------------------------

#include <wstring.hpp>

// Project includes ------------------------------------------------------

#include "mem.h"
#include "prtfuncs.h"

// Methods ---------------------------------------------------------------

PrintFunctions::PrintFunctions( ProjectModel * project )
    : PrintSymbols( project )
/********************************************/
{
    _key.setSymType( DR_SEARCH_FUNCTIONS );
}

void PrintFunctions::printSymbol( Symbol * pSym )
/***********************************************/
{
    WString tmpStr;
    WVList callers;
    FunctionSym * pFuncSym;
    char * funcName;

    pFuncSym = (FunctionSym *) pSym;

    pFuncSym->callers( callers );
    funcName = pFuncSym->scopedName();

    if( callers.count() > 0 ) {
        int i;

        _strTable.outputRow( funcName, EmptyString,
                             ( (Symbol *) callers[ 0 ])->scopedName() );

        for( i = 1; i < callers.count(); i += 1 ) {
            _strTable.outputRow( EmptyString, EmptyString,
                                 ( (Symbol *) callers[ i ])->scopedName() );
        }
    } else {
        _strTable.outputRow( funcName, EmptyString, EmptyString );
    }

    callers.deleteContents();
}

void PrintFunctions::printHeading( SafeFile & )
/*********************************************/
{
    _strTable.outputRow( "Function", EmptyString, "Called By" );
    _strTable.outputRow( "--------", EmptyString, "---------" );
}

