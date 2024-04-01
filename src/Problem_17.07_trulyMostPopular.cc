#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 并查集变形
  vector<string> trulyMostPopular(vector<string>& names, vector<string>& synonyms)
  {
    int n = names.size();
    unordered_map<string, int> freq;

    // 并查集， key(子孙) → value(祖先)
    unordered_map<string, string> umap;
    for (auto& name : names)
    {
      int left = name.find('(');
      int right = name.find(')');
      string key = name.substr(0, left);
      int cnt = stoi(name.substr(left + 1, right - left - 1));
      freq[key] = cnt;
    }
    for (auto& e : synonyms)
    {
      int dot = e.find(',');
      string nameA = e.substr(1, dot - 1);
      string nameB = e.substr(dot + 1, e.length() - dot - 2);
      while (umap.count(nameA))
      {
        // 找 nameA 的祖先
        nameA = umap[nameA];
      }
      while (umap.count(nameB))
      {
        // 找 nameB 的祖先
        nameB = umap[nameB];
      }
      if (nameA != nameB)
      {
        // 合并
        int cnt = freq[nameA] + freq[nameB];
        string min = nameA < nameB ? nameA : nameB;
        string max = min == nameA ? nameB : nameA;
        // 指向 字典序更小的名字
        umap[max] = min;
        // 把频率合并到更小的名字上
        freq.erase(max);
        freq[min] = cnt;
      }
    }
    vector<string> ans;
    for (auto& [key, cnt] : freq)
    {
      ans.push_back(key + "(" + to_string(cnt) + ")");
    }
    return ans;
  }
};
