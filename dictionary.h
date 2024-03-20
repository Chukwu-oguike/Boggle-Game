#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <cassert>

#ifndef DICTIONARY
#define DICTIONARY

using namespace std;

const int ALPHABET_SIZE = 26;

//node for each branch in trie
struct trie_Node
{
   bool isWordPresent;
   
   trie_Node* children[ALPHABET_SIZE];
   
   ~trie_Node();
};

class Dictionary
{
 
    public:
      
      Dictionary();
      //constructor
      
      bool isPrefix(string s);
      // functions checks if a prefix is in a trie
      
      bool isWord(string s);
      // functions checks if a word is in a trie
      
      bool insert(string s);
      // functions inserts a word into a trie
      
      ~Dictionary();
      //destroys the root node
      
    private:
      
      trie_Node *root;
      
      trie_Node *current;
      //pointer that points to the last 
      //node traced out by the prefix function.
      
      int charToInt(char c);
      //function converts indexes alphabets from 0 to 25
      // in the order they appear in the english alpahbetic 
      //system
      
      void initializeNodes(trie_Node* N);
      //function initializes all pointers in a node to NULL
      
      string convertToValidString(string st);
      //function reads a string of non-alphabetic characters
      //and convert alphabets to lower case
         
      bool isDictionaryEmpty();
      //checks if the dictionary is empty
};
#endif
