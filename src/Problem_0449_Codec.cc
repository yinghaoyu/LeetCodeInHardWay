#include <iostream>
#include <string>
#include <vector>

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
    string ans;
    vector<int> arr;
    postOrder(root, arr);
    if (arr.size() == 0)
    {
      return ans;
    }
    for (int i = 0; i < arr.size(); i++)
    {
      ans.append(std::to_string(arr[i]) + ",");
    }
    ans.pop_back();  // cut ',' at back
    return ans;
  }

  void postOrder(TreeNode *cur, vector<int> &arr)
  {
    if (cur == nullptr)
    {
      return;
    }
    postOrder(cur->left, arr);
    postOrder(cur->right, arr);
    arr.push_back(cur->val);
  }

  // Decodes your encoded data to tree.
  TreeNode *deserialize(string data)
  {
    if (data.size() == 0)
    {
      return nullptr;
    }
    vector<int> arr = split(data, ',');
    return construct(INT32_MIN, INT32_MAX, arr);
  }

  vector<int> split(const string &str, char dec)
  {
    vector<int> ans;
    int i = 0;
    int start = 0;
    while (i < str.size())
    {
      while (i < str.size() && str[i] == dec)
      {
        i++;
      }
      start = i;
      while (i < str.size() && str[i] != dec)
      {
        i++;
      }
      if (start < str.size())
      {
        ans.emplace_back(stoi(str.substr(start, i - start)));
      }
    }
    return ans;
  }

  // arr = [1, 3, 2]
  // 当 value = 2 时，符合区间 (INT32_MIN, INT32_MAX)，限定左边值区间(INT32_MIN, 2)，限定右边值区间 (2, INT32_MAX)
  // 当 value = 3 时，符合区间 (2, INT32_MAX)(即 2 的右子节点)，限定左边值区间(2, 3)，限定右边值区间 (3, INT32_MAX)
  // 当 value = 1 时，不符合区间(2, 3)，也不符合区间(3, INT32_MAX)，所以不是 value = 3 的子节点
  // 再次尝试 value = 1 时，符合区间 (INT32_MIN, 2)，说明是 2 的左子节点
  TreeNode *construct(int lower, int upper, vector<int> &arr)
  {
    if (arr.size() == 0 || arr.back() < lower || arr.back() > upper)
    {
      // 注意，这里的 lower 和 upper 非常关键
      return nullptr;
    }
    int value = arr.back();
    arr.pop_back();
    TreeNode *node = new TreeNode(value);
    // 右子树所有的值必须 > value
    node->right = construct(value, upper, arr);
    // 左子树所有的值必须 < value
    node->left = construct(lower, value, arr);
    return node;
  }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
