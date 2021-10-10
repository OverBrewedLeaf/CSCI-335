#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// SequenceMap class
//
// CONSTRUCTION: two parameter
//
// ******************PUBLIC OPERATIONS*********************
// 
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

class SequenceMap{
    public:
        SequenceMap() = default;//Zero parameter constructor
        ~SequenceMap() = default;//Destuctor
        SequenceMap(const SequenceMap &rhs) = default;//Copy Constructor
        SequenceMap& operator=(const SequenceMap &rhs) = default;//Copy Assignment
        SequenceMap(SequenceMap &rhs) = default;//Move Constructor
        SequenceMap& operator=(SequenceMap &&rhs) = default;//Move Assignment
        bool operator<(const SequenceMap &rhs) const{
            return 1;
        }
        SequenceMap(const string &a_rec_seq, const string &an_enz_acro){

        }

    private:
        string recognition_sequence_;
        vector<string> enzyme_acronyms_;
};

#endif