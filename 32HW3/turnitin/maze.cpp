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
