#ifndef STUDENTSPELLCHECK_H_
#define STUDENTSPELLCHECK_H_

#include "SpellCheck.h"

#include <string>
#include <vector>


class StudentSpellCheck : public SpellCheck {
public:
    StudentSpellCheck() {}
	virtual ~StudentSpellCheck();
	bool load(std::string dict_file);
	bool spellCheck(std::string word, int maxSuggestions, std::vector<std::string>& suggestions);
	void spellCheckLine(const std::string& line, std::vector<Position>& problems);

private:
    struct Trie
    {
        Trie* characters[27];
        bool endWord;
    };
    void insert(Trie* root, std::string word);
    bool search(Trie* root, std::string potential);
    void destructTrie(Trie* root);
    void createTrie(Trie* newNode);
    Trie* m_root = nullptr;
};

#endif  // STUDENTSPELLCHECK_H_
