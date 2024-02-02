#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
 public:
  int numRabbits(vector<int>& answers)
  {
    // a / b 向上取整 -> (a + b - 1) / b
    std::sort(answers.begin(), answers.end());
    int n = answers.size();
    int ans = 0;
    for (int i = 0, j = 1, x; i < n; j++)
    {
      x = answers[i];
      while (j < n && x == answers[j])
      {
        j++;
      }
      // i...j-1都是同一种答案，当前组有j-i个回答
      ans += (j - i + x) / (x + 1) * (x + 1);
      i = j;
    }
    return ans;
  }
};
