// THIS IS JUST AN EXAMPLE FROM A LARGER CODE OF MINE
// My heuristic function / approach is the manhattanDistance / algo
int manhattanDistance(const State& state, const int goal[][SIZE]) {
    int distance = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int value = state.puzzle[i][j];
 
 
            if (value != 0) {
                // Find the goal position of the current value
                int goalI, goalJ;
                for (goalI = 0; goalI < SIZE; ++goalI) {
                    for (goalJ = 0; goalJ < SIZE; ++goalJ) {
                        if (goal[goalI][goalJ] == value) {
                            distance += abs(i - goalI) + abs(j - goalJ);
                        }
                    }
                }
            }
        }
    }
    return distance;
 }