#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int N;
double L, W;
vector<int> MEM_VECTOR;
const int BOTTOM = -1;
using sprinkler = tuple<double, double, int>;


double pitagoras(double hypotenuse, double leg){
    return sqrt(pow(hypotenuse, 2) - pow(leg, 2));
}

sprinkler sprinklerScope(double &c, double &r, double &w, int &p) {
    double d = pitagoras(r, w/2);
    return make_tuple(c - d, c + d, p);
}

int BTSolve(double &l, const int &i, vector<sprinkler> &s) {
    if (MEM_VECTOR[i] == BOTTOM) {
        int x0 = i == -1 ? 0 : get<1>(s[i]);

        vector<int> candidates;
        vector<int> K;
        for (int c = 0; c < s.size(); c++) {
            if (get<0>(s[c]) < x0 && get<1>(s[c]) > x0) {
                candidates.push_back(c);
            } else {
                K.push_back(c);
            }
        }

        if (candidates.empty()) {
            MEM_VECTOR[i] = INFINITY;
        }

        vector<int> resVec;

        for (int &c : candidates) {
            int r;
            if (get<1>(s[c]) >= L) {
                r = get<2>(s[c]);
            } else if (K.empty()) {
                r = INFINITY;
            } else {
                r = get<2>(s[c]) + BTSolve(L, c, s);
            }
            resVec.push_back(r);
        }

        if (!resVec.empty()) {
            MEM_VECTOR[i] = *min_element(resVec.begin(), resVec.end());
        } else {
            MEM_VECTOR[i] = INFINITY;
        }
    }
    return MEM_VECTOR[i];
}


int main()
{
    while(cin >> N >> L >> W) {
        vector<sprinkler> sprinklers(N, make_tuple(0,0,0));
        for (int i = 0; i < N; i++) {
            double center;
            double radius;
            int cost;
            cin >> center >> radius >> cost;
            // If the inputted radius is valid (i.e. greater or equal than
            // half the width of the strip of grass) calculate its scope
            if (radius >= W/2) {
                sprinklers[i] = sprinklerScope(center, radius, W, cost);
            }
        }
        // Sort sprinklers vector in ascending order by scope
        sort(sprinklers.begin(), sprinklers.end(), [](const sprinkler &left, const sprinkler &right) {
            return get<0>(left) < get<0>(right);
        });

        MEM_VECTOR = vector<int>(sprinklers.size(), BOTTOM);

        cout << BTSolve(L, -1, sprinklers) << endl;
    }

    return 0;
}

