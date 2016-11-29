//
// move.cpp: implementation of the chessmove struct.
//
// Copyright (C) 2003 Tristan Miller <psychonaut@nothingisreal.com>
//  
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChessBoard.h"

// -------------------------------------------------------------------
// Print move (<< operator overload)
// -------------------------------------------------------------------
ostream &operator<<(ostream &os, const chessmove &m) {
    return os << (string)m;
}

// -------------------------------------------------------------------
// Cast move to string
// -------------------------------------------------------------------
chessmove::operator string() const {
    static char s[6]="\0\0\0\0\0";
    s[0] = (char)(ChessBoard::which_file(this->from)+'a');
    s[1] = (char)(ChessBoard::which_rank(this->from)+'1');
    s[2] = (char)(ChessBoard::which_file(this->to)+'a');
    s[3] = (char)(ChessBoard::which_rank(this->to)+'1');
    switch (this->promotion) {
    case Empty:
        s[4]='\0';
        break;
    case Queen:
        s[4]='q';
        break;
    case Knight:
        s[4]='n';
    case Rook:
        s[4]='r';
        break;
    case Bishop:
        s[4]='b';
        break;
    }
    return s;
}
