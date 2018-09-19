#include "cacheLRU.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <random>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

/**
 * README.md:
 * You are going to need to add PUBLIC DATA MEMBERS to your rotateBST and splayTree in order for this analysis to work.
 * You can see the variables used at the bottom of this program. They are all ints.  In rotateBST, add public data members
 * mLeftRotateCount, mRightRotateCount, and mTotalRotateCount
 * In your constructor for rotateBST, intitialize
 * mLeftRotateCount, mRightRotateCount, and mTotalRotateCount to 0.  Put a statement at the bottom of your leftRotate function
 * that increments mLeftRotateCount and mTotalRotateCount, and similar for right rotate.  In you splayTree, add public data
 * member mRemoveCount and set it to 0 in the constructor.  Increment it at the bottom of deleteMinLeaf function
 * 
 * This file goes on the same level as your source code files i.e not in hw8-check
 * 
 * g++ -std=c++11  -g -Wall cacheAnalysis.cpp -o cacheAnalysis 
 * to compile. Needs the -std=c++11
 * You can see the command line arguments below.  The program writes the results of the analysis
 * to the ouput file after reading the input file.  If you provide a fourth parameter, a uniformly
 * random text file will be generated with the number of words given as the parameter in the input file,
 * so provide a blank input file
 * 
 * 
 * First parameter: input file name
 * Second parameter: output file name
 * Third parameter: cache size
 * Fourth parameter(optional) : number of words in random file
 */
int main (int argc, char* argv[])
{
    if (argc < 4)
    {
        return 1;
    }
    
    if (argc >= 5) // if number of words for random generator given
    {
        default_random_engine generator(time(0));
        uniform_int_distribution<int> distribution = uniform_int_distribution<int>(97, 122);
        uniform_int_distribution<int> distribution2 = uniform_int_distribution<int>(1,9);  

        string filename = argv[1];
        int len = atoi(argv[4]);

        ofstream ofile(filename.c_str());
        
        // for len words, create a random word and add it to file
        for (int i = 0; i < len; i++)
        {
            string randWord;
            int len = distribution2(generator); // word is of random length [1,9]
    
            for (int i = 0; i < len; i++)
            {
                randWord += distribution(generator);
            }
           
            ofile << randWord;
            ofile << " ";
            
            // add newline every ten words
            if (i % 10 == 0) ofile << endl;
        }
    }

    ifstream ifile(argv[1]);

    // create cache with parameter size
    cacheLRU<string, string> cache(atoi(argv[3]));

    // parse through each line of the file
    string line, word;
    stringstream ss;
    while(getline(ifile, line))
    {
        ss.str("");
        ss.clear();
        ss << line;

        // put each word in the cache
        while (ss >> word)
        {
            pair<string, string> new_pair (word, word);
            cache.put(new_pair);
        }
    }

    // write results to ouput
    ofstream ofile(argv[2]);

    ofile << "Input file name: " << argv[1] << endl;
    ofile << "Cache size: " << argv[3] << endl;
    ofile << "Left Rotations: " << cache.mLeftRotateCount << endl;
    ofile << "Right Rotations: " << cache.mRightRotateCount << endl;
    ofile << "Total Rotations: " << cache.mTotalRotateCount << endl;
    ofile << "Cache Misses: " << cache.mRemoveCount << endl;

    if (argc >= 5)
    {
        ofile << "Number of random words: " << argv[4] << endl;
    }

    return 0;
}