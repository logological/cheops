// HumanPlayer.h: interface for the HumanPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HUMANPLAYER_H__EBEFC221_5256_11D3_BC7B_0080C84DB68D__INCLUDED_)
#define AFX_HUMANPLAYER_H__EBEFC221_5256_11D3_BC7B_0080C84DB68D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
