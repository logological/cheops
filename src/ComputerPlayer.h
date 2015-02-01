// $Id$
//
// ComputerPlayer.h: interface for the ComputerPlayer class.
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

#if !defined(AFX_COMPUTERPLAYER_H__EBEFC222_5256_11D3_BC7B_0080C84DB68D__INCLUDED_)
#define AFX_COMPUTERPLAYER_H__EBEFC222_5256_11D3_BC7B_0080C84DB68D__INCLUDED_

#include "Player.h"

class ComputerPlayer : public Player {
public:
    static bool show_thinking;
    string get_command(const ChessBoard &b) const;
    void set_stats();
    ComputerPlayer();
    virtual ~ComputerPlayer();

private:
    long ply;
    long draw_value;
    long endgame_threshold;

    long p_material;
    long p_doubled;
    long p_backward;
    long p_edge_prox;
    long p_isolated[4];

    long n_material;
    long n_king_dist;
    long n_centre_prox;

    long b_material;
    long b_centre_prox;
    long b_mobility;
    long b_xmobility;
    long b_both;
    long b_mobilitybonus;
    long b_xmobilitybonus;

    long r_material;
    long r_king_prox;
    long r_xmobility;
    long r_mobility;
    long r_pawns;
    long r_mobilitybonus;
    long r_xmobilitybonus;

    long q_material;
    long q_king_prox;
    long q_centre_prox;

    long k_centre_dist;
    long k_pawn;
    long k_castle;

    int chebychev(int from, int to) const;
    int chebychev(int from) const;
    int manhattan(int from, int to) const;
    move_list get_all_moves(const ChessBoard &b) const;
    long get_score(const ChessBoard &b) const;
    long alphabeta(const ChessBoard &b, long depth, long alpha, long beta, move &chosen_move) const;
    bool adjacent_friendly_pawns(const ChessBoard &b, int sq) const;
    long rook_mobility(const ChessBoard &b, int from) const;
    long bishop_mobility(const ChessBoard &b, int from) const;
    long rook_xmobility(const ChessBoard &b, int from) const;
    long bishop_xmobility(const ChessBoard &b, int from) const;
    int friendly_pawns_on_file(const ChessBoard &b, int sq) const;
    bool both_bishops_present(const ChessBoard &b, bool white) const;
    bool isolated_pawn(const ChessBoard &b, int sq) const;
    bool backward_pawn(const ChessBoard &b, int sq) const;
    bool is_endgame(const ChessBoard &b) const;
};

//////////////////////////////////////////////////////////////////////
// Functions used by the AI engine
//////////////////////////////////////////////////////////////////////

// -------------------------------------------------------------------
// Chebychev (i.e. queen- and bishop-wise) distance between two
// board squares
//  - this function is also used for knight distances, since short of
//    a 64x64 lookup table, there is no easy way to compute L-shaped
//    distances
// - if the second argument (destination) is omitted, function returns
//   distance to centre of the board
// -------------------------------------------------------------------
inline int ComputerPlayer::chebychev(int from, int to) const {
    int dy=abs(ChessBoard::which_rank(from)-ChessBoard::which_rank(to)),
        dx=abs(ChessBoard::which_file(from)-ChessBoard::which_file(to));
    return dx>dy?dx:dy;
}
inline int ComputerPlayer::chebychev(int from) const {
    return chebychev(from, (((ChessBoard::which_rank(from))>3)?32:24) +
        (((ChessBoard::which_file(from))>3)?4:3));
}

// -------------------------------------------------------------------
// Manhattan (i.e. rook-wise) distance between two board squares
// -------------------------------------------------------------------
inline int ComputerPlayer::manhattan(int from, int to) const {
    return abs(ChessBoard::which_rank(from)-ChessBoard::which_rank(to)) +
        abs(ChessBoard::which_file(from)-ChessBoard::which_file(to));
}

#endif // !defined(AFX_COMPUTERPLAYER_H__EBEFC222_5256_11D3_BC7B_0080C84DB68D__INCLUDED_)
