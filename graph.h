//Author: Jeffrey Li
//Graph Code

#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include <limits>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

//This file is for your graph implementation.
//Add everything you need in between the "ifndef and "endif" statements.
//Do not put anything outside those statements

template <typename DistType>
class Vertex
{
    private:
    vector<Vertex<DistType>> adjacent_;
    DistType weight_ = 0;

    public: 
    Vertex()
    {
        // weight_ = numeric_limits<DistType>::max();
    }

    Vertex(DistType weight)
    {
        weight_ = weight;
    }

    DistType getweight()
    {
        return weight_;
    }

    void insert(size_t vertex, DistType weight)
    {
        if(adjacent_.size() <= vertex)
        {
            adjacent_.resize(vertex+2);
        }
        adjacent_[vertex] = Vertex<DistType>(weight);
    }
    string printVertex(){//debug
        string result = "weight: " + to_string(weight_) + "\n";
        for (size_t i = 0; i < adjacent_.size(); i++){
            result += "\tadjacent of " + to_string(i) + " has weight of " + to_string(adjacent_[i].weight_) + "\n";
        }
        return result;
    }

    void adjacent(size_t end)
    {
        if (adjacent_.size() < end)
            cout << "not_connected";
        // else if(adjacent_[end].getweight() != numeric_limits<DistType>::max())
        else if(adjacent_[end].getweight() != 0)
        {
            cout << "connected ";
            cout << fixed << setprecision(1) << adjacent_[end].getweight();
        }
        else cout << "not_connected";
    }

} ;

template <typename DistType>
class Graph
{ 
    private:
    Vertex<DistType> *vertex_;
    int size_;

    public:
    Graph(size_t size)
    {
        vertex_ = new Vertex<DistType>[size+1];
        size_ = size;
    }
    ~Graph(){};

    void insert(int vertex, int vertexid, DistType weight)
    {
        vertex_[vertex].insert(vertexid,weight);
    }
    void printGraph(){
        cout << "entered print graph " << endl;
        cout << "size is " << size_ << endl;
        for(int i=0; i<size_; i++){
            cout << "i = " << i << endl;
            cout << vertex_[i].printVertex() << endl;
        }
    }
    void connection(int start,int end)
    {
        vertex_[start].adjacent(end);
    }
};



#endif