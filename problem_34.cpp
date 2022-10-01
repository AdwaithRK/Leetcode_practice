#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    vector<int> searchRange(vector<int> &nums, int target)
    {

        int end = nums.size() - 1;
        int start = 0;
        int found_index = -1;

        while (start <= end)
        {
            int mid = (start + end) / 2;

            if (nums[mid] == target)
            {
                found_index = mid;
                break;
            }

            if (nums[mid] < target)
                start = mid + 1;

            if (nums[mid] > target)
                end = mid - 1;
        }

        if (found_index == -1)
            return {-1, -1};

        int left_end = found_index, right_end = found_index;

        while (left_end - 1 >= 0 && nums[left_end] == nums[left_end - 1])
            left_end = left_end - 1;

        while (right_end + 1 <= end && nums[right_end] == nums[right_end + 1])
            right_end = right_end + 1;

        return {left_end, right_end};
    }
};

int main()
{
    Solution a;
    vector<int> result = {1};
    a.searchRange(result, 1);

    return 0;
}