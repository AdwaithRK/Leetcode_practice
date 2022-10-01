#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

class Solution
{
    vector<vector<int>> pascal_dp;

public:
    vector<int> getRow(int rowIndex)
    {
        pascal_dp.resize(34); // resize top level vector

        for (int i = 0; i <= rowIndex; i++)
        {
            pascal_dp[i].resize(34);
            for (int j = 0; j <= i; j++)
            {
                if (i == j || j == 0)
                {
                    pascal_dp[i][j] = 1;
                }
                else
                {
                    pascal_dp[i][j] = pascal_dp[i - 1][j] + pascal_dp[i - 1][j - 1];
                }
            }
        }
        return pascal_dp[rowIndex];
    }
};

int main(int argc, const char **argv)
{
    Solution k;
    k.getRow(3);

    return 0;
}