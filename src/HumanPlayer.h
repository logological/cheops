//
// HumanPlayer.h: interface for the HumanPlayer class.
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

#if !defined(AFX_HUMANPLAYER_H__EBEFC221_5256_11D3_BC7B_0080C84DB68D__INCLUDED_)
#define AFX_HUMANPLAYER_H__EBEFC221_5256_11D3_BC7B_0080C84DB68D__INCLUDED_

#include "Player.h"

class HumanPlayer : public Player  
{
public:
    string get_command(const ChessBoard &b) const;
    HumanPlayer();
    virtual ~HumanPlayer();
    void set_stats(void);
};

#endif // !defined(AFX_HUMANPLAYER_H__EBEFC221_5256_11D3_BC7B_0080C84DB68D__INCLUDED_)
