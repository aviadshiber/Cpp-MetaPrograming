#ifndef INTLISTCOMPARATORS
#define INTLISTCOMPARATORS
#include "IntList.h"
/**
 * checks iff two lists are equal.
 * two lists are equal if they have the same length, same values, same order.
 * for example: IntListsEqual<IntList<2, 3>, IntList<2, 3>>::value; // = true
 */

template<typename IntList1,typename IntList2>
struct IntListsEqual;

template<int h1,int...t1,int h2,int...t2>
struct IntListsEqual<IntList<h1,t1...>,IntList<h2,t2...> > {
private:
	using tailsEquals = IntListsEqual< IntList<t1...> , IntList<t2...> >;
public:
	constexpr static bool value = h1 == h2 ? true : typename tailsEquals::value;
};

/* base case when the lists are not on the same size*/
template<int t>
struct IntListsEqual<IntList<t> , IntList<>> {
	constexpr static bool value = false;
};
template<int t>
struct IntListsEqual<IntList<> , IntList<t>> {
	constexpr static bool value = false;
};
/* base case of two empty lists*/
struct IntListsEqual<IntList<>,IntList<>> {
	constexpr static bool value = true;
};



/* --------------------------------------------------------------------------*/
/**
 * checks iff IntList1 have the same numbers as VALUES, same length, same order.
 * for example: IntListContains<IntList<2, 2, 3>, 2, 2, 3>::value; // = true
 * 
 */
template<class IntList1,int... VALUES>
struct IntListContains;

template<int h1,int...t1,int num1,int...otherNumbers>
struct IntListContains< IntList<h1,t1...> ,num1 , otherNumbers... > {
	typedef  IntListContains<IntList<t1...> ,otherNumbers... > containsInListTail;
	constexpr static bool value = h1 == num1 ? true : typename containsInListTail::value;
};

template<>
struct IntListContains< IntList<> > {

	constexpr static bool value = true;
};



#endif // !INTLISTCOMPARATORS
