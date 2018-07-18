#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#define zero 48 
#define little_a 97
#define little_alphabet 26
#define ll long long
using namespace std;

long long CalPow(int k, int i) {
    if (i == 0) return 1;
    if (i == 1) return k;
    long long res = k;
    int p = 1;
    while (p * 2 <= i) {
        res = res * res % long long(1e9 + 7);
        p = p * 2;
    }
    return res * CalPow(k, i - p) % long long(1e9 + 7);
}

long long GetPower(long long* A, int N, int i) {
    long long ret = 0;
    for (int length = 1; length <= N; length++) {
        for (int start = 0; start <= N - length; start++) {
            for (int k = 0; k < length; k++) {
                ret += A[start + k] * long long (CalPow(k + 1, i)) % long long(1e9 + 7);
                ret = ret % long long(1e9 + 7);
            }
        }
    }
    return ret;
}

long long GetResult(long long* A, int N, int K) {
    ll ret = 0;
    ll argument = K;
    for (int x = 1; x <= N; x++) {
        if (x != 1) {
            argument += (CalPow(x, K + 1) - x) * CalPow(x - 1, ll(1e9 + 5));
            argument %= ll(1e9 + 7);
        }
        ret += (N - x + 1) * (( argument * A[x - 1])% ll(1e9 + 7));
        ret %= ll(1e9 + 7);
    }
    return ret;
}
int main() {
    string infile = "Input/C-large-practice.in";
    string outfile = "Output/C-large-practice.out";
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
    for (int i = 1; i < T + 1; i++) {
        ll N, K, x1, y1, C, D, E1, E2, F;
        instream >> N >> K >> x1 >> y1 >> C >> D >> E1 >> E2 >> F;
        ll* A = new long long[N];
        ll x_prev = x1;
        ll y_prev = y1;
        A[0] = (x1 + y1) % F;
        for (int i = 1; i < N; i++) {
            ll x = (C * x_prev + D * y_prev + E1) % F;
            ll y = (D * x_prev + C * y_prev + E2) % F;
            A[i] = (x + y) % F;
            x_prev = x;
            y_prev = y;
        }
        long long res = 0;
        res = GetResult(A, N, K);
        delete[] A;
        cout << "Case #" << i << ": " << res << endl;
        outstream << "Case #" << i << ": " << res << endl;
    }
    cout << "Input to exit: ";
    cin >> T;
}