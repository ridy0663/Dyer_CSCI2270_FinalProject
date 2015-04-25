//Author: Richard Dyer
//Date: April 25th, 2015

#include <iostream>
#include "Word.h"
#include "WordTree.h"
#include <fstream>

using namespace std;

bool openAndBuild(WordTree &w, string filename);

//Basic driver function: Creates a WordTree object, calls the openAndBuild function with the object and first command
//line argument as parameters, displays a menu, and calls methods from the object based on the user's input.
//This program requires std==c++11, because of the stoi.
int main(int argc, char* argv[])
{
//Checks that you actually entered a filename into the command line.
    if(argc == 1)
    {
        cout<<"Please enter the name of a text file in the command line."<<endl;
        return 1;
    }
    WordTree w;
    int userInput = 0;
    string strInput;
//Checks that file was actually opened.
    if(!openAndBuild(w, argv[1]))
        return 1;
    while(userInput != 3)
    {
        cout<<"======Main Menu====="<<endl;
        cout<<"1. Print Unique Words"<<endl;
        cout<<"2. Find Data"<<endl;
        cout<<"3. Quit"<<endl;
//It is appreciably difficult to use the cin>> method to read user input that incorporates a space. Thus, I try to use
//getline wherever possible, hence the need for the string to int function.
        getline(cin, strInput);
        if(strInput != "1" && strInput != "2" && strInput != "3")
            cout<<strInput<<" is not a valid input. Please try again."<<endl;
        else
        {
//The only justification I can give for my converting the string to an int is that I like switch statements
            userInput = stoi(strInput);
            switch(userInput)
            {
            case 1:
                cout<<"\n***Unique Words***"<<endl;
                w.printUniqueWords();
                break;
            case 2:
                cout<<"Enter the name of a unique word:"<<endl;
                getline(cin, strInput);
                cout<<endl;
                w.findAndPrint(strInput);
            }
        }
        cout<<endl;
    }
    cout<<"Goodbye!"<<endl;
    return 0;
}

//openAndBuild function: Opens the given text file, and feeds each line from that file into the given WordTree object
//via the parseString method. Returns a bool to show if it was successful in opening the file.
bool openAndBuild(WordTree &w, string filename)
{
    ifstream infile(filename);
    if(infile.is_open())
    {
        string line;
        while(getline(infile, line))
        {
            w.parseString(line);
        }
        infile.close();
        return true;
    }
    else
        cout<<"Could not open "<<filename<<endl;
    return false;
}
