//Author: Richard Dyer
//Date: April 24th, 2015

#include "Word.h"
#include <iostream>
#include "string.h"

using namespace std;

//Default constructor. Initiates object's name to "NULL".
Word::Word()
{
    name = "NULL";
    root = new subWord();
}

//Overloaded constructor. Initiates object's name to the string parameter.
Word::Word(string _word)
{
    name = _word;
    root = new subWord();
}

//Standard destructor
Word::~Word()
{
    deleteTree(root);
}

/*
Function prototype:
void Word::addString(string inWord);

Function description:
This functions cycles through the object's tree of subWords. If a match is found, that words quantity is incremented.
Else it creates a new subWord with quantity 1.

Example:
Word w("hello");
w.addString("world");

Precondition: root subWord must not be NULL, one string must be inputted.
Post condition: if a match is found, that subWord is incremented, else a new subWord is created.
*/
void Word::addString(string inWord)
{
//This checks to see if there is a legitimate subWord in the root, and, if there isn't, creates one.
    if(root->name == "NULL")
    {
        root->name = inWord;
        root->quantity = 1;
//This exits the function before the next lines can needlessly allocate memory that won't be used.
        return;
    }
//I had originally tried to allocate temp on the stack, but I was getting stack overflow.
    subWord* temp = new subWord;
    subWord* newWord = new subWord(inWord, 1);
    bool done = false;

//temp will traverse the tree to find a match for the string, or the place to create it as a new subWord.
    temp = root;
    while(!done)
    {
//If we already have a matching subWord, we need only increment the value.
        if(temp->name == inWord)
        {
            temp->quantity++;
            done = true;
        }
        else if(strcmp(inWord.c_str(), temp->name.c_str()) < 0)
        {
//If its destined to go left, but there is nothing to the left, then we have found the place for this new subWord.
            if(temp->left == NULL)
            {
                temp->left = newWord;
                newWord->parent = temp;
                done = true;
            }
            else
            {
                temp = temp->left;
            }
        }
        else
        {
//If its destined to go right, but there is nothing to the right, then we have found the place for this new subWord.
            if(temp->right == NULL)
            {
                temp->right = newWord;
                newWord->parent = temp;
                done = true;
            }
            else
            {
                temp = temp->right;
            }
        }
    }
}

//Standard setter.
void Word::setName(string n)
{
    name = n;
}

//Standard getter.
string Word::getName()
{
    return name;
}

//Recursive print function: Public method. Takes no parameters and feeds the root into the private recursive print
//function.
void Word::printContents()
{
    cout<<"***"<<name<<"***"<<endl;
    if(root->name != "NULL")
        printContents(root);
}

//Recursive print function: Private method. Recursively prints the name of every subWord in the tree in alphabetical
//order.
void Word::printContents(subWord* _word)
{
    if(_word->left != NULL)
        printContents(_word->left);
    cout<<_word->name<<':'<<_word->quantity<<endl;
    if(_word->right != NULL)
        printContents(_word->right);
}

//Recursive Delete Function: Private method. Recursively deallocates all of the memory used by the tree. Called by
//destructor.
void Word::deleteTree(subWord* doomedWord)
{
//Somehow, this function seems to occasionally get fed NULL pointers, so I have to use this error check, lest I invoke
//a segmentation fault.
    if(doomedWord == NULL)
        return;

    if(doomedWord->left != NULL)
        deleteTree(doomedWord->left);
    if(doomedWord->right != NULL)
        deleteTree(doomedWord->right);

    delete doomedWord;
}
