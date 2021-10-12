// Author: Jeffrey Li
// Date 10/11/21
// Main file for Part2c of Homework 2.

#include "avl_tree_mod.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
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
  }
  // @a_tree: type of tree
  // @seq_filename: inputted sequences
  // returns the amount of successful queries
  template <typename TreeType>
  int success_query(const TreeType &a_tree, const string &seq_filename)
  {
    ifstream input(seq_filename);
    string sequence;
    int temp,success = 0;
    while (getline(input, sequence))
    {
      SequenceMap map(sequence, "");
      if (a_tree.contains(map, temp))
      {
        success++;
      }
    }
    input.close();
    return success;
  }

  // @a_tree: type of tree
  // @seq_filename: inputted sequences
  // returns the amount of total queries
  template <typename TreeType>
  float total_query(const TreeType &a_tree, const string &seq_filename)
  {
    ifstream input(seq_filename);
    string sequence;
    int count = 0;
    while (getline(input, sequence))
    {
      SequenceMap map(sequence, "");
      a_tree.contains(map, count);
    }
    input.close();
    return count;
  }

  // @a_tree: type of tree
  // @seq_filename: inputted sequences
  // returns the amount of every other removed sequence.
  template <typename TreeType>
  int success_remove(TreeType &a_tree, const string &seq_filename)
  {
    ifstream input(seq_filename);
    string sequence;
    int count = 0;
    int min = 0;
    int temp = 0;
    bool toggle = true;
    while (getline(input, sequence))
    {
      if (toggle){
        SequenceMap map(sequence, "");
        if (a_tree.contains(map, temp))
        {
          a_tree.remove(map, count, min);
        }
      }
      toggle = !toggle;
    }
    input.close();
    return count + min;
  }

  // @db_filename: inputted file name for database
  // @seq_file: inputted sequences
  // @a_tree: type of tree, either avl or BST
  // TestTree tests all tasks
  template <typename TreeType>
  void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree)
  {
    // Code for running Part2(b)  
    TreeConstruct(db_filename, a_tree);
    // 2. Prints the number of nodes in	your tree n.	
    cout << "2: " << a_tree.total_Nodes() << endl;

    // 3a. Prints	the	average	depth
    cout << "3a: " << a_tree.avg_Depth() << endl;

    // 3b. Prints the	ratio	of the	average	depth
    cout << "3b: " << a_tree.avg_Depth() / log2(a_tree.total_Nodes()) << endl;

    // 4a. Prints the total	number of	successful queries
    cout << "4a: " << success_query(a_tree, seq_filename) << endl;

    // 4b. Prints the	average	number of recursion calls
    cout << "4b: " << total_query(a_tree, seq_filename) / success_query(a_tree, seq_filename) << endl;
    
    int num_Nodes = a_tree.total_Nodes();
    float total_remove = success_remove(a_tree, seq_filename);
    // 5a. Prints	the	total	number successful removes.
    cout << "5a: " << num_Nodes - a_tree.total_Nodes() << endl;

    // 5b. Prints the	average	number of recursion calls
    cout << "5b: " << total_remove / (num_Nodes - a_tree.total_Nodes()) << endl;

    // 6a. Prints number of nodes in your tree
    cout << "6a: " << a_tree.total_Nodes() << endl;

    // 6b. Prints the average depth.
    cout << "6b: " << a_tree.avg_Depth() << endl;

    // 6c. Prints the ratio	of the average depth to log2n
    cout << "6c: " << a_tree.avg_Depth() / log2(a_tree.total_Nodes()) << endl;
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
    cout << "Unknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
