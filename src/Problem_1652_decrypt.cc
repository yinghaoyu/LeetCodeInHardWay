#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> decrypt(vector<int> &code, int k)
  {
    int N = code.size();
    vector<int> ans(N);
    if (k == 0)
    {
      return ans;
    }
    // 简化，二倍扩容
    code.resize(N * 2);
    std::copy(code.begin(), code.begin() + N, code.begin() + N);
    int l = k > 0 ? 1 : N + k;
    int r = k > 0 ? k : N - 1;
    int w = 0;
    for (int i = l; i <= r; i++)
    {
      w += code[i];
    }
    // 滑动窗口
    for (int i = 0; i < N; i++)
    {
      ans[i] = w;
      w -= code[l];
      w += code[r + 1];
      l++;
      r++;
    }
    return ans;
  }
};

bool isVectorEqual(vector<int> a, vector<int> b)
{
  if (a.size() != b.size())
  {
    return false;
  }
  for (int i = 0; i < a.size(); i++)
  {
    if (a[i] != b[i])
    {
      return false;
    }
  }
  return true;
}

void testDecrypt()
{
  Solution s;
  vector<int> in1 = {5, 7, 1, 4};
  vector<int> out1 = {12, 10, 16, 13};
  vector<int> in2 = {1, 2, 3, 4};
  vector<int> out2 = {0, 0, 0, 0};
  vector<int> in3 = {2, 4, 9, 3};
  vector<int> out3 = {12, 5, 6, 13};
  EXPECT_TRUE(isVectorEqual(out1, s.decrypt(in1, 3)));
  EXPECT_TRUE(isVectorEqual(out2, s.decrypt(in2, 0)));
  EXPECT_TRUE(isVectorEqual(out3, s.decrypt(in3, -2)));
  EXPECT_SUMMARY;
}

int main()
{
  testDecrypt();
  return 0;
}
