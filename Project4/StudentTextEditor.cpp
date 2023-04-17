#include "StudentTextEditor.h"
#include "Undo.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

TextEditor* createTextEditor(Undo* un)
{
	return new StudentTextEditor(un);
}

StudentTextEditor::StudentTextEditor(Undo* undo)
 : TextEditor(undo) {
	// TODO
    m_row = 0; m_column = 0;
    textToEdit.push_back("");
    m_lineIterator = textToEdit.begin();
}

StudentTextEditor::~StudentTextEditor()
{
	// TODO
    list<string>::iterator it;
    for (it = textToEdit.begin(); it != textToEdit.end(); it++)
    {
        it = textToEdit.erase(it);
    }
    // This method must run in O(N) time where N is the number of lines in the file currently being edited.
}

bool StudentTextEditor::load(std::string file) {
    ifstream infile(file);
    
    // if specified file cannot be found, load method should do nothing and return false
    if (!infile )
        return false;
    
    string s;
    
    // getline returns infile; the while tests its success/failure state
    while (getline(infile, s))
    {
        if (!s.empty() && s[s.size() - 1] == '\r')
            s.erase(s.size() - 1); // if there is a return character get rid of it
        textToEdit.push_back(s);
    }
    
    // after loading the specified file, reset the current editing position to the beginning row/column of the file and return true.
    m_row = 0; m_column = 0; m_lineIterator = textToEdit.begin();
    return true;
    // This method must run in O(M+N) time where M is the number of lines in the editor currently being edited, and N is the number of lines in the new file being loaded.
}

bool StudentTextEditor::save(std::string file) {
	// DO I clear the file before?
    ofstream outfile(file);   // outfile is a name of our choosing.
    if (!outfile ) // if creation failed
        return false;
    
    // create an iterator to beginning of textToEdit
    list<string>::iterator it;
    for (it = textToEdit.begin(); it != textToEdit.end(); it++)
    {
        outfile << (*it) << '\n'; // copy over each line followed by newline character
    }
    return true;
    //  This method must run in O(M) time where M is the number of lines in the editor currently being edited.
}

void StudentTextEditor::reset() {
	// TODO
    // delete every string/line in the linked list
    for (m_lineIterator = textToEdit.begin(); m_lineIterator != textToEdit.end(); m_lineIterator++)
    {
        m_lineIterator = textToEdit.erase(m_lineIterator);
    }
    // reset position
    m_row = 0; m_column = 0;
    // This operation must run in O(N) time, where N is the number of rows being edited.
}

void StudentTextEditor::move(Dir dir) {
	// TODO
    switch (dir)
    {
        case TextEditor::UP:
            if (m_row != 0) // if not at top row
            {
                m_row--;
                m_lineIterator--;
                m_column = m_column>(*m_lineIterator).size() ? (*m_lineIterator).size() : m_column; // in case new line to move to is shorter
                return;
            }
            break;
        case TextEditor::DOWN:
            if (m_row != textToEdit.size() - 1) // if not at bottom row
            {
                m_row++;
                m_lineIterator++;
                m_column = m_column>(int)(*m_lineIterator).size() ? (int)(*m_lineIterator).size() : m_column; // in case new line to move to is shorter
                return;
            }
            break;
        case TextEditor::LEFT:
            if (m_row == 0 && m_column == 0) // if at first char of first row
                return;
            if (m_column == 0)
            {
                m_lineIterator--;
                m_row--;
                m_column = (*m_lineIterator).size(); // cursor after last char of line
                return;
            }
            m_column--;
            return;
            break;
        case TextEditor::RIGHT:
            if (m_row == textToEdit.size() - 1 && m_column == (*m_lineIterator).size()) // last char of last row
                return;
            if (m_column == (*m_lineIterator).size())
            {
                m_lineIterator++;
                m_row++;
                m_column = 0; // first char of next line
                return;
            }
            m_column++;
            return;
            break;
        case TextEditor::HOME:
            m_column = 0;
            return;
            break;
        case TextEditor::END:
            m_column = (*m_lineIterator).size();
            return;
            break;
    }
}

void StudentTextEditor::del() {
	// TODO
    if (m_row == textToEdit.size() - 1 && m_column == (*m_lineIterator).size()) // last char of last row
        return;
    if (m_column == (*m_lineIterator).size()) // if just after last character on a line
    {
        m_lineIterator++;
        string addText = (*m_lineIterator); // next line
        m_lineIterator = textToEdit.erase(m_lineIterator);
        m_lineIterator--;
        (*m_lineIterator) += addText;
        getUndo()->submit(Undo::Action::JOIN, m_row, m_column); // call submit with appropriate information
        return;
    }
    
    // call the submit function for StudentUndo
    char deleted = (*m_lineIterator).at(m_column);
    
    // delete character
    (*m_lineIterator).erase(m_column, 1);
    getUndo()->submit(Undo::Action::DELETE, m_row, m_column, deleted);
}

