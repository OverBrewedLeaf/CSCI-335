#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"

#include <iomanip>
#include <iostream>

//This file is for your graph implementation.
//Add everything you need in between the "ifndef and "endif" statements.
//Do not put anything outside those statements

template <typename DistType>
class Vertex
{
    private:
    std::vector<Vertex<DistType>> adjacent_;
    DistType distance_;//currently same as weight


    public: 
    Vertex()
    {
        distance_ = 0;
    }

    Vertex(DistType distance)
    {
        distance_ = distance;
    }

    DistType getDistance()
    {
        return distance_;
    }

    void insert(size_t vertex, DistType distance)
    {
        // std::cout << "inside insert function vertex- " << vertex << "   distance- " << distance << std::endl;
        if(adjacent_.size() <= vertex)
        {
            adjacent_.resize(vertex+2);
        }
        // std::cout << "\t adjacent size is " << adjacent_.size() << std::endl;
        adjacent_[vertex] = Vertex<DistType>(distance);
        // adjacent_.insert(vertex,Vertex<DistType>(distance));
        // std::cout << "inside insert adjacent_ is " << adjacent_.size() << std::endl;
    }
    string printVertex(){
        string result = "distance: " + to_string(distance_) + "\n";
        for (size_t i = 0; i < adjacent_.size(); i++){
            result += "\tadjacent of " + to_string(i) + " has distance of " + to_string(adjacent_[i].distance_) + "\n";
        }
        return result;
    }

    string adjacent(size_t end)
    {
        string result = ""
        // std::cout << "the adjacent_ size is " << adjacent_.size() << std::endl;
        // std::cout << printVertex() << std::endl;
        if (adjacent_.size() < end)
            result += "not_connected";
        else if(adjacent_[end].getDistance() != 0)
            result += "connected " + to_string(adjacent_[end].getDistance());
        else result += "not_connected";
        return result;
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

    void insert(int vertex, int vertexid, DistType distance)
    {
        vertex_[vertex].insert(vertexid,distance);
    }
    void printGraph(){
        std::cout << "entered print graph " << std::endl;
        std::cout << "size is " << size_ << std::endl;
        for(int i=0; i<size_; i++){
            std::cout << "i = " << i << std::endl;
            std::cout << vertex_[i].printVertex() << std::endl;
        }
    }
    void connection(int start,int end)
    {
        return vertex_[start].adjacent(end);
    }
};



#endif