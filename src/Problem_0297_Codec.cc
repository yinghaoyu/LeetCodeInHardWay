#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec
{
 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode *root)
  {
    deque<string> ans;
    if (root == nullptr)
    {
      ans.push_back("null");
    }
    else
    {
      ans.push_back(std::to_string(root->val));
      queue<TreeNode *> q;
      q.push(root);
      while (!q.empty())
      {
        root = q.front();
        q.pop();
        if (root->left != nullptr)
        {
          ans.push_back(std::to_string(root->left->val));
          q.push(root->left);
        }
        else
        {
          ans.push_back("null");
        }
        if (root->right != nullptr)
        {
          ans.push_back(std::to_string(root->right->val));
          q.push(root->right);
        }
        else
        {
          ans.push_back("null");
        }
      }
    }
    while (!ans.empty() && ans.back() == "null")
    {
      ans.pop_back();
    }
    string res;
    res.append("[");
    string str;
    if (!ans.empty())
    {
      str = ans.front();
      ans.pop_front();
    }
    res.append(str);
    while (!ans.empty())
    {
      str = ans.front();
      ans.pop_front();
      res.append("," + str);
    }
    res.append("]");
    return res;
  }

  vector<string> split(string str, string pattern)
  {
    string::size_type pos;
    vector<string> result;
    str += pattern;  //扩展字符串以方便操作
    int size = str.size();
    for (int i = 0; i < size; i++)
    {
      pos = str.find(pattern, i);
      if (pos < size)
      {
        std::string s = str.substr(i, pos - i);
        result.push_back(s);
        i = pos + pattern.size() - 1;
      }
    }
    return result;
  }

  // Decodes your encoded data to tree.
  TreeNode *deserialize(string data)
  {
    vector<string> strs = split(data.substr(1, data.length() - 2), ",");
    int index = 0;
    TreeNode *root = generateNode(strs[index++]);
    queue<TreeNode *> q;
    if (root != nullptr)
    {
      q.push(root);
    }
    while (!q.empty())
    {
      TreeNode *node = q.front();
      q.pop();
      node->left = generateNode(index == strs.size() ? "null" : strs[index++]);
      node->right = generateNode(index == strs.size() ? "null" : strs[index++]);
      if (node->left != nullptr)
      {
        q.push(node->left);
      }
      if (node->right != nullptr)
      {
        q.push(node->right);
      }
    }
    return root;
  }

  TreeNode *generateNode(string val)
  {
    if (val.length() == 0 || val == "null")
    {
      return nullptr;
    }
    return new TreeNode(stoi(val));
  }
};
// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
