#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 只有先让身高高的先进入队伍，后面身高低的才能根据前面高的来找自己的位置
  vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
  {
    // 输入: [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
    // 排序: [[7,0], [7,1], [6,1], [5,0], [5,2], [4,4]]
    // 输出:
    // [[7, 0]]
    // [[7, 0], [7, 1]]
    // [[7, 0], [6, 1], [7, 1]]
    // [[5, 0], [7, 0], [6, 1], [7, 1]]
    // [[5, 0], [7, 0], [5, 2], [6, 1], [7, 1]]
    // [[5, 0], [7, 0], [5, 2], [6, 1], [4, 4], [7, 1]]
    // 先让所有人身高从高到低排序，身高相同再按位置从小到大
    std::sort(people.begin(), people.end(),
              [](const vector<int> &lhs, const vector<int> &rhs) { return lhs[0] > rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]); });
    vector<vector<int>> ans;
    for (const vector<int> &person : people)
    {
      // 再让每个人依次插入自己的位置
      ans.insert(ans.begin() + person[1], person);
    }
    return ans;
  }
};

void testReconstructQueue()
{
  Solution s;
  vector<vector<int>> n1 = {{7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5, 2}};
  vector<vector<int>> o1 = {{5, 0}, {7, 0}, {5, 2}, {6, 1}, {4, 4}, {7, 1}};
  vector<vector<int>> n2 = {{6, 0}, {5, 0}, {4, 0}, {3, 2}, {2, 2}, {1, 4}};
  vector<vector<int>> o2 = {{4, 0}, {5, 0}, {2, 2}, {3, 2}, {1, 4}, {6, 0}};
  EXPECT_TRUE(o1 == s.reconstructQueue(n1));
  EXPECT_TRUE(o2 == s.reconstructQueue(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testReconstructQueue();
  return 0;
}
