// move.h: interface for the move struct.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVE_H__EBEFC224_5256_11D3_BC7B_0080C84DB68D__INCLUDED_)
#define AFX_MOVE_H__EBEFC224_5256_11D3_BC7B_0080C84DB68D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChessTypes.h"

struct move {
    int from;
    int to;
    piece_type promotion;
    operator string() const;
};

typedef list<move> move_list;

ostream &operator<<(ostream &os, const move &m);

#endif // !defined(AFX_MOVE_H__EBEFC224_5256_11D3_BC7B_0080C84DB68D__INCLUDED_)
