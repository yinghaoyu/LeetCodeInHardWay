#include <vector>

using namespace std;

// TODO: figure it out
class Solution
{
 public:
  int minOperations(vector<int>& nums)
  {
    vector<int> stack;
    int ans = 0;
    for (int num : nums)
    {
      while (!stack.empty() && stack.back() > num)
      {
        stack.pop_back();
      }
      if (num == 0)
      {
        continue;
      }
      if (stack.empty() || stack.back() < num)
      {
        ans++;
        stack.push_back(num);
      }
    }
    return ans;
  }
};
