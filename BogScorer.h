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

const string correct = " OK ";

const string wrong = " NO ";

const int ZER_O = 0;

const int length3 = 1;

const int length4 = 1;

const int length5 = 2;

const int length6 = 3;

const int length7 = 5;

const int length8 = 11;

class BogScorer
{
    public:
      
      BogScorer(); 
      // constructor 
      
      ~BogScorer(); 
      // destructor
      
      bool readDict(); 
      //function reads in words into the dictionary
      
      bool readBoard(); 
      //function reads in characters into the boggle table
      // and initializes the 2D array of bool to false
      
      bool isValid(string s); 
      //function checks if a string is valid
      
      void scoreWords(); 
      //function outputs all the words with the
      //points earned per word
      
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
      //function that solves the boggle
      
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
      
      int score(int L);
      //function calculates the score for each word
      

};
#endif
