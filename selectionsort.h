//
// Created by raymo on 4/13/2021.
//

#ifndef UNTITLED_SELECTIONSORT_H
#define UNTITLED_SELECTIONSORT_H
#include <vector>
#include<iostream>
template<typename Comparable>


void printVector(const std::vector<Comparable>& v){
    for(Comparable item : v){
        std::cout << item << " "; // for each item in the vector, print and add a space
    }
    std::cout << std::endl;
}

// create a function that implements selection sort
void selectionSort(std::vector<Comparable>& v){
    int numComparisons = 0; // tracks the number of times we compare
    int numSwaps = 0; // tracks the # of swaps

    // for loop
    for(int swapIndex = 0; swapIndex < v.size(); ++swapIndex){
        int minIndex = swapIndex;

        // inner loop
        for(int i  = swapIndex + 1; i < v.size(); ++i){
            ++numComparisons; //  every iteration of this is a comparison
            // find the index of the min value of the unsorted portion
            if(v[i] < v[minIndex]){
                minIndex = i;
            }
        }
        Comparable temp = v[minIndex]; // element in the vector that is the smallest
        v[minIndex] = v[swapIndex]; // leftmost unsorted
        v[swapIndex] = temp;
        ++numSwaps;
        printVector(v);
    }
    std::cout << "Comparisons: " << numComparisons << std::endl;
    std::cout << "Swaps: " << numSwaps << std::endl;

}






#endif //UNTITLED_SELECTIONSORT_H
