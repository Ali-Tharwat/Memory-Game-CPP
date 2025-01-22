#ifndef CARD_H
#define CARD_H

class Card {
    private :
    int value;
    bool isFaceUp;
    bool isRemoved;
public:
    int getValue() const;
    void setValue(int value);
    void setIsFaceUp(bool isFaceUp);
    bool getIsFaceUp() const;
    void setIsRemoved(bool isRemoved);
    bool getIsRemoved() const;

    Card(int value);
    virtual ~Card();

    virtual void display() = 0 ;
};

class StandardCard : public Card {
    public :

    StandardCard(int value);
    ~StandardCard() ;

    void display() override;
};

class BonusCard : public Card {
    public :

    BonusCard();
    ~BonusCard();

    void display() override;
};
class PenaltyCard : public Card {
    public :

    PenaltyCard();
    ~PenaltyCard();

    void display() override;
};
#endif