#include <iostream>
#include <vector>

using namespace std;

// seem as leetcode 0421
// https://leetcode-cn.com/problems/maximum-xor-of-two-numbers-in-an-array/
// see at Problem_0421_findMaximumXOR.cc
class Solution
{
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
  int search(int num)
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
          x = 2 * x + 1;
          cur = cur->right;
        }
        else
        {
          x = 2 * x;
          cur = cur->left;
        }
      }
      else
      {
        if (cur->left)
        {
          x = 2 * x + 1;
          cur = cur->left;
        }
        else
        {
          x = 2 * x;
          cur = cur->right;
        }
      }
    }
    return x;
  }

 public:
  int findMaximumXOR(vector<int> &nums)
  {
    int x = 0;
    for (int i = 1; i < nums.size(); i++)
    {
      add(nums[i - 1]);
      x = std::max(x, search(nums[i]));
    }
    return x;
  }
};
