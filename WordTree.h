//Author: Richard Dyer
//Date: April 24th, 2015

#ifndef WORDTREE_H
#define WORDTREE_H
#include "Word.h"

//wordNode: stores a Word object, and pointers to a parent and left and right children. Used to build the
//binary search tree of unique words found in inputed text.
struct wordNode
{
    Word content;
    wordNode* left;
    wordNode* right;
    wordNode* parent;
};

class WordTree
{
    public:
        WordTree();
        virtual ~WordTree();
        void parseString(std::string);
        void printUniqueWords();
        void findAndPrint(std::string);
    protected:
    private:
        wordNode* root;
        std::string remainder;
        void addNode(std::string, std::string);
        void printTraverse(wordNode*);
        wordNode* findNode(wordNode*, std::string);
        void deleteTree(wordNode*);
};

#endif
