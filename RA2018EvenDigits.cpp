#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#define zero 48 
#define ll long long
using namespace std;

int GetPrefix(string s, string rest, int e) {
    int max_match = 0;
    int i = 0;
    while (i < e - max_match) {
        int j = i;
        while (j < e && j < s.size() - e + i && rest[j - i] == s[j]) {
            j++;
        }
        if (j - i > max_match)
            max_match = j - i;
        i++;
    }
    return max_match;
}

int GetClip(string s, string clipboard, int e) {
    int i = e;
    int length = 0;
    while (i < s.size() && i < clipboard.size() + e && s[i] == clipboard[i - e]) {
        i++;
    }
    length = i - e;
    return length;
}

int main() {
    string infile = "Input/A-small-practice.in";
    string outfile = "Output/A-small-practice.out";
    ifstream instream(infile);
    ofstream outstream(outfile);
    int T;
    if (!instream.is_open() || !outstream.is_open()) 
    {
        cout << "Error Opening File" << endl;
        exit(1);
    }
    instream >> T;
    //cout << T << endl;
    for (int times = 1; times < T + 1; times++) {
        ll res = 0;
        string N;
        instream >> N;
        int first = -1;
        int size = -1;
        for (int i = 0; i < N.size(); i++) {
            if ((N[i] - zero) % 2 == 1) {
                first = i;
                break;
            }
        }
        if (first >= 0) {
            cout << N << endl;
            ll up, low;
            if (N[first] - zero == 9) {
                up = 2 * ll(pow(10, N.size() - first));
            }
            else {
                up = (N[first] - zero + 1) * pow(10, N.size() - first - 1);
            }
            low = (N[first] - zero - 1) * pow(10, N.size() - first - 1);
            for (int i = 0; i < N.size() - first - 1; i++) {
                low += 8 * pow(10, i);
            }
            ll val = _atoi64(N.c_str()) % ll(pow(10, N.size() - first));
            cout << val << " " << up << " " << low << endl;
            res = val - low < up - val ? val - low : up - val;
        }
        cout << "Case #" << times << ": " << res << endl;
        outstream << "Case #" << times << ": " << res << endl;
    }
    cout << "Input to exit: ";
    cin >> T;
}
