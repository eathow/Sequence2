//
//  sequence2.cpp
//  DS Project 3
//
//  Created by Emma Athow on 3/05/20.
//  Copyright © 2020 Emma Athow. All rights reserved.
//

#include "sequence2.h"
#include <cassert>

namespace main_savitch_4 {
sequence :: sequence(size_type initial_capacity) {
    //Using this constructor, we allocate a dynamic array
    data = new value_type[initial_capacity];
    capacity = initial_capacity;
    used = 0;
}
sequence :: sequence(const sequence& source) {
    //Here we are copying all data from source into our dynamic array, data
    data = new value_type[source.capacity];
    capacity = source.capacity;
    used = source.used;
    for(size_type i = 0; i < used; i++) {
        data[i] = source.data[i];
    }
    if(source.is_item()) {
        current_index = source.current_index;
    }
    else {
        current_index = used;
    }
}
sequence :: ~sequence() {
    //Destructor returns data to heap
    delete [] data;
}

void sequence :: start() {
    //Postcondition: The first item in the sequence becomes the current item (but if the sequence is empty, then there is no current item).
    current_index = 0;
}

void sequence :: advance() {
    //Precondition: is_item returns true.
    //Postcondition: If the current item was already the last item in the sequence, then there is no longer any current item. Otherwise, the new item is the item immediately after the original current item.
    assert(is_item() == true);
    current_index += 1;
}

void sequence :: insert(const value_type& entry) {
    //Precondition: size( ) < CAPACITY.
    //Postcondition: A new copy of entry has been inserted in the sequence before the current item. If there was no current item, then the new entry has been inserted at the front. In either case, the new item is now the current item of the sequence.
    if(size() == capacity) {
        resize(capacity + DEFAULT_CAPACITY);
    }
    if(is_item() == false) {
        current_index = 0;
    }
    //We now want to create a for loop that will go through the sequence and, in a way, shift the values leftward.
    for(unsigned long int i = used; i > current_index; --i) {
        data[i] = data[i-1];
    }
    data[current_index] = entry;
    used += 1;
}

void sequence :: attach(const value_type& entry) {
   //Precondition: size( ) < CAPACITY.
   //Postcondition: A new copy of entry has been inserted in the sequence after the current item. If there was no current item, then the new entry has been attached to the end of the sequence. In either case, the new item is now the current item of the sequence.
    if(size() == capacity) {
        resize(capacity + DEFAULT_CAPACITY);
    }
    if(is_item() == true) {
    //This for loop is much like the for loop used in the function insert. The main difference between the two is the way in which the values of the sequence are being shifted (rightward versus leftward).
        for(unsigned long int i = used; i > current_index + 1; --i) {
            //This loop moves values one index higher than where they were previously placed
            data[i] = data[i-1];
        }
        data[current_index + 1] = entry;
        //Used increases because we have one more value in our array
        used += 1;
        current_index += 1;
    }
    else {
        //In this case, there was no current item, so the current item then becomes the new entry.
        data[used] = entry;
        current_index = used;
        used += 1;
    }
}

void sequence :: remove_current() {
    //Precondition: is_item returns true.
    //Postcondition: The current item has been removed from the sequence, and the item after this (if there is one) is now the new current item.
    assert(is_item() == true);
    if(size() == 0) {
        current_index = used;
    }
    else {
        //Again, this for loop's logic works much like that of attach and insert wherein we are simply moving around the values of the sequence.
        for(unsigned long int i = current_index + 1; i < used; ++i){
        data[i-1] = data[i];
    }
    //We must now decrease the value of used because we have one less number
    used -= 1;
    }
}

void sequence :: resize(size_type new_capacity) {
 value_type *larger_array;
    if (new_capacity < used) {
        new_capacity = used;
    }
    larger_array = new value_type[new_capacity];
    for(int i = 0; i < used; i++){
        //Here we are relocating the values in the old dynamic array, data, to our new dynamic array, larger_array
        larger_array[i] = data[i];
    }
    delete [] data; //We now delete the old pointer and return it to the heap!
    data = larger_array;
    capacity = new_capacity;
}
void sequence :: operator=(const sequence& source){
    value_type *new_data;
    if(this == &source) {
        //Here we first stop self-assignment in its tracks
        return;
    }
    if(capacity != source.capacity) {
        //Allocating a dynamic array
        new_data = new value_type[source.capacity];
        delete [] data;
        data = new_data;
        capacity = source.capacity;
    }
    used = source.used;
    for(int i = 0; i < used; i++) {
        //Copying data from source
        data[i] = source.data[i];
    }
    if(source.is_item()) {
        current_index = source.current_index;
    }
    else {
        current_index = used;
    }
}
sequence :: size_type sequence :: size() const {
 //Postcondition: The return value is the number of items in the sequence.
 return used;
}

bool sequence :: is_item() const {
//Postcondition: A true return value indicates that there is a valid “current” item that may be retrieved by the current member function (listed below). A false return value indicates that there is no valid current item.
    if(current_index >= size() || size() == 0) {
        //This is necessary because we need to make sure there is a current number to begin with
        return false;
    }
    else {
        return true;
    }
}

sequence :: value_type sequence :: current() const {
 //Precondition: is_item( ) returns true.
 //Postcondition: The item returned is the current item in the sequence.
 assert(is_item() == true);
 return data[current_index];
}
}

