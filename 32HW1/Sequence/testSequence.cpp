
 
#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    assert(s.insert(42) == 0); // 42
    assert(s.size() == 1  &&  s.find(42) == 0);
    assert(s.erase(0) == true);
    assert(s.empty()); // empty array
    assert(s.insert(42) == 0);              // 42
    assert(s.insert(50) == 1);              // 42  50
    assert(s.insert(30) == 0);              // 30  42  50
    assert(s.insert(70) == 3);              // 30  42  50  70
    assert(s.insert(40) == 1);              // 30  40  42  50  70
    assert(s.insert(3) == 0);               // 3   30  40  42  50  70
    assert(s.insert(3, 66) == 3);           // 3   30  40  66  42  50  70
    assert(s.insert(7, 12) == 7);           // 3   30  40  66  42  50  70  12
    assert(s.insert(12) == 1);              // 3   12  30  40  66  42  50  70  12
    assert(s.erase(0) == true);             // 12  30  40  66  42  50  70  12
    assert(s.remove(12) == 2);              // 30  40  66  42  50  70
    assert(s.remove(70) == 1);              // 30  40  66  42  50
    unsigned long value;
    assert(s.get(3, value));
    assert(value == 42);
    assert(s.set(4, value));                // 30  40  66  42  42
    assert(s.find(42) == 3);
    assert(s.find(69) == -1);
    Sequence t;
    assert(t.insert(4) == 0);
    assert(t.insert(4) == 0);
    assert(t.insert(4) == 0);
    assert(t.size() == 3);
    t.swap(s);
    assert(t.size() == 5);
    assert(t.find(4) == -1);
    assert(t.find(42) == 3);
    assert(s.size() == 3);
    assert(s.find(4) == 0);
    assert(s.find(42) == -1);
    
    cout << "All tests succeeded." << endl;
}




