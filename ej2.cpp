#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int N;
double L, W;
using sprinkler = pair<double, double>;

double pitagoras(double hypotenuse, double leg){
    return sqrt(pow(hypotenuse, 2) - pow(leg, 2));
}

sprinkler sprinklerScope(double &c, double &r, double &w) {
    double d = pitagoras(r, w/2);
    return make_pair(c - d, c + d);
}


int greedySolve(int &n, double &l, double &w, vector<sprinkler> s){
    double maxLengthCovered = 0;
    int res = 0;
    int lastSprinkleUsed = -1;
    while (maxLengthCovered < l) {
        int rightmostSprinkle = n - 1;
        while (s[rightmostSprinkle].first > maxLengthCovered && rightmostSprinkle > lastSprinkleUsed) {
            rightmostSprinkle--;
        }
        if (rightmostSprinkle > lastSprinkleUsed) {
            maxLengthCovered = s[rightmostSprinkle].second;
            lastSprinkleUsed = rightmostSprinkle;
            res++;
        } else {
            return -1;
        }
    }
    return res;
}

int main()
{
    while(cin >> N >> L >> W) {
        vector<sprinkler> sprinklers(N, make_pair(0,0));
        for (int i = 0; i < N; i++) {
            double center;
            double radius;
            cin >> center >> radius;
            // If the inputted radius is valid (i.e. greater or equal than
            // half the width of the strip of grass) calculate its scope
            if (radius >= W/2) {
                sprinklers[i] = sprinklerScope(center, radius, W);
            }
        }
        // Sort sprinklers vector in ascending order by scope
        sort(sprinklers.begin(), sprinklers.end(), [](const sprinkler &left, const sprinkler &right) {
            return left.second < right.second;
        });


        cout << greedySolve(N, L, W, sprinklers) << endl;
    }

    return 0;
}

