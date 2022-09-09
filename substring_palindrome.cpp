#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;

class Solution
{

    string find_substring(string s)
    {
        cout << s;
        int n = s.size();
        int max_lenght = 2;
        int start;

        string result = "";

        bool table[n][n];

        memset(table, false, sizeof(n * n));

        for (int i = 0; i < n; i++)
            table[i][i] = true;

        for (int i = 0; i < n - 1; i++)
        {
            if (s[i] == s[i + 1])
                table[i][i + 1] = true;
        }

        for (int k = 3; k < n; k++)
        {

            for (int i = 0; i <= n - k + 1; i++)
            {
                if (s[i] == s[i + k - 1] && table[i - 1][i + k - 2] == true)
                    table[i][i + k - 1] = true;

                if (table[i][i + k - 1] && max_lenght < k)
                {
                    max_lenght = k;
                    start = i;
                }
            }
        }

        for (int i = start; i < max_lenght - 1; i++)
        {
            result.append(1, s[i]);
        }

        return result;
    }

public:
    string longestPalindrome(string s)
    {
        int n = s.size();

        string result = find_substring(s);

        return "";
    }
};

int main()
{
    Solution a;
    a.longestPalindrome("abhbaaabll");
    return 0;
}