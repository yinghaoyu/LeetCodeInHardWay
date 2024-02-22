#include <vector>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution
{
 private:
  class Info
  {
   public:
    TreeNode* pX;
    int depthX;
    bool findX;

    TreeNode* pY;
    int depthY;
    bool findY;

    Info(TreeNode* px, int dx, bool fx, TreeNode* py, int dy, bool fy)
    {
      pX = px;
      depthX = dx;
      findX = fx;
      pY = py;
      depthY = dy;
      findY = fy;
    }
  };

  Info f(TreeNode* cur, TreeNode* parent, int x, int y)
  {
    if (cur == nullptr)
    {
      return Info(nullptr, 0, false, nullptr, 0, false);
    }
    if (cur->val == x)
    {
      return Info(parent, 0, true, nullptr, 0, false);
    }
    if (cur->val == y)
    {
      return Info(nullptr, 0, false, parent, 0, true);
    }

    Info left = f(cur->left, cur, x, y);
    Info right = f(cur->right, cur, x, y);

    TreeNode* pX = nullptr;
    int depthX = 0;
    bool findX = false;

    TreeNode* pY = nullptr;
    int depthY = 0;
    bool findY = false;
    if (left.findX)
    {
      pX = left.pX;
      depthX = left.depthX + 1;
      findX = left.findX;
    }
    if (left.findY)
    {
      pY = left.pY;
      depthY = left.depthY + 1;
      findY = left.findY;
    }
    if (right.findX)
    {
      pX = right.pX;
      depthX = right.depthX + 1;
      findX = right.findX;
    }
    if (right.findY)
    {
      pY = right.pY;
      depthY = right.depthY + 1;
      findY = right.findY;
    }
    return Info(pX, depthX, findX, pY, depthY, findY);
  }

 public:
  bool isCousins(TreeNode* root, int x, int y)
  {
    Info info = f(root, nullptr, x, y);
    return info.findX && info.findY && info.pX != info.pY && info.depthX == info.depthY;
  }
};
