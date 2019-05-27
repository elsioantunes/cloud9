#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <random>

namespace aed2
{

/// Hash function using the division method.
int hf1(int k, int m)
{
    return k % m;
}

/// Hash function using the multiplication method.
int hf2(int k, int m)
{
    unsigned int w = sizeof(int) * 8;
    unsigned int p = log2(m);
    unsigned int s = (sqrt(5)-1)/2.0 * ((unsigned long long)1 << w);
    unsigned int hk = k * (unsigned long long)s;
    return hk >> (w-p);

    //double A = 0.6180339887;
    //double intpart;
    //return floor(m * modf(k * A, &intpart));
}

using HashFunction = int (*)(int, int);

///////////////////////////////////////////////////////////////////////////////
/// A simple chained hash table.
///
/// Implements a chained hash table using integers as keys.
///////////////////////////////////////////////////////////////////////////////
class ChainedHash
{
public:
    ChainedHash(int m, HashFunction f = &hf1);
    ~ChainedHash();

    /// Getters.
    int m() { return _m; }
    int n() { return _n; }
    float loadFactor() { return _n / (float) _m; }

    void Insert(int key);
    bool Search(int key);
    bool Delete(int key);

    void Print();

protected:
    std::list<int>* _table; ///< Hash table as an array of lists.
    int _m; ///< Table size.
    int _n; ///< Actual number of stored keys.

    HashFunction _f; ///< Selected hash function.
};

///////////////////////////////////////////////////////////////////////////////
/// Constructor.
///
/// \param m Table size.
///////////////////////////////////////////////////////////////////////////////
ChainedHash::ChainedHash(int m, HashFunction f)
{
    _n = 0;
    _m = m;
    _f = f;

    if (_m <= 0)
        _m = 1;

    _table = new std::list<int>[_m];
}

///////////////////////////////////////////////////////////////////////////////
/// Destructor.
///////////////////////////////////////////////////////////////////////////////
ChainedHash::~ChainedHash()
{
    delete _table;
    _table = nullptr;
}

///////////////////////////////////////////////////////////////////////////////
/// Inserts the given key in the hash table.
///
/// \param key Key to be inserted.
///////////////////////////////////////////////////////////////////////////////
void ChainedHash::Insert(int key)
{
    int hv = (*_f)(key, _m);

    _table[hv].push_back(key);

    _n++;
}

///////////////////////////////////////////////////////////////////////////////
/// Searches the given key in the hash table.
///
/// \param key Search key.
///
/// \return TRUE if key was found, FALSE otherwise.
///////////////////////////////////////////////////////////////////////////////
bool ChainedHash::Search(int key)
{
    int hv = (*_f)(key, _m);

    std::list<int> &l = _table[hv];
    if (std::find(l.begin(), l.end(), key) != l.end())
        return true;

    return false;
}

///////////////////////////////////////////////////////////////////////////////
/// Removes the given key from the hash table.
///
/// \param key Key to be removed.
///
/// \return TRUE if key was found and removed, FALSE otherwise.
///////////////////////////////////////////////////////////////////////////////
bool ChainedHash::Delete(int key)
{
    int hv = (*_f)(key, _m);

    std::list<int> &l = _table[hv];
    auto it = std::find(l.begin(), l.end(), key);
    if (it != l.end())
    {
        l.erase(it, it);
        _n--;
        return true;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////////
/// Prints the contents of the hash table.
///////////////////////////////////////////////////////////////////////////////
void ChainedHash::Print()
{
    std::cout << "Load factor: " << loadFactor() << std::endl;
    std::cout << "n: " << n() << std::endl;
    std::cout << "m: " << m() << std::endl;

    std::cout << std::endl;

    int digits1 = (int) log10 ((double) m()) + 1;
    int digits2 = (int) log10 ((double) n()) + 1;

    for (int i = 0; i < _m; ++i)
    {
        std::cout << "T[";
        std::cout << std::setfill('0') << std::setw(digits1) << i;
        std::cout << "]: ";
        for (int& key : _table[i])
        {
            std::cout << std::setfill(' ') << std::setw(digits2) << key << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

}

#endif // HASH_H
