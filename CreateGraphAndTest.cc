#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


#include "graph.h"

using namespace std;

template <typename DistType>
int graphTestDriver(int argc, char **argv) {
    
    //Begin your code here. Feel free to add any helper functions or classes you need,
    //as long as we only have to call this function to run the specified assignment.

    ifstream input_file(argv[1]);
    ifstream query_file(argv[2]);
    string line;

    getline(input_file,line);

    Graph<DistType> graph(stoi(line));


    while(getline(input_file,line))
    {
      stringstream stream(line);
      int vertex = 0;
      int vertexid = 1;
      DistType weight = 2;

      stream >> vertex;
      
      while(stream)
      {
        stream >> vertexid;
        stream >> weight;
        if(stream){
          graph.insert(vertex,vertexid,weight);
        }
      }
    }
    // std::cout << "after inserting Graph is" << std::endl;
    // graph.printGraph();

    while(getline(query_file,line))
    {
      int start, end;
      stringstream stream(line);
      stream >> start;
      stream >> end;
      std::cout << line << ": ";
      graph.connection(start,end);
      std::cout << std::endl;
    }
    // std::cout << "later Graph is " << std::endl;
    // graph.printGraph();


    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
		return 0;
    }

    graphTestDriver<float>(argc, argv);

    return 0;
}
