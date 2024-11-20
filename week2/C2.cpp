#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <set>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;

#define REPi(n) for (ll i = 0; i < n; i++)
#define REPj(n) for (ll j = 0; j < n; j++)

ll numStudents, bugs, maxPass;

auto cmp = [](const tuple<long long, long long, long long>& a,
                const tuple<long long, long long, long long>& b) {
    return get<1>(a) > get<1>(b); 
};

// bugNum, complexity
vector<pair<ll, ll>> complexities;

// skills, pass, student num
vector<tuple<ll, ll, ll>> students;

// indicates which bug was completed by which student
vector<ll> bugCompleted;

bool canDo(ll days) {
    priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, decltype(cmp)> pq(cmp);
    vector<ll> studentOrder;
    ll currPass = 0;

    ll studentIndex = 0;

    ll remainingBugs = bugs;
    ll bugIndex = 0;
    ll studentsUsed = 0;
    while (remainingBugs > 0) {
        ll hardBug = complexities[bugIndex].second;
        // push all students to pq that can solve currhardestbug
        while (studentIndex < numStudents && get<0>(students[studentIndex]) >= hardBug) {
            pq.push(students[studentIndex]);
            studentIndex++;
        }

        // ran out of students
        if (pq.empty()) {
            std::cerr << "No student can solve bug" << endl;
            return false;
        }

        // get top student and their passes
        auto bestStudent = pq.top();
        ll passes = get<1>(bestStudent);
        ll studentNum = get<2>(bestStudent);
        studentOrder.push_back(studentNum);

        if ((currPass + passes) > maxPass) {
            // means no other student can help
            return false;
        }

        currPass += passes;
        ll bugsToSolve = min(days, remainingBugs);
        remainingBugs -= bugsToSolve;
        pq.pop();
        studentsUsed++;

        bugIndex += bugsToSolve;
    }

    // populate the ting
    bugIndex = 0;
    REPi(studentsUsed) {
        ll studentNum = studentOrder[i];
        for (int j = 0; j < days; j++) {
            if (bugIndex >= bugs) {
                break;
            }

            ll bugNum = complexities[bugIndex].first;
            bugCompleted[bugNum] = studentNum; 
            bugIndex++;
        }
    }

    cerr << "BUG ASSIGNMENTS COMPLETE" << endl;

    return true;
}

int main() {
    cin >> numStudents >> bugs >> maxPass;

    ll bugI = 0;
    REPi(bugs) {
        ll complexity;
        cin >> complexity;
        complexities.push_back({bugI, complexity});
        bugI++;
    }

    // Sort complexities in descending order of their complexity
    sort(complexities.begin(), complexities.end(), [](const pair<ll, ll>& a, const pair<ll, ll>& b) {
        return a.second > b.second;
    });

    vector<ll> skills(numStudents);
    for (ll i = 0; i < numStudents; ++i) {
        cin >> skills[i];
    }

    int studentNum = 1;
    for (ll i = 0; i < numStudents; ++i) {
        ll passes;
        cin >> passes;
        students.push_back(make_tuple(skills[i], passes, studentNum));
        studentNum++;
    }

    // sort students by their skills in descending order
    sort(students.begin(), students.end(), [](const tuple<ll, ll, ll>& a, const tuple<ll, ll, ll>& b) {
        return get<0>(a) > get<0>(b);
    });

    bugCompleted.resize(bugs, -1);

    ll lo = 1;
    ll hi = bugs;
    ll ans = -1;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        cerr << "mid: " << mid << " hi: " << hi << endl;
        if (canDo(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    cerr << ans << endl;
    if (ans == -1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        REPi(bugs) {
            cout << bugCompleted[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
