#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  class Line
  {
   public:
    int start;
    int end;

    Line()  // 兼容vector默认构造
    {
      start = 0;
      end = 0;
    }

    Line(int s, int e)
    {
      start = s;
      end = e;
    }
  };

  class StartAsc
  {
   public:
    bool operator()(const Line &lhs, const Line &rhs) { return lhs.start < rhs.start; }
  };

  class EndAsc
  {
   public:
    bool operator()(const Line &lhs, const Line &rhs) { return lhs.end > rhs.end; }
  };

 public:
  int minMeetingRooms(vector<vector<int>> &intervals)
  {
    vector<Line> lines(intervals.size());
    for (int i = 0; i < intervals.size(); i++)
    {
      lines[i] = {intervals[i][0], intervals[i][1]};
    }
    std::sort(lines.begin(), lines.end(), StartAsc());
    priority_queue<Line, vector<Line>, EndAsc> q;
    int max = 0;
    for (int i = 0; i < lines.size(); i++)
    {
      while (!q.empty() && q.top().end <= lines[i].start)
      {
        q.pop();
      }
      q.push(lines[i]);
      max = std::max(max, (int) q.size());
    }
    return max;
  }
};

void testMinMeetingRooms()
{
  Solution s;
  vector<vector<int>> n1 = {{0, 30}, {5, 10}, {15, 20}};
  vector<vector<int>> n2 = {{7, 10}, {2, 4}};
  EXPECT_EQ_INT(2, s.minMeetingRooms(n1));
  EXPECT_EQ_INT(1, s.minMeetingRooms(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testMinMeetingRooms();
  return 0;
}
