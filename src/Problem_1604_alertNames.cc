#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<string> alertNames(vector<string> &keyName, vector<string> &keyTime)
  {
    unordered_map<string, vector<int>> timeMap;
    int n = keyName.size();
    for (int i = 0; i < n; i++)
    {
      string name = keyName[i];
      string time = keyTime[i];
      // 转为时间戳
      int hour = (time[0] - '0') * 10 + (time[1] - '0');
      int minute = (time[3] - '0') * 10 + (time[4] - '0');
      timeMap[name].emplace_back(hour * 60 + minute);
    }
    vector<string> ans;
    for (auto &[name, list] : timeMap)
    {
      // 时间戳按升序排列
      std::sort(list.begin(), list.end());
      int size = list.size();
      // 只检查3次及以上的
      for (int i = 2; i < size; i++)
      {
        int time1 = list[i - 2], time2 = list[i];
        // 因为时间戳是升序排列，所以只需要检查第0项和第2项的时间戳
        int difference = time2 - time1;
        if (difference <= 60)
        {
          ans.emplace_back(name);
          break;
        }
      }
    }
    std::sort(ans.begin(), ans.end());
    return ans;
  }
};

bool isEuqalVector(vector<string> a, vector<string> b)
{
  return a == b;
}

void testAlertNames()
{
  Solution s;
  vector<string> k1 = {"daniel", "daniel", "daniel", "luis", "luis", "luis", "luis"};
  vector<string> t1 = {"10:00", "10:40", "11:00", "09:00", "11:00", "13:00", "15:00"};
  vector<string> k2 = {"alice", "alice", "alice", "bob", "bob", "bob", "bob"};
  vector<string> t2 = {"12:01", "12:00", "18:00", "21:00", "21:20", "21:30", "23:00"};
  vector<string> o1 = {"daniel"};
  vector<string> o2 = {"bob"};
  EXPECT_TRUE(isEuqalVector(o1, s.alertNames(k1, t1)));
  EXPECT_TRUE(isEuqalVector(o2, s.alertNames(k2, t2)));
  EXPECT_SUMMARY;
}

int main()
{
  testAlertNames();
  return 0;
}
