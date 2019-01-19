#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#define zero 48
using namespace std;

int main()
{
    ifstream instream("Input/B-large-practice.in");
    ofstream outstream("Output/B-large-pracice.out");
    int T;

    if (!instream.is_open() || !outstream.is_open())
    {
        cout << "Error Opening File!" << endl;
        exit(1);
    }

    instream >> T;
    for (int times = 1; times < T + 1; ++times)
    {
        int len;
        instream >> len;
        string s;
        instream >> s;
        //cout << "s = " << s << endl;
        vector<int> v;
        for (int i = 0; i < s.size(); i++)
        {
            v.push_back((int)s[i] - zero);
        }
        int max_score = 0;
        int score = 0;
        //cout << "len =" << s.size() / 2 << endl;
        for (int i = 0; i < s.size() / 2 + 1; i++)
        {
            if (i == 0)
            {
                for (int j = 0; j < (s.size() + 1) / 2; j++)
                {
                    score += v[j];
                }
            }
            else
            {
                score += s[i + (s.size() - 1) / 2] - s[i - 1];
            }
            //cout << "score = " << score << endl;
            if (score > max_score)
                max_score = score;
        }
        cout << "Case #" << times << ": " << max_score << endl;
        outstream << "Case #" << times << ": " << max_score << endl;
    }
    int done;
    cin >> done;
}