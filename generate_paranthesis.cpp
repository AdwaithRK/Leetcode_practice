#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

class Solution
{
    int limit;
    vector<string> result;

    void recursive_generation_strings(string s, int open, int close)
    {

        if (open == close && close == limit)
        {

            result.push_back(s);
            return;
        }
        else if (close > open)
        {
            return;
        }
        else if (open == close)
        {
            string temp = s;
            return recursive_generation_strings(temp.append("("), open + 1, close);
        }
        else if (open > close && open != limit)
        {
            string temp1 = s;
            recursive_generation_strings(temp1.append("("), open + 1, close);
            string temp2 = s;
            recursive_generation_strings(temp2.append(")"), open, close + 1);
            return;
        }
        else if (open > close && open == limit)
        {
            string temp3 = s;
            recursive_generation_strings(temp3.append(")"), open, close + 1);
        }
    }

public:
    vector<string> generateParenthesis(int n)
    {
        limit = n;
        string s = "";
        recursive_generation_strings(s, 0, 0);

        return result;
    }
};

int main()
{
    Solution s;
    s.generateParenthesis(3);
}