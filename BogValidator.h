#include "BogWordList.h"
#include <iostream>
#include <string>
#include "dictionary.h"
#include "BogSolver.h"
#include <cctype>
#include <cstdlib>

#ifndef BOGVALIDATOR
#define BOGVALIDATOR


using namespace std;

const string correct = "OK ";

const string wrong = "NO ";

class BogValidator
{
    public:
      
      BogValidator(); 
      // constructor
      
      ~BogValidator(); 
      // destructor
      
      bool readDict(); 
      // read in a dictionary
      
      bool readBoard();
      //function reads in characters into the boggle table
      // and initializes the 2D array of bool to false
      
      bool isValid(string s); 
      //function checks if a string is valid
      
      void checkWords(); 
      // compares all the words formed b the played with 
      // the possible words formed on the board
      
    private:
      
       Dictionary dict; 
      
      void solveBoggle(string newString, int r, int c);
      //recursive function that finds all the valid words
      // that can the formed from the boggle board
      
      Dictionary wordsFound;
      //all valid words formed from the boggle board are
      //stored in this dictionary
      
      Dictionary wordsChecked;
      //all words that have been checked are stored in
      // this dictionary
      
      bool solve();
      //function searches board for words in dict
      
      int index[2];
      //array that stores the number of rows in first cell
      // and the number of columns in the second cell
      
      char **board;
      //pointer to the array of characters that represents the 
      //boggle board
      
      bool**checked;
      //pointer to the array of bools that represents the boxes 
      // in the board that have been traversed during the recursive
      //call

};
#endif
