#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  bool check(vector<int>& record, int i, int j)
  {
    for (int k = 0; k < i; k++)
    {
      if (record[k] == j || std::abs(record[k] - j) == std::abs(i - k))
      {
        return false;
      }
    }
    return true;
  }

  void makeNQueen(vector<int>& record, vector<vector<string>>& ans)
  {
    int n = record.size();
    vector<string> nQueen(n, string(n, '.'));
    for (int i = 0; i < n; i++)
    {
      nQueen[i][record[i]] = 'Q';
    }
    ans.emplace_back(nQueen);
  }

  void f(int i, vector<int>& record, vector<vector<string>>& ans)
  {
    if (i == record.size())
    {
      makeNQueen(record, ans);
      return;
    }
    for (int j = 0; j < record.size(); j++)
    {
      if (check(record, i, j))
      {
        record[i] = j;
        f(i + 1, record, ans);
        record[i] = 0;
      }
    }
  }

  vector<vector<string>> solveNQueens(int n)
  {
    vector<vector<string>> ans;
    vector<int> record(n);
    f(0, record, ans);
    return ans;
  }
};
