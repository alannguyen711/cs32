#include "StudentUndo.h"
using namespace std;

Undo* createUndo()
{
	return new StudentUndo;
}

void StudentUndo::submit(const Action action, int row, int col, char ch) {
	// TODO
    string characters = "";
    
    if (!undos.empty())
    {if (action == Undo::Action::DELETE && undos.top().m_action == Undo::Action::DELETE) // for consecutive deletions
        {
            if (undos.top().m_col == col || undos.top().m_col == col + 1) // what if you move one space and then delete?
            {
                toUndo newUndo; // create new toUndo to be pushed
                newUndo.m_row = undos.top().m_row;
                string newCharacters = "";
                if (col < undos.top().m_col) // if you're backspacing and the position is moving
                {
                    newUndo.m_col = col;
                    newCharacters = ch + undos.top().m_characters;
                }
                else // if you're using delete and the position is moving
                {
                    newUndo.m_col = undos.top().m_col;
                    newCharacters = undos.top().m_characters + ch;
                }
                newUndo.m_action = action;
                newUndo.m_characters = newCharacters;
                undos.pop(); // replace with newUndo
                undos.push(newUndo);
                return;
            }
        }
        if (action == Undo::Action::INSERT && undos.top().m_action == Undo::Action::INSERT) // for consecutive insertions
        {
            if (undos.top().m_col == col - undos.top().m_characters.size()) // if at the proper location
            {
                toUndo newUndo; // create new toUndo to be pushed
                newUndo.m_row = undos.top().m_row;
                newUndo.m_col = undos.top().m_col;
                newUndo.m_action = action;
                string newCharacters = "";
                newCharacters = undos.top().m_characters + ch;
                newUndo.m_characters = newCharacters;
                undos.pop(); // replace with newUndo
                undos.push(newUndo);
                return;
            }
        }
    }
    
    characters += ch;
    toUndo newUndo; // create newUndo to push onto stack
    newUndo.m_row = row;
    newUndo.m_col = col;
    newUndo.m_action = action;
    newUndo.m_characters = characters;
    
    undos.push(newUndo); // push onto stack
}

StudentUndo::Action StudentUndo::get(int& row, int& col, int& count, std::string& text) {
    
    if (undos.empty())
        return Undo::Action::ERROR;
    
    // return proper row and col
    row = undos.top().m_row;
    col = undos.top().m_col;
    
    // return proper number of characters
    if (undos.top().m_action == Undo::Action::INSERT) // if (undos.top().m_action == Undo::Action::DELETE)
        count = undos.top().m_characters.size();
    else
        count = 1;
    
    // return proper arrangement of characters
    if (undos.top().m_action == Undo::Action::DELETE) // if (undos.top().m_action == Undo::Action::INSERT)
        text = undos.top().m_characters;
    else
        text = "";
    
    // return proper action
    if (undos.top().m_action == Undo::Action::INSERT)
    {
        undos.pop(); // pop action off the stack
        return Undo::Action::DELETE;
    }
    else if (undos.top().m_action == Undo::Action::DELETE)
    {
        undos.pop(); // pop action off the stack
        return Undo::Action::INSERT;
    }
    else if (undos.top().m_action == Undo::Action::SPLIT)
    {
        undos.pop(); // pop action off the stack
        return Undo::Action::JOIN;
    }
    else if (undos.top().m_action == Undo::Action::JOIN)
    {
        undos.pop(); // pop action off the stack
        return Undo::Action::SPLIT;
    }
    return Undo::Action::ERROR;
}

void StudentUndo::clear() {
	// TODO
    while (!undos.empty())
        undos.pop();
}
