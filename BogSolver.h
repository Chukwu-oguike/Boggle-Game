#ifndef BOGSOLVER
#define BOGSOLVER

#include "BogWordList.h"
#include <iostream>
#include <string>
#include <iostream>
#include "dictionary.h"
#include <queue>
#include <stack>
#include <cctype>
#include <cstdlib>

using namespace std;

class BogSolver
{
    public:
    
      BogSolver();
      //constructor
      
      ~BogSolver();
      //destructor
      
      bool readDict();
      //function reads in words into the dictionary
      
      bool readBoard();
      //function reads in characters into the boggle table
      // and initializes the 2D array of bool to false
      
      bool solve(); 
      //function searches board for words in dict
      
      int numWords(); 
      //function returns number of words found
      
      int numWords(int len); 
      //function returns the number of words of length len
      
      BogWordList* getWords(); 
      //function returns a pointer to a copy of all words found
      
      BogWordList* getWords(int len); 
      // returns a pointer to a copy of words of length len
      
      void printWords(); 
      //function print all words in HBF
      
      void printWords(int len); 
      // print len-length words in HBF
      
      void listWords(); 
      //function print all words
      
      void listWords(int len); 
      // function print all words of length len
      
      
    private:
      
      Dictionary dict; 
      //dictionary
      
      Dictionary wordsFound;
           
      void solveBoggle(string newString, int r, int c);
      //recursive function that finds all the valid words
      // that can the formed from the boggle board
      
      char **board;
      //pointer to the array of bools that represents the boxes 
      // in the board that have been traversed during the recursive
      //call
      
      BogWordList wordList;
      //stores the list of words
      
      void addToWordList(string wrd);
      //function adds characters and their
      //coordinates to a list
     
      int listSize;
      //variable to hold the size of the array created
      // to store words
      
      BogLett* copyLettersList(int indx);
      //function returns a pointer to an array
      //containing characters and their coordinates
      // on the boggle board
      
      void expand();
      //function increases the size of the array of word 
      // precondition: the number of words must be greater 
      //or equal to listSize
      
      int index[2];
      //array that stores the number of rows in first cell
      // and the number of columns in the second cell
      
      queue<int> indexQueue;
      //queue to store the coordinates 
      // of characters on the board that are
      //used to form words
      
      queue<int> tempQueue;
      
      bool **checked;
      //pointer to the array of characters that represents the 
      //boggle board
      
      char *storeCharacters;
      
      void checkForValidBoard();
      //funciton ensures that valid characters are
      //inputted into the board and that the number of 
      //elements the board can take match the number of 
      //elements that are inputted into the board
      
      void popBackOfQueue();
      //function removes the last two elements on the queue
      
      
};
#endif
