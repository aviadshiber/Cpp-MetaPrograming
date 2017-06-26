#ifndef INTLISTCOMPARATORS
#define INTLISTCOMPARATORS
#include "IntList.h"
/**
 * checks if two lists are equal.
 * two lists are equal iff they have the same length, same values, same order.
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
 * checks if IntList1 contains VALUES. 
 * IntList1 contains VALUES iff VALUES have the same numbers as IntList1, same length, same order.
 * for example: IntListContains<IntList<2, 2, 3>, 2, 2, 3>::value; // = true
 * 
 */
template<class IntList1,int... VALUES>
struct IntListContains;

template<int h1,int...t1,int num1,int...otherNumbers>
struct IntListContains< IntList<h1,t1...> ,num1 , otherNumbers... > {
private:
	using containsInListTail = IntListContains<IntList<t1...> ,otherNumbers... >;
public:
	constexpr static bool value = h1 == num1 ? true : typename containsInListTail::value;
};

template<>
struct IntListContains< IntList<> > {
	constexpr static bool value = true;
};


/* --------------------------------------------------------------------------*/

/*
 * checks if IntList1 at INDEX (Zero based) is equal to VALUE.
 * example: IntListIndexEquals<IntList<1, 2>, 0, 1>::value; // = true (index 0 contains 1)
 */
template<class IntList1,int INDEX,int VALUE>
struct IntListIndexEquals;


template<int h,int...t,int INDEX,int VALUE>
struct IntListIndexEquals< IntList<h,t...> > {
private:
	using indexEqualOnTail = IntListIndexEquals<IntList<t...> , (INDEX - 1) , VALUE>;
public:
	constexpr static bool value = INDEX == 0 ? h == VALUE : typename indexEqualOnTail::value;
};
/* base case when list is empty */
template< int INDEX , int VALUE>
struct IntListIndexEquals< IntList<> > {
	constexpr static bool value = false;
};

#endif // !INTLISTCOMPARATORS
