#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> masterMind(string solution, string guess)
  {
    int n = solution.length();
    int hit = 0;
    int phit = 0;
    vector<int> cntA(26);
    vector<int> cntB(26);
    for (int i = 0; i < n; i++)
    {
      if (solution[i] == guess[i])
      {
        hit++;
      }
      else
      {
        cntA[solution[i] - 'A']++;
        cntB[guess[i] - 'A']++;
      }
    }
    for (int i = 0; i < 26; i++)
    {
      phit += min(cntA[i], cntB[i]);
    }
    return {hit, phit};
  }
};
