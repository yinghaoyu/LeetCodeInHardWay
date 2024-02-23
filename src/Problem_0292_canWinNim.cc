#include <vector>

using namespace std;

class Solution
{
 public:
  bool f(int rest)
  {
    if (rest <= 3)
    {
      return true;
    }
    for (int i = 1; i <= 3; i++)
    {
      if (!f(rest - i))
      {
        // 另一个人失败了，你就成功了
        return true;
      }
    }
    return false;
  }

  // 递归超时
  bool canWinNim(int n) { return f(n); }

  // TODO:数学
};
