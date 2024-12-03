#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
/*
 * cross product
 */

typedef long long ll;
const double EPS = 1e-8;
typedef pair<double, double> pt;
#define x first
#define y second

pt operator-(pt p, pt q) {
  return (pt){p.x - q.x, p.y - q.y};
}

bool zero(double x) {
  return fabs(x) <= EPS;
}

ll cross(pt a, pt b) {
  return a.x*b.y - a.y*b.x;
}

// true if left or straight
// sometimes useful to instead return an int
// -1, 0 or 1: the sign of the cross product
bool ccw(pt a, pt b, pt c) {
  return cross(b - a, c - a) >= 0;
}


/*
 * convex hull
 */

vector<pt> half_hull(vector<pt> pts) {
  vector<pt> res;
  for (int i = 0; i < pts.size(); i++) {
    // ccw means we have a left turn; we don't want that
    while (res.size() >= 2 &&
           ccw(pts[i], res[res.size()-1], res[res.size()-2])) {
      res.pop_back();
    }
    res.push_back(pts[i]);
  }
  return res;
}

vector<pt> convex_hull(vector<pt> pts) {
  sort(pts.begin(), pts.end());
  vector<pt> top = half_hull(pts);

  reverse(pts.begin(), pts.end());
  vector<pt> bottom = half_hull(pts);
  
  top.pop_back();
  bottom.pop_back();
  vector<pt> res(top.begin(), top.end());
  res.insert(res.end(), bottom.begin(), bottom.end());
  return res;
}


int main() {
    int n;
    cin >> n;

    return 0;
}
