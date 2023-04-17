

#include <string>
#include <iostream>
using namespace std;


class Coord
{
  public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
  private:
    int m_r;
    int m_c;
};


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    // If the start location is equal to the ending location, then we've solved the maze, so return true.
    if (sr == er && sc == ec)
        return true;
    // Mark the start location as visted.
    maze[sr][sc] = 'O';
    /* For each of the four directions,
        If the location one step in that direction (from the start
            location) is unvisited, and there is a path starting from that
            location (and ending at the same ending location as in the
            current call).
                then return true. */
    if (maze[sr-1][sc] == '.') // NORTH (r-1,c)
    {
        if (pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
            return true;
    }
    if (maze[sr][sc+1] == '.') // EAST (r,c+1)
    {
        if (pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
            return true;
    }
    if (maze[sr+1][sc] == '.') // SOUTH (r+1,c)
    {
        if (pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
            return true;
    }
    if (maze[sr][sc-1] == '.') // WEST (r,c-1)
    {
        if (pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
    }
    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXX.XXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
    
    string maze1[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXXXXXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze1, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
    
    string maze2[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.....X",
        "X..X.X...X",
        "X..X...X.X",
        "X........X",
        "X........X",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze2, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
