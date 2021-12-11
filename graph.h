//Author: Jeffrey Li
//Graph Code

#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include <limits>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//This file is for your graph implementation.
//Add everything you need in between the "ifndef and "endif" statements.
//Do not put anything outside those statements

template <typename DistType>
class Vertex
{
    private:

    vector<Vertex<DistType>> adjacent_;
    Vertex<DistType> * path_;
    DistType weight_ = 0;
    DistType distance_ = numeric_limits<DistType>::max();
    bool known_ = false;
    size_t adjacentSize_ = 0; 
    bool adjacenty_ = false;

    public: 
    Vertex(){}

    Vertex(DistType weight)
    { 
        weight_ = weight;
        adjacenty_ = true;
    }
    DistType getDistance() { return distance_; }
    void setDistance(DistType distance) { distance_ = distance; }
    DistType getWeight() { return weight_; }
    bool getKnown() { return known_; }
    void setKnown(bool known) { known_ = known; }
    size_t getAdjacentSize(){ return adjacentSize_;}
    bool getAdjacenty(){ return adjacenty_; }
    vector<Vertex<DistType>> getAdjacentVector() { return adjacent_;}
    Vertex<DistType> * getPath(){ return path_;}
    void setPath(Vertex<DistType> path){ path_ = path;}

    void insert(size_t vertex, DistType weight)
    {
        if(adjacent_.size() <= vertex)
        {
            adjacent_.resize(vertex+2);
            adjacentSize_ = vertex+2;
            cout << adjacent_.size();
        }
        adjacenty_ = true;
        adjacent_[vertex] = Vertex<DistType>(weight);
    }

    void printVertex(){//debug
        cout << "weight: " << to_string(weight_) << "\n";
        for (size_t i = 1; i <= adjacentSize_; i++){
            cout << "\tis adjacent to " << to_string(i) <<
            ", weight:" << to_string(adjacent_[i].weight_) <<
            ", distance: " << to_string(adjacent_[i].distance_) <<
            ", adjacent: " << to_string(adjacent_[i].adjacenty_) << "\n";
        }
    }

    void adjacent(size_t end)
    {
        if (adjacent_.size() < end)
            cout << "not_connected";
        else if(adjacent_[end].getWeight() != 0)
        {
            cout << "connected ";
            cout << fixed << setprecision(1) << adjacent_[end].getWeight();
        }
        else cout << "not_connected";
    }

    bool operator<(const Vertex &compare) const {
        return distance_ < compare.distance_;
    }

} ;

template <typename DistType>
class Graph
{ 
    private:
    Vertex<DistType> *vertex_;
    int size_;

    // string findPath(size_t start, size_t end)
    // {
    //     if(start == end) return "";
        
    // }

    // DistType findCost(size_t start, size_t end)
    // {
    //     if(start == end) return 0;
        
        
    // }

    public:
    Graph(size_t size)
    {
        vertex_ = new Vertex<DistType>[size+1];
        size_ = size;
    }
    ~Graph()
    {
        delete []vertex_;
        size_ = 0;
    }

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
    void connection(int start,int end){ vertex_[start].adjacent(end); }

    size_t getSize(){ return size_; }

    void Dijkstra(size_t start)
    {
        BinaryHeap<Vertex<DistType>> heap;
        heap.insert(start);
        vertex_[start].setDistance(0);
        while(!heap.isEmpty())
        {
            Vertex<DistType> min = heap.findMin();
            heap.deleteMin();
            min.setKnown(true);
            for(size_t i = 1; i < min.getAdjacentSize(); i++)
            {
                
                if(vertex_[i].getAdjacenty())
                {
                    Vertex<DistType> comparison = vertex_[i];
                    
                    if(!comparison.getKnown())
                    {
                        
                        if(min.getAdjacentVector()[i].getWeight() < comparison.getDistance())
                        {
                            // comparison.setDistance(min.getDistance() + min.getAdjacentVector()[i].getWeight());
                            // comparison.setPath(min);
                            
                        }
                    }
                }
            }
        }
    }

    // void findPath(size_t start, size_t end)
    // {
    //     int cost = findCost(start,end);

        
        
    //     if(cost == numeric_limits<DistType>::max()) cout << "not_possible";
    //     else cout << findPath(size_t start, size_t end) << "cost: " << setprecision(1) << cost;
    // }

};

#endif