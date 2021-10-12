// Author: Jeffrey Li
// Date 10/11/21
// Sequence Map Class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// SequenceMap(string,string)           --> constructs sequence map with 2 parameters, one as
//                                          a recog sequenceand the other as a enzyme acronym
// bool operator<(SequenceMap)          --> overloads comparision operator
// friend ostream &operator<<(ostream,SequenceMap)  --> overloads the print operator to only print the acrnym
// void merge(SequenceMap)              --> merges for duplicate names
// string getRecog()                    --> getter method for recog sequence
// void getAcro()                       --> prints all acronyms
// ********************************************************


#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SequenceMap{
    public:
        SequenceMap() = default;//Zero parameter constructor
        ~SequenceMap() = default;//Destuctor
        SequenceMap(const SequenceMap &rhs) = default;//Copy Constructor
        SequenceMap& operator=(const SequenceMap &rhs) = default;//Copy Assignment
        SequenceMap(SequenceMap &rhs) = default;//Move Constructor
        SequenceMap& operator=(SequenceMap &&rhs) = default;//Move Assignment

        SequenceMap(const string &a_rec_seq, const string &an_enz_acro)//Constructor: two string parameter
        {
            recognition_sequence_ = a_rec_seq;
            enzyme_acronyms_.push_back(an_enz_acro);
        }

        bool operator<(const SequenceMap &rhs) const { return recognition_sequence_ < rhs.recognition_sequence_; }

        friend ostream &operator<<(ostream &out,const SequenceMap &map){
            for(string i: map.enzyme_acronyms_){
                out << i + " ";
            }
            return out << "\n";
        }
        
        void Merge(const SequenceMap &rhs)
        {
            for(auto x: rhs.enzyme_acronyms_)
            {
                enzyme_acronyms_.push_back(x);
            }
            return;
        }

        string getRecog() {return recognition_sequence_;}
        
        void getAcro(){
            for(string x: enzyme_acronyms_){
                cout << x + " ";
            }
            cout << endl;
        }

    private:
        string recognition_sequence_;
        vector<string> enzyme_acronyms_;
};

#endif