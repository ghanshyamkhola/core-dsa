#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> targetIndices(std::vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        std::vector<int> result;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == target) {
                result.push_back(i);
            }
        }
        return result;
    }
};