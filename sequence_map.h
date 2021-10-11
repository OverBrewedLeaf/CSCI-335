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
                out << "[" + i + "], ";
            }
            out << "\n";
        }
        
        void Merge(const SequenceMap &rhs)
        {
            for(auto x: rhs.enzyme_acronyms_)
            {
                enzyme_acronyms_.push_back(x);
            }
        }

    private:
        string recognition_sequence_;
        vector<string> enzyme_acronyms_;
};

#endif