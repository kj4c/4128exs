#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
/*
 * cross product
 */

const double EPS = 1e-8;
typedef long long ll;

typedef pair<int, int> pt;
#define x first
#define y second	

pt operator-(pt a, pt b) {
  return pt(a.x - b.x, a.y - b.y);
}

bool zero(double x) {
  return fabs(x) <= EPS;
}

ll cross(pt a, pt b) {
  return a.x*b.y - a.y*b.x;
}

ll cross3(pt a, pt b, pt c) {
  return (a.x - b.x) * (c.y - b.y) - (a.y - b.y) * (c.x - b.x);
}


// true if left or straight
// sometimes useful to instead return an int
// -1, 0 or 1: the sign of the cross product
bool ccw(pt a, pt b, pt c) {
  return cross(b - a, c - a) > 0;
}

bool inTriangle(pt a, pt b, pt c, pt p) {
  int bcp = abs(cross3(b, c, p));
  int acp = abs(cross3(a, c, p));
  int abp = abs(cross3(a, b, p));
  int abc = abs(cross3(a, b, c));

  return abc == abp + acp + bcp;
}

int main() {
    int n, m;
    cin >> n >> m;  

    vector<pt> redPoints(n), blackPoints(m);

    for (int i = 0; i < n; ++i) {
        cin >> redPoints[i].x >> redPoints[i].y;
    }


    for (int i = 0; i < m; ++i) {
        cin >> blackPoints[i].x >> blackPoints[i].y;
    }

	vector<vector<int>> count(n, vector<int>(n, 0));

	pair<int, int> zero = {0 , 0};

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
		if (cross3(redPoints[i], zero, redPoints[j]) > 0)
		for (int k = 0; k < m; k++) {
			if (inTriangle(redPoints[i], zero, redPoints[j], blackPoints[k])) {
				count[i][j]++;
			}
		}
		count[j][i] = -count[i][j];
      }
    }

    ll Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
		int k;
		cin >> k;
        vector<int> indices(k);
        for (int i = 0; i < k; ++i) {
            cin >> indices[i];
            indices[i]--; 
        }

        int result = 0;
        for (int i = 0; i < k; ++i) {
            int u = indices[i];
            int v = indices[(i + 1) % k];
            result += count[u][v];
        }

        cout << abs(result) << '\n';
    }

    return 0;
}
