#include <string>
#include <fstream>

#include "graph.h"

using namespace std;

int pathfindDriver(int argc, char **argv) {
    
    //Begin your code here. Feel free to add any helper functions or classes you need,
    //as long as we only have to call this function to run the specified assignment.

    ifstream input_file(argv[1]);
    ifstream path_file(argv[2]);
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




    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    pathfindDriver(argc, argv);

    return 0;
}
