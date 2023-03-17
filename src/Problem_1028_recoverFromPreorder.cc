#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
 public:
  TreeNode *recoverFromPreorder(string traversal)
  {
    int number = 0;
    int level = 0;
    queue<int> que;
    // 把字符串 1-2--3--4-5--6--7
    // 转化成 0,1,1,2,2,3,2,4,1,5,2,6,2,7
    // 前一位为层数，后一位为数值，然后在队列里两个为一组进行消费
    bool pickLevel = true;
    for (int i = 0; i < traversal.size(); i++)
    {
      if (traversal[i] != '-')
      {
        // 是数字
        if (pickLevel)
        {
          // 上次的level进队
          que.push(level);
          level = 0;
          pickLevel = false;
        }
        number = number * 10 + traversal[i] - '0';
      }
      else
      {
        // 是字符
        if (!pickLevel)
        {
          // 上次的number进队
          que.push(number);
          number = 0;
          pickLevel = true;
        }
        level++;
      }
    }
    que.push(number);
    return f(que);
  }

  TreeNode *f(queue<int> &que)
  {
    int level = que.front();
    que.pop();
    TreeNode *head = new TreeNode(que.front());
    que.pop();
    if (!que.empty() && que.front() > level)
    {
      head->left = f(que);
    }
    if (!que.empty() && que.front() > level)
    {
      head->right = f(que);
    }
    return head;
  }
};
