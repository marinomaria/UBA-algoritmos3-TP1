#include <iostream>
#include <vector>

using namespace std;

using pos = pair<int, int>;

int const BOTTOM = -1;

vector<vector<int>> GRID;

int N,M,X1,X2,X3,Y1,Y2,Y3;

void initializeGrid(const int &n, const int &m, const int &x1, const int &y1, const int &x2, const int &y2, const int &x3, const int &y3) {
    vector<int> row(m, BOTTOM);
    GRID = vector<vector<int>>(n, row);
    GRID[0][0] = 1;                 // Start
    GRID[x1][y1] = int(n*m/4);      // 1st checkpoint
    GRID[x2][y2] = int(n*m/2);      // 2nd checkpoint
    GRID[x3][y3] = int(3*n*m/4);    // 3rd checkpoint
    GRID[0][1] = n*m;               // End
}

void getNeighborhood(int const &x, int const &y, vector<pos> &v, bool &c) {
    int value = GRID[x][y];
    if (x > 0) {
        if (GRID[x - 1][y] == BOTTOM || GRID[x - 1][y] > value + 1) {
            v.emplace_back(x - 1, y);
        } else if (GRID[x - 1][y] > value) {
            c = true;
        }
    }
    if (x < (N - 1)) {
        if (GRID[x + 1][y] == BOTTOM || GRID[x + 1][y] > value + 1) {
            v.emplace_back(x + 1, y);
        }
        else if (GRID[x + 1][y] > value) {
            c = true;
        }
    }
    if (y > 0) {
        if (GRID[x][y - 1] == BOTTOM || GRID[x][y - 1] > value + 1) {
            v.emplace_back(x, y - 1);
        } else if (GRID[x][y - 1] > value) {
            c = true;
        }
    }
    if (y < (M - 1)) {
        if (GRID[x][y + 1] == BOTTOM || GRID[x][y + 1] > value + 1) {
            v.emplace_back(x, y + 1);
        } else if (GRID[x][y + 1] > value) {
            c = true;
        }
    }
}

bool tBoneSituation(vector<pos> &s) {
    if (s.size() == 2) {
        if (s[0].first == s[1].first || s[0].second == s[1].second) {
            return true;
        }
    }
    return false;
}

pos nextTarget(int const &value) {
    int target_x, target_y;
    if (value < N*M/4) {
        target_x = X1;
        target_y = Y1;
    } else if (value < N*M/2) {
        target_x = X2;
        target_y = Y2;
    } else if (value < 3*N*M/4) {
        target_x = X3;
        target_y = Y3;
    } else {
        target_x = 0;
        target_y = 1;
    }
    return {target_x, target_y};
}

int manhattanDistance(pos const &a, pos const &b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int solve(int const &x, int const &y) {

    int i = GRID[x][y];

    // Finishing condition
    if (i == N*M - 1) {
        if ((x == 1 && y == 1) or (x == 0 && y == 2)) {
            return 1;
        }
    }

    // Get target position
    pos target = nextTarget(i);
    int targetValue = GRID[target.first][target.second];

    // Manhattan Pruning
    if (manhattanDistance({x, y}, target) > targetValue - i) {
        return 0;
    }

    // Get information about current position's neighborhood
    vector<pos> neighbors;
    bool nextToCheckpoint = false;
    getNeighborhood(x, y, neighbors, nextToCheckpoint);

    // Loops pruning
    if (not nextToCheckpoint && tBoneSituation(neighbors)) {
        return 0;
    }

    // Initialize returning variable
    int res = 0;
    // If next to target solve target position directly
    // The Manhattan pruning ensures that if the current value is nextTarget - 1 it
    // can only be next to the target
    if (i == targetValue - 1) {
        res += solve(target.first, target.second);
    }

    // Recursive call
    for (pos ady : neighbors) {
        if (GRID[ady.first][ady.second] == BOTTOM) {
            GRID[ady.first][ady.second] = i + 1;
            res += solve(ady.first, ady.second);
            GRID[ady.first][ady.second] = BOTTOM;
        }
    }
    return res;
}



int main() {

//    clock_t tStart = clock();
    int test_case = 0;
    vector<int> res;
    while(cin >> N >> M, (N != 0 && M != 0)) {
        cin >> X1 >> Y1 >> X2 >> Y2 >> X3 >> Y3;
        initializeGrid(N, M, X1, Y1, X2, Y2, X3, Y3);
        int res_i = solve(0, 0);
        res.push_back(res_i);
        test_case++;
    }
    for (int i = 0; i < test_case; i++) {
        cout << "Case " << i + 1 << ": " <<  res[i] << endl;
    }

//    cout << endl;
//    cout << (clock() - tStart)/CLOCKS_PER_SEC << endl;

    return 0;
}
