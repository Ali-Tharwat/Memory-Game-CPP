cmake_minimum_required(VERSION 3.29)
project(CardsGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(CardsGame
        Card.h
        Game.h
        Deck.h
        Player.h

        Game.cpp
)
