#include <queue>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
 public:
  char pre(char x) { return x == '0' ? '9' : x - 1; }

  char next(char x) { return x == '9' ? '0' : x + 1; }

  vector<string> getNexts(string& status)
  {
    vector<string> ans;
    for (int i = 0; i < 4; i++)
    {
      char tmp = status[i];
      status[i] = pre(tmp);
      ans.push_back(status);
      status[i] = next(tmp);
      ans.push_back(status);
      status[i] = tmp;
    }
    return ans;
  }

  int openLock(vector<string>& deadends, string target)
  {
    if (target == "0000")
    {
      return 0;
    }
    unordered_set<string> dead(deadends.begin(), deadends.end());
    if (dead.count("0000"))
    {
      return -1;
    }

    queue<std::pair<string, int>> q;
    q.push({"0000", 0});
    unordered_set<string> seen;
    seen.emplace("0000");

    // bfs
    while (!q.empty())
    {
      auto [status, step] = q.front();
      q.pop();
      for (auto& next : getNexts(status))
      {
        if (!seen.count(next) && !dead.count(next))
        {
          if (next == target)
          {
            return step + 1;
          }
          q.push({next, step + 1});
          seen.emplace(next);
        }
      }
    }
    return -1;
  }
};
