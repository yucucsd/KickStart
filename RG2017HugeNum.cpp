#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#define zero 48 
#define ll long long
using namespace std;

int CalPow(int a, int exp, int P) {
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
    string inFile = "Input/A-large-practice.in";
    string outFile = "Output/A-large-practice.out";
    ifstream inStream(inFile);
    ofstream outStream(outFile);
    int T;
    string N;
    if (!inStream.is_open() || !outStream.is_open()) 
    {
        cout << "Error Opening File" << endl;
        exit(1);
    }
    inStream >> T;
    //cout << T << endl;
    for (int i = 1; i < T + 1; i++) {
        int A, N, P;
        inStream >> A >> N >> P;
        int sol = A % P;
        for (int i = 2; i <= N; i++) {
            sol = CalPow(sol, i, P);
        }
        cout << "Case #" << i << ": " << sol << endl;
        outStream << "Case #" << i << ": " << sol << endl;
    }
    cout << "Input to exit: ";
    cin >> T;
}