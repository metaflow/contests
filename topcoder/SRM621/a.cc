#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class RadioRange {
public:
    double RadiusProbability(vector <int> X, vector <int> Y, vector <int> R, int Z) {
        vector<pair<double,double>> zones;
        for (int i = 0; i < X.size(); i++) {
            double t = sqrt(1.0d * X[i] * X[i] + Y[i] * Y[i]);
            zones.push_back(make_pair(t - R[i], t + R[i]));
        }
        sort(zones.begin(), zones.end());
        int i = 0;
        double sum = 0;
        while (i < zones.size()) {
            double f = zones[i].first;
            double t = zones[i].second;
            // cerr << "f" << f << " t " << t << endl;
            while (i + 1 < zones.size() && zones[i + 1].first <= t) {
                i++;
                t = max(t, zones[i].second);
            }
            f = min(max(0.0, f), 1.0*Z);
            t = min(max(0.0, t), 1.0*Z);
            sum += t - f;
            i++;
        }
        // cerr << "sum " <<  sum << endl;
        return 1 - sum / Z;
    }
};


int main() {
    RadioRange r;
    cout << r.RadiusProbability({0}, {0}, {5}, 10) << endl;
    cout << r.RadiusProbability({0}, {0}, {10}, 10) << endl;
    cout << r.RadiusProbability({10}, {10}, {10}, 10) << endl;
    cout << r.RadiusProbability({11, -11, 0, 0}, {0, 0, 11, -11}, {10, 10, 10, 10}, 31) << endl;
    cout << r.RadiusProbability({100} ,{100}, {1}, 10) << endl;

    cout << r.RadiusProbability({1000000000}, {1000000000}, {1000000000}, 1000000000) << endl;
    cout << r.RadiusProbability({20, -20, 0, 0}, {0, 0, 20, -20}, {50, 50, 50, 50}, 100) << endl;
    cout << r.RadiusProbability({0, -60, -62, -60, 63, -97}, {-72, 67, 61, -8, -32, 89}, {6, 7, 8, 7, 5, 6}, 918) << endl;
}

