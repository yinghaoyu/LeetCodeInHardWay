#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> constructArr(vector<int> &a)
  {
    int n = a.size();
    vector<int> left(n + 1, 1);
    vector<int> right(n + 1, 1);
    for (int i = 0; i < n; i++)
    {
      left[i + 1] = left[i] * a[i];
    }
    for (int i = n - 1; i >= 0; i--)
    {
      right[i] = right[i + 1] * a[i];
    }
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
      ans[i] = left[i] * right[i + 1];
    }
    return ans;
  }
};
