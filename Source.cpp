#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "AI.h"
#include <thread>   // For std::this_thread::sleep_for
#include <chrono>   // For std::chrono::seconds
#include <windows.h>



using namespace std;

// Function prototypes
void displayRules();
void initializeChamber(vector<int>& chamber, int blanks, int realShots);
bool shoot(vector<int>& chamber, int& health, string playerName);
void displayHealth(int player1Health, int player2Health);

void waitRandomTime() {
    int waitTime = rand() % 3 + 2;
    std::this_thread::sleep_for(std::chrono::seconds(waitTime));
}

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}



int main() {
    srand(static_cast<unsigned>(time(0))); 

    const int totalBuckshots = 6;
    int blanks, realShots;
    vector<int> chamber;

    cout << "Welcome to Buckshot Roulette!" << endl;
    displayRules();

    // Game loop
    char choice = 'n';
    do {

        blanks = rand() % (totalBuckshots - 1) + 1; 
        realShots = totalBuckshots - blanks;


        cout << "\nThis round, the shotgun is loaded with:\n";
        setConsoleColor(9);
        cout << blanks << " blanks\n";
        setConsoleColor(12);
		cout << realShots << " real shots\n";
        setConsoleColor(7);

        initializeChamber(chamber, blanks, realShots);

        // Initialize player health
        int player1Health = 3, player2Health = 3;
        int currentPlayer = 1; // 1 for Player 1, 2 for AI
        bool gameOver = false;

        cout << "\nGame Start!\n";

        while (true) { // Loop until the player decides to quit
            // Add formatting lines
            cout << "________________________" << endl;
            cout << "It's Player " << (currentPlayer == 1 ? "1" : "2 (AI)") << "'s turn!" << endl;
            displayHealth(player1Health, player2Health);

            // Check if the chamber is empty
            if (chamber.empty()) {
                cout << "\nThe shotgun is empty! Starting a new round...\n";
                blanks = rand() % (totalBuckshots - 1) + 1; // At least 1 blank
                realShots = totalBuckshots - blanks;

                cout << "\nThis round, the shotgun is loaded with:\n";
                setConsoleColor(9);
                cout << blanks << " blanks\n";
                setConsoleColor(12);
                cout << realShots << " real shots\n";
                setConsoleColor(7);

                initializeChamber(chamber, blanks, realShots);
                continue; // Restart the loop with the new chamber
            }

            if (currentPlayer == 1) {
                // Player 1's turn
                waitRandomTime();
                cout << "\nChoose your action:\n"
                    << "1. Shoot yourself\n"
                    << "2. Shoot the opponent\n"
                    << "Your choice: ";
                int action;
                cin >> action;


                if (action == 1) {
                    cout << "Player 1 shoots themselves...\n";

                    waitRandomTime();

                    bool isBlank = shoot(chamber, player1Health, "Player 1");
                    if (player1Health <= 0) { // Player 1 is dead
                        cout << "\nPlayer 1 is dead! Game over.\n";
                        break; // Exit the current game loop
                    }
                    if (isBlank) {
                        cout << "You survived! You get another turn!\n";
                    }
                    else {
                        currentPlayer = 2; // Pass turn to AI
                    }
                }
                else if (action == 2) {

                   

                    cout << "Player 1 shoots the opponent...\n";
                    waitRandomTime();
                    bool isBlank = shoot(chamber, player2Health, "Player 2");
                    if (player2Health <= 0) { // AI is dead
                        cout << "\nPlayer 2 (AI) is dead! You win!\n";
                        break; // Exit the current game loop
                    }
                    if (!isBlank) {
                        currentPlayer = 2; // Pass turn to AI
                    }
                }
                else {
                    cout << "Invalid choice. Try again.\n";
                }
            }
            else {
                // AI's turn
                waitRandomTime();
                int action = aiDecision(player2Health, player1Health, chamber);

                if (action == 1) {
                    cout << "\nPlayer 2 (AI) shoots itself...\n";
                    waitRandomTime();
                    bool isBlank = shoot(chamber, player2Health, "Player 2");
                    if (player2Health <= 0) { // AI is dead
                        cout << "\nPlayer 2 (AI) is dead! You win!\n";
                        break; // Exit the current game loop
                    }
                    if (isBlank) {
                        cout << "AI survived! It gets another turn!\n";
                        continue; // Let the AI take another turn
                    }
                    else {
                        currentPlayer = 1; // Pass turn to Player 1
                    }
                }
                else {
                    cout << "\nPlayer 2 (AI) shoots the opponent...\n";
					waitRandomTime();
                    bool isBlank = shoot(chamber, player1Health, "Player 1");
                    if (player1Health <= 0) { // Player 1 is dead
                        cout << "\nPlayer 1 is dead! Game over.\n";
                        break; // Exit the current game loop
                    }
                    if (!isBlank) {
                        currentPlayer = 1; // Pass turn to Player 1
                    }
                }
            }

            // Add formatting lines
            cout << "_____________________" << endl;
        }

        // Ask the player if they want to restart or quit
        char choice;
        cout << "\nDo you want to play again? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            // Restart the game by resetting health and chamber
            player1Health = 3;
            player2Health = 3;

            blanks = rand() % (totalBuckshots - 1) + 1;
            realShots = totalBuckshots - blanks;

            cout << "\nThis round, the shotgun is loaded with:\n";
            setConsoleColor(9);
            cout << blanks << " blanks\n";
            setConsoleColor(12);
            cout << realShots << " real shots\n";
            setConsoleColor(7);

            initializeChamber(chamber, blanks, realShots);
            currentPlayer = 1; // Reset to Player 1
            continue; // Restart the loop
        }
        else {
            cout << "Thanks for playing Buckshot Roulette! Goodbye!\n";
            break; // Exit the outer loop
        }



        cout << "\nGame over! Do you want to play again? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "Thanks for playing Buckshot Roulette!" << endl;
    return 0;
}

