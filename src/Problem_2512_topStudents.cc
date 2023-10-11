#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
 private:
  vector<string> takeWords(string &str)
  {
    vector<string> ans;
    int begin = 0;
    for (int end = 0; end < str.length(); end++)
    {
      if (str[end] == ' ')
      {
        ans.push_back(str.substr(begin, end - begin));
        begin = end + 1;
      }
    }
    if (begin < str.length())
    {
      ans.push_back(str.substr(begin));
    }
    return ans;
  }

 public:
  vector<int> topStudents(vector<string> &positive_feedback, vector<string> &negative_feedback, vector<string> &report, vector<int> &student_id, int k)
  {
    unordered_map<string, int> map;
    for (auto &s : positive_feedback)
    {
      map[s] = 3;
    }
    for (auto &s : negative_feedback)
    {
      map[s] = -1;
    }
    int n = student_id.size();
    vector<int> score(n);
    for (int i = 0; i < n; i++)
    {
      vector<string> words = takeWords(report[i]);
      for (auto &word : words)
      {
        if (map.count(word))
        {
          score[i] += map[word];
        }
      }
    }
    vector<int> idx(n);
    for (int i = 0; i < n; i++)
    {
      idx[i] = i;
    }
    std::sort(idx.begin(), idx.end(), [&](int i, int j) { return score[i] == score[j] ? student_id[i] < student_id[j] : score[i] > score[j]; });
    vector<int> ans(k);
    for (int i = 0; i < k; i++)
    {
      ans[i] = student_id[idx[i]];
    }
    return ans;
  }
};
