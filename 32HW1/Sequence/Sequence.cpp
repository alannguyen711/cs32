

#include <iostream>
#include "Sequence.h"
using namespace std;


Sequence::Sequence()
{
    m_size = 0;
}

bool Sequence::empty() const
{
    // Return true if the sequence is empty, otherwise false.
    if (m_size == 0)
        return true;
    return false;
}

int Sequence::size() const
{
    // Return the number of items in the sequence.
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value) 
{
  // Insert value into the sequence so that it becomes the item at
  // position pos.  The original item at position pos and those that
  // follow it end up at positions one higher than they were at before.
  // Return pos if 0 <= pos <= size() and the value could be
  // inserted.  (It might not be, if the sequence has a fixed capacity,
  // e.g., because it's implemented using a fixed-size array.)  Otherwise,
  // leave the sequence unchanged and return -1.  Notice that
  // if pos is equal to size(), the value is inserted at the end.
    // tells how many bytes the array is sizeof(m_sequence)/sizeof(m_sequence[0])
    if (pos < 0 || pos > size()) 
        return -1;
    for (int i = size(); i > pos; i--)
    {
        m_sequence[i] = m_sequence[i-1];
    }
    m_sequence[pos] = value;
    m_size++; // added another element
    return pos;
}

int Sequence::insert(const ItemType& value)
{
  // Let p be the smallest integer such that value <= the item at
  // position p in the sequence; if no such item exists (i.e.,
  // value > all items in the sequence), let p be size().  Insert
  // value into the sequence so that it becomes the item in position
  // p.  The original item at position p and those that follow it end
  // up at positions one higher than before.  Return p if the value
  // was actually inserted.  Return -1 if the value was not inserted
  // (perhaps because the sequence has a fixed capacity and is full).
    if (size() == 0)
    {
        m_sequence[0] = value;
        m_size++;
        return 0;
    }
    int p = -1;
    for (int i = 0; i < size(); i++)
    {
        if (value <= m_sequence[i])
        {
            p = i;
            break;
        }
        p = m_size;
    }
    for (int i = size(); i > p; i--)
    {
        m_sequence[i] = m_sequence[i-1];
    }
    m_sequence[p] = value;
    m_size++;
    return p;
}
 
bool Sequence::erase(int pos)
{
  // If 0 <= pos < size(), remove the item at position pos from
  // the sequence (so that all items that followed that item end up at
  // positions one lower than they were at before), and return true.
  // Otherwise, leave the sequence unchanged and return false.
    if (pos < 0 || pos >= size())
        return false;
    for (int i = pos; i < size(); i++)
    {
        m_sequence[i] = m_sequence[i+1];
    }
    m_size--;
    return true;
}
 
int Sequence::remove(const ItemType& value)
{
  // Erase all items from the sequence that == value.  Return the
  // number of items removed (which will be 0 if no item == value).
    int removed = 0;
    for (int i = 0; i < size(); i++)
    {
        if (m_sequence[i] == value)
        {
            erase(i);
            removed++;
        }
    }
    return removed;
}

bool Sequence::get(int pos, ItemType& value) const
{
  // If 0 <= pos < size(), copy into value the item at position pos
  // of the sequence and return true.  Otherwise, leave value unchanged
  // and return false.
    if (pos < 0 || pos >= size())
        return false;
    value = m_sequence[pos];
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
  // If 0 <= pos < size(), replace the item at position pos in the
  // sequence with value and return true.  Otherwise, leave the sequence
  // unchanged and return false.
    if (pos < 0 || pos >= size())
        return false;
    m_sequence[pos] = value;
    return true;
}

int Sequence::find(const ItemType& value) const
{
  // Let p be the smallest integer such that value == the item at
  // position p in the sequence; if no such item exists, let p be -1.
  // Return p.
    int p = -1;
    for (int i = 0; i < size(); i++)
    {
        if (value == m_sequence[i])
        {
            p = i;
            break;
        }
    }
    return p;
}

void Sequence::swap(Sequence& other)
{
  // Exchange the contents of this sequence with the other one.
    // index by index, use a temporary variable and a for loop
    // find the longer one?
    int length;
    if (size() > other.size())
        length = size();
    else
        length = other.size();
    for (int i = 0; i < length; i++)
    {
        ItemType temporary = m_sequence[i];
        m_sequence[i] = other.m_sequence[i];
        other.m_sequence[i] = temporary;
    }
    int temp = m_size;
    m_size = other.m_size;
    other.m_size = temp;
    
}

void Sequence::dump() const
{
    for (int i = 0; i < size(); i++)
    {
        cerr << m_sequence[i];
    }
    
}





