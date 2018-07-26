#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>
#include <set>
#include <queue>
#include <tuple>
#include <map>
#define zero 48 
#define ll long long
using namespace std;

ll Choose3(ll k) {
    return k * (k - 1) *(k - 2) / 6;
}

ll Choose2(ll k) {
    return k * (k - 1) / 2;
}

int main() {
    string inFile = "Input/B-large-practice.in";
    string outFile = "Output/B-large-practice.out";
    ifstream instream(inFile);
    ofstream outstream(outFile);
    int T;
    if (!instream.is_open() || !outstream.is_open())
    {
        cout << "Error Opening File" << endl;
        exit(1);
    }
    instream >> T;
    //cout << T << endl;
    for (int times = 1; times < T + 1; times++) {
        int N;
        instream >> N;
        int* S = new int[N];
        for (int i = 0; i < N; i++) {
            S[i] = 0;
            instream >> S[i];
        }
        map<int, int> m_c;
        for (int i = 0; i < N; i++) {
            if (m_c.find(S[i]) == m_c.end()) {
                m_c[S[i]] = 1;
            }
            else {
                m_c[S[i]] += 1;
            }
        }
        vector<ll> sum_prefix(m_c.size(), 0);
        vector<ll> count(m_c.size(), 0);
        vector<ll> val(m_c.size(), 0);
        sum_prefix[0] = m_c.begin()->second;
        int p = 0;
        for (map<int, int>::iterator iter = m_c.begin(); iter != m_c.end(); iter++) {
            count[p] = iter->second;
            val[p] = iter->first;
            if (p >= 1)
                sum_prefix[p] = sum_prefix[p - 1] + count[p];
            p++;
        }
        /*for (int i = 0; i < val.size(); i++) {
            cout << val[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < count.size(); i++) {
            cout << count[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < sum_prefix.size(); i++) {
            cout << sum_prefix[i] << " ";
        }
        cout << endl;*/
        ll res = 0;
        for (int i = 0; i < val.size(); i++) {
            if (count[i] >= 3) {
                vector<ll>::iterator iter = lower_bound(val.begin(), val.end(), 3 * val[i]);
                if (iter != val.end()) {
                    for (int j = 0; j < val.size(); j++) {
                        if (val[j] == *iter)
                            p = j;
                    }
                    p--;
                }
                else {
                    p = val.size() - 1;
                }
                res += (sum_prefix[p] - count[i]) * Choose3(count[i]);
            }
        }
        for (int i = 0; i < val.size(); i++) {
            if (count[i] >= 2) {
                for (int j = 0; j < val.size(); j++) {
                    if (j != i) {
                        vector<ll>::iterator iter = lower_bound(val.begin(), val.end(), 2 * val[i] + val[j]);
                        if (iter != val.end()) {
                            for (int k = 0; k < val.size(); k++) {
                                if (val[k] == *iter)
                                    p = k;
                            }
                            p--;
                        }
                        else {
                            p = val.size() - 1;
                        }
                        if (p > j && j < i) {
                            res += (sum_prefix[p] - sum_prefix[j] - count[i]) * count[j] * Choose2(count[i]);
                        }
                        else if (p > j && j > i) {
                            res += (sum_prefix[p] - sum_prefix[j]) * count[j] * Choose2(count[i]);
                        }
                    }
                }
            }
        }
        cout << "Case #" << times << ": " << res << endl;
        outstream << "Case #" << times << ": " << res << endl;
    }
    cout << "Press to exit: ";
    cin >> T;
}