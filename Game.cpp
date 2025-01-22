#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Game.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

Card::Card(int value) {
    this->value = value;
    this->isFaceUp = false;
    this->isRemoved = false;
}

Card::~Card() { /*std::cout << "Card destructor called." << std::endl;*/ }

int Card::getValue() const {
    return value;
}
void Card::setValue(int value) {
    this->value = value;
}
bool Card::getIsFaceUp() const {
    return isFaceUp;
}
void Card::setIsFaceUp(bool isFaceUp) {
    this->isFaceUp = isFaceUp;

}

bool Card::getIsRemoved() const {
    return isRemoved;
}

void Card::setIsRemoved(bool isRemoved)
{
    this->isRemoved = isRemoved;
}

StandardCard::StandardCard(int value): Card(value) {}
StandardCard::~StandardCard() { /*std::cout << "StandardCard destructor called." << std::endl;*/ }
void StandardCard::display() {
    if (getIsRemoved()) {
        cout << " ";
    } else if (getIsFaceUp()) {
        cout << getValue();
    } else {
        cout << "*";
    }
}

BonusCard::BonusCard() :  Card(7){}

BonusCard::~BonusCard(){ /*std::cout << "BonusCard destructor called." << std::endl;*/ }
void BonusCard::display() {
    if (getIsRemoved()) {
        cout << " ";
    } else if (getIsFaceUp()) {
        cout << "B";
    } else {
        cout << "*";
    }
}

PenaltyCard::PenaltyCard():Card(8){}

PenaltyCard::~PenaltyCard() { /*std::cout << "PenaltyCard destructor called." << std::endl;*/ }
void PenaltyCard::display() {
    if (getIsRemoved()) {
        cout << " ";
    } else if (getIsFaceUp()) {
        cout << "P";
    } else {
        cout << "*";
    }
}

Player::Player(const string& name) {
    this->name = name ;
    score = 0;
}

Player::~Player(){ /*std::cout << "Player destructor called." << std::endl;*/ }
string Player::getName() const{
    return name;
}
int Player::getScore() const {
    return score;
}
void Player::setName(const string& name) {
    this->name = name;
}
void Player::setScore(int score) {
    this->score = score;
}
void Player::displayScore() const {
cout << "Player: " << this->getName() << ", Score: " << this->getScore() << endl;
}

Deck::Deck() {
    grid = new Card*[16];
    int  values[16] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8};
    for (int i = 0; i < 16; i++) {
            if (values[i] <= 6) {
                grid[i] = new StandardCard(values[i]);
            } else if (values[i] == 7) {
                grid[i] = new BonusCard();
            } else if (values[i] == 8) {
                grid[i] = new PenaltyCard();
            }

        }
}

Deck::~Deck() {
    for (int i = 0; i < 16; ++i) {
        delete grid[i]; // Delete each dynamically allocated Card
    }
    delete[] grid; // Deallocate the array of pointers
    // std::cout << "Deck destructor called." << std::endl;
}

Card** Deck::getGrid() const {
    return grid;
}

void Deck::setGrid(Card** grid) {
    this->grid =grid;
}

void Deck::shuffle() {
    // We Used the Fisher-Yates algorithm to shuffle the deck
    srand(time(0));
    for (int i = 16-1 ; i > 0; --i) {
        int j = rand() % (i + 1); // Random index from 0 to i
        swap(grid[i], grid[j]);
    }
}

void Deck::displayGrid() const {
    for (int i = 0; i < 16; ++i) {
        {
            grid[i]->display();
        }
        if ((i + 1) % 4 == 0) {
            cout << endl; // New line after every 4 cards
        } else {
            cout << " "; // Space between every other card
        }
    }
}

Game::Game()
{
    this->p1=new Player("Player 1");
    this->p2= new Player("Player 2");
    this->d = new Deck();
    this->initializeGame();
    this->playGame();
}
Game::~Game()
{
    delete p1;
    delete p2;
    delete d;
    //std::cout << "Game destructor called." << std::endl;
}
Player* Game::getPlayer1() const
{
    return p1;
}
Player* Game::getPlayer2() const
{
    return p2;
}
Deck* Game::getDeck() const
{
    return d;
}
void Game::setDeck(Deck* d) {
    this->d = d;
}
void Game::setPlayer1(Player* p1) {
    this->p1 = p1;
}
void Game::setPlayer2(Player* p2) {
    this->p2 = p2;
}
void Game::initializeGame() {
    cout<<endl << "Enter name for Player 1 :  ";
    string name1;
    cin >> name1;
    this->p1->setName(name1);

    cout << "Enter name for Player 2 :  ";
    string name2;
    cin >> name2;
    this->p2->setName(name2);

    cout<<endl<< "Deck Before Shuffling" << endl<<endl;
    for(int i = 0; i < 16; i++)
    {
        d->getGrid()[i]->setIsFaceUp(true);
    }

    this->d->displayGrid();

    for(int i = 0; i < 16; i++)
    {
        d->getGrid()[i]->setIsFaceUp(false);
    }

    this->d->shuffle();
    cout<<endl<< "Deck is Shuffled" << endl<<endl;
    this->d->displayGrid();

    cout <<endl<< "The game is ready! Let's start." << endl;

}

