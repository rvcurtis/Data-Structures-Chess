/**
 * Raymond Curtis
 * 4/27/2021
 * Project 5
 * Implementing Quadratic Probing

 */

#ifndef LINEARPROBING_H
#define LINEARPROBING_H

/**
 * We want `<optional>` so we can use in our hash table,
 * i.e. some elements have values, others do not, hence
 * `nullopt`. We've been using C++ 14 standard so far for
 * this class, and optional was introduced in C++ 17.
 * So here we try to include <experimental/optional> if
 * standard is < 17, if that fails we go with C++ version
 * <optional>
 *
 * If this produces errors, go into CMakeLists.txt and change
 * the CMAKE_CXX_STANDARD from 14 to 17.
 *
 * Here also is a valid use case for `using` in a header
 * file. We want `optional`, `nullopt`, and `make_optional`,
 * but these reside in different scopes in C++ 14 vs C++ 17.
 * Hence we apply `using` here, so that the code in our
 * header is portable between 14 and 17. Notice that we don't
 * use the entire namespace, just what we actually use.
 */


#include <experimental/optional>
using std::experimental::optional;
using std::experimental::nullopt;
using std::experimental::make_optional;
#endif

#include <functional>  // so we can pass functions as parameters and store them
#include <iostream>
#include <string>
#include <vector>


template<typename Hashable>
class QuadraticProbing {
private:
    enum state {empty, filled, removed};
    struct hashItem {
        Hashable item;
        state status;
    };
    std::vector<hashItem> table; // This allows table[i].item and table[i].status
    unsigned long tableSize;
    unsigned long numItems;

    // The function to get the key from the object
    std::function<std::string(Hashable)> getKey;
    // Store the hash function to be used
    std::function<unsigned long(std::string, unsigned long)> hashFunc;

    // Find the next prime number
    int nextPrime(int n) {
        if (n % 2 == 0) {
            ++n;
        }
        bool prime = false;
        while (!prime) {
            prime = true;
            for (int i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    prime = false;
                }
            }
            n += 2;
        }
        return (n - 2);
    }

    // Helper method to rehash
    void rehash(int &numReads) {
        // Save a copy of the hash table
        std::vector<hashItem> oldTable = table;
        // Double the size of the table and go to the next prime
        tableSize = nextPrime(tableSize * 2);
        table.clear();
        table.resize(tableSize);
        // Reinsert all of the items
        numItems = 0;
        for (unsigned long i = 0; i < oldTable.size(); ++i) {
            if (oldTable[i].status == filled) {
                insert(oldTable[i].item,numReads);
            }
        }
    }

public:
    // Constructor
    QuadraticProbing(unsigned long tableSize,
                     std::function<std::string(Hashable)> getKey,
                     std::function<unsigned long(std::string, unsigned long)> hashFunc) {
        this->tableSize = nextPrime(tableSize);
        this->getKey = getKey;
        this->hashFunc = hashFunc;
        numItems = 0;
        // Make sure the vector has room for tableSize number of elements
        // This should default all the statuses to empty
        table.resize(this->tableSize);
    }

    // insert
    // we're also going to pass in a numReads variable by reference to count the number of times an item is read in hash

    void insert(Hashable item, int &numReads) {
        // Get the key from the item
        std::string key = getKey(item);
        if (!find(key,numReads)) {   // if this key is not already in the table...
            // Hash the key to get an index
            unsigned long index = hashFunc(key, tableSize);
            // Linear probe until we find a spot to insert
            int i = 1;
            while (table[index].status == filled) {
                index = (index + i*i) % tableSize;
                i++;
                numReads++;
            }
            // Save a copy of the state
            state temp = table[index].status;
            // Insert the item
            table[index].item = item;
            table[index].status = filled;
            if (temp == empty) {
                // Update numItems
                ++numItems;
                // Check if we need to rehash
                if (numItems > (tableSize / 2)) {
                    // Less than half of the table is empty. Rehash.
                    rehash(numReads);
                }
            }
        }
    }

    // TODO: make sure we do not infinitely probe
    // find
    // Return type is optional<Hashable> because if we find the item,
    // we return it; otherwise we return nullopt.
    optional<Hashable> find(std::string key, int &numReads) {
        unsigned long index = hashFunc(key, tableSize);
        // Probe
        int i = 1;
        while (table[index].status != empty) {
            numReads++;
            // Check if there's an item and if that item is the one we're looking for
            if (table[index].status == filled && key == getKey(table[index].item)) {
                // We found the object
                return table[index].item;
            }
            index = (index + (i*i)) % tableSize;
        }
        // We did not find the object
        return nullopt;
    }

    // delete
    optional<Hashable> remove(std::string key, int &numReads) {
        unsigned long index = hashFunc(key, tableSize);
        // Probe
        int i = 1;
        while (table[index].status != empty) {
            // increment number of reads
            numReads++;
            // Check if there's an item and if that item is the one we're looking for
            if (table[index].status == filled && key == getKey(table[index].item)) {
                // We found the object. Remove it.
                table[index].status = removed;
                return table[index].item;
            }
            index = (index + i*i) % tableSize;
            i++;
        }
        // We did not find the object
        return nullopt;
    }

    // Getter for table size
    int getTableSize() {
        return tableSize;
    }

    // printTable
    void printTable() const {
        for (unsigned long i = 0; i < table.size(); ++i) {
            std::cout << i << ": ";
            // If there is a value at this index in the table
            if (table[i].status == filled) {
                std::cout << table[i].item;
            } else if (table[i].status == removed) {
                std::cout << "X";
            }
            std::cout << std::endl;
        }
    }
};

// LINEARPROBING_H
