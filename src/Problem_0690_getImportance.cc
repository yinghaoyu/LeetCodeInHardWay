#include <unordered_map>
#include <vector>

using namespace std;

class Employee
{
 public:
  int id;
  int importance;
  vector<int> subordinates;
};

class Solution
{
 private:
  int f(unordered_map<int, Employee*>& map, int i)
  {
    int ans = map[i]->importance;
    for (int j : map[i]->subordinates)
    {
      ans += f(map, j);
    }
    return ans;
  }

 public:
  int getImportance(vector<Employee*> employees, int id)
  {
    unordered_map<int, Employee*> map;
    for (auto e : employees)
    {
      // id 不一定有序
      map[e->id] = e;
    }
    return f(map, id);
  }
};
