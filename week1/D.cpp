#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    long long days;
    cin >> days;

    vector<long long> values;
    for (long long i = 0; i < days; i++) {
        long long value;
        cin >> value;
        values.push_back(value);
    }

    // start from right to left
    vector<long long> final_marks(days, 0);
    long long marks = 0;
    for (long long i = days - 1; i >= 0; i--) {
        // try to decrease by 1 each time
        marks = max(0LL, marks - 1);
        marks = max(values[i] + 1, marks);
        final_marks[i] = marks;
    }

    long long max_val = 0;
    // now left to right to ensure all the values are increasing
    for (long long i = 0; i < values.size(); i++) {
        max_val = max(max_val, final_marks[i]);
        final_marks[i] = max_val;
    }

    long long total_water_marks = 0;

    for (long long i = 0; i < final_marks.size(); i++) {
        total_water_marks += final_marks[i] - values[i] - 1;
    }

    cout << total_water_marks << endl;

    return 0;
}