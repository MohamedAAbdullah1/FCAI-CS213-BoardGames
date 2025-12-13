# CS213 Board Games Collection 🎮

A comprehensive **C++ Object-Oriented board games application** built as part of **CS213 – Object Oriented Programming (Programming II)** at the **Faculty of Computers & Artificial Intelligence, Cairo University**.

This repository integrates **multiple Tic-Tac-Toe variants and board games** into **one unified application** using a reusable OOP framework.

---

## 📌 Project Overview

The goal of this project is to demonstrate strong understanding of:

* Object-Oriented Programming (OOP)
* Inheritance & Polymorphism
* Templates & STL
* Code reuse & extensibility (Open/Closed Principle)
* Team collaboration using Git & GitHub

All games are built on top of a **generic Board Game Framework** and launched through a **single menu-driven application**.

---

## 🧩 Implemented Games

### 🔹 Individual & Group Games

| #  | Game Name                       |
| -- | ------------------------------- |
| 1  | SUS                             |
| 2  | Four-in-a-row                   |
| 3  | 5 × 5 Tic Tac Toe               |
| 4  | Word Tic-Tac-Toe                |
| 5  | Misère Tic Tac Toe              |
| 6  | Diamond Tic-Tac-Toe             |
| 7  | 4 × 4 Tic-Tac-Toe               |
| 8  | Pyramid Tic-Tac-Toe             |
| 9  | Numerical Tic-Tac-Toe *(Group)* |
| 10 | Obstacles Tic-Tac-Toe *(Group)* |
| 11 | Infinity Tic-Tac-Toe *(Group)*  |
| 12 | Ultimate Tic Tac Toe *(Bonus)*  |
| 13 | Memory Tic-Tac-Toe *(Bonus)*    |

---

## 🏗️ Project Structure

```
├── BoardGame_Classes.h     # Core framework (Board, Player, UI, GameManager)
├── Game_Runners.h/.cpp    # Game launcher & menu
├── main.cpp               # Application entry point
├── XO/                    # Classic Tic-Tac-Toe example
├── 1. SUS/
├── 2. Four-in-a-row/
├── 3. 5 x 5 Tic Tac Toe/
├── 4. Word Tic-tac-toe/
├── 5. Misère Tic Tac Toe/
├── 6. Diamond Tic-Tac-Toe/
├── 7. 4 x 4 Tic-Tac-Toe/
├── 8. Pyramid Tic-Tac-Toe/
├── 9. Numerical Tic-Tac-Toe/
├── 10. Obstacles Tic-Tac-Toe/
├── 11. Infinity Tic-Tac-Toe/
├── 12. Ultimate Tic Tac Toe/
├── 13. Memory Tic-Tac-Toe/
├── dic.txt                # Dictionary for Word Tic-Tac-Toe
└── README.md
```

---

## ⚙️ Framework Architecture

The project is built on a **generic template-based framework**:

* **Board<T>** *(abstract)* – Game board & rules
* **Move<T>** – Represents a single move
* **Player<T>** – Human or Computer player
* **UI<T>** *(abstract)* – Handles input/output
* **GameManager<T>** – Controls game flow *(not modified)*

Each game:

* Inherits from `Board<T>`
* Uses or extends `Player<T>` and `UI<T>`
* Implements its own rules without modifying the framework

✔ Fully follows the **Open/Closed Principle**

---

## 🧠 AI Players (Bonus)

Some games include **smart computer players** using:

* Minimax
* Backtracking
* Heuristic-based decision making

Instead of random moves, AI players analyze the board to choose optimal actions.

---

## ▶️ How to Run

### Requirements

* C++17 or later
* Any standard compiler (g++, clang, MSVC)

### Compile

```bash
g++ -std=c++17 main.cpp Game_Runners.cpp -o BoardGames
```

### Run

```bash
./BoardGames
```

You will be presented with a **menu** to choose and play any available game.

---

## 📄 Documentation

* The project supports **Doxygen documentation**
* HTML docs can be generated for all classes and APIs

```bash
doxygen Doxyfile
```

---

## 👥 Contributors

* **Mohamed A. Abdullah**
* **Mohamed Ashraf**
* **Malik Mohamed Ali**
* **Msiefi41**

---

## 🎓 Course Information

* **Course:** CS213 – Object Oriented Programming
* **Faculty:** Computers & Artificial Intelligence
* **University:** Cairo University
* **Instructor:** Dr. Mohammad El-Ramly
* **Semester:** First Semester 2025–2026

---

## 📜 Academic Integrity

⚠️ This project was developed strictly for educational purposes.

* No third-party libraries were used
* No framework files were modified
* All code is original and team-written

Any reuse must comply with course and academic integrity policies.

---

⭐ If you find this project useful, feel free to star the repository!
