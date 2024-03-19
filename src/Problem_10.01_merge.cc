#include <vector>

using namespace std;

class Solution
{
 public:
  void merge(vector<int>& A, int m, vector<int>& B, int n)
  {
    int t = A.size() - 1;
    int x = m - 1;
    int y = n - 1;
    while (t >= 0 && x >= 0 && y >= 0)
    {
      A[t--] = A[x] < B[y] ? B[y--] : A[x--];
    }
    while (x >= 0)
    {
      A[t--] = A[x--];
    }
    while (y >= 0)
    {
      A[t--] = B[y--];
    }
  }
};
