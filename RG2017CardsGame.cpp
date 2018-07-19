#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>
#include <set>
#include <queue>
#include <tuple>
#define zero 48 
using namespace std;

struct edge {
    int w;
    int u;
    int v;
    edge(int x, int y, int z) {
        w = x, u = y, v = z;
    }
    friend bool operator<(const edge& e1, const edge& e2) {
        return e1.w < e2.w;
    }
};

void GetEdges(int* R, int* B, vector<edge>& graph, int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (i != j) {
                int weight = (B[i] ^ R[j]) < (R[i] ^ B[j]) ? (B[i] ^ R[j]) : (R[i] ^ B[j]);
                graph.push_back(edge(weight, i, j));
            }
        }
    }
}

int GetAncestor(vector<int> ancestor, int x) {
    while (ancestor[x] != x) {
        x = ancestor[x];
    }
    return x;
}

int main() {
    string inFile = "Input/B-large-practice.in";
    string outFile = "Output/B-large-practice.out";
    ifstream inStream(inFile);
    ofstream outStream(outFile);
    int T;
    if (!inStream.is_open() || !outStream.is_open())
    {
        cout << "Error Opening File" << endl;
        exit(1);
    }
    inStream >> T;
    //cout << T << endl;
    for (int times = 1; times < T + 1; times++) {
        int N;
        inStream >> N;
        int* R = new int[N];
        int* B = new int[N];
        for (int i = 0; i < N; i++) {
            R[i] = 0;
            inStream >> R[i];
        }
        for (int i = 0; i < N; i++) {
            B[i] = 0;
            inStream >> B[i];
        }
        vector<edge> graph;
        /*cout << "R = ";
        for (int i = 0; i < N; i++) {
            cout << R[i] << " ";
        }
        cout << endl;
        cout << "B = ";
        for (int i = 0; i < N; i++) {
            cout << B[i] << " ";
        }
        cout << endl;*/
        GetEdges(R, B, graph, N);
        /*for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << graph[i][j] << " ";
            }
            cout << endl;
        }*/
        sort(graph.begin(), graph.end());
        vector<int>ancestor;
        long long res = 0;
        for (int i = 0; i < N; i++) {
            ancestor.push_back(i);
        }
        for (auto e: graph) {
            if (GetAncestor(ancestor, e.v) != GetAncestor(ancestor, e.u)) {
                res += e.w;
                ancestor[GetAncestor(ancestor, e.v)] = GetAncestor(ancestor, e.u);
            }
        }
        cout << "Case #" << times << ": " << res << endl;
        outStream << "Case #" << times << ": " << res << endl;
    }
    cout << "Press to exit: ";
    cin >> T;
}