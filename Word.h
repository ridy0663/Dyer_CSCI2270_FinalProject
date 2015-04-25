//Author: Richard Dyer
//Date: April 24th, 2015

#ifndef WORD_H
#define WORD_H
#include <string>

//subWord: stores a word, that word's quantity, and pointers to a parent and left and right children. Used to build the
//binary search tree of words that follow the object's word.
struct subWord
{
    std::string name;
    int quantity;
    subWord* left;
    subWord* right;
    subWord* parent;

    subWord()
    {
        name = "NULL";
        quantity = 0;
    }

    subWord(std::string n, int q)
    {
        name = n;
        quantity = q;
    }
};

class Word
{
    public:
        Word();
        Word(std::string);
        virtual ~Word();
        void addString(std::string);
        void setName(std::string);
        std::string getName();
        void printContents();
    protected:
    private:
        std::string name;
        subWord* root;
        void printContents(subWord*);
        void deleteTree(subWord*);
};

#endif