void displayRules() {
    cout << "Rules:\n"
        << "1. There are 6 buckshots in the shotgun. Some are ";
	setConsoleColor(9);
    cout << "blanks";
    setConsoleColor(7);
    cout << ", some are ";
    setConsoleColor(12);
    cout << "real";
    setConsoleColor(7);
    cout <<".\n"
        << "2. Players take turns choosing to shoot themselves or the opponent.\n"
        << "3. If you shoot yourself with a blank, you get another turn.\n"
        << "4. If a real buckshot is fired, the shotgun is passed to the next player.\n"
        << "5. Each player has 3 health points. Lose them all, and you're out!\n"
        << "Good luck!\n";
}

#include <random>    
#include <algorithm> 

void initializeChamber(vector<int>& chamber, int blanks, int realShots) {
    chamber.clear();
    for (int i = 0; i < blanks; i++) chamber.push_back(0); // 0 for blanks
    for (int i = 0; i < realShots; i++) chamber.push_back(1); // 1 for real shots

    // Shuffle the chamber
    random_device rd;
    mt19937 eng(rd());
    shuffle(chamber.begin(), chamber.end(), eng);
}


bool shoot(vector<int>& chamber, int& health, string playerName) {
    if (chamber.empty()) {
        cout << "The shotgun is empty! Reloading...\n";
        return false;
    }

    int shot = chamber.back();
    chamber.pop_back();

    if (shot == 0) {
        cout << "Click! It was a ";
		setConsoleColor(9);
        cout << "blank\n";
        setConsoleColor(7);
        return false;
    }
    else {
        cout << "BOOM! It was a ";
        setConsoleColor(12);
        cout << "real shot\n";
        setConsoleColor(7);
        health--;
        cout << playerName << " loses 1 health point. Remaining health: " << health << endl;
        if (health <= 0) {
            cout << playerName << " is dead!\n";
            return true; // Game over
        }
        return false;
    }
}

void displayHealth(int player1Health, int player2Health) {
    setConsoleColor(14);
    cout << "\nPlayer 1 Health: " << player1Health << " | Player 2 Health: " << player2Health << endl;
    setConsoleColor(7);
}
