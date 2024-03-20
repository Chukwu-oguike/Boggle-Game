
#include "BogWordList.h"
#include <iostream>
#include <string>
#include <iostream>
#include "dictionary.h"
#include "BogValidator.h"

using namespace std;

int main()
{
   BogValidator v;
   v.readDict();
   v.readBoard();
   v.checkWords();

    return 0;
}