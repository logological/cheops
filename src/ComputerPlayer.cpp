//
// ComputerPlayer.cpp: implementation of the ComputerPlayer class.
//
// Copyright (C) 2003-2016 Tristan Miller <psychonaut@nothingisreal.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComputerPlayer.h"
#include <climits>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

bool ComputerPlayer::show_thinking=false;

ComputerPlayer::ComputerPlayer() {
    human=false;
        ply=4;
    draw_value=0;
    endgame_threshold=1500;

    p_material=100;
    p_doubled=-12;
    p_backward=-6;
    p_edge_prox=1;
    p_isolated[0]=-12;
    p_isolated[1]=-14;
    p_isolated[2]=-16;
    p_isolated[3]=-20;

    n_material=330;
    n_king_dist=-1;
    n_centre_prox=10;

    b_material=330;
    b_centre_prox=10;
    b_mobility=1;
    b_xmobility=1;
    b_both=-20;
    b_mobilitybonus=8;
    b_xmobilitybonus=8;

    r_material=500;
    r_king_prox=20;
    r_mobility=1;
    r_xmobility=1;
    r_pawns=10;
    r_mobilitybonus=8;
    r_xmobilitybonus=8;

    q_material=900;
    q_king_prox=20;
    q_centre_prox=10;

        k_centre_dist=10;
    k_pawn=-16;
        k_castle=10;

    set_stats();
}

ComputerPlayer::~ComputerPlayer() {
    
}

// -------------------------------------------------------------------
// Set computer weights for static evaluation
// -------------------------------------------------------------------
void ComputerPlayer::set_stats() {
    long *vars[] = {&draw_value, &endgame_threshold, &p_material, &p_doubled,
        &p_backward, &p_edge_prox, &p_isolated[0], &p_isolated[1],
        &p_isolated[2], &p_isolated[3], &n_material, &n_king_dist,
        &n_centre_prox, &b_material, &b_centre_prox, &b_mobility, &b_xmobility,
        &b_both, &b_mobilitybonus, &b_xmobilitybonus, &r_material,
        &r_king_prox, &r_mobility, &r_xmobility, &r_pawns, &r_mobilitybonus,
        &r_xmobilitybonus, &q_material, &q_king_prox, &q_centre_prox,
        &k_centre_dist, &k_pawn, &k_castle, &ply, NULL};
    const char *desc[] = {"draw value", "endgame threshold", "pawn material",
        "doubled pawn", "backward pawn", "pawn proximity to opposite edge",
        "isolated pawn on file 1 or 8", "isolated pawn on file 2 or 7",
        "isolated pawn on file 3 or 6", "isolated pawn on file 4 or 5",
        "knight material", "knight distance to either king",
        "knight proximity to centre", "bishop material",
        "bishop proximity to centre", "bishop mobility",
        "bishop X-ray mobility", "presence of both bishops",
        "bishop mobility bonus", "bishop X-ray mobility bonus",
        "rook material", "rook proximity to enemy king", "rook mobility",
        "rook X-ray mobility", "friendly pawns on same file as rook",
        "rook mobility bonus", "rook X-ray mobility bonus", "queen material",
        "queen proximity to enemy king", "queen proximity to centre",
        "king distance from centre (except endgame)",
        "no friendly pawns adjacent to king", "king castling",
        "search ply", NULL};
    int i, attrib;
    string s;
    while (1) {
        for (i=0;vars[i];i++) {
            cout.width(2);
            cout << i;
            cout.width(0);
            cout << " : " << desc[i] << " [" << *vars[i] << "]\n";
        }
        cout << "Enter attribute # to change or 'done' when done: ";
        cin >> s;
        cout << endl;
        if (s=="done")
            break;
        attrib=atoi(s.c_str());
        if (attrib<0 || attrib>=i)
            cout << "Not a valid attribute.  Try again.\n";
        else {
            cout << "Enter new value for " << desc[attrib] << ": ";
            cin >> s;
            cout << endl;
            *vars[attrib]=atol(s.c_str());
        }
    }
}


