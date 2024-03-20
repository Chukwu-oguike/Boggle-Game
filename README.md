Project: The Game of Boggle

The aim of the game of Boggle is to find sequences of adjacent letters that form words,
and there is a time limit. Adjacent includes vertical, horizontal, and diagonal.

In this program, users will play against a computer. 

The programs in the file 

1) Loads a Boggle board
2) Finds all words in the board
3) Checks the user’s words to make sure they are correct
4) Scores the user’s words


Input Data Format

The input data for the Boggle board looks like this:
           4 4
           EOHM
           AHFO
           ZROV
           YPLE

The first line has two numbers: the number of rows and the number of columns of the board.
Your program must work for boards of any size. After the first line are rows of letters. Each row
is a single string with the correct width. These might be upper or lower case. You must convert
all to upper case. There is no sentinel value for the board because you are told at the outset
how many rows there will be.

Function of subprograms:

Program 1: BogSolver

The first program is the boggle solver.

This program reads in two sets of data. First, it will read in a list of legal words (the dictionary). Then the
program will read in a boggle board.

After reading in the dictionary and boggle board, the program will solve the board by searching
for all legal words that can be formed by sequences of adjacent letters (including duplicate
words). The same cell may not be used twice in the same word. Check online for details of the
rules of boggle.  

Then it prints out its complete solution. The solution will be a list of the words it
found. The output is more than just a list of strings, though. The output will also include the
locations of the letters. And the output must use a very precise format. Here is an example. The
words "ROLE" and "HAZY" appear on the board shown above. We assign coordinates (0,0) to
the upper left cell. Giving row and column positions with each letter, we report these two words
as follows:
< R 2 1 O 2 2 L 3 2 E 3 3 >
< H 1 1 A 1 0 Z 2 0 Y 3 0 >

Each word begins with "<" and ends with ">". Between those markers is a sequence of triples:
letter, row number, column number. All items are separated by spaces. The end of the list is
marked by the empty word: "< > “

Program 2: BogChecker

This program checks the user’s answers to see if they are valid answers. The checker first reads from cin the dictionary.  T
he checker then reads from cin the boggle board the user
worked on. The Bogchecker program then prints out a report on all the words the user gave it. Each user answer 
is printed preceded by OK or NO. OK means the word is a legal answer. NO
means it is not a legal answer. 

Program 3: BogScorer

This program reads in a checker report as shown above. And it prints out each line
with a score printed at the left. At the end of the output, the program will print the number of
valid words and the total number of points, using the scoring rules for Boggle. The
output for the sample data shown above is:
1 OK ROLE
1 OK MOVE
0 NO LAZY
0 NO MOVE
...

Program 4: Dictionary:

This is a Trie structure that stores all the legal words for the Boggle game.
