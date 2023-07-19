#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

// seem as leetcode 0380
// https://leetcode-cn.com/problems/insert-delete-getrandom-o1/
// see at Problem_0380_RandomizedSet.cc
class RandomizedSet
{
 private:
  unordered_map<int, int> keyIdxMap;
  unordered_map<int, int> idxKeyMap;
  int size;

 public:
  /** Initialize your data structure here. */
  RandomizedSet() { size = 0; }

  /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
  bool insert(int val)
  {
    if (keyIdxMap.count(val))
    {
      return false;
    }
    keyIdxMap[val] = size;
    idxKeyMap[size++] = val;
    return true;
  }

  /** Removes a value from the set. Returns true if the set contained the specified element. */
  bool remove(int val)
  {
    if (keyIdxMap.count(val))
    {
      int lastIdx = --size;
      int lastKey = idxKeyMap[lastIdx];
      int removeIdx = keyIdxMap[val];
      // 把最后一个元素移动到删除的位置
      keyIdxMap[lastKey] = removeIdx;
      idxKeyMap[removeIdx] = lastKey;
      // 删除最后一个位置
      keyIdxMap.erase(val);
      idxKeyMap.erase(lastIdx);
      return true;
    }
    return false;
  }

  /** Get a random element from the set. */
  int getRandom()
  {
    if (size == 0)
    {
      return -1;
    }
    int idx = random() % size;
    return idxKeyMap[idx];
  }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
