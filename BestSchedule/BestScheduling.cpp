//
// Created by enszhou on 2019/11/8.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int n, k, best;

void schedule(int i, vector<int> &t, vector<int> &work, vector<int> &ends, vector<int> &dispatch) {
    if (i == n) {
        best = *max_element(ends.begin(), ends.end());
        dispatch.assign(work.begin(), work.end());
        return;
    }
    for (int j = 0; j < k; j++) {
        work[i] = j;
        ends[j] += t[i];
        if (ends[j] < best)
            schedule(i + 1, t, work, ends, dispatch);
        ends[j] -= t[i];
    }
}

int main() {
    cout << "n = ";
    cin >> n;
    cout << "k = ";
    cin >> k;
    cout << "cost:\n";
    best = INT_MAX;
    vector<int> t(n);
    vector<int> work(n);
    vector<int> ends(k, 0);
    vector<int> dispatch(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }
    schedule(0, t, work, ends, dispatch);
    cout << "the earliest time:" << best << endl;
    for (int i = 0; i < n; i++) {
        printf("%dth task -> %dth machine\n", i + 1, dispatch[i]+1);
    }
}
