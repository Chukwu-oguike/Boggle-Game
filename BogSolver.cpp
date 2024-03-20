#include "BogSolver.h"
#include "BogWordList.h"

//constructor
BogSolver::BogSolver()
{
    board = NULL;
    
    checked = NULL;
        
    wordList.numWords = 0;
    
    listSize = 50;
    
    wordList.words = new BogWord[listSize];   
    
    index[0] = 0;
     
    index[1] = 0;
}

//function reads in words into the dictionary
bool BogSolver::readDict()
{
    string endOfList;
    
    cin >> endOfList;
    
    while(endOfList != ".")
    {
	 dict.insert(endOfList);
	    
         cin >> endOfList;	
    }
    
    return true;
}

//function reads in characters into the boggle table
//which is a 2D array of integers
// and initializes the 2D array of bool to false
bool BogSolver::readBoard()
{
    int i, j,k = 0;    
    
    //the number of rows are stored in the first
    //element of index array
    cin >> index[0];
    
    //the number of columns are stored in the first
    //element of index array
    cin >> index[1];
    
    checkForValidBoard();
    
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
	    board[i][j] = toupper(storeCharacters[k]);
	    
	    checked[i][j] = false;
	    
	    k++;
	}	
	 
    }
    
    return true;
}


//function ensures that the number of elements
//stored are equal to the calculated number 
// of characters and also ensures valid characters are stored
void BogSolver::checkForValidBoard()
{
    char input; 
    
    int counter = 0;
  
    if(index[0] < 0 || index[1] < 0)
    {
      cerr<<"invalid board";
       exit(1);
    }
    
    int expctdSizeOfB = index[0] * index[1];
    
    storeCharacters = new char[expctdSizeOfB + 2];
    
    while(cin>>input && !cin.eof())
    {
       if(!isalpha(input))
       {
	 cerr<<" invalid character";
         exit(1);
       }
      
       storeCharacters[counter] = input;
       
       counter++;
       
       if(counter > expctdSizeOfB)
       {
	 cerr<< " the number of characters are more the number of"
	 <<"slots on the board";
          exit(1);
       }
    }
    
    if(counter < expctdSizeOfB)
    {
      cerr<< " the number of characters are less than the number of slots"
      <<"on the board";
       exit(1);
    }
}

//function searches board for words in dict
bool BogSolver::solve()
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

//function adds characters and their
//coordinates, row then column to a queue
void BogSolver::addToWordList(string wrd)
{
    if(wordsFound.isWord(wrd))
      return;
    
    int i = 0;

    if(wordList.numWords >= listSize)
      expand();
    
    wordList.words[wordList.numWords].numLetts = wrd.length();
    
    wordList.words[wordList.numWords].letts = new BogLett
    [wordList.words[wordList.numWords].numLetts];
  
    while( i < wordList.words[wordList.numWords].numLetts)
    {
	 if(wrd[i] == 'Q' && wrd[i+1] == 'U')
	 {
	    wordList.words[wordList.numWords].letts[i].c = wrd[i];
	    
	    i++;
	 }
    
         //the temporary queue is necessary because a word might be a 
         //prefix to another word and will need to stores the same coordinates
	 // of the characters in the prefix used to store the next word.
	 wordList.words[wordList.numWords].letts[i].c = wrd[i];
	
	 wordList.words[wordList.numWords].letts[i].row = indexQueue.front();
	 
	 tempQueue.push(indexQueue.front());
	 
	 indexQueue.pop();
	
	 wordList.words[wordList.numWords].letts[i].col = indexQueue.front();
	 
	 tempQueue.push(indexQueue.front());
	 	
	 indexQueue.pop();
	 	 
	 i++;
     }
	
     wordList.numWords++;
         
     while(!tempQueue.empty())
     {
	 indexQueue.push(tempQueue.front());
	     
	 tempQueue.pop();    
     }
    
}

//function increases the size of the array pointed to by word 
// precondition: the number of words must be greater 
//or equal to listSize
void BogSolver::expand()
{
        int i;
  
        BogWordList tempWordList;
	
	tempWordList.words = new BogWord[wordList.numWords * 2];
	
	listSize = wordList.numWords * 2;
	
	for(i = 0; i < wordList.numWords; i++)
	{			   	
	    tempWordList.words[i].letts = wordList.words[i].letts; 
	    
	    tempWordList.words[i].numLetts = wordList.words[i].numLetts;
	}

	delete [] wordList.words;
	
	wordList.words = tempWordList.words;
}

//When a a current recursive call reaches it end, the 
//coordinates of the last character will have to be popped
//of the queue. the way to pop of the back of a queue is to
//transfer the elements of the queue to a stack and, pop the stack
//transfer to another stack to flip the order of the previous stack
// then transfer back to a queue
void BogSolver::popBackOfQueue()
{
   stack<int> s2;
   
   stack<int> s3;
   
   while(!indexQueue.empty())
   {
     s2.push(indexQueue.front());
     
     indexQueue.pop();
   }
   
   s2.pop();
   
   s2.pop();
   
   while(!s2.empty())
   {
     s3.push(s2.top());
     
     s2.pop();
   }
   
   while(!s3.empty())
   {
     indexQueue.push(s3.top());
     
     s3.pop();
   }
}

