#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#define ll long long
#define zero 48
using namespace std;

int main()
{
    ifstream instream("Input/A-large-practice.in");
    ofstream outstream("Output/A-large-pracice.out");
    int T;

    if (!instream.is_open() || !outstream.is_open())
    {
        cout << "Error Opening File!" << endl;
        exit(1);
    }

    instream >> T;
    for (int times = 1; times < T + 1; ++times)
    {
        int N, P;
        instream >> N >> P;
        set<string> v;
        for (int p = 0; p < P; ++p)
        {
            string s;
            instream >> s;
            v.insert(s);
        }
        set<string>::iterator iter_prev = v.begin();
        set<string>::iterator iter = v.begin();
        ++iter;
        while (iter != v.end())
        {
            if ((*iter_prev).size() <= (*iter).size())
            {
                string t = (*iter).substr(0, (*iter_prev).size());
                if (t.compare(*iter_prev) == 0)
                {
                    set<string>::iterator iter_t = iter;
                    ++iter;
                    v.erase(iter_t);
                    continue;
                }
            }
            ++iter;
            ++iter_prev;
        }
        double res = pow(2.0, (double)N);
        for (iter = v.begin(); iter != v.end(); ++iter)
        {
            double deduct = pow(2.0, (double)(N - (*iter).size()));
            res -= deduct;
        }
        cout << "Case #" << times << ": " << (ll)res << endl;
        outstream << "Case #" << times << ": " << (ll)res << endl;
    }
    int done;
    cin >> done;
}

/*
for loop execution sequence:
for(A.initialization; B.condition; C.increment)
{
    D...
}
A->B->D->C->B->D->C->B->D->бн
*/