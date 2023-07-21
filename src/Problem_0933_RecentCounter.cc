#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class RecentCounter
{
 private:
  // vector<int> arr;
  queue<int> que;

 public:
  RecentCounter() {}

  int ping(int t)
  {
    que.push(t);
    while (!que.empty() && que.front() < t - 3000)
    {
      que.pop();
    }
    return que.size();
  }

  // 二分查找
  // int ping(int t) {
  //   arr.push_back(t);
  //   int idx = -1;
  //   int n = arr.size();
  //   int left = 0;
  //   int right = n - 1;
  //   int target = t - 3000;
  //   while(left <= right)
  //   {
  //     int mid = (right - left) / 2 + left;
  //     if(target <= arr[mid])
  //     {
  //       idx = mid;
  //       right = mid - 1;
  //     }
  //     else
  //     {
  //       left = mid + 1;
  //     }
  //   }
  //   return arr.size() - idx;
  // }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
