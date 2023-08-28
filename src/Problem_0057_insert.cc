#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
  {
    int left = newInterval[0];
    int right = newInterval[1];
    bool inserted = false;
    vector<vector<int>> ans;
    for (auto &interval : intervals)
    {
      if (interval[1] < left)
      {
        // 在插入区间的左侧，且无交集
        ans.push_back({interval[0], interval[1]});
      }
      else if (right < interval[0])
      {
        // 在插入区间的右侧，且无交集
        if (!inserted)
        {
          ans.push_back({left, right});
          inserted = true;
        }
        ans.push_back({interval[0], interval[1]});
      }
      else
      {
        left = std::min(interval[0], left);
        right = std::max(interval[1], right);
      }
    }
    if (!inserted)
    {
      ans.push_back({left, right});
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> n1 = {{1, 3}, {6, 9}};
  vector<int> x1 = {2, 5};
  vector<vector<int>> o1 = {{1, 5}, {6, 9}};

  vector<vector<int>> n2 = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
  vector<int> x2 = {4, 8};
  vector<vector<int>> o2 = {{1, 2}, {3, 10}, {12, 16}};
  EXPECT_TRUE(o1 == s.insert(n1, x1));
  EXPECT_TRUE(o2 == s.insert(n2, x2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
