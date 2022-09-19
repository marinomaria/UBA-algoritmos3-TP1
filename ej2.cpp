#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int N;
double L, W;
using sprinkle = pair<int, int>;

double distance(double x1, double y1, double x2, double y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

    double pitagoras(double hypotenuse, double leg){
    return sqrt(pow(hypotenuse, 2) - pow(leg, 2));
}


int greedySolve(int &n, double &l, double &w, vector<sprinkle> s){
    double maxWidth = 0;
    int res = 0;
    int lastSprinkleUsed = -1;
    while(maxWidth < l) {
        int rightmostSprinkle = n - 1;
        bool dry = distance(maxWidth, w / 2, s[rightmostSprinkle].first, 0) > s[rightmostSprinkle].second;
        while(dry && rightmostSprinkle > lastSprinkleUsed){
            rightmostSprinkle--;
            if (distance(maxWidth, w / 2, s[rightmostSprinkle].first, 0) <= s[rightmostSprinkle].second) {
                dry = false;
            }
        }
        if (rightmostSprinkle > lastSprinkleUsed) {
            maxWidth = pitagoras(s[rightmostSprinkle].second, w / 2) + s[rightmostSprinkle].first;
            lastSprinkleUsed = rightmostSprinkle;
            res++;
        } else {
            return -1;
        }
    }
    return maxWidth >= l ? res : -1;
}

int main()
{
    while(cin >> N >> L >> W) {
        vector<sprinkle> sprinkles(N, make_pair(0,0));
        for (int i = 0; i < N; i++) {
            int pos;
            int radius;
            cin >> pos >> radius;
            sprinkles[i] = make_pair(pos,radius);
        }
        // Sort sprinkles vector in ascending order by position
        sort(sprinkles.begin(), sprinkles.end(), [](const sprinkle &left, const sprinkle &right) {
            return left.first < right.first;
        });
        cout << greedySolve(N, L, W, sprinkles) << endl;
    }

    return 0;
}

