#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <stack>

using namespace std;

unordered_map<string, int> wordIndex;
vector<string> words(16);
// vector<vector<int>> adj(16);
vector<int> group(16, -1);
// see if this would work
int adjMatrix[16][16] = {{0}};

vector<int> degree(16, 0);

// use of this for O(1) checks
// vector<bitset<16>> neighborMasks(16);

// this would place it inside of the group
// this would store the index instead of hte whole strings.
bool canPlaceInGroup(int wordIndex, int groupIndex, const vector<vector<int>>& groups) {
    if (groups[groupIndex].size() == 4) return false;

    // fjkldsahflkdash too easy
    for (int index : groups[groupIndex]) {
        if (adjMatrix[wordIndex][index] == 0) {
            return false;
        }
    }

    return true;
}

// backtracking with index
bool backtrack(vector<vector<int>>& groups) {
    // use of stack for this quesiton where its the same idea but recursion might be too slow
    stack<pair<int, vector<vector<int>>>> stk;
    stk.push({0, groups});
    
    while (!stk.empty()) {
        auto [index, currGroups] = stk.top();
        stk.pop();

        // as soon as i get to 16 leaveee
        if (index == 16) {
            groups = currGroups;
            return true;
        }

        for (int i = 0; i < 4; ++i) {
            if (canPlaceInGroup(index, i, currGroups)) {
                currGroups[i].push_back(index);
                stk.push({index + 1, currGroups});
                currGroups[i].pop_back();
            }
        }
    }

    return false;
}

// this would check if it has degree of 3 
// if its les than 3 then it owuld output as false
bool check() {
    for (int i = 0; i < 16; ++i) {
        if (degree[i] < 3) {
            return false;
        }
    }

    return true;
}


int main() {
    // hope this works
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 16; ++i) {
        cin >> words[i];
        wordIndex[words[i]] = i;
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string word1, word2;
        cin >> word1 >> word2;

        int index1 = wordIndex[word1];
        int index2 = wordIndex[word2];

        // storing it as a adjacency list instead of an actual string
        adjMatrix[index1][index2] = 1;
        adjMatrix[index2][index1] = 1;

        degree[index1]++;
        degree[index2]++;
    }

    // this would be the valid componenet
    vector<vector<int>> groups(4);

    if (!check()) {
        cout << "Impossible\n";
        return 0;
    }

    // // pre setting the neighbours to optimise it 
    // vector<unordered_set<int>> neighbors(16);
    // for (int i = 0; i < 16; ++i) {
    //     for (int j : adj[i]) {
    //         neighbors[i].insert(j);
    //     }
    // }

    if (backtrack(groups)) {
        cout << "Possible" << endl;
        for (int i = 0; i < 4; ++i) {
            for (int indx : groups[i]) {
                cout << words[indx] << " ";
            }
            cout << "\n";
        }
    } else {
        cout << "Impossible" << endl;
    }

    return 0;
}
