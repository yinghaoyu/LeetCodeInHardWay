#include <list>
#include <vector>

using namespace std;

class MyHashMap
{
  // 链地址法
  vector<list<pair<int, int>>> memory;

  static const int PRIM = 1021;

  int hash(int value) { return value % PRIM; }

 public:
  MyHashMap() : memory(PRIM) {}

  void put(int key, int value)
  {
    int hk = hash(key);
    for (auto& e : memory[hk])
    {
      if (e.first == key)
      {
        e.second = value;
        return;
      }
    }
    memory[hk].push_back({key, value});
  }

  int get(int key)
  {
    int hk = hash(key);
    for (auto& e : memory[hk])
    {
      if (e.first == key)
      {
        return e.second;
      }
    }
    return -1;
  }

  void remove(int key)
  {
    int hk = hash(key);
    for (auto itr = memory[hk].begin(); itr != memory[hk].end(); ++itr)
    {
      if (itr->first == key)
      {
        memory[hk].erase(itr);
        break;
      }
    }
  }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
