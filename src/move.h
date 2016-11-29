// $Id$
//
// move.h: interface for the chessmove struct.
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

#if !defined(AFX_MOVE_H__EBEFC224_5256_11D3_BC7B_0080C84DB68D__INCLUDED_)
#define AFX_MOVE_H__EBEFC224_5256_11D3_BC7B_0080C84DB68D__INCLUDED_

#include "ChessTypes.h"

struct chessmove {
    int from;
    int to;
    piece_type promotion;
    operator string() const;
};

typedef list<chessmove> move_list;

ostream &operator<<(ostream &os, const chessmove &m);

#endif // !defined(AFX_MOVE_H__EBEFC224_5256_11D3_BC7B_0080C84DB68D__INCLUDED_)
