// cheops.cpp : Defines the entry point for the console application.
//
// 14/08/1999: v0.99
// 28/05/2000: v1.00
// 18/02/2002: v1.01

#include "stdafx.h"
#include "ChessBoard.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <cstdio>

void show_menu(void);
move *parse_move(const string& s);
void who_plays(Player *&w, Player *&b);

int main(int argc, char* argv[]) {

    ChessBoard c;
    Player *w_player=NULL, *b_player=NULL, *this_player;
    string cmd, log;
    game_status status=Normal;
    move *m = NULL;
    int turn=0;

    // Print title screen
    cout << "\t\t\t__   __\n"
            "\t\t\t\\ \\ / /      Cheops v1.0\n"
            "\t\t\t \\ v / ___ ___  _  _  _\n"
            "\t\t\t  > < / __) _ \\| || || |\n"
            "\t\t\t / ^ \\> _| (_) ) \\| |/ |\n"
            "\t\t\t/_/ \\_\\___)___/ \\_   _/\n"
            "\t\t\t _________________| |__\n"
            "\t\t\t(_________________|_|__)\n\n"
            "\t\t\tCopyright (C) 1999, 2000 Tristan Miller\n"
            "\t\t\thttp://www.nothingisreal.com/cheops/\n\n";

    who_plays(w_player, b_player);

    cout << "\nEnter \"help\" or \"?\" for the menu.\n" << c;

    // Main loop
    while (1) {
        cout.flush();
        this_player=c.white_moves()?w_player:b_player;
        cmd=this_player->get_command(c);

        if (cmd=="board" || cmd=="bd")
            cout << c;
        else if (cmd=="reverse")
            c.show_reverse=!c.show_reverse;
        else if (cmd=="coords")
            c.show_coordinates=!c.show_coordinates;
        else if (cmd=="think")
            ComputerPlayer::show_thinking=!ComputerPlayer::show_thinking;
        else if (cmd=="help" || cmd=="?")
            show_menu();
        else if (cmd=="who")
            who_plays(w_player, b_player);
        else if (cmd=="save") {
            ofstream logfile("cheops.log");
            logfile << log << endl;
            logfile.close();
        }
        else if (cmd=="new") {
            c=ChessBoard();
            turn=0;
            log=string();
        }
        else if (cmd=="quit" || cmd=="exit")
            break;
        else if (cmd=="log")
            cout << log << endl;
        else if (cmd=="resign") {
            cout << "You resign. " << (c.white_moves()?"Black":"White") << 
                " wins!\n";
            c.in_progress=false;
        }
        else {
            delete m;
            // Kingside castling
            if (cmd=="o-o") {
                m = new move;
                m->promotion=Empty;
                m->from=this_player==w_player?e1:e8;
                m->to=this_player==w_player?g1:g8;
            }
            // Queenside castling
            else if (cmd=="o-o-o") {
                m = new move;
                m->promotion=Empty;
                m->from=this_player==w_player?e1:e8;
                m->to=this_player==w_player?c1:c8;
            }
            // Regular move
            else
                m=parse_move(cmd);
            if (c.in_progress && (!this_player->human || m && c.can_move(*m))) {
                status=c.do_move(*m);
                cout << c;

                // Update board log
                if (turn%2==0) {
                    char tmp[6];
                    sprintf(tmp,"%2d. ",turn/2+1);
                    log+=tmp;
                    log+=*m;
                }
                else {
                    log+='\t';
                    log+=*m;
                    log+='\n';
                }
                turn++;

                // Display board status
                switch (status) {
                case Checkmate:
                    cout << "Checkmate!\n";
                    break;
                case Stalemate:
                    cout << "Stalemate!\n";
                    break;
                case TripleOccurrence:
                    cout << "Triple occurrence -- game is drawn.\n";
                    break;
                case FiftyMoves:
                    cout << "Fifty move rule -- game is drawn.\n";
                case Check:
                    cout << "Check!\n";
                    break;
                }
            }
            else
                cout << "Illegal move\n";
        }
    }

    return 0;
}

// -------------------------------------------------------------------
// Display the menu
// -------------------------------------------------------------------
void show_menu(void) {
    cout << "\nCHEOPS command summary\n";
    cout << "---------------------------------------------------------\n";
    cout << "a1b3\tmove from a1 to b3\n";
    cout << "a7a8n\tpromote pawn to knight\n";
    cout << "o-o\tcastle king-side\n";
    cout << "o-o-o\tcastle queen-side\n";
//  cout << "draw\toffer/force draw\n";
    cout << "resign\tresign\n";
    cout << "bd\tredisplay board\n";
    cout << "coords\ttoggle coordinates\n";
    cout << "reverse\treverse board display\n";
    cout << "think\ttoggle display of computer thinking\n";
    cout << "log\tlog of moves\n";
    cout << "save\tsave log to cheops.log\n";
    cout << "new\tnew game\n";
    cout << "who\twho plays (modify current players)\n";
    cout << "quit\tquit program\n";
    cout << "---------------------------------------------------------\n";
}

// -------------------------------------------------------------------
// Parse move
//  - returns pointer to a move structure on success, else NULL
// -------------------------------------------------------------------
move *parse_move(const string& s) {

    // Is this a valid move string?
    int len=s.length();
    if (len>5 || len<4 || s[0]<'a' || s[0]>'h' || s[2]<'a' ||
        s[2]>'h' || s[1]<'1' || s[1]>'8' || s[3]<'1' || s[3]>'8')
        return NULL;
    if (len==5 && !strchr("qrnb", s[4]))
        return NULL;

    // Determine promotion type
    move *m = new move;
    if (len==5) {
        switch(s[4]) {
        case 'q':
            m->promotion=Queen;
            break;
        case 'r':
            m->promotion=Rook;
            break;
        case 'n':
            m->promotion=Knight;
            break;
        case 'b':
            m->promotion=Bishop;
            break;
        }
    }
    else 
        m->promotion=Empty;

    // Determine source and destination squares
    m->from=s[0]-'a'+(s[1]-'1')*8;
    m->to=s[2]-'a'+(s[3]-'1')*8;

    return m;
}

// -------------------------------------------------------------------
// Set players
// -------------------------------------------------------------------
void who_plays(Player *&w, Player *&b) {
    string s;
    while (s!="c" && s!="h") {
        cout << "White [c]omputer or [h]uman? ";
        cin >> s;
        cout << endl;
    }
    if (s=="h") {
        if (!(w && w->human==true)) {
            delete w;
            w = new HumanPlayer;
        }
    }
    else {
        if (!(w && w->human==false)) {
            delete w;
            w = new ComputerPlayer;
        }
        else
            w->set_stats();
    }

    s=string();
    while (s!="c" && s!="h") {
        cout << "Black [c]omputer or [h]uman? ";
        cin >> s;
        cout << endl;
    }
    if (s=="h") {
        if (!(b && b->human==true)) {
            delete b;
            b = new HumanPlayer;
        }
    }
    else {
        if (!(b && b->human==false)) {
            delete b;
            b = new ComputerPlayer;
        }
        else
            b->set_stats();
    }
}
