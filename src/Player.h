// Player.h: interface for the Player class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYER_H__EBEFC220_5256_11D3_BC7B_0080C84DB68D__INCLUDED_)
#define AFX_PLAYER_H__EBEFC220_5256_11D3_BC7B_0080C84DB68D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
