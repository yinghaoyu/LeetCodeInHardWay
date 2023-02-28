#include <iostream>
#include <map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<vector<int>> mergeSimilarItems(vector<vector<int>> &items1, vector<vector<int>> &items2)
  {
    map<int, int> map;
    for (int i = 0; i < items1.size(); i++)
    {
      map[items1[i][0]] = items1[i][1];
    }
    for (int i = 0; i < items2.size(); i++)
    {
      map[items2[i][0]] += items2[i][1];
    }
    vector<vector<int>> ans;
    for (auto &[key, value] : map)
    {
      vector<int> cur = {key, value};
      ans.push_back(cur);
    }
    return ans;
  }
};

void testMergeSimilarItems()
{
  Solution s;
  vector<vector<int>> n1 = {{1, 1}, {4, 5}, {3, 8}};
  vector<vector<int>> n2 = {{3, 1}, {1, 5}};
  vector<vector<int>> n3 = {{1, 1}, {3, 2}, {2, 3}};
  vector<vector<int>> n4 = {{2, 1}, {3, 2}, {1, 3}};
  vector<vector<int>> n5 = {{1, 3}, {2, 2}};
  vector<vector<int>> n6 = {
      {7, 1},
      {2, 2},
      {1, 4},
  };

  vector<vector<int>> o1 = {{1, 6}, {3, 9}, {4, 5}};
  vector<vector<int>> o2 = {{1, 4}, {2, 4}, {3, 4}};
  vector<vector<int>> o3 = {{1, 7}, {2, 4}, {7, 1}};
  EXPECT_TRUE(o1 == s.mergeSimilarItems(n1, n2));
  EXPECT_TRUE(o2 == s.mergeSimilarItems(n3, n4));
  EXPECT_TRUE(o3 == s.mergeSimilarItems(n5, n6));
  EXPECT_SUMMARY;
}

int main()
{
  testMergeSimilarItems();
  return 0;
}
