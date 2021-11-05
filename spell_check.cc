// Jeffrey Li
// spell_check.cc: A simple spell checker.

#include <fstream>
#include <iostream>
#include <string>

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "double_hashing.h"
using namespace std;

// You can add more functions here.

// CaseA: Insert a character somewhere within the string to find a match within dictionary.
// @dictionary: dictionary used from input throughout the whole code
// @x: the string that was inputted incorrectly
bool CaseA(HashTableDouble<string>& dictionary, string x)
{
  int corrected = 0;
  string word = "";
  string alphabet = "abcdefghijklmnopqrstuvwxyz";
  for(size_t i = 0; i <= x.size(); i++)
  {
    for(char j : alphabet)
    {
      word = x;
      word.insert(i,string(1, j));
      if(dictionary.Contains(word)){
        cout << "*** " << x << " -> " << word << " *** case A\n";
        corrected++;
      }
    }
  }
  return corrected > 0;
} 

// CaseB: Removes a character somewhere within the string to find a match within dictionary.
// @dictionary: dictionary used from input throughout the whole code
// @x: the string that was inputted incorrectly
bool CaseB(HashTableDouble<string>& dictionary, string x)
{
  int corrected = 0;
  string word = "";
  for(size_t i = 0; i < x.size(); i++){
    word = x;
    word.erase(i,1);
    if(dictionary.Contains(word)){
      cout << "*** " << x << " -> " << word << " *** case B\n";
      corrected++;
    }
  }
  return corrected > 0;
} 

// CaseC: Swaps the position of two adjacent characters to find a match within dictionary.
// @dictionary: dictionary used from input throughout the whole code
// @x: the string that was inputted incorrectly
bool CaseC(HashTableDouble<string>& dictionary, string x)
{
  int corrected = 0;
  string word;
  for(size_t i = 0; i < x.size()-1; i++){
    word = x;
    swap(word[i], word[i+1]);
    if(dictionary.Contains(word)){
      cout << "*** " << x << " -> " << word << " *** case C\n";
      corrected++;
    }
  }
  return corrected > 0;
} 
// Creates and fills double hashing hash table with all words from
// @dictionary_file: string for file name
HashTableDouble<string> MakeDictionary(const string &dictionary_file) {
  HashTableDouble<string> dictionary_hash;
  // Fill dictionary_hash.
  fstream dictionary_in(dictionary_file);
  string line;
  while(dictionary_in >> line)
  {
    dictionary_hash.Insert(line);
  }
  return dictionary_hash;
}


// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(HashTableDouble<string>& dictionary, const string &document_file) {
  fstream document(document_file);
  string temp;
  string line;
  while(document >> temp){
    line.clear();
    //format and add line
    for(char x : temp)
    {
      if(isalnum(x) || x == '\'' || x == '-')
      {
        line += tolower(x);
      }
    }
    if(dictionary.Contains(line)){
    cout << line << " is CORRECT\n";
    }
    else
    {
      cout << line << " is INCORRECT\n";
      CaseA(dictionary, line);
      CaseB(dictionary, line);
      CaseC(dictionary, line);
    }
    
  }
}

// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
    SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);
  
  return 0;
}
