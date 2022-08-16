#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxScore(string s)
  {
    int n = s.length();
    vector<int> sumZeros(n);
    vector<int> sumOnes(n);
    sumZeros[0] = s[0] == '0' ? 1 : 0;
    sumOnes[n - 1] = s[n - 1] == '1' ? 1 : 0;
    for (int i = 1; i < n; i++)
    {
      sumZeros[i] = sumZeros[i - 1] + (s[i] == '0' ? 1 : 0);
    }
    for (int i = n - 2; i >= 0; i--)
    {
      sumOnes[i] = sumOnes[i + 1] + (s[i] == '1' ? 1 : 0);
    }
    int ans = sumZeros[0] + sumOnes[1];
    for (int i = 0; i < n - 1; i++)
    {
      ans = std::max(ans, sumZeros[i] + sumOnes[i + 1]);
    }
    return ans;
  }
};

void testMaxScore()
{
  Solution s;
  EXPECT_EQ_INT(s.maxScore("011101"), 5);
  EXPECT_EQ_INT(s.maxScore("00111"), 5);
  EXPECT_EQ_INT(s.maxScore("1111"), 3);
  EXPECT_SUMMARY;
}

int main()
{
  testMaxScore();
  return 0;
}
