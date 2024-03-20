#include "dictionary.h"

Dictionary::Dictionary()
{
    root = new trie_Node;
    
    initializeNodes(root);
    //initializes all pointers in the node to NULL
}

//checks if a string is a prefix in the dictionary
bool Dictionary::isPrefix(string s)
{     //gets the alphabets in the string and converts to lower case
      string valString = convertToValidString(s);
      
      current = root;
    
      //checks if the root node has any word
      //the root node always stores the empty string
      if(valString.length() == 0)
      {
	  return(!isDictionaryEmpty());
      }
      
      int index = 0, i = 0, prefixLength = valString.length(); 
      
      //checks if the children of the nodes with the index of 
      //the alphabets in string are pointing to NULL       
      while(i < prefixLength)
      { 
	  index = charToInt(valString[i]); 
	  	  
	  if(current->children[index] == NULL)
	  {
	      return false;
	  }
	  
	  else
	  {	  
	      current = current->children[index];    
	  }
	  
	  i++;
      }
      
      
      return true;
}

//since current always points to the last node 
//traced out by the isPrefix function, we then 
//need to see if the prefix exist (which will point 
//current to the last node traced out by isPrefix) then check
//if the prefix is stored as word has been stored in the last node
bool Dictionary::isWord(string s)
{  
   return(isPrefix(s) && current->isWordPresent); 
}

bool Dictionary::insert(string s)
{
          string validString = convertToValidString(s);

	  int indx, i = 1, wordLength = validString.length();

          if(wordLength == 0)
            root->isWordPresent = true;
	  
          if(!isWord(validString))
          {
	  //we want to find the largest sub-string (starting 
	  //from the first alphabet)
	  //of the word that is a prefix in the dictionary
	  while(isPrefix(validString.substr(0,i)))
	  {	
	      i++;

            

	   }
      
          //since the index of each letter is one less than the 
	  //smallest sub-string that contains that letter
	  i--;
      
	  //Then we need to create more nodes to accomodate 
	  //the other end of the string once we have found the largest
	  //string that is a prefix in the dictionary
	  while(i < wordLength)
	  {   
	      
	      indx = charToInt(validString[i]);
	
	      trie_Node *newNode = new (nothrow) trie_Node;
	       
	      //if we run out of memory exit
	      if(newNode == NULL)
	      {
		return false;
	      }
	    
	      initializeNodes(newNode);
	   
	      current->children[indx] = newNode;
	    
	      current = current->children[indx];
	  
	      i++;
	  }
        }
	  
	  current->isWordPresent = true;

      return true;  
}

//function converts indexes alphabets from 0 to 25
// in the order they appear in the english alpahbetic 
//system
int Dictionary::charToInt(char c)
{
    return(c - 'a');
}

//initializes all pointers in newly created nodes
//to NULL and isWordPresent to false

void Dictionary::initializeNodes(trie_Node* N)
{
    int i;
   
    N->isWordPresent = false;
   
    for(i = 0; i < 26; i++)
    {
	N->children[i] = NULL;
    }  
}

//extracts all alphabets from a string in order and converts
//them to lower case
string Dictionary::convertToValidString(string st)
{
    int i = 0;
    
    char t;
    
    int initialWordLength = st.length();
    
    string validString;
    
    while(i < initialWordLength)
    {
        //if character at index is an apphabet
	if(isalpha(st[i]))
	{   
	   t = tolower(st[i]);
	    
	   validString = validString + t; 
	}
	
	i++;
    }
   
    return validString;
}

bool Dictionary::isDictionaryEmpty()
{
	int i;

        if(root->isWordPresent)
          return false;

	for(i = 0; i < 26; i++)
	{
		if(root->children[i] != NULL)
                  return false;
	}

	return true;
}

//destructor deletes all the nodes in the dictionary
trie_Node::~trie_Node()
{
    int i;
  
    for(i = 0; i < 26; i++)
    {
	if(children[i] != NULL)
	delete children[i];
    }
    
}

//deletes the node pointed to by root
Dictionary::~Dictionary()
{
  delete root;
}
