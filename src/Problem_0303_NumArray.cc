#include <vector>

using namespace std;

class NumArray
{
 private:
  vector<int> sum;

 public:
  NumArray(vector<int>& nums)
  {
    sum = vector<int>(nums.size() + 1);
    for (int i = 1; i <= nums.size(); i++)
    {
      sum[i] = sum[i - 1] + nums[i - 1];
    }
  }

  int sumRange(int left, int right) { return sum[right + 1] - sum[left]; }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
