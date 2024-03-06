#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/substring-with-concatenation-of-all-words/solutions/2105460/duo-qi-dian-hua-dong-chuang-kou-by-yexis-ecld/
class Solution
{
 public:
  vector<int> findSubstring(string s, vector<string>& words)
  {
    vector<int> ans;
    // 设 words中所有单词的长度为 d
    int n = s.size();
    int m = words.size();
    int d = words[0].size();
    int len = m * d;
    unordered_map<string, int> freq;
    for (auto& w : words)
    {
      // 统计词频
      freq[w]++;
    }

    // 初始化滑动窗口
    vector<unordered_map<string, int>> win(d);
    // 从 0、1、2 ... d - 1开始进行多起点滑动窗口
    for (int i = 0; i < d && i + len <= n; i++)
    {
      //
      for (int j = i; j < i + len; j += d)
      {
        // 统计每个窗口内的词频
        string w = s.substr(j, d);
        win[i][w]++;
      }
      if (win[i] == freq)
      {
        // 词频相同说明，符合条件
        ans.push_back(i);
      }
    }

    // sliding window: 滑动窗口，每次移动 d 个位置
    for (int i = d; i + len <= n; i++)
    {
      // 找到当前窗口的位置
      int r = i % d;
      string wa = s.substr(i - d, d), wb = s.substr(i + len - d, d);
      if (--win[r][wa] == 0)
      {
        // 左边单词出去
        win[r].erase(wa);
      }
      // 右边单词进来
      win[r][wb]++;
      if (win[r] == freq)
      {
        ans.emplace_back(i);
      }
    }

    return ans;
  }
};
