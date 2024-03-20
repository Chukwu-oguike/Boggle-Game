#include "BogScorer.h"

BogScorer::BogScorer()
{
     board = NULL;
     
     checked = NULL;
     
     index[0] = 0;
     
     index[1] = 0;
}

//function reads in words into the dictionary
bool BogScorer::readDict()
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
bool BogScorer::readBoard()
{
	int i, j;
	
	char cube;
    
	cin >> index[0];
    
	cin >> index[1];
    
	board = new char*[index[0]];
    
	checked = new bool*[index[0]];
    
	//the 2D array of characters and bools are created together
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
bool BogScorer::isValid(string s)
{
    return (wordsFound.isWord(s) && !wordsChecked.isWord(s)) ;
}

//recursive function that finds all the valid words
// that can the formed from the boggle board
void BogScorer::solveBoggle(string newString, int r, int c)
{
	if(board[r][c] == 'q')
	newString = newString + board[r][c] + 'u';
    
	else
        newString = newString + board[r][c];
    
	if(!dict.isPrefix(newString))
	return;
    
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

//function outputs all the words with the
//points earned per word
void BogScorer::scoreWords()
{
    solve();
  
    string s1;
    
    int sum = 0; 
    
    int numCorrect = 0;
    
    int length1;
    
    while(cin>>s1)
    {
	if(isValid(s1))
	{
	    length1 = s1.length();
	    
	    numCorrect++;
	    
	    cout<<score(length1)<<correct<<s1<<endl;
	    
	    sum = sum + score(length1);	    
	}
	
	else
	  cout<<ZER_O<<wrong<<s1<<endl;
	
	wordsChecked.insert(s1);
    }
    
    cout<<numCorrect<<" words "<<sum<<" points"<<endl;
}

//function that solves the boggle
bool BogScorer::solve()
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


int BogScorer::score(int L)
{
    if(L == length3)
      return 1;
      
    if(L == length4)
      return 1;
      
    if(L == length5)
      return 2;
     
    if(L == length6)
      return 3; 
      
    if(L == length7)
      return 5;
      
    return 11;
}

//function calculates the score for each word
BogScorer::~BogScorer()
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