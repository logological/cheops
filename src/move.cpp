// move.cpp: implementation of the move struct.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChessBoard.h"

// -------------------------------------------------------------------
// Print move (<< operator overload)
// -------------------------------------------------------------------
ostream &operator<<(ostream &os, const move &m) {
    return os << (string)m;
}

// -------------------------------------------------------------------
// Cast move to string
// -------------------------------------------------------------------
move::operator string() const {
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

