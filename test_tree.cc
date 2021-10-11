// Jeffrey Li
// Main file for Part2(b) of Homework 2.
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
// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
  template<typename TreeType>
  void TreeConstruct(const string &db_filename, TreeType &a_tree){
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
    string input = "";
    for(int i = 0; i < 3; i++)
    {
      cin >> input;
      a_tree.printSeq(input);
    }
  }



  template <typename TreeType>
  void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree)
  {
    // Code for running Part2(b)  

    // 2. Prints the number of nodes in	your tree n.	
    cout << "2: " << a_tree.total_Nodes() << endl;

    // 3a. Prints	the	average	depth
    cout << "3a: " << endl;

    // 3b. Prints the	ratio	of the	average	depth
    cout << "3b: " << endl;

    // 4a. Prints the total	number of	successful queries
    cout << "4a: " << endl;

    // 4b. Prints the	average	number of recursion calls
    cout << "4b: " << endl;

    // 5a. Prints	the	total	number successful removes.
    cout << "5a: " << endl;

    // 5b. Prints the	average	number of recursion calls
    cout << "4b: " << endl;

    // 6a. Prints number of nodes in your tree
    cout << "6a: " << endl;

    // 6b. Prints the average depth.
    cout << "6b: " << endl;

    // 6c. Prints the ratio	of the average depth to log2n
    cout << "6c: " << endl;




  }

}  // namespace

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else if (param_tree == "AVL") {
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
