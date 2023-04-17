#include "StudentSpellCheck.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

SpellCheck* createSpellCheck()
{
	return new StudentSpellCheck;
}

StudentSpellCheck::~StudentSpellCheck() {
    destructTrie(m_root);
    
}

bool StudentSpellCheck::load(std::string dictionaryFile) {
    // return false;
    ifstream infile(dictionaryFile);
    
    // if specified file cannot be found, load method should do nothing and return false
    if (!infile)
        return false;
    
    if (m_root != nullptr)
        destructTrie(m_root); // if a dictionary already exists
    
    m_root = new Trie();
    createTrie(m_root); // create and initialize trie
    string line;
    while (getline(infile, line))
    {
        insert(m_root, line); // insert into tree using insert function
    }
    
	return true;
}

bool StudentSpellCheck::spellCheck(std::string word, int max_suggestions, std::vector<std::string>& suggestions) {
    // make all letters lowercase
    for (int i = 0; i < word.size(); i++)
    {
        if (word[i] == '\'')
            continue; // move to next iteration if an apostrophe
        word[i] = tolower(word[i]); // lowercase if a letter
    }
    
    bool inDictionary = search(m_root, word); // is the word in the dictionary?
    if (inDictionary)
        return true;
    
    else
    {
        if (!suggestions.empty())
            suggestions.clear(); // clear suggestions vector
        for (int i = 0; i < word.size(); i++)
        {
            if (suggestions.size() >= max_suggestions) break;
            for (int j = 0; j < 27; j++) // look at each letter in the word
            {
                char replace;
                if (i == 26)
                    replace = '\'';
                else replace = 'a' + j; // find character to replace with
                
                string newWord = word.substr(0, i) + replace + word.substr(i+1, word.size());
                if (newWord == word)
                    continue;
                else
                {
                    if (search(m_root, newWord)) // if the new word is found
                    {
                        suggestions.push_back(newWord);
                    }
                }
            }
        }
    }
    
	return false; // TODO
}

void StudentSpellCheck::spellCheckLine(const std::string& line, std::vector<SpellCheck::Position>& problems) {
	
    string thisWord;
    for (int i = 0; i <= line.size(); i++)
    {
        if ((line[i] == '\'' || isalpha(line[i])) && !(i == line.size()))
        {
            thisWord += line[i]; // append to the word
        }
        else
        {
            if (!search(m_root, thisWord)) // if not found
            {
                // push position of word onto stack
                Position posWord = { i-(int)thisWord.size(), i-1 };
                problems.push_back(posWord);
            }
            thisWord = ""; // reset thisWord
        }
    }
    
}

void StudentSpellCheck::insert(Trie* root, string word)
{
    Trie* current = root;
    for (int i = 0; i < word.length(); i++)
    {
        int charNumber;
        if (word[i] == '\'')
            charNumber = 26;
        else
            charNumber = tolower(word[i]) - 'a'; // get the number of the character
        if (current->characters[charNumber] == nullptr) // if the path doesn't exist yet
        {
            Trie* toInsert = new Trie;
            createTrie(toInsert);
            current->characters[charNumber] = toInsert;
        }
        current = current->characters[charNumber]; // move down the pointer
    }
    current->endWord = true;
}

bool StudentSpellCheck::search(Trie* root, string potential)
{
    Trie* current = root;
    
    for (int i = 0; i < potential.size(); i++) // go through characters
    {
        int charNumber;
        if (potential[i] == '\'')
            charNumber = 26;
        else
        {
            char lowerPotential = tolower(potential[i]);
            charNumber =  lowerPotential - 'a'; // get the proper index to search with lowercase letter
        }
        
        if (current->characters[charNumber] == nullptr) // if there is no child
            return false;
        
        current = current->characters[charNumber]; // move pointer downwards
    }
    if (current != nullptr && current->endWord) // word is found, and it is the end of a word
        return true;
    
    return false;
}

void StudentSpellCheck::destructTrie(Trie* root)
{
    if (root == nullptr)
        return;
    for (int i = 0; i < 27; i++)
    {
        if (root->characters[i] != nullptr)
            destructTrie(root->characters[i]); // call destructor on all its children
    }
    delete root; // delete the root after deleting the children
}

void StudentSpellCheck::createTrie(Trie* newNode)
{
    newNode->endWord = false;
    for (int i = 0; i < 27; i++)
    {
        newNode->characters[i] = nullptr;
    }
}
