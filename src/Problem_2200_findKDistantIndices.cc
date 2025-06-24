#include <vector>

using namespace std;

class Solution {
  public:
    vector<int> findKDistantIndices(vector<int> &nums, int key, int k) {
        int n = nums.size();
        vector<int> ans;
        int l = 0;
        int r = 0;
        // 区间为 [l, r)
        for (int j = 0; j < n; j++) {
            if (nums[j] == key) {
                // 为了避免重复添加，需要取r与j-k的最大值
                l = std::max(r, j - k);
                r = std::min(n - 1, j + k) + 1;
                for (int i = l; i < r; i++) {
                    ans.push_back(i);
                }
            }
        }
        return ans;
    }
};
