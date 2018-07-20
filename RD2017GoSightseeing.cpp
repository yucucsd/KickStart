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

ll arrive(ll time, ll s, ll f, ll d) {
    if (time <= s)
        return s + d;
    else
        return (time - s + f - 1) / f * f + s + d;
}
int main() {
    string infile = "Input/A-large-practice.in";
    string outfile = "Output/A-large-practice.out";
    ifstream instream(infile);
    ofstream outstream(outfile);
    int T;
    string N;
    if (!instream.is_open() || !outstream.is_open()) 
    {
        cout << "Error Opening File" << endl;
        exit(1);
    }
    instream >> T;
    //cout << T << endl;
    for (int times = 1; times < T + 1; times++) {
        int N, Ts, Tf;
        instream >> N >> Ts >> Tf;
        vector<ll> S(N - 1, 0);
        vector<ll> F(N - 1, 0);
        vector<ll> D(N - 1, 0);
        for (int i = 0; i < N - 1; i++) {
            instream >> S[i] >> F[i] >> D[i];
        }
        vector<vector<ll>> res;
        for (int i = 0; i < N - 1; i++) {
            vector <ll> v(i + 2, 0);
            res.push_back(v);
        }
        res[0][0] = arrive(0, S[0], F[0], D[0]);
        res[0][1] = arrive(Ts, S[0], F[0], D[0]);
        for (int i = 1; i < N - 1; i++) {
            for (int j = 0; j <= i + 1; j++) {
                if (j > 0 && j < i + 1)
                    res[i][j] = min(arrive(res[i - 1][j], S[i], F[i], D[i]), arrive(res[i - 1][j - 1] + Ts, S[i], F[i], D[i]));
                else {
                    if (j >= i + 1)
                        res[i][j] = arrive(res[i - 1][j - 1] + Ts, S[i], F[i], D[i]);
                    if (j == 0)
                        res[i][j] = arrive(res[i - 1][j], S[i], F[i], D[i]);
                }
            }
        }
        ll maxcity = -1;
        for (int j = 0; j <= N - 1; j++) {
            if (res[N - 2][j] <= Tf && j > maxcity)
                maxcity = j;
        }
       if (maxcity > -1){
            cout << "Case #" << times << ": " << maxcity << endl;
            outstream << "Case #" << times << ": " << maxcity << endl;
        }
        else {
            cout << "Case #" << times << ": IMPOSSIBLE"  << endl;
            outstream << "Case #" << times << ": IMPOSSIBLE" << endl;
        }
    }
    cout << "Input to exit: ";
    cin >> T;
}