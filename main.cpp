/**
 * Raymond Curtis
 * CS 124
 * Section Z
 *
 * All code produced is mine, and utilized the framework provided by the instructor and assistance was provided by teaching assistants in office hours
 *
 * Whitespace after :: operator fixed from project 1
 */

#include <iostream>
#include <vector>
#include "Chess.h"
#include <fstream>
#include <random>
#include <algorithm>
#include <chrono>
#include <cmath>
#include "Node.h"
#include "Stack.h"
#include "Queue.h"
#include "sort.h"
#include "QuadraticProbing.h"
#include "SeparateChaining.h"
#include <optional>

using namespace std;

// create a horner hash function
unsigned long hornerHash(string key, unsigned long tableSize){
    unsigned long hashValue = 0;
    for(char &letter:key){
        hashValue = hashValue * 37 + letter;
    }
    return hashValue % tableSize;
}


unsigned long alternativeHash(string key, unsigned long tableSize){
    unsigned long hashValue = 0;
    for(char &letter:key){
        hashValue = hashValue * 83 + letter; // altered the value we multiply by to see the differences
    }
    return hashValue % tableSize;
}

// create a function to get a key from my data set
string getKeyFromChess(Chess game){
    return game.getGame_id();
}

// get a different key
string getKey2FromChess(Chess game){
    return game.getBlack_id();
}

// Experiment 1: Create Varying table sizes for my objects using separate chaining and quadratic probing
int main(){

    // create a vector filled with my chess objects
    std::vector<Chess> game;
    loadFromFile("../games.csv",game);

    // Create separate int values for the varying table sizes for quad probing and sep chaining
    int quadReads1, quadReads2, quadReads3, quadReads4, quadReads5, quadReads6, quadReads7,quadReads8 = 0;

    // Same for sep chaining
    int sepReads1, sepReads2, sepReads3, sepReads4, sepReads5, sepReads6, sepReads7, sepReads8 = 0;

    // Create varying table sizes using quadratic probing methodology
    QuadraticProbing<Chess>game1(20063,getKeyFromChess,hornerHash);

    QuadraticProbing<Chess>game2(20071,getKeyFromChess,hornerHash);

    QuadraticProbing<Chess>game3(21001,getKeyFromChess,hornerHash);

    QuadraticProbing<Chess>game4(43609,getKeyFromChess,hornerHash);

    QuadraticProbing<Chess>game5(25013,getKeyFromChess,hornerHash);

    ofstream fout;
    fout.open("../QuadraticProbing1.csv");
    if(fout){
        for(Chess &game: game){
            game1.insert(game,quadReads1);
        }
        fout << "Quad Reads 1:" << quadReads1 << endl;

        for(Chess &game: game){
            game2.insert(game,quadReads2);
        }
        fout << "Quad Reads 2:" << quadReads2 << endl;

        for(Chess &game: game){
            game3.insert(game,quadReads3);
        }
        fout << "Quad Reads 3:" << quadReads3 << endl;

        for(Chess &game: game){
            game4.insert(game,quadReads4);
        }
        fout << "Quad Reads 4:" << quadReads4 << endl;

        for(Chess &game: game){
            game5.insert(game,quadReads5);
        }
        fout << "Quad Reads 5:" << quadReads5 << endl;
    }
    fout.close();


    // Create varying table sizes using quadratic probing methodology
    SeparateChaining<Chess>game6(20063,getKeyFromChess,hornerHash);

    SeparateChaining<Chess>game7(20071,getKeyFromChess,hornerHash);

    SeparateChaining<Chess>game8(21001,getKeyFromChess,hornerHash);

    SeparateChaining<Chess>game9(43609,getKeyFromChess,hornerHash);

    SeparateChaining<Chess>game10(25013,getKeyFromChess,hornerHash);

    ofstream fout2;
    fout2.open("../SeparateChaining1.csv");
    if(fout2){
        for(Chess &game: game){
            game6.insert(game,sepReads1);
        }
        fout2 << "Separate Chaining Reads 1:" << sepReads1 << endl;

        for(Chess &game: game){
            game7.insert(game,sepReads3);
        }
        fout2 << "Separate Chaining Reads 2:" << sepReads3 << endl;

        for(Chess &game: game){
            game8.insert(game,sepReads3);
        }
        fout2 << "Separate Chaining Reads 3:" << sepReads3 << endl;

        for(Chess &game: game){
            game9.insert(game,sepReads4);
        }
        fout2 << "Separate Chaining Reads 4:" << sepReads4 << endl;

        for(Chess &game: game){
            game10.insert(game,sepReads5);
        }
        fout2 << "Separate Chaining Reads 5:" << sepReads5 << endl;
    }
    fout2.close();



    // Experiment 2, Create a new hash function, and use alternative keys to test
    // instantiate 4 hash tables of each type again

    // create another set of reads for quad probing for this test
    int quadReadsTest1, quadReadsTest2, quadReadsTest3,quadReadsTest4;

    QuadraticProbing<Chess>test1(25013,getKeyFromChess,hornerHash); // default key and horner hash
    QuadraticProbing<Chess>test2(25013,getKey2FromChess,hornerHash); // alternative key and horner hash
    QuadraticProbing<Chess>test3(25013,getKeyFromChess,alternativeHash); // default key and alternative hash
    QuadraticProbing<Chess>test4(25013,getKey2FromChess,alternativeHash); // alternative key and alternative hash


    ofstream fout3;
    fout3.open("../QuadraticProbingTest.csv");
    if(fout3){
        for(Chess &game: game){
            test1.insert(game,quadReadsTest1);
        }
        fout3 << "Default key and horner hash reads: " << quadReadsTest1 << endl;

        for(Chess &game: game){
            test2.insert(game,quadReadsTest2);
        }
        fout3 << "Alternative key and horner hash reads: " << quadReadsTest2 << endl;

        for(Chess &game: game){
            test3.insert(game,quadReadsTest3);
        }
        fout3 << "Default key and alternative hash reads: " << quadReadsTest3 << endl;

        for(Chess &game: game){
            test4.insert(game,quadReadsTest4);
        }
        fout3 << "Alternative key and alternative hash reads: " << quadReadsTest4 << endl;
    }
    fout.close();


    // create another set of reads for quad probing for this test
    int sepReadsTest1, sepReadsTest2, sepReadsTest3,sepReadsTest4;

    SeparateChaining<Chess>test5(25013,getKeyFromChess,hornerHash); // default key and horner hash
    SeparateChaining<Chess>test6(25013,getKey2FromChess,hornerHash); // alternative key and horner hash
    SeparateChaining<Chess>test7(25013,getKeyFromChess,alternativeHash); // default key and alternative hash
    SeparateChaining<Chess>test8(25013,getKey2FromChess,alternativeHash); // alternative key and alternative hash

    ofstream fout4;
    fout4.open("../SeparateChainingTest.csv");
    if(fout4){
        for(Chess &game: game){
            test5.insert(game,sepReadsTest1);
        }
        fout4 << "Default key and horner hash reads: " << sepReadsTest1 << endl;

        for(Chess &game: game){
            test6.insert(game,sepReadsTest2);
        }
        fout4 << "Alternative key and horner hash reads: " << sepReadsTest2 << endl;

        for(Chess &game: game){
            test7.insert(game,sepReadsTest3);
        }
        fout4 << "Default key and alternative hash reads: " << sepReadsTest3 << endl;

        for(Chess &game: game){
            test8.insert(game,sepReadsTest4);
        }
        fout4 << "Alternative key and alternative hash reads: " << sepReadsTest4 << endl;
    }
    fout.close();


}


