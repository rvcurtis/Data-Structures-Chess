//
// Created by raymo on 4/20/2021.
//

#ifndef UNTITLED_SORT_H
#define UNTITLED_SORT_H

#include <iostream>
#include <vector>
#include "Chess.h"
#include <fstream>
#include <random>
#include <algorithm>
#include <chrono>
#include <cmath>



// Here is a little function to print our vectors
template<typename Comparable>
void printVector(const std::vector<Comparable>& v){
    for(Comparable item : v){
        std::cout << item << " "; // for each item in the vector, print and add a space
    }
    std::cout << std::endl;
}



template<typename Comparable>
void bubbleSort(std::vector<Comparable>& v, int &bubbleReads, int &bubbleWrites){
    int numComparisons = 0;
    bool haveSwapped = true;
    int numPasses = 0;
    // outer loop
    while(haveSwapped){
        haveSwapped = false; // if we compare no swaps, then it will hold
        for(int i = 0; i < v.size() - numPasses - 1;++i){
            ++numComparisons;
            if(v[i] > v[i+1]){
                bubbleReads +=2;
                // the two items are out of order, so swap em
                Comparable temp = v[i];
                bubbleReads +=1;
                bubbleWrites +=1;
                // overwrite the current item with the new one, and iterate bubble reads and writes
                v[i] = v[i+1];
                bubbleReads +=1;
                bubbleWrites +=1;
                v[i+1] = temp; // we use this temporary value to to this swap, again iterate reads and writes
                bubbleReads +=1;
                bubbleWrites +=1;
                haveSwapped = true; // this allows us to compare so long as items need to be swapped
            }
            else{
                bubbleReads += 2; // if we compare no swaps, we simply have read twice, and move on
            }
        }
        ++numPasses; // this allows the num of comparisons to reduce by one
        //printVector(v);
    }
    std::cout << "Read Bubble:" << bubbleReads << std::endl;
    std::cout << "Write Bubble: " << bubbleWrites << std::endl;
}


// Section 2: Next I am choosing to implement selection sort, simply because I thought this one was cooler than insertion :)
// create a function that implements selection sort



template<typename Comparable>
void selectionSort(std::vector<Comparable>& v,int &selectionReads, int &selectionWrites){
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
                selectionReads +=2;
                minIndex = i;
            }
            else{
                selectionReads += 2;
            }
        }
        Comparable temp = v[minIndex]; // element in the vector that is the smallest
        selectionReads +=1;
        selectionWrites +=1;
        v[minIndex] = v[swapIndex]; // leftmost unsorted
        selectionReads +=1;
        selectionWrites +=1;
        v[swapIndex] = temp;
        selectionReads +=1;
        selectionWrites +=1;
        ++numSwaps;
        //printVector(v);
    }
    std::cout << "Read Selection:" << selectionReads << std::endl;
    std::cout << "Write Selection: " << selectionWrites << std::endl;
}


// Section 3: I chose quicksort, using recursion, hence stability

template<typename Comparable>
void quicksortStable(std::vector<Comparable>& v,int &quickReads, int &quickWrites) {
    // Recursive base case
    if (v.size() < 2) {
        return; // there is nothing to sort
    }
    Comparable pivot = v[0];
    quickReads += 1;
    quickWrites += 1;

    std::vector<Comparable> smaller, equal, larger;
    int i;  // OK to declare here. See where we copy values back to orig. vector
    for (i = 0; i < v.size(); ++i) {
        if (v[i] < pivot) {
            quickReads += 2;
            smaller.push_back(v[i]);
            quickWrites += 1;
            quickReads += 1;
        } else if (v[i] > pivot) {
            quickReads += 4;
            larger.push_back(v[i]);
            quickWrites += 1;
            quickReads += 1;
        } else {
            quickReads += 4;
            equal.push_back(v[i]);
            quickWrites += 1;
            quickReads += 1;
        }
    }

    quicksortStable(smaller,quickReads,quickWrites);
    quicksortStable(larger,quickReads,quickWrites);

    // Copy everything back into vector
    for (i = 0; i < smaller.size(); ++i) {
        v[i] = smaller[i];
        quickReads += 1;
        quickWrites += 1;
    }
    // Omit initialization of i and continue...
    for (; i < smaller.size() + equal.size(); ++i) {
        v[i] = equal[i - smaller.size()];
        quickReads += 1;
        quickWrites += 1;
    }
    // Omit initialization of i and continue...
    for (; i < v.size(); ++i) {
        v[i] = larger[i - smaller.size() - equal.size()];
        quickReads += 1;
        quickWrites += 1;
    }
}


