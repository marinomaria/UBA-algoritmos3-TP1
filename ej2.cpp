#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int N;
double L, W;
using sprinkle = pair<int, int>;


// pickea el sprinkle mas a la derecha que cubra ultimo_ancho_cubierto;
// repeti
double distance(double x1, double y1, double x2, double y2){
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

double pitagoras_H_y_C(double r, double c){
    // Pitagoras con Hipotenusa y un cateto como datos.
    return sqrt(pow(r, 2) - pow(c, 2) * 1.0);
}


double greedy_aspersores_2(int &n, double &l, double &w, vector<sprinkle> aspersores){
    double ultimo_ancho_cubierto = 0;
    int res = 0;
        while(ultimo_ancho_cubierto < l){
            res++;
            int aspersor_mas_derecha = n - 1;
            bool no_cubre;
            no_cubre = distance(ultimo_ancho_cubierto, w/2, aspersores[aspersor_mas_derecha].second,0) > aspersores[aspersor_mas_derecha].first;
            while(no_cubre){
                aspersor_mas_derecha--;
                if (distance(ultimo_ancho_cubierto, w/2, aspersores[aspersor_mas_derecha].second,0) <= aspersores[aspersor_mas_derecha].first) {
                    no_cubre = false;
                }
            }
            ultimo_ancho_cubierto = pitagoras_H_y_C(aspersores[aspersor_mas_derecha].first, w/2);
        }
    return res;
}

int main()
{
    int test_case = 0;
    vector<double> res;
    while(scanf("%d%lf%lf", &N, &L, &W) != EOF){
        vector<sprinkle> sprinkles(N, make_pair(0,0));
        for (int i = 0; i < N; i++) {
            int pos;
            int radius;
            scanf("%d%d", &pos, &radius);
            sprinkles[i] = make_pair(pos,radius);
        }
        res.push_back(greedy_aspersores_2(N, L, W, sprinkles));
        test_case++;
    }

    for (int i = 0; i < test_case; i++) {
        cout << "Case " << i + 1 << ": " << res[i];
        if (i != test_case - 1) {
            cout << endl;
        }
    }

    return 0;
}

