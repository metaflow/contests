#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class SixteenBricks {
    public:
    int maximumSurface(vector<int> bricks) {
        sort(bricks.begin(), bricks.end());
        int a[4][4];
        for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) a[i][j] = 0;
        a[1][2] = bricks[0];
        a[2][1] = bricks[1];
        a[0][1] = bricks[2];
        a[1][0] = bricks[3];
        a[2][3] = bricks[4];
        a[3][2] = bricks[5];
        a[3][0] = bricks[6];
        a[0][3] = bricks[7];
        int k = 8;
        int r = 16;
        for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            if (a[i][j]) {
                if (i == 0 || i == 3) r += a[i][j];
                if (j == 0 || j == 3) r += a[i][j];
                continue;
            }
            a[i][j] = bricks[k];
            k++;
            if (i == 0 || i == 3) r += a[i][j];
            if (j == 0 || j == 3) r += a[i][j];
            if (i > 0) r += a[i][j] - a[i-1][j];
            if (j > 0) r += a[i][j] - a[i][j-1];
            if (i < 3) r += a[i][j] - a[i+1][j];
            if (j < 3) r += a[i][j] - a[i][j+1];
        }
        return r;
    }
};

int main() {
    SixteenBricks b;
    cout << b.maximumSurface({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) << endl;
    cout << b.maximumSurface({1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2}) << endl;
    cout << b.maximumSurface({77, 78, 58, 34, 30, 20, 8, 71, 37, 74, 21, 45, 39, 16, 4, 59}) << endl;

}
