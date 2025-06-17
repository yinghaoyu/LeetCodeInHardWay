#include <vector>

using namespace std;

class Solution {
  public:
    int removeDuplicates(vector<int> &nums) {
        int n = nums.size();
        int stack_size = 2; // 栈的大小，前两个元素默认保留
        for (int i = 2; i < n; i++) {
            if (nums[i] != nums[stack_size - 2]) { // 和栈顶下方的元素比较
                nums[stack_size++] = nums[i];      // 入栈
            }
        }
        // nums数组又可能只有一个元素
        return std::min(stack_size, n);
    }
};
