// ChessTypes.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHESSTYPES_H__EBEFC225_5256_11D3_BC7B_0080C84DB68D__INCLUDED_)
#define AFX_CHESSTYPES_H__EBEFC225_5256_11D3_BC7B_0080C84DB68D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum game_status {
    Normal, Check, Checkmate, Stalemate, TripleOccurrence, FiftyMoves
};

enum piece_type {
    Empty=0,
        Pawn=1, Knight=2, Bishop=4, Rook=8, Queen=16, King=32,
    White=0,
        w_Pawn=Pawn+White, w_Knight=Knight+White, w_Bishop=Bishop+White,
        w_Rook=Rook+White, w_Queen=Queen+White,   w_King=King+White,
    Black=64,
        b_Pawn=Pawn+Black, b_Knight=Knight+Black, b_Bishop=Bishop+Black,
        b_Rook=Rook+Black, b_Queen=Queen+Black,   b_King=King+Black
};

enum square_type {
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8,
    Rank=8, File=1, No_square=-100
};

#endif // !defined(AFX_CHESSTYPES_H__EBEFC225_5256_11D3_BC7B_0080C84DB68D__INCLUDED_)
