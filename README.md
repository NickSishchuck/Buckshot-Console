### Buckshot Roulette (Console Game)
### 🎮 Overview
Buckshot Console is a text-based console game inspired by the Steam game "Buckshot Roulette". It's a thrilling turn-based game where players take calculated risks with a shotgun loaded with blanks and real buckshots.
The game features an AI opponent and randomized gameplay.
![image](https://github.com/user-attachments/assets/759e607a-bf82-4a9d-bda1-477d495321a7)


### 🎲 Rules
At the start of each round, the shotgun is loaded with a random mix of blanks and real shots.
At least one blank and one real shot are guaranteed.
Players alternate turns, choosing to shoot themselves or their opponent.
Shooting yourself with a blank grants you another turn.
Shooting yourself with a real shot deducts 1 health and passes the turn.
Each player starts with 3 health points. The game ends when a player's health reaches 0.

### 🖥️ System Requirements
Operating System: Windows (for colored console output via SetConsoleTextAttribute).

Compiler: Any C++ compiler supporting C++11 or later (e.g., GCC, MSVC, or Clang).

Libraries: Standard C++ libraries, and <windows.h> for console coloring.

### 🚀 How to Play
Clone this repository:
```
git clone https://github.com/NickSishchuck/Buckshot-Console.git
```
Navigate to the project directory:
```
cd buckshot-console
```
Run the precompiled binary (Windows users):
Navigate to the release folder and run the Buckshot Console.exe file.

Alternatively, compile the project manually:
Using GCC:
```
g++ Source.cpp AI.cpp -o BuckshotConsole
```
Using Visual Studio:
Open the project in Visual Studio.
Build and run the solution.
Follow the on-screen instructions to play.
