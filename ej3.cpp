#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

#define BOTTOM (-1)
#define INF numeric_limits<int>::max()

int N;
double L, W;
vector<int> MEM_VECTOR;
using sprinkler = tuple<double, double, int>;


double pitagoras(double hypotenuse, double leg){
    return sqrt(pow(hypotenuse, 2) - pow(leg, 2));
}

sprinkler sprinklerScope(double &c, double &r, double &w, int &p) {
    double d = pitagoras(r, w/2);
    return make_tuple(c - d, c + d, p);
}

int BTSolve(const int &i, vector<sprinkler> &s) {
    if (MEM_VECTOR[i] == BOTTOM) {

        // Define the target point to cover.
        // If this is the first call (i == N), x0 = 0.
        // Otherwise set x0 to the right border of the i-th sprinkler
        double x0 = i == N ? 0 : get<1>(s[i]);

        vector<int> candidates;
        vector<int> K;
        // Iterate over the sprinklers vector
        for (int c = 0; c < s.size(); c++) {
            if (get<0>(s[c]) < x0 && get<1>(s[c]) > x0) {
                // c is a candidate <=> x0 it's within its scope
                candidates.push_back(c);
            } else if (get<0>(s[c]) > x0) {
                // c is in K <=> it isn't a candidate and its scope begins on the right of x0
                K.push_back(c);
            }
        }

        vector<int> resVec;

        for (int &c: candidates) {
            int r;
            if (get<1>(s[c]) >= L) {
                // If the candidate sprinkler covers the full length of the grass left
                // then the cost of picking it would be its associated cost
                r = get<2>(s[c]);
            } else if (K.empty()) {
                // If the sprinkler doesn't cover the full length and we don't have
                // more sprinklers to the right, there's no solution when choosing this one
                r = INF;
            } else {
                // Otherwise, the cost of picking this sprinkler is its associated cost +
                // the cost of covering the strip that's left on the right of its scope
                r = get<2>(s[c]) + BTSolve(c, s);
            }
            resVec.push_back(r);
        }

        if (!resVec.empty()) {
            MEM_VECTOR[i] = *min_element(resVec.begin(), resVec.end());
        } else {
            MEM_VECTOR[i] = INF;
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

        MEM_VECTOR = vector<int>(N + 1, BOTTOM);

        int res = BTSolve(N, sprinklers);

        cout <<  ((res < INF) ? res : -1)  << endl;
    }

    return 0;
}

