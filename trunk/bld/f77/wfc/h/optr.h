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
* Description:  operator index for expression generate routines
*
****************************************************************************/


enum OPERATIONS {
   OPTR_EQV,            //  .eqv. operation
   OPTR_NEQV,           //  .neqv. operation
   OPTR_OR,             //  .or. operation
   OPTR_AND,            //  .and. operation
   OPTR_NOT,            //  .not. operation
   OPTR_FILLER,         //  filler
   OPTR_ASGN,           //  ,
   OPTR_CH_ASGN,        //  character assignment
   OPTR_CH_REL,         //  character compare
   OPTR_REL,            //  relational operation (,
   OPTR_ADD,            //  + operation
   OPTR_SUB,            //  - operation
   OPTR_MUL,            //  * operation
   OPTR_DIV,            //  / operation
   OPTR_EXP,            //  exponentiation
   OPTR_CAT             //  concatenation
};

typedef enum OPERATIONS OPTR;