// -------------------------------------------------------------------
// Returns the computer's move
// -------------------------------------------------------------------
string ComputerPlayer::get_command(const ChessBoard &b) const {
    if (b.in_progress) {
        chessmove mv;
        long v=alphabeta(b, ply,-LONG_MAX,LONG_MAX,mv);
        // To offer draw:
        // if v<DRAW_THRESHOLD && haven't_offered_draw_in_a_while then
        //      moves_since_last_draw=0;
        //      if offer_draw()==accept;
        //          game over
        //      else
        //          return mv;
        // else
        //      moves_since_last_draw++;
        //      return mv;
        cout << "\nComputer moves: " << mv << endl;
        return mv;
    }
    else {
        string cmd;
        cout << "\nCommand: ";
        cin >> cmd;
        return cmd;
    }
}

//////////////////////////////////////////////////////////////////////
// Functions used by the AI engine
//////////////////////////////////////////////////////////////////////

// -------------------------------------------------------------------
// Generate a list of all possible moves for the given side
// -------------------------------------------------------------------
move_list ComputerPlayer::get_all_moves(const ChessBoard &b) const {
    move_list moves, temp;
    static const int sq_order[] =  {d4, d5, e5, e4, e3, d3, c3, c4, c5, c6, d6,
        e6, f6, f5, f4, f3, f2, e2, d2, c2, b2, b3, b4, b5, b6, b7, c7, d7, e7,
        f7, g7, g6, g5, g4, g3, g2, g1, f1, e1, d1, c1, b1, a1, a2, a3, a4, a5,
        a6, a7, a8, b8, c8, d8, e8, f8, g8, h8, h7, h6, h5, h4, h3, h2, h1};
    if (!b.in_progress)
        return moves;
    for (int sq=0;sq<64;sq++) {
        if (b.is_colour(b.square[sq_order[sq]], b.w_turn)) {
            switch (b.make_neutral(b.square[sq_order[sq]])) {
            case King:
                temp=b.mobility_king(sq_order[sq]); 
                break;
            case Pawn:
                temp=b.mobility_pawn(sq_order[sq]);
                break;
            case Knight:
                temp=b.mobility_knight(sq_order[sq]); 
                break;
            case Bishop:
                temp=b.mobility_bishop(sq_order[sq]);
                break;
            case Rook:
                temp=b.mobility_rook(sq_order[sq]);
                break;
            case Queen:
                temp=b.mobility_queen(sq_order[sq]);
                break;
            }
            moves.splice(moves.end(),temp);
        }
    }

    return moves;
}

// -------------------------------------------------------------------
// Determine a board's score
// -------------------------------------------------------------------
long ComputerPlayer::get_score(const ChessBoard &b) const {
    long value=0, w_score=0, b_score=0;

    // Game is won
    if (b.status==Checkmate) {
        if (b.w_turn && b.w_check || !b.w_turn && b.b_check)
            return -LONG_MAX;
        else
            return LONG_MAX;
    }
    // Game is drawn
    else if (b.status==Stalemate || b.status==TripleOccurrence ||
        b.status==FiftyMoves)
        return draw_value;

    for (int sq=a1;sq<=h8;sq++) {
        switch(b.make_neutral(b.square[sq])) {
        case Pawn:
            value=p_material +
                  p_edge_prox*(7-abs(ChessBoard::which_rank(sq)-
                  (b.is_white(b.square[sq])?7:0)));
            if (isolated_pawn(b, sq))
                value+=p_isolated[ChessBoard::which_file(sq)%4];
            if (friendly_pawns_on_file(b, sq)>1)
                value+=p_doubled;
            if (backward_pawn(b, sq))
                value+=p_backward;
            break;
        case Knight:
            value=n_material +
                  n_king_dist*manhattan(sq, b.w_king_pos) +
                  n_king_dist*manhattan(sq, b.b_king_pos) +
                  n_centre_prox*(3-chebychev(sq));
            break;
        case Bishop:
            value=b_material +
                  b_centre_prox*(3-chebychev(sq)) +
                  b_xmobility*bishop_xmobility(b, sq) +
                  b_mobility*bishop_mobility(b, sq);
            break;
        case Rook:
            value=r_material +
                  r_king_prox*(14-manhattan(sq,
                     b.is_white(b.square[sq])?b.b_king_pos:b.w_king_pos)) +
                  r_xmobility*rook_xmobility(b, sq) +
                  r_mobility*rook_mobility(b, sq);
            if (!friendly_pawns_on_file(b, sq))
                value+=r_pawns;
        case Queen:
            value=q_material +
                  q_king_prox*(7-chebychev(sq,
                     b.is_white(b.square[sq])?b.b_king_pos:b.w_king_pos)) +
                  q_centre_prox*(3-chebychev(sq));
            break;
        case King:
            value=0;
            if (!is_endgame(b))
                value+=k_centre_dist*chebychev(sq);
//              value+=k_centre_dist*(chebychev(a1)-chebychev(sq));
            if (!adjacent_friendly_pawns(b, sq))
                value+=k_pawn;
            if (b.w_turn && b.b_castled || !b.w_turn && b.w_castled)
                value+=k_castle;
            break;
        default:
            continue;
        }
        if (b.is_white(b.square[sq]))
            w_score+=value;
        else
            b_score+=value;
    }

    if (!both_bishops_present(b, true))
        w_score+=b_both;
    if (!both_bishops_present(b, false))
        b_score+=b_both;

    return b.w_turn?w_score-b_score:b_score-w_score;
}

