#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  class TireTree
  {
   public:
    class Node
    {
     public:
      int pass;
      int end;
      unordered_map<int, Node *> nexts;
      Node()
      {
        pass = 0;
        end = 0;
      }
    };

    class Tire
    {
     public:
      Node *root;
      Tire() { root = new Node; }
    };
  };

 public:
  int equalPairs(vector<vector<int>> &grid)
  {
    int n = grid.size();
    TireTree::Tire t;
    for (int i = 0; i < n; i++)
    {
      TireTree::Node *cur = t.root;
      for (int j = 0; j < n; j++)
      {
        int v = grid[i][j];
        if (cur->nexts.find(v) == cur->nexts.end())
        {
          cur->nexts.emplace(v, new TireTree::Node);
        }
        cur = cur->nexts[v];
        cur->pass++;
      }
      cur->end++;
    }

    int ans = 0;
    for (int j = 0; j < n; j++)
    {
      TireTree::Node *cur = t.root;
      for (int i = 0; i < n; i++)
      {
        int v = grid[i][j];
        if (cur->nexts.find(v) == cur->nexts.end())
        {
          break;
        }
        cur = cur->nexts[v];
      }
      ans += cur->end;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> g1 = {{3, 2, 1}, {1, 7, 6}, {2, 7, 7}};
  vector<vector<int>> g2 = {{3, 1, 2, 2}, {1, 4, 4, 5}, {2, 4, 2, 2}, {2, 4, 2, 2}};
  EXPECT_EQ_INT(1, s.equalPairs(g1));
  EXPECT_EQ_INT(3, s.equalPairs(g2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
