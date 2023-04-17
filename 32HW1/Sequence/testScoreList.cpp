

#include "Sequence.h"
#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    ScoreList s;
    s.add(4);
    assert(s.size() == 1);
    s.add(6);
    assert(s.size() == 2);
    s.add(9);                       // 4   6   9
    assert(s.maximum() == 9);
    assert(s.minimum() == 4);
    assert(s.size() == 3);
    s.remove(4);
    assert(s.size() == 2);
    assert(s.minimum() == 6);       // 6   9
    s.add(8);
    assert(s.size() == 3);
    s.add(6);
    s.add(12);
    assert(s.size() == 5);
    assert(s.maximum() == 12);
    s.add(45);                      // 6   9   8   6   12  45
    assert(s.maximum() == 45);
    assert(s.size() == 6);
    s.add(45);                      // 6   9   8   6   12  45   45
    assert(s.size() == 7);
    s.remove(45);
    assert(s.size() == 6);
    assert(s.remove(45));
    assert(s.size() == 5);
    assert(s.maximum() == 12);
    cout << "All tests succeeded." << endl;
}



