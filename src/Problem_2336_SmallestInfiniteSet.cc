#include <set>

using namespace std;

class SmallestInfiniteSet
{
 public:
  SmallestInfiniteSet() {}

  int popSmallest()
  {
    if (s.empty())
    {
      int ans = anchor;
      anchor++;
      return ans;
    }
    int ans = *s.begin();
    s.erase(s.begin());
    return ans;
  }

  void addBack(int num)
  {
    if (num < anchor)
    {
      s.insert(num);
    }
  }

  set<int> s;
  int anchor = 1;
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */
