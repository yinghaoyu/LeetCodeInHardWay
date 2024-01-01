#include <map>
#include <random>
#include <set>
#include <vector>

using namespace std;

class RandomizedCollection
{
 public:
  RandomizedCollection() {}

  bool insert(int val)
  {
    arr.push_back(val);
    map[val].emplace(arr.size() - 1);
    return map[val].size() == 1;
  }

  // 删除 value 时，把最后一个元素移动到这个 index 上
  bool remove(int val)
  {
    if (!map.count(val))
    {
      return false;
    }
    auto&& valSet = map[val];
    int valIndex = *valSet.begin();
    int endValue = arr.back();
    if (val == endValue)
    {
      // fast path
      // 最后一个元素跟当前相等，直接移除这项即可
      valSet.erase(arr.size() - 1);
    }
    else
    {
      // slow path
      auto&& endSet = map[endValue];
      endSet.emplace(valIndex);
      arr[valIndex] = endValue;
      endSet.erase(arr.size() - 1);
      valSet.erase(valIndex);
    }
    arr.pop_back();
    if (valSet.empty())
    {
      map.erase(val);
    }
    return true;
  }

  int getRandom() { return arr[random(0, arr.size() - 1)]; }

  int random(int min, int max)
  {
    random_device seed;
    ranlux48 engine(seed());
    uniform_int_distribution<> distrib(min, max);
    int res = distrib(engine);
    return res;
  }

 private:
  // val，{index1, index2, ...}
  map<int, set<int>> map;
  // arr[index] = val;
  vector<int> arr;
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
