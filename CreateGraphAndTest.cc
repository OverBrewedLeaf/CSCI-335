//Author: Jeffrey Li
//Driver Code
#include <string>
#include <fstream>

#include "graph.h"

using namespace std;

int graphTestDriver(int argc, char **argv) {
    
    //Begin your code here. Feel free to add any helper functions or classes you need,
    //as long as we only have to call this function to run the specified assignment.

    ifstream input_file(argv[1]);
    ifstream query_file(argv[2]);
    string line;

    getline(input_file,line);

    Graph<float> graph(stoi(line));


    while(getline(input_file,line))
    {
      stringstream stream(line);
      int vertex = 0;
      int vertexid = 0;
      float weight = 0;

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

    while(getline(query_file,line))
    {
      int start, end;
      stringstream stream(line);
      stream >> start;
      stream >> end;
      cout << line << ": ";
      graph.connection(start,end);
      cout << endl;
    }
    
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
      cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
      return 0;
    }

    graphTestDriver(argc, argv);

    return 0;
}