void Game::playGame() {
    bool gameRunning = true;
    Player* currentPlayer = p1;
    Player* skipPlayer = nullptr;//Handles if player chooses penalty : skip next turn
    int turn = 1;

    while (gameRunning) {
        cout<<"\n======================================================"<<endl;
        cout << "\nTurn " << turn++ << " || Player 1: " << p1->getName() << " , Score: " << p1->getScore() << " || Player 2: " << p2->getName() << " , Score: " << p2->getScore() << endl;

        if (skipPlayer == currentPlayer) {
            cout << "\n" << currentPlayer->getName() << " skips this turn due to a penalty.\n";
            skipPlayer = nullptr;
            currentPlayer = (currentPlayer == p1) ? p2 : p1;
            continue;
        }

        cout << "\nCurrent Turn: " << currentPlayer->getName() << "\n";
        d->displayGrid();

        int x1, y1, x2, y2;

        cout << "\nEnter row and column of the first card : ";
        cin >> x1 >> y1;

        cout << "Enter row and column of the second card : ";
        cin >> x2 >> y2;


            while (x1 < 1 || x1 > 4 || y1 < 1 || y1 > 4 || x2 < 1 || x2 > 4 || y2 < 1 || y2 > 4 || (x1 == x2 && y1 == y2) ) {
                if (x1 < 1 || x1 > 4 || y1 < 1 || y1 > 4 || x2 < 1 || x2 > 4 || y2 < 1 || y2 > 4) {
                    cout << endl << "Invalid coordinates! Please enter values between 1 and 4 for both rows and columns.\n";
                }
                else {
                    cout << endl << "You selected the same card twice. Please choose two different cards.\n";
                }
                cout << "\nEnter row and column of the first card : ";
                cin >> x1 >> y1;
                cout << "Enter row and column of the second card : ";
                cin >> x2 >> y2;
            }

        int index1 = (x1 - 1) * 4 + (y1 - 1);
        int index2 = (x2 - 1) * 4 + (y2 - 1);
        Card* card1 = d->getGrid()[index1];
        Card* card2 = d->getGrid()[index2];

        while (card1->getIsRemoved() || card2->getIsRemoved()) {
            cout << "\nOne or both of the selected cards have already been removed. Please try again.\n";
            cout << "\nEnter row and column of the first card : ";
            cin >> x1 >> y1;
            cout << "Enter row and column of the second card : ";
            cin >> x2 >> y2;
            while (x1 < 1 || x1 > 4 || y1 < 1 || y1 > 4 || x2 < 1 || x2 > 4 || y2 < 1 || y2 > 4 || (x1 == x2 && y1 == y2) ) {
                if (x1 < 1 || x1 > 4 || y1 < 1 || y1 > 4 || x2 < 1 || x2 > 4 || y2 < 1 || y2 > 4) {
                    cout << endl << "Invalid coordinates! Please enter values between 1 and 4 for both rows and columns.\n";
                }
                else {
                    cout << endl << "You selected the same card twice. Please choose two different cards.\n";
                }
                cout << "\nEnter row and column of the first card : ";
                cin >> x1 >> y1;
                cout << "Enter row and column of the second card : ";
                cin >> x2 >> y2;
            }
            index1 = (x1 - 1) * 4 + (y1 - 1);
            index2 = (x2 - 1) * 4 + (y2 - 1);
            card1 = d->getGrid()[index1];
            card2 = d->getGrid()[index2];
        }

        card1->setIsFaceUp(true);
        card2->setIsFaceUp(true);

        cout << endl;
        d->displayGrid();


        bool turnContinues = false;
        if (card1->getValue() == 7 && card2->getValue() == 7) {
            cout << "\nBoth cards are Bonus Cards! Choose an option:\n";
            cout << "1. Gain +2 points.\n";
            cout << "2. Gain +1 point and take another turn.\n";

            int choice;
            while (true) {
                cin >> choice;
                if (choice == 1) {
                    currentPlayer->setScore(currentPlayer->getScore() + 2);
                    break;
                } else if (choice == 2) {
                    currentPlayer->setScore(currentPlayer->getScore() + 1);
                    turnContinues = true;
                    break;
                } else {
                    cout << "\nInvalid Option, Please Choose 1 or 2:\n";
                    cout << "1. Gain +2 points.\n";
                    cout << "2. Gain +1 point and take another turn.\n";
                }
            }
            card1->setIsRemoved(true);
            card2->setIsRemoved(true);
        } else if (card1->getValue()==8 && card2->getValue()==8) {
            cout << "\nBoth cards are Penalty Cards! Choose an option:\n";
            cout << "1. Lose 2 points.\n";
            cout << "2. Lose 1 point and skip the next turn.\n";
            int choice;
            while (true) {
                cin >> choice;
                if (choice == 1) {
                    currentPlayer->setScore(currentPlayer->getScore() - 2);
                    break;
                } if (choice == 2) {
                    currentPlayer->setScore(currentPlayer->getScore() - 1);
                    skipPlayer = currentPlayer;
                    break;
                } else {
                    cout << "\nInvalid Option, Please Choose 1 or 2:\n";
                    cout << "1. Lose 2 points.\n";
                    cout << "2. Lose 1 point and skip the next turn.\n";
                }
            }
            card1->setIsRemoved(true);
            card2->setIsRemoved(true);
        } else if ((card1->getValue()==7 && card2->getValue()==8 ) ||
                   (card1->getValue()==8 && card2->getValue()==7)) {
            cout << "\nA Bonus Card and a Penalty Card were revealed. They cancel out.\n";
            card1->setIsRemoved(true);
            card2->setIsRemoved(true);
        } else if (card1->getValue()==7 || card2->getValue()==7) {
            cout << "\nA Bonus Card and a Standard Card were revealed. You gain +1 point.\n";
            currentPlayer->setScore(currentPlayer->getScore() + 1);

            if (card1->getValue()==7) card1->setIsRemoved(true);
            if (card2->getValue()==7) card2->setIsRemoved(true);
        } else if (card1->getValue()==8 || card2->getValue()==8)
        {
            cout << "\nA Penalty Card and a Standard Card were revealed. You lose -1 point.\n";
            currentPlayer->setScore(currentPlayer->getScore() - 1);

            if (card1->getValue()==8) card1->setIsRemoved(true);
            if (card2->getValue()==8) card2->setIsRemoved(true);
        }else if (((card1->getValue()<=6)&& (card2->getValue()<=6))&&
                   card1->getValue() == card2->getValue()) {
            cout << "\nIt's a match! You gain +1 point and play again\n";
            currentPlayer->setScore(currentPlayer->getScore() + 1);
            turnContinues = true;
            card1->setIsRemoved(true);
            card2->setIsRemoved(true);
        } else {
            cout << "\nNo match. The cards will be flipped back.\n";
        }

        cout<<"\nPress Enter to continue...";
        cin.ignore(); cin.get();

        if (!card1->getIsRemoved()) card1->setIsFaceUp(false);
        if (!card2->getIsRemoved()) card2->setIsFaceUp(false);



        bool allMatched = true;
        for (int i = 0; i < 16; ++i) {
            if (d->getGrid()[i] && !d->getGrid()[i]->getIsRemoved()) {
                allMatched = false;
                break;
            }
        }
        if (allMatched) {
            cout<<endl;
            cout<<"======================================================"<<endl;
            cout <<endl<< "\nGame Over! All cards have been matched.\n";
            cout << "Final Scores:\n";
            p1->displayScore();
            p2->displayScore();

            if (p1->getScore() > p2->getScore()) {
                cout << "\nWinner: " << p1->getName() << "! Congratulations!\n";
            } else if (p2->getScore() > p1->getScore()) {
                cout << "\nWinner: " << p2->getName() << "! Congratulations!\n";
            } else {
                cout << "\nIt's a tie! Great game!\n";
            }

            gameRunning = false;
            continue;
        }

        // Switch turn if the player doesn't play again
        if (!turnContinues) {
            currentPlayer = (currentPlayer == p1) ? p2 : p1;
        }
    }
}

