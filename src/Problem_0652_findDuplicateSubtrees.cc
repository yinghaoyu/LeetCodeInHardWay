#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class TreeNode
{
 public:
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
  string process(TreeNode *cur, vector<TreeNode *> &res, unordered_map<string, int> &map)
  {
    if (cur == nullptr)
    {
      return "#";
    }
    // 这里不能用中序遍历，只能前序或者后序遍历
    string str = std::to_string(cur->val) + ',' + process(cur->left, res, map) + ',' + process(cur->right, res, map);
    if (map.find(str) != map.end() && map[str] == 1)
    {
      res.push_back(cur);
    }
    if (map.find(str) == map.end())
    {
      map[str] = 1;
    }
    else
    {
      map[str]++;
    }
    return str;
  }

  vector<TreeNode *> findDuplicateSubtrees(TreeNode *root)
  {
    vector<TreeNode *> res;
    unordered_map<string, int> map;
    process(root, res, map);
    return res;
  }
};

bool isSameValueStructure(TreeNode *head1, TreeNode *head2)
{
  if (head1 == nullptr && head2 != nullptr)
  {
    return false;
  }
  if (head1 != nullptr && head2 == nullptr)
  {
    return false;
  }
  if (head1 == nullptr && head2 == nullptr)
  {
    return true;
  }
  if (head1->val != head2->val)
  {
    return false;
  }
  return isSameValueStructure(head1->left, head2->left) && isSameValueStructure(head1->right, head2->right);
}

void testFindDuplicateSubtrees()
{
  Solution s;
  TreeNode *x7 = new TreeNode(4, nullptr, nullptr);
  TreeNode *x6 = new TreeNode(4, nullptr, nullptr);
  TreeNode *x5 = new TreeNode(2, x7, nullptr);
  TreeNode *x4 = new TreeNode(4, nullptr, nullptr);
  TreeNode *x3 = new TreeNode(3, x5, x6);
  TreeNode *x2 = new TreeNode(2, x4, nullptr);
  TreeNode *x1 = new TreeNode(1, x2, x3);

  vector<TreeNode *> exp1{x2, x4};
  vector<TreeNode *> act1 = s.findDuplicateSubtrees(x1);
  std::sort(exp1.begin(), exp1.end());
  std::sort(act1.begin(), act1.end());
  EXPECT_EQ_INT(static_cast<int>(exp1.size()), static_cast<int>(act1.size()));
  for (int i = 0; i < exp1.size(); i++)
  {
    EXPECT_TRUE(isSameValueStructure(exp1[i], act1[i]));
  }

  TreeNode *y5 = new TreeNode(3, nullptr, nullptr);
  TreeNode *y4 = new TreeNode(3, nullptr, nullptr);
  TreeNode *y3 = new TreeNode(2, y5, nullptr);
  TreeNode *y2 = new TreeNode(2, y4, nullptr);
  TreeNode *y1 = new TreeNode(2, y2, y3);

  vector<TreeNode *> exp2{y3, y4};
  vector<TreeNode *> act2 = s.findDuplicateSubtrees(y1);
  std::sort(exp2.begin(), exp2.end());
  std::sort(act2.begin(), act2.end());
  EXPECT_EQ_INT(static_cast<int>(exp2.size()), static_cast<int>(act2.size()));
  for (int i = 0; i < exp2.size(); i++)
  {
    EXPECT_TRUE(isSameValueStructure(exp2[i], act2[i]));
  }

  TreeNode *z3 = new TreeNode(1, nullptr, nullptr);
  TreeNode *z2 = new TreeNode(1, nullptr, nullptr);
  TreeNode *z1 = new TreeNode(2, z2, z3);

  vector<TreeNode *> exp3{z2};
  vector<TreeNode *> act3 = s.findDuplicateSubtrees(z1);
  std::sort(exp3.begin(), exp3.end());
  std::sort(act3.begin(), act3.end());
  EXPECT_EQ_INT(static_cast<int>(exp3.size()), static_cast<int>(act3.size()));
  for (int i = 0; i < exp3.size(); i++)
  {
    EXPECT_TRUE(isSameValueStructure(exp3[i], act3[i]));
  }
  EXPECT_SUMMARY;
}

int main()
{
  testFindDuplicateSubtrees();
  return 0;
}
