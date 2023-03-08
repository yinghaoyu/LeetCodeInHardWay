#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  class Node
  {
   public:
    int value;
    int index;

    Node()
    {
      value = -1;
      index = -1;
    }

    Node(int v, int i)
    {
      value = v;
      index = i;
    }
  };

 public:
  void process(vector<Node> &arr, int L, int R, vector<int> &ans)
  {
    if (L == R)
    {
      return;
    }
    int M = (R - L) / 2 + L;
    process(arr, L, M, ans);
    process(arr, M + 1, R, ans);
    merge(arr, L, M, R, ans);
  }

  void merge(vector<Node> &arr, int L, int M, int R, vector<int> &ans)
  {
    int l = M;
    int r = R;
    vector<Node> help(R - L + 1);
    int index = help.size() - 1;
    while (L <= l && M + 1 <= r)
    {
      if (arr[l].value > arr[r].value)
      {
        ans[arr[l].index] += r - M;
      }
      help[index--] = arr[l].value > arr[r].value ? arr[l--] : arr[r--];
    }
    while (l >= L)
    {
      help[index--] = arr[l--];
    }
    while (r >= M + 1)
    {
      help[index--] = arr[r--];
    }
    for (int i = 0; i < help.size(); i++)
    {
      arr[L + i] = help[i];
    }
  }

  vector<int> countSmaller(vector<int> &nums)
  {
    if (nums.size() == 0)
    {
      return {};
    }
    int n = nums.size();
    vector<int> ans(n);
    if (nums.size() < 2)
    {
      return ans;
    }
    vector<Node> arr(n);
    for (int i = 0; i < arr.size(); i++)
    {
      arr[i] = Node(nums[i], i);
    }
    process(arr, 0, arr.size() - 1, ans);
    return ans;
  }
};

void testCountSmaller()
{
  Solution s;
  vector<int> n1 = {5, 2, 6, 1};
  vector<int> o1 = {2, 1, 1, 0};
  vector<int> n2 = {-1};
  vector<int> o2 = {0};
  vector<int> n3 = {-1, -1};
  vector<int> o3 = {0, 0};
  EXPECT_TRUE(o1 == s.countSmaller(n1));
  EXPECT_TRUE(o2 == s.countSmaller(n2));
  EXPECT_TRUE(o3 == s.countSmaller(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testCountSmaller();
  return 0;
}
