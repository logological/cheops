// $Id: HumanPlayer.cpp,v 1.2 2003-11-24 21:10:45 psy Exp $
//
// HumanPlayer.cpp: implementation of the HumanPlayer class.
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
