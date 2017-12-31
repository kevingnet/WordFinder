
/*

Find Longest Word Made of Other Words

Write a program that reads a file containing a sorted list of words (one word per line, no spaces, all lower case), then identifies 
the longest word in the file that can be constructed by concatenating copies of shorter words also found in the file. 
The program should then go on to report the second longest word found as well as how many of the words in the list can be constructed of other words in the list.
Please reply to this email with your solution as source code along with the (2) longest words that the program finds and the count 
of words that can be constructed as an output in the body of the email and any comments you have on the approach you took.
If you have any questions about the problem, please feel free to email us back.
For example, if the file contained:

       cat
       cats
       catsdogcats
       catxdogcatsrat
       dog
       dogcatsdog
       hippopotamuses
       rat
       ratcatdogcat

The longest word would be 'ratcatdogcat' - at 12 letters, it is the longest word made up of other words in the list.  

Please send your solution in source code form, written in C or C++.   This is not just a puzzle or classroom assignment; 
it is your opportunity to demonstrate your engineering judgment in a way that you cannot do in a personal interview.  
Performance matters: the program should return results quickly even for very large lists (100,000+ items).  

Please find attached a file, words for problem.txt, containing a word list, with 173k rows, for testing purposes.

sorted list of words (no spaces, lower case)
longest word constructed by concatenating copies of shorter words
NOTE: shorter, not shortest

The program should then go on to report the second longest word found
as well as how many of the words in the list can be constructed of other words in the list.

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
struct compare 
{
	bool operator()(const string& first, const string& second) const 
	{
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
class CompoundWordCounter
{
public:
	CompoundWordCounter		();

	//get some stats
	int		WordCount		() const { return m_Words.size(); }
	int		CompoundCount	() const { return m_Compounds.size(); }

	void	CalcCount		();
	void	AddWord			(const string& s);
	void	Print			();

private:
	//disable copy const. and assignment
	CompoundWordCounter				(const CompoundWordCounter&) {}
	CompoundWordCounter& operator=	(const CompoundWordCounter&) { return * this; }
	
	bool	IsCompound		(const string w) const;

	sset	m_Words;
	svec	m_Compounds;
	size_t	m_Min;
};
//------------------------------------------------------------------------------


#endif	/* _compoundwords_H */

