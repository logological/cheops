// $Id: HumanPlayer.cpp,v 1.3 2003-12-06 16:44:51 psy Exp $
//
// HumanPlayer.cpp: implementation of the HumanPlayer class.
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

#include "stdafx.h"
#include "HumanPlayer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HumanPlayer::HumanPlayer() {
    human=true;
}

HumanPlayer::~HumanPlayer() {

}

// -------------------------------------------------------------------
// Get command from user
// -------------------------------------------------------------------
string HumanPlayer::get_command(const ChessBoard &b) const {
    string cmd;
    cout << "\nCommand: ";
    cin >> cmd;
    return cmd;
}

// -------------------------------------------------------------------
// Set stats
// -------------------------------------------------------------------
void HumanPlayer::set_stats(void) {
    // Nothing to set... yet. Maybe in a future version this place will
    // store the player's name, rating, etc.
    return;
}
