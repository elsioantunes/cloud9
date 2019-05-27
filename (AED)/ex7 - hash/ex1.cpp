#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <cmath>

#include "hash.h"

#define NUM_KEYS 32

using namespace std;

int main(){
    // Set up pseudorandom number generator
    int seed = (int) chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rndGen(seed);

    cout << "Hash table." << endl;

    // Fill vector of keys
    vector<int> v;
    for (int i = 1; i <= NUM_KEYS; ++i)
        v.push_back(i*1);

	/*
    vector<pair<int, int>> objs;
    for (int i = 1; i <= NUM_KEYS; ++i)
        objs.push_back(pair<int, int>(i - 1, i));
    aed2::PerfectHash<int> ph(objs, seed);

    ph.Print();
	*/

    aed2::ChainedHash hs(32, &aed2::hf1);

    time_point t1;

    // Insertions
    //shuffle(v.begin(), v.end(), rndGen);
    t1 = time_now();
    for (int i = 0; i < (int)v.size(); ++i)
        hs.Insert(v.at(i));
    auto duration = itime_ns(time_now() - t1);
    cout << "Insertion time: " << duration << " ns." << endl;

    // Searches
    shuffle(v.begin(), v.end(), rndGen);
    t1 = time_now();
    for (int i = 0; i < (int)v.size(); ++i)
        hs.Search(v.at(i));
    duration = itime_ns(time_now() - t1);
    cout << "Search time: " << duration << " ns." << endl;

    cout << endl;

    hs.Print();

    return 0;
}