// Part 4: Now we're on to heap sort

// again, create two ints for heapreads and writes



inline int leftChild(int i) {
    return 2 * i + 1;
}

template<typename Comparable>
void percolateDown(std::vector<Comparable>& v, int start, int end,int &heapReads, int &heapWrites) {
    int root = start;

    heapReads += 1;
    heapWrites +=1;

    while (leftChild(root) <= end) {
        int child = leftChild(root);
        if (child + 1 <= end && v[child] < v[child + 1]){
            ++child;
        }
        heapReads += 2;
        if (v[root] < v[child]) {
            heapReads += 2;
            Comparable temp = v[root];
            v[root] = v[child];
            v[child] = temp;
            root = child;
            heapReads += 1;
            heapWrites += 1;
        } else {
            return;
        }
    }
}

/**
 * heapify; used by heapSort()
 */
template<typename Comparable>
void heapify(std::vector<Comparable>& v, int size,int &heapReads, int &heapWrites) {
    int start = (size - 2) / 2;
    while (start >= 0) {
        percolateDown(v, start, size - 1,heapReads,heapWrites);
        --start;
    }
}

/**
 * Heap sort
 */
template<typename Comparable>
void heapSort(std::vector<Comparable>& v,int &heapReads, int &heapWrites) {
    int size = v.size();
    int end = size - 1;
    heapify(v, size,heapReads,heapWrites);
    while (end > 0) {
        Comparable temp = v[end];
        heapReads += 1;
        heapWrites +=1;

        v[end] = v[0];
        heapReads += 1;
        heapWrites +=1;

        v[0] = temp;
        heapReads += 1;
        heapWrites +=1;

        --end;
        percolateDown(v, 0, end,heapReads,heapWrites);
    }
    std::cout << "Read Heapsort:" << heapReads << std::endl;
    std::cout << "Write Heapsort: " << heapWrites << std::endl;
}


// Part 5, Onto two sort
// I am going to first use and then I am going to use insertion sort and then I will use a non-templated version of insertion sort for the second part

/**
 * Insertion sort. Treat the 0 index item as being sorted
 * from the start. Outer loop begins at index 1.
 */

// again create variables to read and write inerstions

template<typename Comparable>
void insertionSort(std::vector<Comparable>& v,int &insertReads, int &insertWrites) {
    for (int i = 1; i < v.size(); ++i) {
        Comparable value = v[i];
        insertReads += 1; // counts as a read and write
        insertWrites += 1;// the value we're going to insert
        int j = i - 1;
        while (j >= 0 && v[j] > value) {
            insertReads += 2; // counts as a read and write
            v[j + 1] = v[j];  // shift the larger item right
            insertReads += 1; // counts as a read and write
            insertWrites += 1;
            --j;  // move left
        }
        v[j + 1] = value; // insert
        insertReads += 1; // counts as a read and write
        insertWrites += 1;
    }

}


void bubbleSortTurns(std::vector<Chess>& v, int &bubbleReads, int &bubbleWrites){
    int numComparisons = 0;
    bool haveSwapped = true;
    int numPasses = 0;
    // outer loop
    while(haveSwapped){
        haveSwapped = false; // if we compare no swaps, then it will hold
        for(int i = 0; i < v.size() - numPasses - 1;++i){
            ++numComparisons;
            if(v[i].getTurns() > v[i+1].getTurns()){
                bubbleReads +=2;
                // the two items are out of order, so swap em
                Chess temp = v[i];
                bubbleReads +=1;
                bubbleWrites +=1;
                // overwrite the current item with the new one, and iterate bubble reads and writes
                v[i] = v[i+1];
                bubbleReads +=1;
                bubbleWrites +=1;
                v[i+1] = temp; // we use this temporary value to to this swap, again iterate reads and writes
                bubbleReads +=1;
                bubbleWrites +=1;
                haveSwapped = true; // this allows us to compare so long as items need to be swapped
            }
            else{
                bubbleReads += 2; // if we compare no swaps, we simply have read twice, and move on
            }
        }
        ++numPasses; // this allows the num of comparisons to reduce by one
        //printVector(v);
    }
}

void twoSort(std::vector<Chess>& v,int &twoSortReads, int &twoSortWrites){
    insertionSort(v,twoSortReads,twoSortWrites);
    bubbleSortTurns(v,twoSortReads,twoSortWrites);
    std::cout << "Read twosort:" << twoSortReads << std::endl;
    std::cout << "Write twosort: " << twoSortWrites << std::endl;
}




#endif //UNTITLED_SORT_H