// -------------------------------------------------------------------
// Alpha beta game tree search
// -------------------------------------------------------------------
long ComputerPlayer::alphabeta(const ChessBoard &b, long depth, long alpha,
    long beta, chessmove &chosen_move) const {
    if (depth==0)
        return get_score(b);

    move_list moves=get_all_moves(b);
    if (moves.empty())
        return get_score(b);

    long best_score=-LONG_MAX;
    chessmove best_move=*(moves.begin());
    for (move_list::iterator i=moves.begin();
        i!=moves.end() && best_score<beta; ++i) {
        ChessBoard c=b;
        c.do_move(*i);
        long value=-alphabeta(c, depth-1, -beta, 
            -(best_score>alpha?best_score:alpha), chosen_move);
        if (show_thinking && depth==ply) {
            cout << "\tMove " << *i << " SCORE: ";
            cout.width(6);
            cout << value << endl;
            cout.width(1);
        }
        if (value>best_score) {
            best_score=value;
            best_move=*i;
        }
    }
    chosen_move=best_move;
    return best_score;
}

// -------------------------------------------------------------------
// Determines whether there are adjacent friendly pawns
// -------------------------------------------------------------------
bool ComputerPlayer::adjacent_friendly_pawns(const ChessBoard &b, int sq) const {
    // List of adjacent squares
    const int adj_sq[] = {sq-Rank-File, sq-Rank, sq-Rank+File,
        sq-File, sq+File, sq+Rank-File, sq+Rank, sq+Rank+File};

    for (int i=0;i<8;i++) {
        if (b.is_on_board(adj_sq[i]) && abs(ChessBoard::which_file(sq)-
            ChessBoard::which_file(adj_sq[i]))<=1 &&
            b.square[adj_sq[i]]==(b.is_white(b.square[sq])?w_Pawn:b_Pawn))
            return true;
    }
    return false;
}

// -------------------------------------------------------------------
// Determine rook X-ray mobility
//  - returns number of squares rook may attack, including attacks
//    "through" pieces, except pawns
//  - bonus for x-ray attacks on enemy queen, rook, or king
// -------------------------------------------------------------------
long ComputerPlayer::rook_xmobility(const ChessBoard &b, int from) const {
    int to, penetrated, attacked=0;
    static const int increment[]={-Rank, Rank, -File, File};
    const int o_Queen=b.is_white(b.square[from])?b_Queen:w_Queen;
    const int o_King=b.is_white(b.square[from])?b_King:w_King;
    const int o_Rook=b.is_white(b.square[from])?b_Rook:w_Rook;
    bool attacks_qrk=false;

    for(int i=0;i<4;i++) {
        penetrated=0;
        for (to=from+increment[i]; penetrated<2 &&
             abs(ChessBoard::which_file(to)-
             ChessBoard::which_file(to-increment[i]))<=1;
             to+=increment[i]) {
            if (!b.is_on_board(to) || !b.is_dest(from, to) &&
                b.is_pawn(b.square[to]))
                break;
            attacked++;
            if ((b.square[to]==o_Queen || b.square[to]==o_King ||
                b.square[to]==o_Rook) && penetrated>0)
                attacks_qrk=true;
            if (b.square[to]!=Empty)
                penetrated++;
            if (b.is_pawn(b.square[to]))
                break;
        }
    }

    if (attacks_qrk)
        return attacked+r_xmobilitybonus;
    else
        return attacked;
}

