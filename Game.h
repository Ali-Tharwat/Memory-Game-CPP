//
// Created by Michael Danial on 16/11/2024.
//

#ifndef GAME_H
#define GAME_H

using namespace std;

class Game {
    private :

    Player* p1;
    Player* p2;
    Deck* d;

    public :

    Player* getPlayer1() const;
    void setPlayer1(Player* p1);
    Player* getPlayer2() const;
    void setPlayer2(Player* p2);
    Deck* getDeck() const;
    void setDeck(Deck* d);

    Game();
    ~Game();

    void initializeGame();
    void playGame();
};

#endif