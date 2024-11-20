#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compareJobs(const pair<long long, long long>& job1, const pair<long long, long long>& job2) {
    // duration first
    if (job1.first != job2.first) {
        return job1.first < job2.first; 
    }
    // deadline second
    return job1.second < job2.second; 
}

int main() {
    long long n;
    cin >> n; 

    vector<pair<long long, long long>> jobs(n);

    for (long long i = 0; i < n; ++i) {
        long long duration, deadline;
        cin >> duration >> deadline;
        jobs[i] = make_pair(duration, deadline);
    }

    // Sort the jobs using the custom comparator
    sort(jobs.begin(), jobs.end(), compareJobs);


    // calculate the price
    long long totalsum = 0;
    long long days_passed = 0;
    for (const auto& job: jobs) {
        days_passed += job.first;
        totalsum += job.second - (days_passed);
    }

    cout << totalsum << endl;

    return 0;
}