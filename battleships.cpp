#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Ship {
private:
    unordered_map<string, int> _positions;

    void GetPositions(string& posString, int& x, int& y) {
        if (posString.size() == 2) {
            x = posString[0] - '0';
            y = posString[1] - 64;
        }
        else if (posString.size() == 3) {
            x = stoi(posString.substr(0, 2));
            y = posString[2] - 64;
        }
    }
public:
    explicit Ship(const string pos) {
            string first;
            string second;

            stringstream s(pos);
            s >> first;
            s >> second;

            int firstx = 1;
            int firsty = 1;
            int lastx = 1;
            int lasty = 1;

            GetPositions(first, firstx, firsty);
            GetPositions(second, lastx, lasty);

            for (int i = firstx; i <= lastx; i++) {
                for (int j = firsty; j <= lasty; j++) {
                    string pos;
                    pos.append(to_string(i));
                    pos += char(j + 64);
                    _positions[pos] = 1;
                }
            }
    }
    
    bool IsHit = false;

    bool IsAlive() {
        for (auto i : _positions) {
            if (i.second != 0) return true;
        }
        return false;
    }

    void TryHit(const string& pos) {
        if (_positions.find(pos) != _positions.end()) {
            _positions[pos] = 0;
            IsHit = true;
        }
    }
};

vector<string> getPositions(string& S) {
    vector<string> ship_pos;
    stringstream Ss(S);
    string temp;

    while (Ss.good()) {
        getline(Ss, temp, ',');
        ship_pos.push_back(temp);
    }

    return ship_pos;
}

vector<string> getHits(string& T) {
    stringstream Ts(T);
    vector<string> hits;
    string temp;

    while (Ts >> temp) {
        hits.push_back(temp);
    }

    return hits;
}

int main() {
    string S = "1A 2A,12A 12A";
    string T = "12A";

    vector<string> ship_pos = getPositions(S);
    vector<string> hits = getHits(T);

    vector<Ship> ships;
    for (string p : ship_pos) {
        Ship s(p);
        ships.push_back(s);
    }

    for (string hit : hits) {
        for (Ship &s : ships) {
            s.TryHit(hit);
        }
    }


    int numHit = 0;
    int numDead = 0;
    for (Ship &s : ships) {
        if (!s.IsAlive()) {
            numDead++;
        }
        else if (s.IsHit) {
            numHit++;
        }
    }

    cout << to_string(numDead) + "," + to_string(numHit) << endl;
    return 0;
}