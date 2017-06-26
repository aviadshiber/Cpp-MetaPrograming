#ifndef MERGEDLIST
#define MERGEDLIST
#include "IntList.h"
#include "Conditional.h"
#include "ConcatedIntLists.h"
/**
 * \brief merges two lists, one to the other.
 * for example: MergedIntLists<IntList<1,9>, IntList<1,2,3,4>>::list; // = IntList<1,1,9,2,3,4>
 */
template< typename IntList1 , typename IntList2 >
struct MergedIntLists;

template<> 
struct MergedIntLists<IntList<>,IntList<> >{
	//merging two empty list results in an empty list
	typedef IntList<> list;
};

template<int h1,int...t1>
struct MergedIntLists<IntList<h1,t1...> , IntList<> > {
	//merging two empty list results in an empty list
	typedef IntList<h1, t1...> list;
};

template<int h1,int...t1>
struct MergedIntLists<IntList<> , IntList<h1,t1...> > {
	//merging two empty list results in an empty list
	typedef IntList<h1,t1...> list;
};

template<int h1,int...t1,int h2,int...t2>
struct MergedIntLists<IntList<h1,t1...>, IntList<h2,t2...> > {
	typedef  typename ConcatedIntLists<IntList<h1,h2>, typename MergedIntLists<IntList<t1...>,IntList<t2...> >::list >::list  list;
};






#endif // !MERGEDLIST
