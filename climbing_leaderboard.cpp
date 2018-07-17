//
// Created by dylan on 14/06/2018.
//

#include <iostream>
#include <bits/stdc++.h>


using namespace std;

vector<int> removeDup(vector<int>& in) {
    unordered_set<int> seen;
    vector<int> ret;
    for (int i : in) {
        if (seen.find(i) == seen.end()) {
            seen.insert(i);
            ret.push_back(i);
        }
    }
    return ret;
}

int calculateRank(vector<int>& scores, int score, int prevRank) {
    int revIdx = scores.size() - prevRank + 1;
    auto i = scores.rbegin() + revIdx;
    for (; i != scores.rend(); i++) {
        cout << score << " < " << *i << endl;
        if (score < *i) {
            return distance(scores.begin(), i.base()) + 1;
        }
    }
    return 1;
}

int get_rank(vector<int>& scores, int score) {
    if (score > scores[0]) return 0;
    if (score < scores[scores.size() - 1]) return scores.size();

    int lo = 0;
    int hi = scores.size() - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (score > scores[mid]) {
            hi = mid - 1;
        }
        else if (score < scores[mid]) {
            lo = mid + 1;
        }
        else {
            return mid;
        }
    }

    // work out which element is closer
    if (scores[lo] - score < scores[hi] - score) return lo;
    else return hi;
}

// Complexity = O(n + m log(n))
// n = scores.size()
// m = alice.size()
vector<int> climbingLeaderboard(vector<int> scores, vector<int> alice) {
    vector<int> ret;
    scores = removeDup(scores);
    int rank = scores.size() + 1;
    for (int score : alice) {
        rank = calculateRank(scores, score, rank);
        ret.push_back(rank);
    }
    return ret;
}

int main() {
    vector<int> a = {100, 100, 50, 40, 40, 20, 10};
    vector<int> b = removeDup(a);
    vector<int> scores = {10, 15, 45, 95, 110};
    for (int score : scores) {
        cout << score << " is rank " << get_rank(b, score) + 1 << endl;
    }
    return 0;
}
