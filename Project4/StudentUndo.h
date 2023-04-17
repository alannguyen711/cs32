#ifndef STUDENTUNDO_H_
#define STUDENTUNDO_H_

#include "Undo.h"
#include <stack>

struct toUndo
{
    int m_row;
    int m_col;
    Undo::Action m_action;
    std::string m_characters;
};

class StudentUndo : public Undo {
public:

	void submit(Action action, int row, int col, char ch = 0);
	Action get(int& row, int& col, int& count, std::string& text);
	void clear();

private:
    std::stack<toUndo> undos;
};

#endif // STUDENTUNDO_H_