// -------------------------------------------------------------------
// Determine rook mobility
//  - returns number of squares rook may attack
//  - bonus for attacks on enemy queen, rook, or king
// -------------------------------------------------------------------
long ComputerPlayer::rook_mobility(const ChessBoard &b, int from) const {
    int to, attacked=0;
    static const int increment[]={-Rank, Rank, -File, File};
    const int o_Queen=b.is_white(b.square[from])?b_Queen:w_Queen;
    const int o_King=b.is_white(b.square[from])?b_King:w_King;
    const int o_Rook=b.is_white(b.square[from])?b_Rook:w_Rook;
    bool attacks_qrk=false;

    for(int i=0;i<4;i++) {
        for (to=from+increment[i];
             abs(ChessBoard::which_file(to)-
                 ChessBoard::which_file(to-increment[i]))<=1;
             to+=increment[i]) {
            if (!b.is_on_board(to) || !b.is_dest(from, to))
                break;
            attacked++;
            if ((b.square[to]==o_Queen || b.square[to]==o_King ||
                b.square[to]==o_Rook))
                attacks_qrk=true;
            if (b.square[to]!=Empty)
                break;
        }
    }

    if (attacks_qrk)
        return attacked+r_xmobilitybonus;
    else
        return attacked;
}

// -------------------------------------------------------------------
// Determine bishop X-ray mobility
//  - returns number of squares bishop may attack, including attacks
//    "through" pieces, except pawns
//  - bonus for x-ray attacks on enemy queen, rook, or king
// -------------------------------------------------------------------
long ComputerPlayer::bishop_xmobility(const ChessBoard &b, int from) const {
    int to, penetrated, attacked=0;
    static const int increment[]={-Rank-File, Rank-File, -Rank+File, Rank+File};
    const int o_Queen=b.is_white(b.square[from])?b_Queen:w_Queen;
    const int o_King=b.is_white(b.square[from])?b_King:w_King;
    const int o_Rook=b.is_white(b.square[from])?b_Rook:w_Rook;
    bool attacks_qrk=false;

    for(int i=0;i<4;i++) {
        penetrated=0;
        for (to=from+increment[i]; penetrated<2 &&
             abs(ChessBoard::which_file(to)-
             ChessBoard::which_file(to-increment[i]))<=1;
             to+=increment[i]) {
            if (!b.is_on_board(to) || !b.is_dest(from, to) &&
                b.is_pawn(b.square[to]))
                break;
            attacked++;
            if ((b.square[to]==o_Queen || b.square[to]==o_King ||
                b.square[to]==o_Rook) && penetrated>0)
                attacks_qrk=true;
            if (b.square[to]!=Empty)
                penetrated++;
            if (b.is_pawn(b.square[to]))
                break;
        }
    }

    if (attacks_qrk)
        return attacked+r_xmobilitybonus;
    else
        return attacked;
}

// -------------------------------------------------------------------
// Determine bishop mobility
//  - returns number of squares bishop may attack
//  - bonus for attacks on enemy queen, rook, or king
// -------------------------------------------------------------------
long ComputerPlayer::bishop_mobility(const ChessBoard &b, int from) const {
    int to, attacked=0;
    static const int increment[]={-Rank-File, Rank-File, -Rank+File, Rank+File};
    const int o_Queen=b.is_white(b.square[from])?b_Queen:w_Queen;
    const int o_King=b.is_white(b.square[from])?b_King:w_King;
    const int o_Rook=b.is_white(b.square[from])?b_Rook:w_Rook;
    bool attacks_qrk=false;

    for(int i=0;i<4;i++) {
        for (to=from+increment[i];
             abs(ChessBoard::which_file(to)-
                 ChessBoard::which_file(to-increment[i]))<=1;
             to+=increment[i]) {
            if (!b.is_on_board(to) || !b.is_dest(from, to))
                break;
            attacked++;
            if ((b.square[to]==o_Queen || b.square[to]==o_King ||
                b.square[to]==o_Rook))
                attacks_qrk=true;
            if (b.square[to]!=Empty)
                break;
        }
    }

    if (attacks_qrk)
        return attacked+r_xmobilitybonus;
    else
        return attacked;
}

