

#include <iostream>
#include "Sequence.h"
#include "ScoreList.h"
using namespace std;


ScoreList::ScoreList()       // Create an empty score list.
{
    
}


bool ScoreList::add(unsigned long score)
{
  // If the score is valid (a value from 0 to 100) and the score list
  // has room for it, add it to the score list and return true.
  // Otherwise, leave the score list unchanged and return false.
    if (score < 0 || score > 100 || sl_sequence.size() >= 150)
        return false;
    sl_sequence.insert(score);
    return true;
}

bool ScoreList::remove(unsigned long score)
{
  // Remove one instance of the specified score from the score list.
  // Return true if a score was removed; otherwise false.
    // use find and then the erase
    int pos = sl_sequence.find(score);
    if (pos == -1)
        return false;
    sl_sequence.erase(pos);
    return true;
}

int ScoreList::size() const
{
  // Return the number of scores in the list.
    return sl_sequence.size();
}

unsigned long ScoreList::minimum() const
{
  // Return the lowest-valued score in the score list.  If the list is
  // empty, return NO_SCORE.
    if (size() == 0)
        return NO_SCORE;
    unsigned long min;
    sl_sequence.get(0, min);
    for (int i = 1; i < sl_sequence.size(); i++)
    {
        unsigned long temp;
        sl_sequence.get(i, temp);
        if (temp < min)
            min = temp;
    }
    return min;
}

unsigned long ScoreList::maximum() const
{
  // Return the highest-valued score in the score list.  If the list is
  // empty, return NO_SCORE.
    if (size() == 0)
        return NO_SCORE;
    unsigned long max;
    sl_sequence.get(0, max);
    for (int i = 1; i < sl_sequence.size(); i++)
    {
        unsigned long temp;
        sl_sequence.get(i, temp);
        if (temp > max)
            max = temp;
    }
    return max;
}








