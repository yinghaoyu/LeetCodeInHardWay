#include <vector>

using namespace std;

class Solution
{
 public:
  void f(int rest, vector<int>& A, vector<int>& B, vector<int>& C)
  {
    if (rest < 1)
    {
      return;
    }

    // 将 A 上面的 rest - 1 个通过 C 移动到 B
    f(rest - 1, A, C, B);
    // 将 A 最后一个移动到 C
    C.push_back(A.back());
    A.pop_back();
    // 将 B 上面 n - 1 个通过的 A 移动到 C
    f(rest - 1, B, A, C);
  }

  void hanota(vector<int>& A, vector<int>& B, vector<int>& C) { f(A.size(), A, B, C); }
};
