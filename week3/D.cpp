#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

typedef long long ll;
const ll N = 200100;
const ll INF = (1LL << 61);
ll n, k;
string rooms;

vector<pair<ll, ll>> segments[N]; // (start, cost)
ll dp[N];
ll tree[1<<20]; // range min tree with poll update
/*
 * range tree query
 */
ll query(ll qL, ll qR, ll i = 1, ll cL = 0, ll cR = n) {
  // the query range exactly matches this node's range of responsibility
  if (cL == qL && cR == qR)
    return tree[i];
  // we might need to query one or both of the children
  ll mid = (cL + cR) / 2;
  ll ans = INF;
  // query the part within the left child [cL, mid), if any
  if (qL < mid) ans = min(ans, query(qL, min(qR, mid), i * 2, cL, mid));
  // query the part within the right child [mid, cR), if any
  if (qR > mid) ans = min(ans, query(max(qL, mid), qR, i * 2 + 1, mid, cR));
  return ans;
}
/*
 * range tree update
 */
void update(ll p, ll v, ll i = 1, ll cL = 0, ll cR = n) {
  if (cR - cL == 1) {
    // this node is a leaf, so apply the update
    tree[i] = v;
    return;
  }
  // figure out which child is responsible for the index (p) being updated
  ll mid = (cL + cR) / 2;
  if (p < mid)
    update(p, v, i * 2, cL, mid);
  else
    update(p, v, i * 2 + 1, mid, cR);
  // once we have updated the correct child, recalculate our stored value.
  tree[i] = min(tree[i*2], tree[i*2+1]);
}

int main() {
    cin >> n >> k;
    cin >> rooms;
    
    for (ll i = 0; i < n; i++) {
        if (rooms[i] == '1') {
            ll s, e, c;
            s = max(0LL, i-k);
            e = min(n - 1, i+k);
            c = i + 1;
            segments[e].emplace_back(s, c);
        }
    }

    for (ll i = 0; i < n; i++)
        update(i, INF);

    for (ll i = 0; i < n; i++) {
        // try just directly connecting
        dp[i] = (i == 0) ? 1 : dp[i-1] + (i + 1);
        for (auto seg : segments[i]) {
            // seg.first = start, seg.second = cost.
            ll prevcost = seg.first == 0 ? 0 : query(seg.first - 1, i);
            
            // find any segements that cover this area and make that the prev cost
            dp[i] = min(dp[i], prevcost + seg.second);
        }
        update(i, dp[i]);
    }
    cout << dp[n - 1] << '\n';

    return 0;
}

