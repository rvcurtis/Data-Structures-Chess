//
// Created by raymo on 4/13/2021.
//

#ifndef UNTITLED_BUBBLE_H
#define UNTITLED_BUBBLE_H
//
// Created by raymo on 4/8/2021.
//
// utility function to print our vector

#include <vector>
#include<iostream>
template<typename Comparable>


// print vector function
void printVector(const std::vector<Comparable>& v){
    for(Comparable item : v){
        std::cout << item << " "; // for each item in the vector, print and add a space
    }
    std::cout << std::endl;
}



template<typename Comparable>
void bubbleSort(std::vector<Comparable>& v){
    int numComparisons = 0;
    bool haveSwapped = true;
    int numPasses = 0;
    // outer loop
    while(haveSwapped){
        haveSwapped = false; // if we compare no swaps, then it will hold
        for(int i = 0; i < v.size() - numPasses - 1;++i){
            ++numComparisons;
            if(v[i] > v[i+1]){
                // the two items are out of order, so swap em
                Comparable temp = v[i];
                // overwrite the current item with the new one
                v[i] = v[i+1];
                v[i+1] = temp; // we use this temporary value to to this swap
                haveSwapped = true; // this allows us to compare so long as items need to be swapped
            }
        }
        ++numPasses; // this allows the num of comparisons to reduce by one
        printVector(v);
    }
    std::cout << numComparisons << std::endl;
}




#endif //UNTITLED_BUBBLE_H
