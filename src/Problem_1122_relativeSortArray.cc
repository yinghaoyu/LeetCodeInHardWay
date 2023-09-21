#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> relativeSortArray(vector<int> &arr1, vector<int> &arr2)
  {
    unordered_map<int, int> map;
    for (int i = 0; i < arr2.size(); i++)
    {
      map[arr2[i]] = i;
    }
    vector<int> ans = arr1;
    std::sort(ans.begin(), ans.end(),
              [&](int x, int y)
              {
                if (map.count(x))
                {
                  return map.count(y) ? map[x] < map[y] : true;
                }
                else
                {
                  return map.count(y) ? false : x < y;
                }
              });
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> a1 = {2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19};
  vector<int> a2 = {2, 1, 4, 3, 9, 6};
  vector<int> a3 = {28, 6, 22, 8, 44, 17};
  vector<int> a4 = {22, 28, 8, 6};
  vector<int> o1 = {2, 2, 2, 1, 4, 3, 3, 9, 6, 7, 19};
  vector<int> o2 = {22, 28, 8, 6, 17, 44};
  EXPECT_TRUE(o1 == s.relativeSortArray(a1, a2));
  EXPECT_TRUE(o2 == s.relativeSortArray(a3, a4));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
