# Dyer_CSCI2270_FinalProject

Project Summary:
  In my project, I will create a library that will read in text. It will store each unique word, and with that word, each unique word that follows it in the text, as well as the number of times that word has followed the first word. I intend to implement this as two classes. One will represent a unique word as a string and will also contain a binary search tree of structs for each unique word imediately proceeding it containing a string of that word and an int of the number of times that word follows the original word. This class will have methods for updating this data structure, and managing sorting. The second class will contain a binary search tree of the first class, and will have methods for updating itself with text its fed.
  
How to Run:
  Included is an example driver function that reads a file from the command line and feeds its text into a WordTree object. In order to use my code as intended, you shouldn't make any explicit declarations of or calls to a Word object, as that is handled entirely within the WordTree class. You can declare a WordTree object with:
  
  WordTree w;
  
as it only has one constructor. There are three public methods you can call: parseString(string line) which takes a line of text, parses it into words, and feeds those words into the object's binary search tree, printUniqueWords() which takes no parameters and prints each unique word found in the text in alphabetical order, and findAndPrint(string name) which finds a given word in the binary search tree and prints each word that immediately followed it in the text, as well as the number of times that word followed the original word.

Dependencies:
  The example driver function requires the use of std==c++11 

The following c++ libraries are necessary to run this code:
  iostream,
  "string.h,"
  sstream,
  queue,
  string,
  fstream(only needed for the example driver function)

System Requirements:
To the best of my knowledge, this program should run on any system that can compile c++. However, if its any help, I wrote and debuuged it on a linux machine.

Group Members:
  Richard Dyer
  
Contributors:

Open issues:
  The code itself is fairly airtight. However, I would appreciate it if someone could write me a function that takes a string as the parameter and does the following: checks the first character of the string and, if its a capital letter, makes it lower case, and checks the last character of the string and, if its a period, comma, question mark, or exclaimation mark, removes it.
