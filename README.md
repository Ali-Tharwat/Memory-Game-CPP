# 🃏 Memory MatchCard Game

A console-based C++ implementation of the classic **Memory MatchCard Game**, developed using object-oriented programming principles.

## 🎯 Objective

This project aims to simulate the memory card game where **two players** take turns flipping cards on a 4x4 board, attempting to find matching pairs. It incorporates both standard and special cards (bonus & penalty), enhancing the game’s logic and strategy.

## 🛠️ Tech Stack

This project was developed using C++  ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge\&logo=c%2B%2B\&logoColor=white) and built in CLion  ![Clion](https://img.shields.io/badge/CLion-000000?style=for-the-badge&logo=clion&logoColor=black&color=black&labelColor=deeppink)

## 🎮 Game Rules

* **Players:** 2
* **Board:** 4x4 grid
* **Card Types:**
  
  * ✱ **Standard Cards (1–6):** Regular cards
  * **𝐁** **Bonus Cards (x2):** Gain a point or take an extra turn
  * **𝐏** **Penalty Cards (x2):** Lose a point or skip a turn

### 🔁 Turn Flow:

* A player flips two cards.
* If matched ➤ gain a point and another turn.
* If not ➤ cards are flipped back, and the other player plays.

### 🏁 Endgame:

* The game ends when all cards are matched.
* The player with the most points wins.

## 🌟 Features

* 📦 Card & Deck Management
* 🧍‍♂️ Player Scoring System
* 🔄 Turn Management
* 🎯 Special Card Effects
* 🏆 Winner Declaration

## 📦 Setup & Run

1. Open the project in **CLion**
2. Run the Game.cpp
3. Play the game via the console
