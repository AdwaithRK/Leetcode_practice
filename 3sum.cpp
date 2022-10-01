#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> k;
        for (int i = 0; i < nums.size(); i++)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            int cur = i;
            int left = cur + 1;
            int right = nums.size() - 1;

            while (left < right)
            {
                int current_sum = nums[i] + nums[left] + nums[right];
                if (current_sum == 0)
                {
                    vector<int> op = {nums[i], nums[left], nums[right]};
                    k.push_back(op);
                    left++;
                    right--;
                }
                else if (current_sum > 0)
                {
                    right--;
                }
                else if (current_sum < 0)
                {
                    left++;
                }
            }
        }
        return k;
    }
};

int main()
{
    Solution a;
    vector<int> k = {-2, 0, 0, 2, 2};
    k = a.threeSum(k);
}