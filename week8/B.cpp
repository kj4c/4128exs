#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

struct pt {
    ll x, y;
    pt(ll _x, ll _y) {
        x = _x;
        y = _y;
    }

    ll cross(const pt& other) const {
        return x * other.y - y * other.x;
    }
};

bool isCollinear(const pt& a, const pt& b, const pt& c) {
    return ((c.y - b.y)*(b.x - a.x) == (b.y - a.y)*(c.x - b.x));
}

bool allInLine(vector<pt> &line) {
    for (int i = 2; i < line.size(); i++) {
        if (!isCollinear(line[0], line[1], line[i]))
            return false;
    }

    return true;
}

bool checkTwoLines(int a, int b, vector<pt> &p) {
    vector<pt> notInLine;

    for (int i = 0; i < p.size(); i++) {
        if (!isCollinear(p[a], p[b], p[i])) {
            notInLine.push_back(p[i]);
        }
    }
    
    if (notInLine.size() <= 2) return true;

    if (allInLine(notInLine)) return true;

    return false;
}

int main() {
    int n;
    cin >> n;

    vector<pt> points;

    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        points.push_back(pt(x, y));
    }

    if (points.size() <= 4) {
        cout << "YES";
        return 0;
    }

    // choose 3 points
    // at least two of these must lie on the same line
    if (checkTwoLines(0, 1, points) || checkTwoLines(0, 2, points) || checkTwoLines(1, 2, points)) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}
