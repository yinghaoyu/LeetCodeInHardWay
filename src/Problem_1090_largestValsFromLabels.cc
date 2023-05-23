#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int process(vector<int> &values, vector<int> &labels, int numWanted, int useLimit, int index, unordered_map<int, int> &map, int total)
  {
    if (index == values.size())
    {
      return total;
    }
    if (numWanted == 0)
    {
      return total;
    }
    int p1 = 0;
    if (map[labels[index]] < useLimit)
    {
      map[labels[index]]++;
      p1 = process(values, labels, numWanted - 1, useLimit, index + 1, map, total + values[index]);
      map[labels[index]]--;
    }
    int p2 = process(values, labels, numWanted, useLimit, index + 1, map, total);
    return std::max(p1, p2);
  }

  int largestValsFromLabels1(vector<int> &values, vector<int> &labels, int numWanted, int useLimit)
  {
    unordered_map<int, int> map;
    return process(values, labels, numWanted, useLimit, 0, map, 0);
  }

  int largestValsFromLabels2(vector<int> &values, vector<int> &labels, int numWanted, int useLimit)
  {
    int n = values.size();
    vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 0);
    std::sort(idx.begin(), idx.end(), [&](int l, int r) { return values[l] > values[r]; });
    int ans = 0;
    unordered_map<int, int> map;
    for (int i = 0; i < n && numWanted; i++)
    {
      int label = labels[idx[i]];
      if (map[label] >= useLimit)
      {
        continue;
      }
      numWanted--;
      map[label]++;
      ans += values[idx[i]];
    }
    return ans;
  }
};

void testLargestValsFromLabels()
{
  Solution s;
  vector<int> v1 = {5, 4, 3, 2, 1};
  vector<int> l1 = {1, 1, 2, 2, 3};
  vector<int> v2 = {5, 4, 3, 2, 1};
  vector<int> l2 = {1, 3, 3, 3, 2};
  vector<int> v3 = {9, 8, 8, 7, 6};
  vector<int> l3 = {0, 0, 0, 1, 1};
  EXPECT_EQ_INT(9, s.largestValsFromLabels1(v1, l1, 3, 1));
  EXPECT_EQ_INT(12, s.largestValsFromLabels1(v2, l2, 3, 2));
  EXPECT_EQ_INT(16, s.largestValsFromLabels1(v3, l3, 3, 1));
  EXPECT_EQ_INT(9, s.largestValsFromLabels2(v1, l1, 3, 1));
  EXPECT_EQ_INT(12, s.largestValsFromLabels2(v2, l2, 3, 2));
  EXPECT_EQ_INT(16, s.largestValsFromLabels2(v3, l3, 3, 1));
  EXPECT_SUMMARY;
}

int main()
{
  testLargestValsFromLabels();
  return 0;
}
