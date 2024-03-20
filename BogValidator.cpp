#include "BogValidator.h"

//CONSTRUCTOR
BogValidator::BogValidator()
{
     board = NULL;
     
     checked = NULL;
     
     index[0] = 0;
     
     index[1] = 0;
}

// read in a dictionary
bool BogValidator::readDict()
{
     string endOfList;
    
    while(endOfList != ".")
    {
	cin >> endOfList;
	
	dict.insert(endOfList);
    }
    
    return true;
}

//function reads in characters into the boggle table
// and initializes the 2D array of bool to false
bool BogValidator::readBoard()
{
    int i, j;
    
    char cube;
    
    //the number of rows are stored in the first
    //element of index array
    cin >> index[0];
    
    //the number of columns are stored in the first
    //element of index array
    cin >> index[1];
    
    board = new char*[index[0]];
    
    checked = new bool*[index[0]];
    
    for(i = 0; i < index[0]; i++)
    {
	board[i] = new char[index[1]];
	
	checked[i] = new bool[index[1]];
    }
    
    for(i = 0; i < index[0]; i++)
    {
	for(j = 0; j < index[1]; j++)
	{
	    cin >> cube;
	  
	    board[i][j] = cube;
	    
	    checked[i][j] = false;	    
	}	 
    }
    
    return true;
}



//function checks if a string is valid
bool BogValidator::isValid(string s)
{
    return (wordsFound.isWord(s) && !wordsChecked.isWord(s));
}

//recursive function that finds all the valid words
// that can the formed from the boggle board
void BogValidator::solveBoggle(string newString, int r, int c)
{
    if(board[r][c] == 'q')
      newString = newString + board[r][c] + 'u';
    
    else
    newString = newString + board[r][c];
    
    if(!dict.isPrefix(newString))
      return;
   //stores found words in the wordsFOund dictionary 
    if(dict.isWord(newString))
      wordsFound.insert(newString);
    
    if(dict.isPrefix(newString))
    {
	if(r+1 < index[0] && c+1 < index[1] && checked[r+1][c+1] == false)	
	  solveBoggle(newString,r+1,c+1);
	
	if(r+1 < index[0] && checked[r+1][c] == false)
	  solveBoggle(newString,r+1,c);
	
	if(c+1 < index[1] && checked[r][c+1] == false)
	  solveBoggle(newString,r,c+1);
	
	if(r-1 >= 0 && checked[r-1][c] == false)
	  solveBoggle(newString,r-1,c);
	
	if(r-1 >= 0 && c+1 < index[1] && checked[r-1][c+1] == false)
	  solveBoggle(newString,r-1,c+1);
	
	if(r-1 >= 0 && c-1 >= 0 && checked[r-1][c-1] == false)
	  solveBoggle(newString,r-1,c-1);
	
	if(c-1 >= 0 && checked[r][c-1] == false)
	  solveBoggle(newString,r,c-1);

	if(r+1 < index[0] && c-1 >= 0 && checked[r+1][c-1] == false)
	  solveBoggle(newString,r+1,c-1);	

    }
    
    checked[r][c] = false;   
    
    return;
}

// compares all the words formed b the played with 
// the possible words formed on the board
void BogValidator::checkWords()
{
    solve();
  
    string s1;
 //correct is a constant that represents OK and wrong represent NO   
    while(cin>>s1)
    {
	if(isValid(s1))
	cout<<correct<<s1<<endl;
	
	else
	  cout<<wrong<<s1<<endl;
	
	wordsChecked.insert(s1);
    }
}

//function searches board for words in dict
bool BogValidator::solve()
{ 
    string baseString = "";
    
    int i,j;
    
    for(i = 0; i < index[0]; i++)
    { 
	for(j = 0; j < index[1]; j++)
	{
	    solveBoggle(baseString, i, j);
	    
	    baseString = "";
	}
    }  
    
    return true;
}

//destructor
BogValidator::~BogValidator()
{
     int i;
  
     for(i = 0; i < index[0]; i++)
     {
	 delete [] board[i];
	 delete [] checked[i];
     }
     
     delete [] board; 
     delete [] checked; 
}