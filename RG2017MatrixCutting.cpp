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

long long GetMinValue(int** matrix, int topleftrow, int topleftcol, int bottomrightrow, int bottomrightcol) {
    int minval = INT_MAX;
    for (int i = topleftrow; i <= bottomrightrow; i++) {
        for (int j = topleftcol; j <= bottomrightcol; j++) {
            minval = min(minval, matrix[i][j]);
        }
    }
    return minval;
}

long long helper(int**** dp, int topleftrow, int topleftcol, int bottomrightrow, int bottomrightcol, int** matrix) {
    if (topleftrow == bottomrightrow && topleftcol == bottomrightcol) {
        return 0;
    }
    if (dp[topleftrow][topleftcol][bottomrightrow][bottomrightcol] > 0) {
        return dp[topleftrow][topleftcol][bottomrightrow][bottomrightcol];
    }
    long long maxval = 0;
    for (int cutrow = topleftrow; cutrow < bottomrightrow; cutrow++)
        maxval = max(maxval, helper(dp, topleftrow, topleftcol, cutrow, bottomrightcol, matrix)\
            + helper(dp, cutrow + 1, topleftcol, bottomrightrow, bottomrightcol, matrix));
    for (int cutcol = topleftcol; cutcol < bottomrightcol; cutcol++)
        maxval = max(maxval, helper(dp, topleftrow, topleftcol, bottomrightrow, cutcol, matrix)\
            + helper(dp, topleftrow, cutcol + 1, bottomrightrow, bottomrightcol, matrix));
    dp[topleftrow][topleftcol][bottomrightrow][bottomrightcol] = maxval + GetMinValue(matrix, topleftrow, topleftcol, bottomrightrow, bottomrightcol);
    return dp[topleftrow][topleftcol][bottomrightrow][bottomrightcol];
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
    for (int times = 1; times < T + 1; times++) {
        int N, M;
        instream >> N >> M;
        int** A = new int*[N];
        for (int i = 0; i < N; i++) {
            A[i] = new int[M];
            for (int j = 0; j < M; j++) {
                instream >> A[i][j];
            }
        }
        int**** dp = new int***[N];
        for (int i = 0; i < N; i++) {
            dp[i] = new int**[M];
            for (int j = 0; j < M; j++) {
                dp[i][j] = new int*[N];
                for (int k = 0; k < N; k++) {
                    dp[i][j][k] = new int[M];
                    for (int l = 0; l < M; l++) {
                        dp[i][j][k][l] = 0;
                    }
                }
            }
        }
        ll res =  helper(dp, 0, 0, N - 1, M - 1, A);
        cout << "Case #" << times << ": " << res << endl;
        outstream << "Case #" << times << ": " << res << endl;
        delete[] A;
        delete[] dp;
    }
    cout << "Input to exit: ";
    cin >> T;
}