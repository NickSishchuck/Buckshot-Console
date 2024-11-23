#include "AI.h"
#include <cstdlib> // For rand

int aiDecision(int aiHealth, int playerHealth, const std::vector<int>& chamber) {
    int blanks = 0, realShots = 0;

    // Count blanks and real shots in the chamber
    for (int shot : chamber) {
        if (shot == 0) blanks++;
        else realShots++;
    }

    // AI logic
    if (aiHealth == 1) {
        // Low health, always shoot opponent
        return 2; // Shoot opponent
    }

    if (blanks > realShots) {
        // More blanks, take the risk
        return 1; // Shoot self
    }

    // Randomized decision (50/50)
    return (rand() % 2 == 0) ? 1 : 2;
}
