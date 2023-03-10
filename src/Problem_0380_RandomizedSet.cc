#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;

class RandomizedSet
{
 private:
  unordered_map<int, int> keyIndexMap;
  unordered_map<int, int> indexKeyMap;
  int size;

 public:
  RandomizedSet() { size = 0; }

  bool insert(int val)
  {
    if (!keyIndexMap.count(val))
    {
      keyIndexMap.emplace(val, size);
      indexKeyMap.emplace(size++, val);
      return true;
    }
    return false;
  }

  bool remove(int val)
  {
    if (keyIndexMap.count(val))
    {
      int deleteIndex = keyIndexMap.at(val);
      int lastIndex = --size;
      int lastKey = indexKeyMap.at(lastIndex);
      keyIndexMap[lastKey] = deleteIndex;
      indexKeyMap[deleteIndex] = lastKey;
      keyIndexMap.erase(val);
      indexKeyMap.erase(lastIndex);
      return true;
    }
    return false;
  }

  int random(int min, int max)
  {
    random_device seed;
    ranlux48 engine(seed());
    uniform_int_distribution<> distrib(min, max);
    int res = distrib(engine);
    return res;
  }

  int getRandom()
  {
    if (size == 0)
    {
      return -1;
    }
    int randomIndex = random(0, size - 1);
    return indexKeyMap.at(randomIndex);
  }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
