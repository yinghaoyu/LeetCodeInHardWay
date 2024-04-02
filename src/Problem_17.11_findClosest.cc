#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  int findClosest(vector<string>& words, string word1, string word2)
  {
    int idx1 = -1;
    int idx2 = -1;
    int n = words.size();
    int ans = n;
    for (int i = 0; i < n; i++)
    {
      if (word1 == words[i])
      {
        idx1 = i;
      }
      else if (word2 == words[i])
      {
        idx2 = i;
      }
      if (idx1 != -1 && idx2 != -1)
      {
        ans = std::min(ans, std::abs(idx1 - idx2));
      }
    }
    return ans;
  }
};
