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
	typedef IntListsEqual< IntList<t1...> , IntList<t2...> > tailsEquals;
public:
	constexpr static bool value = ( (h1 == h2) ? ( tailsEquals::value) : false);
};

/* base case when the lists are not on the same size*/
template<int... t>
struct IntListsEqual<IntList<t...> , IntList<> > {
	constexpr static bool value = false;
};
template<int...t>
struct IntListsEqual<IntList<> , IntList<t...> > {
	constexpr static bool value = false;
};
/* base case of two empty lists*/
template<>
struct IntListsEqual<IntList<>,IntList<> > {
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
	typedef IntListContains<IntList<t1...> ,otherNumbers... > containsInListTail;
public:
	constexpr static bool value = ((h1 == num1) ? ( containsInListTail::value) : false );
};

template<int h,int...t >
struct IntListContains< IntList<h,t...>  > {
	constexpr static bool value = false;
};

template<int num1,int...otherNumbers>
struct IntListContains< IntList<> , num1,otherNumbers... > {
	constexpr static bool value = false;
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
struct IntListIndexEquals< IntList<h,t...>,INDEX,VALUE > {
private:
	typedef IntListIndexEquals<IntList<t...> , (INDEX - 1) , VALUE> indexEqualOnTail;
public:
	constexpr static bool value = ( (INDEX == 0) ? (h == VALUE) : ( indexEqualOnTail::value) );
};

template<int h , int INDEX , int VALUE>
struct IntListIndexEquals< IntList<h> , INDEX , VALUE > {
	constexpr static bool value = ((INDEX == 0) ?( h == VALUE ): false);
};

/* base case when list is empty */
template< int INDEX , int VALUE >
struct IntListIndexEquals< IntList<>,INDEX , VALUE  > {
	constexpr static bool value = false;
};

#endif // !INTLISTCOMPARATORS
