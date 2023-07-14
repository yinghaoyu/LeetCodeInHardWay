#include <iostream>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<vector<int>> findContinuousSequence(int target)
  {
    int left = 1;
    int right = 2;
    int sum = 3;
    vector<vector<int>> ans;
    while (left < right)
    {
      if (sum == target)
      {
        vector<int> cur;
        for (int i = left; i <= right; i++)
        {
          cur.push_back(i);
        }
        ans.emplace_back(cur);
      }

      if (sum < target)
      {
        right++;
        sum += right;
      }
      else
      {
        sum -= left;
        left++;
      }
    }
    return ans;
  }
};
