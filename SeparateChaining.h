/**
 * Raymond Curtis
 * 4/27/2021
 * Project 5
 */

#ifndef SEPARATECHAINING_H
#define SEPARATECHAINING_H

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

#include <functional>  // so we can pass functions as parameters and store them
#include <iostream>
#include <string>
#include <vector>

template <typename Hashable>
class SeparateChaining {
private:
    std::vector<std::vector<Hashable>> table;
    unsigned long tableSize;

    // Store the function that gets they string key from the Hashable
    std::function<std::string(Hashable)> getKey;
    // Store the hash function to be used
    std::function<unsigned long(std::string, unsigned long)> hashFunc;

public:
    // Constructor
    SeparateChaining(unsigned long tableSize,
                     std::function<std::string(Hashable)> getKey,
                     std::function<unsigned long(std::string, unsigned long)> hashFunc) {
        this->tableSize = tableSize;
        this->getKey = getKey;
        this->hashFunc = hashFunc;
        // Make the vector the size of tableSize
        // This will default each index to store an empty vector
        table.resize(tableSize);
    }

    // insert
    void insert(Hashable item, int &numReads) {
        std::string key = getKey(item);
        // Hash the key to get an index
        unsigned long index = hashFunc(key, tableSize);
        if (!find(key,numReads)) {
            numReads++;
            // Put the item at that spot in the vector
            table[index].push_back(item);
        }
    }

    // find
    // Return type is optional Hashable because if we find the item,
    // we return it; otherwise, we return nullopt.
    optional<Hashable> find(std::string key, int &numReads) {
        unsigned long index = hashFunc(key, tableSize);
        // Loop through the items at the index
        for (int i = 0; i < table[index].size(); ++i) {
            numReads++;
            // Check if it's the item we're looking for
            if (key == getKey(table[index][i])) {
                // We found the item
                return table[index][i];
            }
        }
        // We did not find the item
        return nullopt;
    }

    // delete
    optional<Hashable> remove(std::string key,int &numReads) {
        unsigned long index = hashFunc(key, tableSize);
        // Loop through the items at the index
        for (int i = 0; i < table[index].size(); ++i) {
            numReads++;
            // Check if it's the item we're looking for
            if (key == getKey(table[index][i])) {
                // We found the item. Delete it.
                Hashable returnItem = table[index][i];
                // Use the vector's erase method to remove the item.
                table[index].erase(table[index].begin() + i);
                return returnItem;
            }
        }
        // We did not find the item
        return nullopt;
    }

    // Getter for table size
    int getTableSize() {
        return tableSize;
    }

    // print the table
    void printTable() const {
        for (int i = 0; i < tableSize; ++i) {
            std::cout << i << ": ";
            // Loop through the items at the index
            for (int j = 0; j < table[i].size(); ++j) {
                // Access the value with * and print it out
                std::cout << table[i][j] << ", ";
            }
            std::cout << std::endl;
        }
    }
};

#endif // SEPARATECHAINING_H