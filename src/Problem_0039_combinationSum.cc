#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  void process(vector<int> &candidates, int index, int target, vector<int> &cur, vector<vector<int>> &ans)
  {
    if (index == candidates.size())
    {
      if (target == 0)
      {
        ans.push_back(cur);
      }
      return;
    }
    for (int i = 0; i * candidates[index] <= target; i++)
    {
      std::fill_n(std::back_inserter(cur), i, candidates[index]);
      process(candidates, index + 1, target - i * candidates[index], cur, ans);
      cur.erase(std::remove(cur.begin(), cur.end(), candidates[index]), cur.end());
    }
  }

  vector<vector<int>> combinationSum(vector<int> &candidates, int target)
  {
    vector<vector<int>> ans;
    vector<int> cur;
    process(candidates, 0, target, cur, ans);
    return ans;
  }
};

bool isVectorEuqal(vector<vector<int>> a, vector<vector<int>> b)
{
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  return a == b;
}

void testCombinationSum()
{
  Solution s;
  vector<int> n1 = {2, 3, 6, 7};
  vector<int> n2 = {2, 3, 5};
  vector<int> n3 = {2};

  vector<vector<int>> o1 = {{2, 2, 3}, {7}};
  vector<vector<int>> o2 = {{2, 2, 2, 2}, {2, 3, 3}, {3, 5}};
  vector<vector<int>> o3;
  EXPECT_TRUE(isVectorEuqal(o1, s.combinationSum(n1, 7)));
  EXPECT_TRUE(isVectorEuqal(o2, s.combinationSum(n2, 8)));
  EXPECT_TRUE(isVectorEuqal(o3, s.combinationSum(n3, 1)));
  EXPECT_SUMMARY;
}

int main()
{
  testCombinationSum();
  return 0;
}
