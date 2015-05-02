//Author: Richard Dyer
//Date: April 25th, 2015

#include "WordTree.h"
#include <iostream>
#include "string.h"
#include <sstream>
#include <queue>

using namespace std;

//Standard constructor
WordTree::WordTree()
{
    root = new wordNode;
    remainder = "NULL STRING";
}

//Standard destructor
WordTree::~WordTree()
{
    deleteTree(root);
}

/*
Function prototype:
void WordTree::parseString(string line);

Function description:
This function takes a string of several words, parses it, and uses a queue to feed each pairing of subsequent word into
the addNode function. The final word in the queue is saved in the remainder variable in order to be immediately enqueued
the next time this function is called.

Example:
WordTree w;
w.parseString("hello world");

Precondition: root wordNode must not be NULL, one string must be inputted.
Post condition: each set of subsequent words will have been inputted into the addNode function, with the final word
stored in the remainder variable.
*/
void WordTree::parseString(string line)
{
    stringstream ss;//This will be used to parse the string
    deque<string> q;//This will be used to feed strings into the addString function two at a time
    string former, latter;//The two current strings, with names representing their place in the queue

//If there's anything legit in the remainder variable, it gets enqueued first
    if(remainder != "NULL STRING")
        q.push_back(remainder);

    ss.str(line);
//This loop simply parses the line and feeds each word into the queue
    while(getline(ss, former, ' '))
    {
        if(q.size() < q.max_size())
            q.push_back(former);
        else{
            cout<<"Text file is too big!"<<endl;
            return;
        }
    }

    while(!q.empty())
    {
        former = q.front();
        q.pop_front();
//If the queue is now empty, that means that there is no latter left to go with former, and former should be stored as
//the remainder, so that it may be enqueued the next time this function is called.
        if(q.empty())
        {
            remainder = former;
        }
        else
        {
            latter = q.front();
//Notice that there is no q.pop() after I set latter to q.front. This is because what is latter on this cycle of the
//loop will be former on the next cycle, so that now words are lost.
            addNode(former, latter);
        }
    }
}

//Recursive print function: Public method. Takes no parameters and feeds the root node into the private overloaded
//version of this function.
void WordTree::printUniqueWords()
{
    if(root->left != NULL)
        printTraverse(root->left);
    cout<<root->content.getName()<<endl;
    if(root->right != NULL)
        printTraverse(root->right);
}

//Find and Print: Public method. Feeds the string parameter and the root node into the findNode function and, if a
//matching wordNode if found, prints that nodes contents.
void WordTree::findAndPrint(string name)
{
    wordNode* temp = findNode(root, name);
    if(temp == NULL)
        cout<<name<<" not found."<<endl;
    else
        temp->content.printContents();
}

/*
Function prototype:
void WordTree::addNode(string former, string latter);

Function description:
This function takes two strings, labeled former and latter to represent the order they appear in the text, and searches
the tree of wordNodes for a Word object whose name matches the former string. If a match is found, the latter string is
added to the Word object, else a new wordNode is created, containing a new Word object with former as its name, and
latter as its first subWord.

Example:
This is a private method and is only called by the parseString function. See the aforementioned function's code for an
example call to this function.

Precondition: root wordNode must not be NULL; two strings must be inputted.
Post condition: Former string will have been added into its corresponding location in the tree, with latter added into
its Word object.
*/
void WordTree::addNode(string former, string latter)
{
//This checks to see if there is a legitimate wordNode in the root, and, if there isn't, creates one.
    if(root->content.getName() == "NULL")
    {
        root->content.setName(former);
        root->content.addString(latter);
//This exits the function before the next lines can needlessly allocate memory that won't be used.
        return;
    }
    wordNode* temp = new wordNode;
    wordNode* newNode = new wordNode;
//Sets the name of the object to the first word
    newNode->content.setName(former);
//Adds the second word to the object
    newNode->content.addString(latter);
    bool done = false;

//temp will traverse the tree to find a match for the string, or the place to create it as a new wordNode.
    temp = root;
    while(!done)
    {
//If we already have a wordNode that matches former, we can simply add latter to its Word object.
        if(temp->content.getName() == former)
        {
            temp->content.addString(latter);
            done = true;
        }
        else if(strcmp(former.c_str(), temp->content.getName().c_str()) < 0)
        {
//If its destined to go left, but there is nothing to the left, then we have found the place for this new wordNode.
            if(temp->left == NULL)
            {
                temp->left = newNode;
                newNode->parent = temp;
                return;
            }
        else
            {
                temp = temp->left;
            }
        }
        else
        {
//If its destined to go right, but there is nothing to the right, then we have found the place for this new wordNode.
            if(temp->right == NULL)
            {
                temp->right = newNode;
                newNode->parent = temp;
                return;
            }
            else
            {
                temp = temp->right;
            }
        }
    }
}

//Recursive print function: Private method. Recursively prints the name of every wordNode in the tree in alphabetical
//order.
void WordTree::printTraverse(wordNode* node)
{
    if(node->left != NULL)
        printTraverse(node->left);
    cout<<node->content.getName()<<endl;
    if(node->right != NULL)
        printTraverse(node->right);
}

wordNode* WordTree::findNode(wordNode* node, string name)
{
    if(node == NULL)
        return NULL;
    else if(node->content.getName() == name)
        return node;
    else if(strcmp(name.c_str(), node->content.getName().c_str()) < 0)
        return findNode(node->left, name);
    else
        return findNode(node->right, name);
}

//Recursive Delete Function: Private method. Recursively deallocates all of the memory used by the tree. Called by
//destructor.
void WordTree::deleteTree(wordNode* doomedNode)
{
//Somehow, this function seems to occasionally get fed NULL pointers, so I have to use this error check, lest I invoke
//a segmentation fault.
    if(doomedNode == NULL)
        return;

    if(doomedNode->left != NULL)
        deleteTree(doomedNode->left);
    if(doomedNode->right != NULL)
        deleteTree(doomedNode->right);

    delete doomedNode;
}
