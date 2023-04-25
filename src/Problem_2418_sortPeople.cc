#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<string> sortPeople(vector<string> &names, vector<int> &heights)
  {
    int n = names.size();
    vector<int> idx(n);
    for (int i = 0; i < n; i++)
    {
      idx[i] = i;
    }
    std::sort(idx.begin(), idx.end(), [&](int l, int r) { return heights[l] > heights[r]; });
    vector<string> ans(n);
    for (int i = 0; i < n; i++)
    {
      ans[i] = names[idx[i]];
    }
    return ans;
  }
};

void testSortPeople()
{
  Solution s;
  vector<string> n1 = {"Mary", "John", "Emma"};
  vector<int> h1 = {180, 165, 170};
  vector<string> o1 = {"Mary", "Emma", "John"};

  vector<string> n2 = {"Alice", "Bob", "Bob"};
  vector<int> h2 = {155, 185, 150};
  vector<string> o2 = {"Bob", "Alice", "Bob"};
  EXPECT_TRUE(o1 == s.sortPeople(n1, h1));
  EXPECT_TRUE(o2 == s.sortPeople(n2, h2));
  EXPECT_SUMMARY;
}

int main()
{
  testSortPeople();
  return 0;
}
