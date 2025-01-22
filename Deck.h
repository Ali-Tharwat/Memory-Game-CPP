//
// Created by Huawei on 11/19/2024.
//

#ifndef DECK_H
#define DECK_H
class Deck {
    private :
    Card** grid; // Pointer to a dynamically allocated array of Card pointers

    public :
        Card** getGrid() const;
        void setGrid(Card** grid) ;

        Deck();
        ~Deck();

        void shuffle();
        void displayGrid() const;
};

#endif //DECK_H