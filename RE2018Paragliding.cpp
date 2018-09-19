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

class obj {
public:
    obj(ll xi, ll yi) {
        x = xi;
        y = yi;
    }
    ll x;
    ll y;
};
void init(vector<obj>& s, ll x1, ll x2, ll ax, ll bx, ll cx, ll mx, ll y1, ll y2, ll ay, ll by, ll cy, ll my, ll N)
{
    s.push_back(obj(x1, y1));
    s.push_back(obj(x2, y2));
    for (int i = 2; i < N; i++) 
    {
        ll x = (s[i - 1].x * ax + s[i - 2].x * bx + cx) % mx + 1;
        ll y = (s[i - 1].y * ay + s[i - 2].y * by + cy) % my + 1;
        s.push_back(obj(x, y));
    }
}
void print(vector<obj> obs) 
{
    cout << "{";
    for (auto ob : obs) {
        cout << " [" << ob.x << ", " << ob.y << "],";
    }
    cout << "}" << endl;
}

bool cmpobj(obj a, obj b) {
    return a.x < b.x;
}

bool check_covered(obj t,obj b, int k)
{
    if (k == 0) {
        if (abs(t.x - b.x) <= t.y - b.y)
        {
            return true;
        }
        return false;
    }
    else
    {
        if (abs(t.x - b.x) <= abs(t.y - b.y))
        {
            return true;
        }
        return false;
    }
}


vector<obj> remove_covered_tower(vector<obj> tower) {
    vector<obj> tower_clean;
    ll i = 0;
    while (i < tower.size())
    {
        if (tower_clean.size() == 0)
        {
            tower_clean.push_back(tower[i]);
            i++;
        }
        else
        {
            if (check_covered(tower_clean[tower_clean.size() - 1], tower[i], 1))
            {
                if (tower_clean[tower_clean.size() - 1].y < tower[i].y)
                {
                    tower_clean.pop_back();
                }
                else
                {
                    i++;
                }
            }
            else
            {
                tower_clean.push_back(tower[i]);
                i++;
            }
        }
    }
    return tower_clean;
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
        ll N, K;
        instream >> N >> K;
        ll p1, p2, A1, B1, C1, M1, h1, h2, A2, B2, C2, M2, x1, x2, A3, B3, C3, M3, y1, y2, A4, B4, C4, M4;
        instream >> p1 >> p2 >> A1 >> B1 >> C1 >> M1 >> h1 >> h2 >> A2 >> B2 \
        >> C2 >> M2 >> x1 >> x2 >> A3 >> B3 >> C3 >> M3 >> y1 >> y2 >> A4 >> B4 >> C4 >> M4;
        vector<obj> tower;
        vector<obj> balloon;
        init(tower, p1, p2, A1, B1, C1, M1, h1, h2, A2, B2, C2, M2, N);
        init(balloon, x1, x2, A3, B3, C3, M3, y1, y2, A4, B4, C4, M4, K);
        sort(tower.begin(), tower.end(), cmpobj);
        //sort(balloon.begin(), balloon.end(), cmpobj);
        //print(tower);
        vector<obj> tower_clean = remove_covered_tower(tower);
        //print(tower);
        ll c = 0;
        for (auto b : balloon)
        {
            vector<obj>::iterator iter = lower_bound(tower_clean.begin(), tower_clean.end(), b, cmpobj);
            if (iter != tower_clean.begin())
            {
                if (check_covered(*(iter - 1), b, 0))
                {
                    c++;
                    continue;
                }
            }
            if (iter != tower_clean.end())
            {
                if (check_covered(*iter, b, 0))
                {
                    c++;
                    continue;
                }
            }
        }
        cout << "Case #" << times << ": " << c << endl;
        outstream << "Case #" << times << ": " << c << endl;
    }
    cout << "Input to exit: ";
    cin >> T;
}