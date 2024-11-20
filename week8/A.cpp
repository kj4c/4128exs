#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point {
    int x, y, index;
};

long long area(Point p1, Point p2, Point p3) {
    return abs(1LL * p1.x * (p2.y - p3.y) + 
               1LL * p2.x * (p3.y - p1.y) + 
               1LL * p3.x * (p1.y - p2.y));
}

int main() {
    int n;
    cin >> n;

    vector<Point> points(n);

    for (int i = 0; i < n; i++) {
        cin >> points[i].x;
        cin >> points[i].y;
        points[i].index = i + 1;
    }

    sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    // pick first two points and try out if third point gives the triangle
    for (int i = 2; i < n; i++) {
        if (area(points[0], points[1], points[i]) > 0) {
            cout << points[0].index << " " << points[1].index << " " << points[i].index << endl;
            return 0;
        }
    }

    return 0;
}
