//
// Created by Huawei on 11/20/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;

class Player {
    private :

    string name;
    int score;

    public :

    string getName() const;
    void setName(const string& name);
    int getScore() const;
    void setScore(int score);

    Player(const string& name);
    ~Player();

    void displayScore() const;

};
#endif //PLAYER_H
