#include <vector>

using namespace std;

class Solution {
  public:
    int maximumDifference(vector<int> &nums) {
        int n = nums.size();
        int ans = -1;
        // nums[0...j-1]前缀最小值
        int min = nums[0];
        for (int j = 1; j < n; j++) {
            if (nums[j] > min) {
                ans = std::max(ans, nums[j] - min);
            } else {
                min = nums[j];
            }
        }
        return ans;
    }
};
