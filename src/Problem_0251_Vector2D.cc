#include <iostream>
#include <vector>

using namespace std;

class Vector2D
{
 public:
  Vector2D(vector<vector<int>> &vec)
  {
    this->vec = vec;
    row = 0;
    col = 0;
    size = 0;
    for (auto &arr : vec)
    {
      size += arr.size();
    }
  }

  int next()
  {
    while (col == vec[row].size())
    {
      row++;
      col = 0;
    }
    size--;
    return vec[row][col++];
  }

  bool hasNext() { return size != 0; }

 private:
  vector<vector<int>> vec;
  int size;
  int row;
  int col;
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D* obj = new Vector2D(vec);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
