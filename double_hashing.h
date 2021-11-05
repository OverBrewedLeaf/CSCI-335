/*  
*   Jeffrey Li
*
*   Double Hashing Implementation for a Hash Table
*/
#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include "quadratic_probing.h"// for namespace
#include <vector>
#include <algorithm>
#include <functional>

template <typename HashedObj>
class HashTableDouble{
    public:
    enum EntryType {ACTIVE, EMPTY, DELETED};

    explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size)), r_value(65)
    {
        MakeEmpty();
    }

    // to check if x is within the hash table.
    bool Contains(HashedObj &x) {
        return IsActive(FindPos(x));
    }
    
    void MakeEmpty() {
        current_size_ = 0;
        total_elements_ = 0;
        total_collisions_ = 0;
        for(auto &entry : array_)
            entry.info_ = EMPTY;
    }

    bool Insert(const HashedObj &x){
        total_elements_++;
        size_t current_pos = FindPos(x);
        if (IsActive(current_pos)){
            return false;
        }
        array_[current_pos].element_ = x;
        array_[current_pos].info_ = ACTIVE;

        if(++current_size_ > array_.size()/2){
            Rehash();
        }
        return true;
    }

    bool Insert(HashedObj &&x){
        size_t current_pos = FindPos(x);
        if(IsActive(current_pos))
            return false;
        
        array_[current_pos] = std::move(x);
        array_[current_pos].info_ = ACTIVE;

        if(++current_size_ > array_.size()/2)
            Rehash();
        return true;
    }

    bool Remove(const HashedObj &x){
        size_t current_pos = FindPos(x);
        if(!IsActive(current_pos))
            return false;
        array_[current_pos].info_ = DELETED;
        return true;
    }
    //Getter methods for variables
    size_t GetTotalElements(){
        return total_elements_;
    }

    size_t GetTotalCollisions(){
        return total_collisions_;
    }

    size_t GetCurrentSize(){
        return current_size_;
    }

    size_t GetTableSize(){
        return array_.size();
    }

    size_t GetTempSize(){
        return temp_collisions_;
    }

    private:
    struct HashEntry{
        HashedObj element_;
        EntryType info_;

        HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY) : element_{e}, info_{i} {}

        HashEntry(HashedObj &&e, EntryType i = EMPTY) : element_{std::move(e)}, info_{i} {}
    };

    std::vector<HashEntry> array_;
    const int r_value;
    size_t current_size_;
    size_t total_elements_;
    mutable size_t total_collisions_;
    size_t temp_collisions_;

    bool IsActive(size_t current_pos) const{
        return array_[current_pos].info_ == ACTIVE;
    }

    size_t FindPos(const HashedObj &x) {
        std::hash<HashedObj> hashed;
        size_t current_pos = InternalHash(x);
        temp_collisions_ = 1;
        while(array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x)
        {
            temp_collisions_++;
            total_collisions_++;
            current_pos += (r_value - hashed(x)%r_value);
            current_pos %= array_.size();
        }
        return current_pos;
    }

    void Rehash(){
        std::vector<HashEntry> old_array = array_;
        array_.resize(NextPrime(2 * old_array.size()));
        for(auto &entry : array_){
            entry.info_ = EMPTY;
        }

        current_size_ = 0;
        for(auto &entry: old_array){
            if(entry.info_ == ACTIVE){
                Insert(std::move(entry.element_));
            }
        }
    }

    size_t InternalHash(const HashedObj &x) const {
        static std::hash<HashedObj> hf;
        return hf(x)%array_.size();
    }

};
#endif