// -------------------------------------------------------------------
// Counts number of friendly pawns on same file as given square
// -------------------------------------------------------------------
int ComputerPlayer::friendly_pawns_on_file(const ChessBoard &b, int sq) const {
    int n = 0;
    const piece_type f_Pawn=b.is_white(b.square[sq])?w_Pawn:b_Pawn;
    for (int i=a1+ChessBoard::which_file(sq);i<=h8;i+=Rank)
        if (b.square[i]==f_Pawn)
            n++;
    return n;
}

// -------------------------------------------------------------------
// Returns true if the given player has both bishops (queen's and
//    king's)
// -------------------------------------------------------------------
bool ComputerPlayer::both_bishops_present(const ChessBoard &b, bool white) const {
    static const int b_square[] = {a1, a3, a5, a7, b2, b4, b6, b8, c1, c3, c5,
        c7, d2, d4, d6, d8, e1, e3, e5, e7, f2, f4, f6, f8, g1, g3, g5, g7,
        h2, h4, h6, h8};
    static const int w_square[] = {a2, a4, a6, a8, b1, b3, b5, b7, c2, c4, c6,
        c8, d1, d3, d5, d7, e2, e4, e6, e8, f1, f3, f5, f7, g2, g4, g6, g8,
        h1, h3, h5, h7};
    const piece_type f_Bishop=white?w_Bishop:b_Bishop;
    int i;
    bool found_bishop=false;

    for (i=0;i<32;i++)
        if (b.square[b_square[i]]==f_Bishop) {
            found_bishop=true;
            break;
        }

    if (found_bishop==false)
        return false;

    for (i=0;i<32;i++)
        if (b.square[w_square[i]]==f_Bishop)
            return true;

    return false;
}

// -------------------------------------------------------------------
// Determines whether a pawn is isolated
// -------------------------------------------------------------------
bool ComputerPlayer::isolated_pawn(const ChessBoard &b, int sq) const {
    const piece_type f_Pawn=b.is_white(b.square[sq])?w_Pawn:b_Pawn;
    int i;
    if (ChessBoard::which_file(sq)>0)
        for (i=a1+ChessBoard::which_file(sq)-1;i<=h8;i+=Rank)
            if (b.is_on_board(i) && b.square[i]==f_Pawn)
                return false;
    if (ChessBoard::which_file(sq)<7)
        for (i=a1+ChessBoard::which_file(sq)+1;i<=h8;i+=Rank)
            if (b.is_on_board(i) && b.square[i]==f_Pawn)
                return false;
    return true;
}

// -------------------------------------------------------------------
// Determines whether the given pawn is backward
//  - a backward pawn is one whose advance is restrained by an
//    opposing pawn on an adjacent file, and which has no friendly
//    pawn to support that advance.
// -------------------------------------------------------------------
bool ComputerPlayer::backward_pawn(const ChessBoard &b, int sq) const {
    const piece_type f_Pawn=b.is_white(b.square[sq])?w_Pawn:b_Pawn;
    const piece_type o_Pawn=b.is_white(b.square[sq])?b_Pawn:w_Pawn;
    const int ahead=b.is_white(b.square[sq])?1:-1;

    // Make sure pawn can advance
    int temp=sq+ahead*Rank;
    if (!b.is_on_board(temp) || b.square[temp]!=Empty)
        return false;

    // Is pawn advance attacked?
    temp+=ahead*Rank;
    if (!(b.is_on_board(temp+File) && b.square[temp+File]==o_Pawn ||
          b.is_on_board(temp-File) && b.square[temp-File]==o_Pawn))
        return false;

    // Is pawn advance supported?
    temp=sq-File;
    if (!b.is_on_board(temp) || b.square[temp]==f_Pawn)
        return false;
    temp=sq+File;
    if (!b.is_on_board(temp) || b.square[temp]==f_Pawn)
        return false;

    return true;
}

// -------------------------------------------------------------------
// Determines whether the board is in endgame
// -------------------------------------------------------------------
bool ComputerPlayer::is_endgame(const ChessBoard &b) const {
    long value=0;
    for (int i=a1;i<=h8;i++)
        switch (b.make_neutral(b.square[i])) {
        case Pawn:
            value+=p_material;
            break;
        case Knight:
            value+=n_material;
            break;
        case Bishop:
            value+=b_material;
            break;
        case Queen:
            value+=q_material;
            break;
        case Rook:
            value+=r_material;
            break;
        }

    if (value<=endgame_threshold)
        return true;
    else
        return false;
}
