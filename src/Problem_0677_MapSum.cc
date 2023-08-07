#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class MapSum
{
  unordered_map<string, int> map;        // 每个 key 对应的 val
  unordered_map<string, int> prefixMap;  // 每个前缀对应的 val

 public:
  MapSum() {}

  void insert(string key, int val)
  {
    int delta = val;
    if (map.count(key))
    {
      delta -= map[key];
    }
    // 对 key-val 直接修改
    map[key] = val;
    // 对前缀进行增量修改
    for (int i = 1; i <= key.length(); i++)
    {
      prefixMap[key.substr(0, i)] += delta;
    }
  }

  int sum(string prefix) { return prefixMap[prefix]; }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
