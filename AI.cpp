#include "AI.h"
#include <cstdlib>

int aiDecision(int aiHealth, int playerHealth, const std::vector<int>& chamber) {
    int blanks = 0, realShots = 0;

    for (int shot : chamber) {
        if (shot == 0) blanks++;
        else realShots++;
    }

    // AI logic
    if (aiHealth == 1) {
        return 2;
    }

    if (blanks > realShots) {
        return 1;
    }

    // Randomized decision (50/50)
    return (rand() % 2 == 0) ? 1 : 2;
}
