#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <stdio.h>
#include <set>
#define zero 48 
#define ll long long
using namespace std;

int main() {
    string infile = "Input/A-large-practice.in";
    string outfile = "Output/A-large-practice.out";
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
        ll N, K;
        instream >> N >> K;
        //cout << "O = " << O << " D = " << D << endl;
        vector <ll> A;
        for (int i = 0; i < N; i++)
        {
            int t;
            instream >> t;
            A.push_back(t);
        }
        sort(A.begin(), A.end());
        ll d = 0;
        for (ll i = 0; i < N; i++)
        {
            ll day = d / K;
            if (A[i] > day)
            {
                d++;
            }
        }
        printf("Case #%d: %lld\n", times, d);
        outstream << "Case #" << times << ": " << d << endl;
    }
    //cout << (-7 % 2) << endl;
    cout << "Input to exit: ";
    cin >> T;
}