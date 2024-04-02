#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution
{
 public:
  string longestWord(vector<string>& words)
  {
    std::sort(words.begin(), words.end(),
              [](string& a, string& b)
              {
                // 按字符串长度排序，长度相同按字典序排序
                return a.length() < b.length() || (a.length() == b.length() && a < b);
              });
    unordered_set<string> seen;
    string ans;
    for (auto& word : words)
    {
      int n = word.length();
      // dp[i] 的含义为，长度前缀长度为i的字符串是否可以由其他单词组成
      vector<bool> dp(n + 1, false);
      dp[0] = true;
      for (int i = 1; i <= n; i++)
      {
        for (int j = i; j >= 1; j--)
        {
          // dp[j-1] = true 表示 word[0...j-2] 可以由其他单词组成
          // seen.count(word.substr(j - 1, i - j + 1)) 表示 word[j-1 ... i - 1]可以由其他单词组成
          if (dp[j - 1] && seen.count(word.substr(j - 1, i - j + 1)))
          {
            dp[i] = true;
            break;
          }
        }
      }
      if (dp[n] && word.length() > ans.length())
      {
        ans = word;
      }
      seen.emplace(word);
    }
    return ans;
  }
};
