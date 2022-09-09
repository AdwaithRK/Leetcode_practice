#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

class Solution
{
public:
    int reverse(int x)
    {

        if (x < -pow(2, 31) || x > (pow(2, 31) - 1))
            return 0;
        int n = x;
        long result = 0;
        while (n != 0)
        {
            result = result * 10 + n % 10;
            n = n / 10;
        }

        if (result < -pow(2, 31) || result > (pow(2, 31) - 1))
            return 0;

        return (int)result;
    }
};

int main(int argc, const char **argv)
{
    Solution a;
    int k = a.reverse(1534236469);
    cout << k;
    return 0;
}