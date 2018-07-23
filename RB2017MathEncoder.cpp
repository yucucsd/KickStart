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

int CalPow(int a, int exp, ll P) {
    if (exp == 0) return 1 % P;
    if (exp == 1) return a % P;
    int p = 1;
    ll t = a;
    while (2 * p <= exp) {
        t = t * t % P;
        p *= 2;
    }
    return t * CalPow(a, exp - p, P) % P;
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
        int N;
        instream >> N;
        ll res;
        if (N == 1) {
            res = 0;
        }
        else {
            vector<ll> A(N, 0);
            for (int i = 0; i < N; i++) {
                instream >> A[i];
            }
            sort(A.begin(), A.end());
            vector<ll> c(N, 0);
            vector<ll> u(N, 0);
            for (int i = 1; i < c.size(); i++) {
                for (int j = 0; j < i; j++) {
                    u[i] += c[j];
                    c[i] += c[j] + CalPow(2, j, 1e9 + 7) * (A[i] - A[j]);
                    u[i] %= ll(1e9 + 7);
                    c[i] %= ll(1e9 + 7);
                }
            }
            /*for (int i = 0; i < N; i++) {
                cout << c[i] << " ";
            }
            cout << endl;
            for (int i = 0; i < N; i++) {
                cout << u[i] << " ";
            }
            cout << endl;*/
            res = (c[N - 1] + u[N - 1]) % ll(1e9 + 7);
            cout << "Case #" << times << ": " << res << endl;
            outstream << "Case #" << times << ": " << res << endl;
        }
    }
    cout << "Input to exit: ";
    cin >> T;
}