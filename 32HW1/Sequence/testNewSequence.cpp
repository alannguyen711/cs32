
#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{ 
    // throw print statements
    Sequence a(1000);   // a can hold at most 1000 items
    Sequence b(5);      // b can hold at most 5 items
    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType v = 6;
      // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(v) != -1);
      // Failure if we try to insert a sixth item into b
    assert(b.insert(v) == -1);
      // When two Sequences' contents are swapped, their capacities are
      // swapped as well:
    a.swap(b);
    assert(a.insert(v) == -1  &&  b.insert(v) != -1);
    
    // TEST COPY CONSTRUCTOR
    Sequence first(4);
    for (int i = 0; i < 4; i++)
    {
        assert(first.insert(6) == 0);
    }
    Sequence second = first;
    assert(second.size() == 4);
    for (int i = 0; i < 4; i++)
    {
        ItemType num;
        second.get(i, num);
        assert(num == 6);
    }
    
    // TEST ASSIGNMENT OPERATOR
    Sequence third(5);
    for (int i = 0; i < 3; i++)
    {
        assert(third.insert(20 - i) == 0);
        
    }
    assert(third.size() == 3);
    Sequence fourth(9);
    fourth = third;
    assert(fourth.size() == 3);
    assert(fourth.find(18) == 0);
    assert(fourth.find(19) == 1);
    assert(fourth.find(20) == 2);
    assert(fourth.insert(6) == 0);        // array has 6 18 19 20
    assert(fourth.size() == 4);
    assert(fourth.insert(1, 9) == 1);    // TROUBLE HERE
    
    
    Sequence blah(2);
    Sequence bleh(1);
    assert(bleh.insert(8) == 0);
    assert(bleh.insert(10) == -1);
    blah = bleh;
    assert(blah.insert(10) == -1);
    
    
    cout << "All tests succeeded." << endl;
    

}



