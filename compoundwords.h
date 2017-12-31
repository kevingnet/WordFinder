/*
 Find Longest Word Made of Other Words
 */

/////////////////////////////////////////////////////////////////////////////////
//
// Author: KevinG
// classes: CompoundWordCounter
// main()
/*
 */
//////////////////////////////////////////////////////////////////////
#ifndef _compoundwords_H
#define	_compoundwords_H

//------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sys/stat.h>
#include <boost/unordered_set.hpp>

using namespace std;

//------------------------------------------------------------------------------
//lots of trouble just to avoid branch, it improves about 2 tenths of a second (from .37 to .35 avg)
#ifdef CONFIG_64BIT
#define BITS_PER_LONG 64
#else
#define BITS_PER_LONG 32
#endif /* CONFIG_64BIT */
#define B1 (BITS_PER_LONG-1) // bits of signed int minus one
#define MINI(x,y) (((x) & (((int)((x)-(y)))>>B1)) + ((y) & ~(((int)((x)-(y)))>>B1)))

//------------------------------------------------------------------------------
//improves by almost twice as fast
typedef boost::unordered_set<string> sset;
typedef boost::unordered_set<string>::iterator itsset;
typedef vector<string> svec;
typedef vector<string>::const_iterator itsvec;

//------------------------------------------------------------------------------
// comparison for reverse order (words with more letters first)
struct compare {
  bool operator()(const string& first, const string& second) const {
    return first.size() > second.size();
  }
};

//------------------------------------------------------------------------------
//constants
const int MIN_START = 0xffff;
const int DEFAULT_LINE_SIZE = 100;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// CompoundWordCounter
//////////////////////////////////////////////////////////////////////
//NOTE: in the tests the class actually improved overall performance, it improves IsCompound because there are less parameters to pass
class CompoundWordCounter {
public:
  CompoundWordCounter();

  //get some stats
  int WordCount() const {
    return m_Words.size();
  }
  int CompoundCount() const {
    return m_Compounds.size();
  }

  void CalcCount();
  void AddWord(const string& s);
  void Print();

private:
  //disable copy const. and assignment
  CompoundWordCounter(const CompoundWordCounter&) {
  }
  CompoundWordCounter& operator=(const CompoundWordCounter&) {
    return *this;
  }

  bool IsCompound(const string w) const;

  sset m_Words;
  svec m_Compounds;
  size_t m_Min;
};
//------------------------------------------------------------------------------

#endif	/* _compoundwords_H */

