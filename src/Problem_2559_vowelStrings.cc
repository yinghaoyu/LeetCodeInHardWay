#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> vowelStrings(vector<string> &words, vector<vector<int>> &queries)
  {
    int n = words.size();
    vector<int> count(n + 1);
    for (int i = 0; i < n; i++)
    {
      count[i + 1] = count[i] + isVowelString(words[i]);
    }
    vector<int> ans;
    for (int i = 0; i < queries.size(); i++)
    {
      int l = queries[i][0];
      int r = queries[i][1];
      ans.push_back(count[r + 1] - count[l]);
    }

    return ans;
  }

  bool isVowelString(string &s) { return isVowelChar(s.front()) && isVowelChar(s.back()); }

  bool isVowelChar(char c) { return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; }
};

void test()
{
  Solution s;
  vector<string> w1 = {"aba", "bcb", "ece", "aa", "e"};
  vector<vector<int>> q1 = {{0, 2}, {1, 4}, {1, 1}};
  vector<string> w2 = {"a", "e", "i"};
  vector<vector<int>> q2 = {{0, 2}, {0, 1}, {2, 2}};
  vector<int> o1 = {2, 3, 0};
  vector<int> o2 = {3, 2, 1};
  EXPECT_TRUE(o1 == s.vowelStrings(w1, q1));
  EXPECT_TRUE(o2 == s.vowelStrings(w2, q2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
