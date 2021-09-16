// --> Jeffrey Li
// Few comments describing the class Points2
// Template Class with Big-O functionality and 

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {

// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points2D {
 public:
  // Default "big five" -- you have to alter them for your assignment.
  // That means that you will remove the "= default" statement.
  //  and you will provide an implementation.

  // Zero-parameter constructor. 
  // Set size to 0.
  Points2D(){
    size_ = 0;
    sequence_ = nullptr;
  }

  // Copy-constructor.
  Points2D(const Points2D &rhs){
    size_ = rhs.size_;
    if(rhs.size() == 0){
      sequence_ = nullptr;
    }
    sequence_ = new std::array<Object, 2>[rhs.size_];
    for (size_t i = 0; i < rhs.size_; i++){
      sequence_[i] = rhs.sequence_[i];
    }
  }

  // Copy-assignment. If you have already written
  // the copy-constructor and the move-constructor
  // you can just use:
  Points2D& operator=(const Points2D &rhs)
  {
  Points2D copy = rhs; 
  std::swap(*this, copy);
  return *this;
  }

  // Move-constructor. 
  Points2D(Points2D &&rhs){
    sequence_ = std::move(rhs.sequence_);
    size_ = std::move(rhs.size_);
    rhs.size_ = 0;
    rhs.sequence_ = nullptr;
  }

  // Move-assignment.
  // Just use std::swap() for all variables.
  Points2D& operator=(Points2D &&rhs){
    std::swap(sequence_, rhs.sequence_);
    std::swap(size_, rhs.size_);
    return *this;
  }

  ~Points2D(){
    delete[] sequence_;
  }
  // End of big-five.

  // One parameter constructor.
  Points2D(const std::array<Object, 2>& item) {
    sequence_ = new std::array<Object, 2>[1];
    sequence_[0] = item;
    size_= 1;
  }

  // Read a chain from standard input.
  void ReadPoints2D() {
    std::cout << std::endl;// needed for formatting
    // Part of code included (without error checking).
    std::string input_line;
    std::getline(std::cin, input_line); 
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    // Read size of sequence (an integer).
    int size_of_sequence;
    input_stream >> size_of_sequence;
    // Allocate space for sequence.
    // Add code here.
    size_ = size_of_sequence;
    sequence_ = new std::array<Object, 2>[size_of_sequence];
    
    Object token;
    for (int i = 0 ;input_stream >> token; i++) {
      // Read coordinates.
      // Fill sequence_ here.
      sequence_[i][0] = token;
      input_stream >> token;
      sequence_[i][1] = token;
    }
    
  }

  size_t size() const {
    return size_;
  }

  // @location: an index to a location in the sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const { 
    // Code missing.
    if(location >= size_ || location < 0){//out of range check
      abort();
    }
    return sequence_[location];
  }

 //  @c1: A sequence.
 //  @c2: A second sequence.
 //  @return their sum. If the sequences are not of the same size, append the
 //    result with the remaining part of the larger sequence.
 friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
   // Code missing.
   Points2D ans;
   size_t smaller;
   size_t larger;
   // Determines which object is larger & smaller
   if(c1.size() < c2.size()){
     ans.sequence_ = new std::array<Object, 2>[c2.size_];
     smaller = c1.size();
     larger = c2.size();
   }
   else if(c1.size() > c2.size()){
     ans.sequence_ = new std::array<Object, 2>[c1.size_];
     larger = c1.size();
     smaller = c2.size();
   }
   ans.size_ = larger;
   //Adds the sums
   for(unsigned i = 0; i < smaller; i++){
     ans.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
     ans.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
   }
   //Leftover append
   if(c1.size() > c2.size()){
    for(unsigned i = smaller; i < larger; i++){
      ans.sequence_[i][0] = c1.sequence_[i][0];
      ans.sequence_[i][1] = c1.sequence_[i][1];
    } 
   }
   else if(c1.size() < c2.size()){
     for(unsigned i = smaller; i < larger; i++){
       ans.sequence_[i][0] = c2.sequence_[i][0];
       ans.sequence_[i][1] = c2.sequence_[i][1];
     }
   }
  return ans;
 }

 // Overloading the << operator.
 friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points2) {
   if(!some_points2.size_){
     out << "(" << ")";
   }
   else if(some_points2.size_ >= 1){
     for(size_t i = 0; i < some_points2.size_; i++){
       out << "(" << some_points2.sequence_[i][0] << ", " << some_points2.sequence_[i][1] << ") ";
     }
   }
  return out << std::endl;
 }
 
 private:
  // Sequence of points. 
  std::array<Object, 2> *sequence_;
  // Size of this sequence.
  size_t size_;

};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2D_H_
