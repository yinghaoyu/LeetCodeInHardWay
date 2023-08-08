#include <iostream>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int findMaximumXOR1(vector<int> &nums)
  {
    int ans = 0;
    const int mask = 30;
    for (int i = 30; i >= 0; i--)
    {
      unordered_set<int> set;
      for (auto &num : nums)
      {
        set.emplace(num >> i);
      }
      int next = 2 * ans + 1;
      bool found = false;
      for (auto &num : nums)
      {
        if (set.count(next ^ (num >> i)))
        {
          found = true;
          break;
        }
      }
      if (found)
      {
        ans = next;
      }
      else
      {
        ans = next - 1;
      }
    }
    return ans;
  }

  class Node
  {
   public:
    Node *left;
    Node *right;
    Node()
    {
      left = nullptr;
      right = nullptr;
    }
  };

  Node *root = new Node();
  const int mask = 30;

  void add(int num)
  {
    Node *cur = root;
    for (int i = mask; i >= 0; i--)
    {
      int bit = (num >> i) & 1;
      if (bit == 0)
      {
        if (!cur->left)
        {
          cur->left = new Node();
        }
        cur = cur->left;
      }
      else
      {
        if (!cur->right)
        {
          cur->right = new Node();
        }
        cur = cur->right;
      }
    }
  }

  int check(int num)
  {
    Node *cur = root;
    int x = 0;
    for (int i = mask; i >= 0; i--)
    {
      int bit = (num >> i) & 1;
      if (bit == 0)
      {
        if (cur->right)
        {
          cur = cur->right;
          x = x * 2 + 1;
        }
        else
        {
          cur = cur->left;
          x = x * 2;
        }
      }
      else
      {
        if (cur->left)
        {
          cur = cur->left;
          x = x * 2 + 1;
        }
        else
        {
          cur = cur->right;
          x = x * 2;
        }
      }
    }
    return x;
  }

  int findMaximumXOR2(vector<int> &nums)
  {
    int n = nums.size();
    int x = 0;
    for (int i = 1; i < n; i++)
    {
      add(nums[i - 1]);
      x = std::max(x, check(nums[i]));
    }
    return x;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {3, 10, 5, 25, 2, 8};
  vector<int> n2 = {14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70};
  EXPECT_EQ_INT(28, s.findMaximumXOR1(n1));
  EXPECT_EQ_INT(127, s.findMaximumXOR1(n2));
  EXPECT_EQ_INT(28, s.findMaximumXOR2(n1));
  EXPECT_EQ_INT(127, s.findMaximumXOR2(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
