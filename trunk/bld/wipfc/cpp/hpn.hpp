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
* Description:  Process hpn/ehpn tags
*
*   :hp1-:hp9 / :ehp1-:ehp9
*    Cannot nest
*
****************************************************************************/

#ifndef HPN_INCLUDED
#define HPN_INCLUDED

#include "tag.hpp"

class Hpn : public Element {
public:
    Hpn( Document* d, Element *p, const std::wstring* f, unsigned int r,
        unsigned int c, unsigned int l );
    ~Hpn() { };
    static
    unsigned int level() { return nestLevel; };
    static
    void setLevel( unsigned int l ) { nestLevel = l; };
    Lexer::Token parse( Lexer* lexer );
    void buildText( Cell* cell );
private:
    Hpn( const Hpn& rhs );              //no copy
    Hpn& operator=( const Hpn& rhs );   //no assignment
    static
    unsigned int nestLevel;
    unsigned int lvl;
};

class EHpn : public Element {
public:
    EHpn( Document* d, Element *p, const std::wstring* f, unsigned int r,
        unsigned int c, unsigned int l );
    ~EHpn() { };
    Lexer::Token parse( Lexer* lexer );
    void buildText( Cell* cell );
private:
    EHpn( const EHpn& rhs );            //no copy
    EHpn& operator=( const EHpn& rhs ); //no assignment
    unsigned int level;
};

#endif // HPN_INCLUDED

