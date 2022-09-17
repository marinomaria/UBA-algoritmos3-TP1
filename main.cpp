#include <iostream>
#include <vector>

using namespace std;

using pos = pair<int,int>;

int const BOTTOM = -1;

vector<vector<int>> GRILLA;

int N,M,x1,x2,x3,y1,y2,y3;



void initialize_grid(const int n, const int m, const int x1, const int y1, const int x2, const int y2, const int x3, const int y3) {
    vector<int> row(m, BOTTOM);
    GRILLA = vector<vector<int>>(n, row);
    GRILLA[0][0] = 1; // Start
    GRILLA[x1][y1] = int(n*m/4); // 1st checkpoint
    GRILLA[x2][y2] = int(n*m/2); // 2nd checkpoint
    GRILLA[x3][y3] = int(3*n*m/4); // 3rd checkpoint
    GRILLA[0][1] = n*m; // End
}

pair<vector<pos>, bool> adyacentes_posibles(int x, int y) {
    vector<pos> posibles;
    int value = GRILLA[x][y];
    bool checkpoint_al_lado = false;
    if (x > 0) {
        if (GRILLA[x - 1][y] == BOTTOM) {
            posibles.push_back(make_pair(x - 1, y));
        } else if (GRILLA[x - 1][y] > value) {
            checkpoint_al_lado = true;
        }
    }
    if (x < (N - 1)) {
        if (GRILLA[x + 1][y] == BOTTOM) {
            posibles.push_back(make_pair(x + 1, y));
        }
        else if (GRILLA[x + 1][y] > value) {
            checkpoint_al_lado = true;
        }
    }
    if (y > 0) {
        if (GRILLA[x][y - 1] == BOTTOM) {
            posibles.push_back(make_pair(x, y - 1));
        } else if (GRILLA[x][y - 1] > value) {
            checkpoint_al_lado = true;
        }
    }
    if (y < (M - 1)) {
        if (GRILLA[x][y + 1] == BOTTOM) {
            posibles.push_back(make_pair(x, y + 1));
        } else if (GRILLA[x][y + 1] > value) {
            checkpoint_al_lado = true;
        }
    }
    return make_pair(posibles, checkpoint_al_lado);
}

bool t_bone(pair<vector<pos>, bool> &s) {
    vector<pos> adyacentes = s.first;
    bool checkpoint_al_lado = s.second;
    if (adyacentes.size() == 2) {
        if ((adyacentes[0].first == adyacentes[1].first || adyacentes[0].second == adyacentes[1].second) && not checkpoint_al_lado) {
            return true;
        }
    }
    return false;
}

pos next_target(int value) {
    int target_x, target_y;
    if (value < N*M/4) {
        target_x = x1;
        target_y = y1;
    } else if (value < N*M/2) {
        target_x = x2;
        target_y = y2;
    } else if (value < 3*N*M/4) {
        target_x = x3;
        target_y = y3;
    } else {
        target_x = 0;
        target_y = 1;
    }
    return make_pair(target_x, target_y);
}

int solver(int x, int y) {

    int i = GRILLA[x][y];

    // Finishing condition
    if (i == N*M - 1) {
        if ((x == 1 && y == 1) or (x == 0 && y == 2)) {
            return 1;
        }
    }
    // Finishing condition

    // Siguiente target
    pos target = next_target(i);
    // Siguiente target

     // Poda Manhattan
    int manhattan_distance = abs(x - target.first) + abs(y - target.second);
    if (manhattan_distance > GRILLA[target.first][target.second] - i) {
        return 0;
    }
    // Poda Manhattan


    // Poda loops
    pair<vector<pos>, bool> surroundings = adyacentes_posibles(x,y);
    if (t_bone(surroundings) and not surroundings.second) {
        return 0;
    }
    // Poda loops

    int res = 0;

//    for (pos ady : surroundings.first) {
//        pair<vector<pos>, bool> s = adyacentes_posibles(ady.first, ady.second);
//        if ((s.first.size() + s.second) == 1) {
//            GRILLA[ady.first][ady.second] = i + 1;
//            return solver(ady.first, ady.second);
//        }
//    }

    // Checkpoint/target
    if (i == GRILLA[target.first][target.second] - 1) {
        res += solver(target.first, target.second);
    }
    // Checkpoint

    // Backtracking
    for (pos ady : surroundings.first) {
        GRILLA[ady.first][ady.second] = i + 1;
        res += solver(ady.first, ady.second);
        GRILLA[ady.first][ady.second] = BOTTOM;
    }
    return res;
    // Backtracking
}



int main() {

    clock_t tStart = clock();
    int test_case = 1;
    vector<int> res;
    while(scanf("%d %d",&N,&M),(N != 0 && M != 0)) {
        scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
        initialize_grid(N,M,x1,y1,x2,y2,x3,y3);
        int res_i = solver(0,0);
        res.push_back(res_i);
        test_case++;
    }
    for (int i = 0; i < test_case - 1; i++) {
        cout << "Case " << i + 1 << ": " << res[i] << endl;
    }
    cout << (clock() - tStart)/CLOCKS_PER_SEC << endl;

    return 0;
}
