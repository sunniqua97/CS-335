//
//  FastQueue.hpp
//  CS 335 Project 1
//
//  Created by Sunniyatul Quaderin on 6/7/20.
//
//  Copyright © 2020 Sunniyatul Quaderin. All rights reserved.
//
// This program defines the template class FastQueue, which will store elements under a vector
// container in a queue under efficient time constraints. 

#ifndef FastQueue_hpp
#define FastQueue_hpp

#include <stdio.h>
#include <vector>


template <class T>

class FastQueue{
    
public:
    

    
    FastQueue(){
        fq_capacity_ = 0;
        fq_size_ = 0;
        fq_head_ = 0;
        fq_end_ = 0;

    };
    FastQueue(int capacity){
    
        fq_vector_.resize(capacity);
        fq_capacity_ = capacity;
        fq_size_ = 0;
        fq_head_ = 0;
        fq_end_ = 0;
        
    };
    
    /*
    
     @param an element of the vector type specified during instantiation
     @post element is stored at the end of the queue in the FastQueue object, unless there is an available spot before the end
     
     
     */
    
    void enqueue(T element){
        
        // Storing an element in a queue with no capacity
        if ( fq_capacity_ == 0 ){
            
            fq_vector_.resize(1);
            fq_vector_[fq_end_] = element;
            fq_size_++;
            fq_capacity_++;
            fq_end_++;
            
            
            
            
        }
        
        // Storing an element in a queue with full capacity
        else if (fq_size_ == fq_capacity_){
            
            // if there are empty slots in the beginning, add an element to that spot
            
            if (fq_head_ != 0){
                fq_size_ ++;
                
                fq_vector_[fq_head_] = element;
                fq_head_--;
                
                
                
            }
            
            // otherwise append to the end after resizing the queue
            else{
                
                // resize vector and add element (use swap)
                fq_vector_.resize(fq_capacity_*2);
                fq_capacity_ = fq_capacity_ * 2;
                fq_size_ ++;
                
                fq_vector_[fq_end_] = element;
                fq_end_++;
            }
            

            
            
            
        }
        
        // Storing an element in a queue with available capacity
        else{
            // add to end using head and tail
            fq_vector_[fq_end_] = element;
            fq_size_ ++;
            fq_end_ ++;
            
            
        }
    };

    

    void dequeue ();

    
    
    /*

     @pre At least one element in queue (fq_vector_)
     @return Reference to head element in queue (fq_vector_)
     @throw out_of_range if queue (fq_vector_) is empty
     
     */
    const T& front () const{
        
        if (fq_size_ ==  0){
            
            throw std::out_of_range("OUT OF RANGE");
            
        }
        else{
            
            return fq_vector_.at(fq_head_);
            
        }
        
    };
    
    
    /*

     @pre At least one element in queue (fq_vector_)
     @return Reference to end element in queue (fq_vector_)
     @throw out_of_range if queue (fq_vector_) is empty
     
     */
    const T& back()const{
        if (fq_size_ ==  0){
            
            throw std::out_of_range("OUT OF RANGE");
            
        }
        else{
            
            return fq_vector_.at(fq_end_-1);
            
        }

        
    };
    
    /*
    
     @pre At least one element in queue (fq_vector_) and index is within the queue
     @return Reference to element at index
     @throw out_of_range if element is not in queue (fq_vector_) at specified index
     
     
     */
    const T& at(int index)const {
        if (index >= fq_end_){
            throw std::out_of_range("OUT OF RANGE");
            
        }
        else{
        return fq_vector_.at(index);
        }
       
    };
    
    
    /*
     
     @return integer of number of elements in queue (fq_vector_)
     
     */
    int size(){
        
        return fq_size_;
        
    };
    
    
    /*
     
     @return size of allocated memory in queue (fq_vector_)
     
     */
    int capacity(){
        
        return fq_capacity_;
        
    };
    
    
    void shrink_to_fit(){
        
    
        
    }
    
    
    
private:
    
    // stores the elements in the queue
    std::vector<T> fq_vector_;
    
    // tracks the number of elements in the queue
    int fq_size_;
    
    //tracks the size of allocated memory in the queue
    int fq_capacity_;
    
    //tracks the position of the first element in the queue
    int fq_head_;
    
    //tracks the position directly after the last element in the queue
    int fq_end_;
    
    

};


#endif /* FastQueue_hpp */

/*
 
 In this assignment, we use the best programming practices we can. Absolutely no pointers, not even smartpointers, and no explicit dynamic memory allocation.
  
 Write a class template FastQueue. It uses vector<> as an underlying container.
  
 enqueue( element ) Adds a new element to the end of the queue. O(1) average. Possible relocation.
  
 dequeue( ) Removes an element from the head of the queue. Does nothing if the queue is already empty. O(1).
  
 front() Returns reference to the first element of the queue. Throws out_of_range if the container is empty.
  
 back() Returns reference to the last element of the queue. Throws out_of_range if the container is empty.
  
 at(index) Returns reference to the index-th element of the queue. Throws
 out_of_range if the container size is less than index.
  
 size() Returns the number of elements in the queue. Do not try to use vector::size() method! It won’t work for you!
  
 capacity() Returns the size of allocated memory in terms of elements.
  
 shrink_to_fit() Shrinks the size of allocated memory to exactly fit the elements
 currently in queue. Reallocation is possible (almost unavoidable). Since you use
 vector<>, you won’t be able to fully control the amount of allocated memory. Assume that vector<> always follows your size you specify during construction.
 Do not try to use vector<> method shrink_to_fit(). Due to the nature of your
 container, it won’t work for you. For the same reason, I suggest you to be careful with resize() and reserve() methods.
 
 
 */
