#include <iostream>
#include <set>
#include <vector>

using namespace std;

class MyCalendar
{
 private:
  set<pair<int, int>> set;

 public:
  MyCalendar() {}

  bool book(int start, int end)
  {
    // 找到第一个元素 {start', end'} 满足 start' >= end
    // 打算将当前 {start, end} 插入在这个元素之前
    auto ptr = set.lower_bound({end, 0});
    if (ptr == set.begin() || (--ptr)->second <= start)
    {
      // 前面没有元素，或者前面元素的 end' <= start
      // 说明符合条件
      set.insert({start, end});
      return true;
    }
    return false;
  }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
