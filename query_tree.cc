// Author: Jeffrey Li
// Date 10/11/21
// Main file for Part2(a) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

namespace
{
  // helper to retrieve sequence and acronyms from line
  // also removes the sequence/acronym from current line
  string GetSeqFromLine(string &line)
  {
    string temp = line.substr(0,line.find("/"));
    line = line.substr(line.find("/")+1);
    return temp;
  }
  // @db_filename: an input filename.
  // @a_tree: an input tree of the type TreeType. It is assumed to be
  //  empty.
  template <typename TreeType>
  void QueryTree(const string &db_filename, TreeType &a_tree) {
    // Code for running Part2(a)
    // Parse input file @db_filename and feel tree @a_tree
    // Then prompt the user for exactly three strings (do a loop) and
    // provide the results of find() as described in the assignment.

    ifstream database(db_filename);
    string line = "";
    for(int i = 0; i < 10; i++)//skips first 10 lines
    {
      getline(database,line);
    }

    string acryonym = "";
    while (getline(database, line))
    {
      if(line.empty()) 
        continue;
      acryonym = GetSeqFromLine(line);//map acronym
      while(line.length() > 1)
      {
        SequenceMap map(GetSeqFromLine(line),acryonym);
        a_tree.insert(map);
      }
    }
    database.close();

    //asks for user input
    string input = "";
    for(int i = 0; i < 3; i++)
    {
      cin >> input;
      a_tree.printSeq(input);
    }
  }

}  // namespace

int main(int argc, char **argv){
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