// function finds all the possible valid combination of words 
void BogSolver::solveBoggle(string newString, int r, int c)
{
    checked[r][c] = true;
  
   if(board[r][c] == 'Q')
    {
	newString = newString + board[r][c] + 'U';
    
	indexQueue.push(r);
	       
	indexQueue.push(c);
    }
    
    else
    {  
      	newString = newString + board[r][c];
      
      	indexQueue.push(r);
	       
      	indexQueue.push(c);
    }
    
    if(dict.isWord(newString))
    {
	if(newString.length() > 2)
	{
	    addToWordList(newString);
	    
	    wordsFound.insert(newString);
	}  
    }
  
    //if prefix recurse on every adjacent cell
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
    
    popBackOfQueue();
    
    checked[r][c] = false;
    
    return;
}

//function returns a pointer to an array
//containing characters and their coordinates
// on the boggle board
BogLett* BogSolver::copyLettersList(int indx)
{
    int i, numb = wordList.words[indx].numLetts;
  
    BogLett* temp = new BogLett[numb];
    
    for(i = 0; i < numb; i++)
    {
	temp[i].c = wordList.words[indx].letts[i].c;
      
	temp[i].row = wordList.words[indx].letts[i].row;
      
	temp[i].col = wordList.words[indx].letts[i].col;
    }
    
   return temp; 
}

//function returns number of words found
int BogSolver::numWords()
{
    return wordList.numWords;
}

//function returns the number of words of length len
int BogSolver::numWords(int len)
{
    int i, num = 0;
    
    for(i = 0; i < wordList.numWords; i++)
    {
	if(wordList.words[i].numLetts == len)
	  num++;
    }
    
    return num;
}

//function returns a pointer to a copy of all words found
BogWordList* BogSolver::getWords()
{
   int i; 
   
   BogWordList* pntr1 = new BogWordList;
   
   pntr1->numWords = numWords();
   
   pntr1->words = new BogWord[pntr1->numWords]; 
  
   for(i = 0; i < pntr1->numWords; i++)
   {      
	pntr1->words[i].numLetts = wordList.words[i].numLetts;
	
	pntr1->words[i].letts = copyLettersList(i);
   }
   
   return pntr1;
}

// returns a pointer to a copy of words of length len
BogWordList* BogSolver::getWords(int len)
{
    int i, num = numWords(); 
   
    BogWordList* pntr2 = new BogWordList;
   
    pntr2->numWords = numWords(len);
    
   
    pntr2->words = new BogWord[pntr2->numWords]; 
   
    for(i = 0; i < num; i++)
    {      
 	 if(wordList.words[i].numLetts == len)
 	 {
	     pntr2->words[i].numLetts = wordList.words[i].numLetts;
	
	     pntr2->words[i].letts = copyLettersList(i);
	 }
    }
   
    return pntr2;
}

//function print all words in HBF
void BogSolver::printWords()
{
     
     int i,j,num2 = numWords();
    
     for(i = 0; i < num2; i++)
     {
	 cout<<"< ";
	
	 for(j = 0; j < wordList.words[i].numLetts; j++)
	 {      
	      if(wordList.words[i].letts[j].c == 'Q' &&
		 wordList.words[i].letts[j+1].c == 'U')
              {    
		   cout<<wordList.words[i].letts[j].c;			 
		   
		   j++;
	      }
	   
	     cout<<wordList.words[i].letts[j].c<<
	     " "<<wordList.words[i].letts[j].row<<" "<<wordList.words[i].
	     letts[j].col<<" ";
	 }
	
	 cout<<" >"<<endl;
      }
}

//function prints len-length words in HBF
void BogSolver::printWords(int len)
{
     int i,j,num3 = numWords();
    
      for(i = 0; i < num3; i++)
      {
	  if(wordList.words[i].numLetts == len)
	  {
	      cout<<"< ";
	
	      while(j < wordList.words[i].numLetts)
	      {   
	          if(wordList.words[i].letts[j].c == 'Q' &&
		      wordList.words[i].letts[j+1].c == 'U')
		      {
			  cout<<wordList.words[i].letts[j].c;
			  j++;
		      }
	      
		  cout<<wordList.words[i].letts[j].c<<
		  " "<<wordList.words[i].letts[j].row<<" "
		  <<wordList.words[i].letts[j].col;
		  
		  j++;
		  
	      }
	
	      cout<<" >"<<endl;
	  }
      } 
}

//function print all words
void BogSolver::listWords()
{
    int i,j,num2 = numWords();
    
    for(i = 0; i < num2; i++)
    {	
	for(j = 0; j < wordList.words[i].numLetts; j++)
	{      
	    cout<<wordList.words[i].letts[j].c;
	}
	
	cout<<endl;
     }
}

// function print all words of length len
void BogSolver::listWords(int len)
{
    int i,j,num3 = numWords();
    
      for(i = 0; i < num3; i++)
      {
	  if(wordList.words[i].numLetts == len)
	  {	
	      for(j = 0; j < wordList.words[i].numLetts; j++)
	      {      
		  cout<<wordList.words[i].letts[j].c;		  
	      }
	
	      cout<<endl;
	  }
      } 
}

//destructor gets read of all allocated memory
BogSolver::~BogSolver()
{
     int i,j, num4 = numWords();
  
     for(i = 0; i < index[0]; i++)
     {
	 delete [] board[i];
	 delete [] checked[i];
     }
     
     delete [] board;
     delete [] checked;
     
     for(j = 0; j < num4; j++)
     {
	delete [] wordList.words[j].letts;
     }
     
     delete [] wordList.words;
     
     delete [] storeCharacters;
}
