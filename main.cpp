#include <iostream>
#include <vector>

using namespace std;

using pos = pair<int,int>;

int const BOTTOM = -1;

vector<vector<int>> GRILLA;

int N,M,X1,X2,X3,Y1,Y2,Y3;

void initialize_grid(const int &n, const int &m, const int &x1, const int &y1, const int &x2, const int &y2, const int &x3, const int &y3) {
    vector<int> row(m, BOTTOM);
    GRILLA = vector<vector<int>>(n, row);
    GRILLA[0][0] = 1; // Start
    GRILLA[x1][y1] = int(n*m/4); // 1st checkpoint
    GRILLA[x2][y2] = int(n*m/2); // 2nd checkpoint
    GRILLA[x3][y3] = int(3*n*m/4); // 3rd checkpoint
    GRILLA[0][1] = n*m; // End
}

void calcular_adyacentes_posibles(int const &x, int const &y, vector<pos> &v, bool &c) {
    int value = GRILLA[x][y];
    if (x > 0) {
        if (GRILLA[x - 1][y] == BOTTOM || GRILLA[x - 1][y] > value + 1) {
            v.emplace_back(x - 1, y);
        } else if (GRILLA[x - 1][y] > value) {
            c = true;
        }
    }
    if (x < (N - 1)) {
        if (GRILLA[x + 1][y] == BOTTOM || GRILLA[x + 1][y] > value + 1) {
            v.emplace_back(x + 1, y);
        }
        else if (GRILLA[x + 1][y] > value) {
            c = true;
        }
    }
    if (y > 0) {
        if (GRILLA[x][y - 1] == BOTTOM || GRILLA[x][y - 1] > value + 1) {
            v.emplace_back(x, y - 1);
        } else if (GRILLA[x][y - 1] > value) {
            c = true;
        }
    }
    if (y < (M - 1)) {
        if (GRILLA[x][y + 1] == BOTTOM || GRILLA[x][y + 1] > value + 1) {
            v.emplace_back(x, y + 1);
        } else if (GRILLA[x][y + 1] > value) {
            c = true;
        }
    }
}

bool t_bone(vector<pos> &s) {
    if (s.size() == 2) {
        if (s[0].first == s[1].first || s[0].second == s[1].second) {
            return true;
//        } else if () {
//
        }
    }
    return false;
}

pos next_target(int const &value) {
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
    return make_pair(target_x, target_y);
}

int solver(int const &x, int const &y) {

    int i = GRILLA[x][y];

    // Finishing condition
    if (i == N*M - 1) {
        if ((x == 1 && y == 1) or (x == 0 && y == 2)) {
            return 1;
        }
    }
    // Finishing condition

    pos target = next_target(i);
     // Poda Manhattan
    int manhattan_distance = abs(x - target.first) + abs(y - target.second);
    if (manhattan_distance > GRILLA[target.first][target.second] - i) {
        return 0;
    }
    // Poda Manhattan

    vector<pos> vecinos;
    bool checkpoint_al_lado = false;
    calcular_adyacentes_posibles(x,y, vecinos, checkpoint_al_lado);

    // Poda loops
    if (not checkpoint_al_lado && t_bone(vecinos)) {
        return 0;
    }
    // Poda loops

    int res = 0;

    // Checkpoint/target
    if (i == GRILLA[target.first][target.second] - 1) {
        res += solver(target.first, target.second);
    }
    // Checkpoint

    // Backtracking
    for (pos ady : vecinos) {
        if (GRILLA[ady.first][ady.second] == BOTTOM) {
            GRILLA[ady.first][ady.second] = i + 1;
            res += solver(ady.first, ady.second);
            GRILLA[ady.first][ady.second] = BOTTOM;
        }
    }
    return res;
    // Backtracking
}



int main() {

    clock_t tStart = clock();
    int test_case = 1;
    vector<int> res;
    while(scanf("%d %d",&N,&M),(N != 0 && M != 0)) {
        scanf("%d %d %d %d %d %d", &X1, &Y1, &X2, &Y2, &X3, &Y3);
        initialize_grid(N,M,X1,Y1,X2,Y2,X3,Y3);
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