void StudentTextEditor::backspace() {
	// TODO
    if (m_row == 0 && m_column == 0) // nothing to backspace over
        return;
    
    if (m_column > 0)
    {
        // call the submit function for StudentUndo
        char deleted = (*m_lineIterator).at(m_column-1);
        (*m_lineIterator).erase(m_column-1, 1); // delete the character just before the editing position from the current line
        m_column--; // move pos left by one
        getUndo()->submit(Undo::Action::DELETE, m_row, m_column, deleted);
        return;
    }
    
    if (m_column == 0 || (*m_lineIterator).size() == 0) // if at the beginning of a line or at empty line
    {
        string addText = (*m_lineIterator); // retrieve line to be appended
        m_lineIterator = textToEdit.erase(m_lineIterator);
        m_lineIterator--;
        
        m_column = (*m_lineIterator).size(); // set correct column and row
        m_row--;
        (*m_lineIterator) += addText;
        getUndo()->submit(Undo::Action::JOIN, m_row, m_column); // call submit with appropriate information
        return;
    }
    
}

void StudentTextEditor::insert(char ch) {
	// TODO
    string character = ""; // if a tab character add 4 spaces
    if (ch == '\t')
        character += "    ";
    else
        character += ch;
    
    (*m_lineIterator).insert(m_column, character);
    if (ch == '\t') // move position accordingly
        m_column += 4;
    else
        m_column++;
    
    // call the submit function for StudentUndo
    getUndo()->submit(Undo::Action::INSERT, m_row, m_column, ch);
    
    // Insertion of a character into a line must run in O(L) time where L is the length of the line of text containing the current editing position.
}

void StudentTextEditor::enter() {
    // call the submit function for StudentUndo
    getUndo()->submit(Undo::Action::SPLIT, m_row, m_column);
    
	// at point of separation create the new line
    string newLine = (*m_lineIterator).substr(m_column, (*m_lineIterator).size());
    
    // erase the part of the current line to be "entered"
    (*m_lineIterator).erase((*m_lineIterator).begin() + m_column, (*m_lineIterator).end());
    m_lineIterator++;
    
    // add appropriate text to the next line
    m_lineIterator = textToEdit.insert(m_lineIterator, newLine);
    
    m_row++;
    m_column = 0; // adjust positions accordingly
}

void StudentTextEditor::getPos(int& row, int& col) const {
	row = m_row;
    col = m_column;
}

int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const {
	// TODO
    // check parameters are valid
    if (startRow < 0 || numRows < 0 || startRow > textToEdit.size())
        return false;
    
    if (!lines.empty())
        lines.clear(); // clear the lines vector
    list<string>::const_iterator it;
    it = textToEdit.begin();
    
    // get iterator pointing at correct starting row
    for (int i = 0; i < startRow; i++)
        it++;
    
    int linesMoved = 0;
    for (int i = 0; i < numRows; i++)
    {
        if (it != textToEdit.end())
        {
            lines.push_back(*it);
            it++;
            linesMoved++;
        }
        
    }
    return linesMoved;
}

void StudentTextEditor::undo() {
	// copy over information from get function
    string newLine;
    int row, col, count;
    string text;
    Undo::Action lastAction = getUndo()->get(row, col, count, text);
    if  (lastAction == Undo::Action::INSERT)
    {
        m_row = row; m_column = col; // position the cursor on the specified row and column
        (*m_lineIterator).insert(m_column, text);
        // m_column++;
    }
    if  (lastAction == Undo::Action::DELETE)
    {
        m_row = row; m_column = col; // position the cursor on the specified row and column
        (*m_lineIterator).erase(m_column - 1, count); // delete the character just before the editing position from the current line
        m_column--;
    }
    if  (lastAction == Undo::Action::SPLIT)
    {
        m_row = row; m_column = col; // position the cursor on the specified row and column
        // at point of separation create the new line
        newLine = (*m_lineIterator).substr(m_column, (*m_lineIterator).size());
        
        // erase the part of the current line to be "entered"
        (*m_lineIterator).erase((*m_lineIterator).begin() + m_column, (*m_lineIterator).end());
        m_lineIterator++;
        
        // add appropriate text to the next line
        m_lineIterator = textToEdit.insert(m_lineIterator, newLine);
        m_lineIterator--;
        m_row++;
        m_column = 0; // adjust positions accordingly
        
        m_row = row; m_column = col; // the cursor must be set to the specified row, column
    }
    if  (lastAction == Undo::Action::JOIN)
    {
        m_row = row; m_column = col; // position the cursor on the specified row and column
        // m_lineIterator++;
        string addText = (*m_lineIterator); // next line
        m_lineIterator = textToEdit.erase(m_lineIterator);
        m_lineIterator--;
        (*m_lineIterator) += addText;

        m_row = row; m_column = col; // the cursor must be set to the specified row, column
        return;
    }
    if  (lastAction == Undo::Action::ERROR)
    {}
}
