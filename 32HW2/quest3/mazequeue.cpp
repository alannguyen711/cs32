
#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Coord
{
  public:
    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
  private:
    int m_row;
    int m_col;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
    // Push the starting coordinate (sr,sc) onto the coordinate stack and update maze[sr][sc] to indicate that the algorithm has encountered it (i.e., set maze[sr][sc] to have a value other than '.').
    queue<Coord> coordQueue;
    coordQueue.push(Coord(sr, sc));
    maze[sr][sc] = '#';
    while (!(coordQueue.empty())) // While the queue is not empty,
    {
        Coord cur = coordQueue.front();
        coordQueue.pop(); // Pop the top coordinate off the stack. This gives you the current (r,c) location that your algorithm is exploring.
        if (cur.r() == er && cur.c() == ec)
            return true;
        
        if (maze[cur.r()-1][cur.c()] == '.') // NORTH (r-1,c)
        {
            coordQueue.push(Coord(cur.r()-1,cur.c()));
            maze[cur.r()-1][cur.c()] = '#';
        }
        if (maze[cur.r()][cur.c()+1] == '.') // EAST (r,c+1)
        {
            coordQueue.push(Coord(cur.r(),cur.c()+1));
            maze[cur.r()][cur.c()+1] = '#';
        }
        if (maze[cur.r()+1][cur.c()] == '.') // SOUTH (r+1,c)
        {
            coordQueue.push(Coord(cur.r()+1,cur.c()));
            maze[cur.r()+1][cur.c()] = '#';
        }
        if (maze[cur.r()][cur.c()-1] == '.') // WEST (r,c-1)
        {
            coordQueue.push(Coord(cur.r(),cur.c()-1));
            maze[cur.r()][cur.c()-1] = '#';
        }
    }
    
    return false;
}

int main()
{}
