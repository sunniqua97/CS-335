//
//  my_memory.hpp
//  CS 335 Project 2
//
//  Created by Sunniyatul Quaderin on 6/8/20.
//  Copyright © 2020 Sunniyatul Quaderin. All rights reserved.
//

#ifndef my_memory_h
#define my_memory_h

#include <stdio.h>
#include <iostream>

template <class T>
class my_unique_ptr{
    
public:
    
    my_unique_ptr(){
        
        my_unique_data = nullptr;
        
    }; // default constructor
    
    
    
    // Constructor that takes a pointer Type * as a parameter and sets the object to point there. We say that the newly created object takes ownership of the pointed memory.
    my_unique_ptr(T* user_input){
        my_unique_data = user_input;
        user_input = nullptr;
        delete user_input;
    }; // parameterized constructor
    
    
    my_unique_ptr( my_unique_ptr && user_input){
        my_unique_data = user_input.my_unique_data;
        user_input.my_unique_data = nullptr;
        delete user_input.my_unique_data;
        
       
        
        
    }; // move constructor
    
    
    my_unique_ptr( const my_unique_ptr & user_input) = delete; // copy constructor to be deleted
    
    
    // DOUBLE CHECK THIS
    ~my_unique_ptr(){
        
        if (my_unique_data){
            my_unique_data = nullptr;
            delete my_unique_data;
        }
        
        
        
    }; // destructor
    
    
    T& operator* (){
        
        return *my_unique_data;
        
    };

    
    
    T* operator-> (){
        return my_unique_data;
    };
    
    
    
     my_unique_ptr& operator= (my_unique_ptr && user_input){
        
           if (this!= &user_input){
            
            
            my_unique_data = user_input.my_unique_data;
           

           
        
        }
        
        return *this;
        
        
        
    };
    
    
    my_unique_ptr & operator= (const my_unique_ptr & user_input) = delete; // copy assignment to be deleted
    
    
    bool isNullptr(){
        
        return (!(my_unique_data));
        
    }; // returns true if the pointer is to a nullptr and false otherwise
    
    
private:
    
    T* my_unique_data;
    
};


using namespace std;
template <class T>
class my_shared_ptr{

    
public:
    
    my_shared_ptr(){
        my_shared_data = nullptr;
        my_shared_counter   = nullptr;
    };
    
    my_shared_ptr(T* user_input){
        
        my_shared_data = user_input;
        my_shared_counter   = new int(1);
                
        
       
    };
 
    // Copy constructor. Since the original object already points to the block of memory and now the newly created object points there too, you must increase the counter by 1.
    my_shared_ptr( const my_shared_ptr & user_input){
        
        
        my_shared_data = user_input.my_shared_data;
        my_shared_counter = user_input.my_shared_counter;
        
        if (my_shared_counter){ // point has a value
            (*my_shared_counter)++;
        }
        else{ // point is null
            my_shared_counter   = new int(1);
            
        }
   
        
        
        
        
    }; // copy constructor
    
    
    
    my_shared_ptr( my_shared_ptr && user_input){
        
        my_shared_data = user_input.my_shared_data;
        my_shared_counter = user_input.my_shared_counter;
        if(my_shared_counter){

        }
        
        
        
    }; // move constructor
    
    
    ~my_shared_ptr(){
        
        if (my_shared_counter){ // my shared counter has a value and not null
            (*my_shared_counter)--;
            if (*my_shared_counter == 0){ // no more instances of the variable
                my_shared_data = nullptr;
                my_shared_counter = nullptr;
                
                delete my_shared_data;
                delete my_shared_counter;
            }
        }
        
        
        
    };
    

    T& operator* (){
        
        return *my_shared_data;
        
    };

    
    
    T* operator-> (){
        return my_shared_data;
    };
    
    
    my_shared_ptr & operator= (my_shared_ptr && user_input){
       if(my_shared_counter){
           if (*(my_shared_counter) > 0){
               (*my_shared_counter)--;
           }
           
           // destructor call
           if (*(my_shared_counter) == 0){
               //delete my_shared_data;
               //delete my_shared_counter;
               this->~my_shared_ptr();
               
           }
           
           
            
        }
        
        if (this!= &user_input){
            
       
            my_shared_data = user_input.my_shared_data;
            my_shared_counter = user_input.my_shared_counter;
            
            
            user_input.my_shared_data = nullptr;
            user_input.my_shared_counter = nullptr;
            
        }
        
        return *this;
        
        
    }; // move assignment
    
    
    
    my_shared_ptr & operator= (const my_shared_ptr & user_input){
        if(my_shared_counter){
            if (*(my_shared_counter) > 0){
                (*my_shared_counter)--;
            }

            
             
         }
         
         if (this!= &user_input){
             
        
             my_shared_data = user_input.my_shared_data;
             my_shared_counter = user_input.my_shared_counter;
             
        
             if (my_shared_counter){
                 
                 (*my_shared_counter)++;
                 
             }
            
             
         }
         
         return *this;
        
        
    }; // copy assignment
    
    bool isNullptr(){
        
        return (my_shared_data == nullptr);
        
        
    }; // returns true if the pointer is to a nullptr and false otherwise
    
    
    
private:
    T* my_shared_data;
    int* my_shared_counter;
    
    
    
};

#endif /* my_memory_h */
