// $Id: move.h,v 1.2 2003-11-24 21:14:42 psy Exp $
//
// move.h: interface for the move struct.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVE_H__EBEFC224_5256_11D3_BC7B_0080C84DB68D__INCLUDED_)
#define AFX_MOVE_H__EBEFC224_5256_11D3_BC7B_0080C84DB68D__INCLUDED_

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
