#include <iostream>
#include <vector>

using namespace std;

// seem as leetcode 0085
// https://leetcode-cn.com/problems/maximal-rectangle/
// see at Problem_0085_maximalRectangle.cc
class Solution
{
 public:
  int maxLine(vector<int> &arr)
  {
    int n = arr.size();
    vector<int> stack;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      while (!stack.empty() && arr[stack.back()] >= arr[i])
      {
        int j = stack.back();
        stack.pop_back();
        int k = stack.empty() ? -1 : stack.back();
        int area = (i - k - 1) * arr[j];
        ans = std::max(ans, area);
      }
      stack.push_back(i);
    }
    while (!stack.empty())
    {
      int j = stack.back();
      stack.pop_back();
      int k = stack.empty() ? -1 : stack.back();
      int area = (n - k - 1) * arr[j];
      ans = std::max(ans, area);
    }
    return ans;
  }

  int maximalRectangle(vector<string> &matrix)
  {
    if (matrix.size() == 0)
    {
      return 0;
    }
    int n = matrix.size();
    int m = matrix[0].size();
    vector<int> arr(m);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        arr[j] += matrix[i][j] == '1' ? 1 : -arr[j];
      }
      ans = std::max(ans, maxLine(arr));
    }
    return ans;
  }
};
