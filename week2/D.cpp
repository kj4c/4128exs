#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <tuple>
#include <algorithm>
#include <map>
#include <climits>
#include <queue>

using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> pll;
typedef pair<ll, ll> pii;
typedef vector<pll> vpll;
typedef pair<char, ll> pci;
#define REPi(n) for (ll i = 0; i < n; i++)
#define REPj(n) for (ll j = 0; j < n; j++)
#define REPk(n) for (ll k = 0; k < n; k++)
#define REP1i(n) for (ll i = 1; i <= n; i++)
#define REP1j(n) for (ll j = 1; j <= n; j++)
#define REP1k(n) for (ll k = 1; k <= n; k++)


const ll N = 4*100100;
ll n; // actual length of underlying array

struct node {
    ll sum;
    ll max;
    bool increasing;
    bool decreasing;
    ll left;
    ll right;
};

node tree[N];

// the number of additional nodes created can be as high as the next power of
// two up from N (2^17 = 131,072)
// query the sum over [qL, qR) (0-based)
// i is the index in the tree , rooted at 1 so children are 2i and 2i+1
// instead of explicitly storing each node's range of responsibility [cL,cR), we
// calculate it on the way down
// the root node is responsible for [0, n)
ll maxQuery(ll qL, ll qR, ll i = 1, ll cL = 0, ll cR = n) {
    // the query range exactly matches this node's range of responsibility
    if (cL == qL && cR == qR) {
        return tree[i].max;
    }
    // we might need to query one or both of the children
    ll mid = (cL + cR) / 2;
    ll ans = 0;
    // query the part within the left child [cL, mid), if any
    if (qL < mid) ans = max(ans, maxQuery(qL, min(qR, mid), i * 2, cL, mid));
        
        // query the part within the right child [mid, cR), if any
    if (qR > mid) ans = max(ans, maxQuery(max(qL, mid), qR, i * 2 + 1, mid, cR));   
    return ans;
}

ll sumQuery(ll qL, ll qR, ll i = 1, ll cL = 0, ll cR = n) {
      // the query range exactly matches this node's range of responsibility
    if (cL == qL && cR == qR)
        return tree[i].sum;
    // we might need to query one or both of the children
    ll mid = (cL + cR) / 2;
    ll ans = 0;

    if (qL < mid) ans += sumQuery(qL, min(qR, mid), i * 2, cL, mid);
        
        // query the part within the right child [mid, cR), if any
    if (qR > mid) ans += sumQuery(max(qL, mid), qR, i * 2 + 1, mid, cR);

    return ans;
}

bool increasingQuery(ll qL, ll qR, ll i = 1, ll cL = 0, ll cR = n) {
      // the query range exactly matches this node's range of responsibility
    if (cL == qL && cR == qR)
        return tree[i].increasing;
    // we might need to query one or both of the children
    ll mid = (cL + cR) / 2;
    bool left = true;
    bool right = true;

    if (qL < mid) left = increasingQuery(qL, min(qR, mid), i * 2, cL, mid);
        
    // query the part within the right child [mid, cR), if any
    if (qR > mid) right = increasingQuery(max(qL, mid), qR, i * 2 + 1, mid, cR);

    if (left && right) {
        if (qL < mid && qR > mid) {
            return tree[i * 2].right <= tree[i * 2 + 1].left;
        }
        return true;
    }

    return false;
}

bool decreasingQuery(ll qL, ll qR, ll i = 1, ll cL = 0, ll cR = n) {
    // the query range exactly matches this node's range of responsibility
    if (cL == qL && cR == qR)
        return tree[i].decreasing;
        
    // we might need to query one or both of the children
    ll mid = (cL + cR) / 2;
    bool left = true;
    bool right = true;

    if (qL < mid) left = decreasingQuery(qL, min(qR, mid), i * 2, cL, mid);
        
    // query the part within the right child [mid, cR), if any
    if (qR > mid) right = decreasingQuery(max(qL, mid), qR, i * 2 + 1, mid, cR);

    if (left && right) {
        if (qL < mid && qR > mid) {
            return tree[i * 2].right >= tree[i * 2 + 1].left;
        }
        return true;
    }

    return false;
}

// p is the index in the array (0-based)
// v is the value that the p-th element will be updated to
// i is the index in the tree , rooted at 1 so children are 2i and 2i+1
// instead of explicitly storing each node's range of responsibility [cL,cR), we
// calculate it on the way down
// the root node is responsible for [0, n)
void update(ll p, ll v, ll i = 1, ll cL = 0, ll cR = n) {
    if (cR - cL == 1) {
        // this node is a leaf , so apply the update
        tree[i].max = v;
        tree[i].sum = v;
        tree[i].left = v;
        tree[i].right = v;
        tree[i].increasing = true;
        tree[i].decreasing = true;
        return;
    }
    // figure out which child is responsible for the index (p) being updated
    ll mid = (cL + cR) / 2;
    if (p < mid)
        update(p, v, i * 2, cL, mid);
    else
        update(p, v, i * 2 + 1, mid, cR);

    // once we have updated the correct child , recalculate our stored value.
    tree[i].sum = tree[i*2].sum + tree[i*2+1].sum;
    tree[i].max = max(tree[i*2].max, tree[i*2+1].max);
    tree[i].left = tree[i*2].left;
    tree[i].right = tree[i*2+1].right;
    tree[i].increasing = tree[i*2].increasing && tree[i*2+1].increasing &&
                        (tree[i*2].right <= tree[i*2+1].left);
    tree[i].decreasing = tree[i*2].decreasing && tree[i*2+1].decreasing &&
        (tree[i*2].right >= tree[i*2+1].left);
}

// prll the entire tree to stderr
// instead of explicitly storing each node's range of responsibility [cL,cR), we
// calculate it on the way down
// the root node is responsible for [0, n)
void debug(ll i = 1, ll cL = 0, ll cR = n) {
    // prll current node's range of responsibility and value
    cerr << "tree[" << cL << "," << cR << ") = " << tree[i].increasing << endl;
    if (cR - cL > 1) { // not a leaf
        // recurse within each child
        ll mid = (cL + cR) / 2;
        debug(i * 2, cL, mid);
        debug(i * 2 + 1, mid, cR);
    }
}

int main()
{
    ll operations;
    cin >> n >> operations;

    for(ll i = 0; i < n; i++) 
    {
        ll difficulty;
        cin >> difficulty;
        update(i, difficulty);
    }

    REPi(operations) {
        char operation;
        ll x, y;
        cin >> operation >> x >> y;
        
        // update problem
        if (operation == 'U') {
            update(x - 1, y);
        } else if (operation == 'M') {
            cout << maxQuery(x - 1, y) << endl;
            // find most difficult problem
            // max
        } else if (operation == 'S') {
            cout << sumQuery(x - 1, y) << endl;
            // sum
        } else if (operation == 'I') {
            cout << increasingQuery(x - 1, y) << endl;
            // are problems in range x to y increasing
        } else if (operation == 'D') {
            // are problems in range x to y decreasing
            cout << decreasingQuery(x - 1, y) << endl;
        } else {
            cout << "Invalid operation " << operation << endl;
            return 0;
        }
    }

    // debug();
    return 0;
}
