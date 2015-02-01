// $Id$
//
// Player.h: interface for the Player class.
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

#if !defined(AFX_PLAYER_H__EBEFC220_5256_11D3_BC7B_0080C84DB68D__INCLUDED_)
#define AFX_PLAYER_H__EBEFC220_5256_11D3_BC7B_0080C84DB68D__INCLUDED_

#include "ChessBoard.h"

class Player {
public:
    bool human;
    virtual string get_command(const ChessBoard &b) const = 0;
    Player();
    virtual ~Player();
    virtual void set_stats(void) = 0;
};

#endif // !defined(AFX_PLAYER_H__EBEFC220_5256_11D3_BC7B_0080C84DB68D__INCLUDED_)