int main() {
    Game g ;
    return 0 ;
}



/*int main()
{
   Game g ;

    /*
    // For Testing Purposes

    // 1) Flip all cards face-up

    Deck* deck = g.getDeck();

    cout<<endl<< "Deck with all cards face-up:" << endl;
    Card** grid = deck->getGrid();
    for (int i = 0; i < 16; ++i) {
            grid[i]->setIsFaceUp(true);
    }
    //after 1st shuffle(automatically happens when initializing the game)
    deck->displayGrid();

    //2) Shuffle the deck
    deck->shuffle();
    //after 2nd shuffle
    cout<<endl<< "Deck after shuffling:" << endl;
    deck->displayGrid();

    //3) Testing player class
    g.getPlayer1()->setScore(10);
    g.getPlayer2()->setScore(20);
    g.getPlayer1()->displayScore();
    g.getPlayer2()->displayScore();
    g.getPlayer1()->setName("Player 1");
    g.getPlayer2()->setName("Player 2");
    g.getPlayer1()->displayScore();
    g.getPlayer2()->displayScore();

    // 4) Flip all cards face-down

        for (int i = 0; i < 16; ++i) {
            grid[i]->setIsFaceUp(false);
        }
        cout << endl << "Deck with all cards face-down:" << endl;
        deck->displayGrid();

    // 5) Test setting and getting card values
        cout << endl << "Testing card values:" << endl;
        for (int i = 0; i < 16; ++i) {
            cout << "Card " << i + 1 << " value: " << grid[i]->getValue() << endl;
        }
    cout<<endl;
    #1#

return 0 ;
}*/
