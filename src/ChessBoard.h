// $Id: ChessBoard.h,v 1.3 2003-12-06 16:44:51 psy Exp $
//
// ChessBoard.h: interface for the ChessBoard class.
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

#if !defined(AFX_CHESSBOARD_H__8478B260_34AF_11D3_BC7B_0080C84DB68D__INCLUDED_)
#define AFX_CHESSBOARD_H__8478B260_34AF_11D3_BC7B_0080C84DB68D__INCLUDED_

#include "ChessTypes.h"
#include "move.h"

class ChessBoard {
    friend class ComputerPlayer;

public:
    string boardlog;                // log of board configurations
    bool in_progress;               // game in progress flag
    operator string() const;
    ChessBoard();
    virtual ~ChessBoard();
    void print(ostream *os) const;
    bool can_move(int from, int to, piece_type promotion=Empty) const;
    bool can_move(const move &m) const
        {return can_move(m.from, m.to, m.promotion);}
    game_status do_move(int from, int to, piece_type promotion=Empty);
    game_status do_move(const move& m)
        {return do_move(m.from, m.to, m.promotion);}
    bool white_moves(void) const;
    static bool show_reverse;
    static bool show_coordinates;
    static int which_rank(int sq);
    static int which_file(int sq);

private:
    piece_type square[64];          // array of board squares
    bool w_turn;                    // flag for white to move
    bool w_castle_k;                // white can castle kingside
    bool w_castle_q;                // white can castle queenside
    bool b_castle_k;                // black can castle kingside
    bool b_castle_q;                // black can castle queenside
    bool b_castled;                 // black castled last move
    bool w_castled;                 // white castled last move
    bool w_check;                   // white is in check
    bool b_check;                   // black is in check
    int fifty;                      // fifty-move rule counter
    int en_passant;                 // location of en passant square
    int b_king_pos;                 // position of black king
    int w_king_pos;                 // position of white king
    game_status status;             // status of game (checkmate, etc.)

    bool triple_occurrence(void) const;
    bool is_attacked(bool by_white, int to) const;
    bool causes_check(const move& m) const;
    bool is_in_check(bool white) const;
    bool is_black(piece_type p) const;
    bool is_white(piece_type p) const;
    bool is_colour(piece_type p, bool white) const;
    bool is_pawn(piece_type p) const;
    bool is_rook(piece_type p) const;
    bool is_king(piece_type p) const;
    bool is_queen(piece_type p) const;
    bool is_bishop(piece_type p) const;
    bool is_knight(piece_type p) const;
    bool is_on_board(int sq) const;
    bool is_dest(int from, int to) const;
    bool is_edge(int sq) const;
    piece_type make_white(piece_type p) const;
    piece_type make_black(piece_type p) const;
    piece_type make_colour(piece_type p, bool white) const;
    piece_type make_neutral(piece_type p) const;
    move_list mobility_knight(int from) const;
    move_list mobility_king(int from) const;
    move_list mobility_pawn(int from) const;
    move_list mobility_queen(int from) const;
    move_list mobility_bishop(int from) const;
    move_list mobility_rook(int from) const;
};

ostream &operator<<(ostream &os, const ChessBoard &c);

// Various short self-explanatory functions for performing menial status checks

inline int ChessBoard::which_rank(int sq) {
    return sq/8;
}
inline int ChessBoard::which_file(int sq) {
    return sq%8;
}
inline bool ChessBoard::is_edge(int sq) const {
    return sq>=a1 && sq<=h1 || sq>=a8 && sq<=h8;
}
inline bool ChessBoard::is_black(piece_type p) const {
    return p!=Empty &&  (p & Black);
}
inline bool ChessBoard::is_white(piece_type p) const {
    return p!=Empty && !(p & Black);
}
inline bool ChessBoard::is_colour(piece_type p, bool white) const {
    return white?is_white(p):is_black(p);
}
inline bool ChessBoard::is_pawn(piece_type p) const {
    return (p & Pawn)!=0;
}
inline bool ChessBoard::is_rook(piece_type p) const {
    return (p & Rook)!=0;
}
inline bool ChessBoard::is_king(piece_type p) const {
    return (p & King)!=0;
}
inline bool ChessBoard::is_queen(piece_type p) const {
    return (p & Queen)!=0;
}
inline bool ChessBoard::is_bishop(piece_type p) const {
    return (p & Bishop)!=0;
}
inline bool ChessBoard::is_knight(piece_type p) const {
    return (p & Knight)!=0;
}
inline bool ChessBoard::is_on_board(int sq) const {
    return sq>=a1 && sq<=h8;
}
inline bool ChessBoard::is_dest(int from, int to) const {
    return is_on_board(to) &&
        (is_white(square[from]) && !is_white(square[to]) ||
         is_black(square[from]) && !is_black(square[to]));
}

// Colour-converting functions
inline piece_type ChessBoard::make_white(piece_type p) const {
    return p==Empty ? Empty : (piece_type)(p & ~Black);
}
inline piece_type ChessBoard::make_black(piece_type p) const {
    return p==Empty ? Empty : (piece_type)(p | Black);
}
inline piece_type ChessBoard::make_colour(piece_type p, bool white) const {
    return white ? make_white(p) : make_black(p);
}
inline piece_type ChessBoard::make_neutral(piece_type p) const {
    return p==Empty ? Empty : (piece_type)(p & ~Black);
}

#endif // !defined(AFX_CHESSBOARD_H__8478B260_34AF_11D3_BC7B_0080C84DB68D__INCLUDED_)
