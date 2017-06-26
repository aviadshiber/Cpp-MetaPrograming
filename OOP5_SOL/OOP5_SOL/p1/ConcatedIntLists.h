#ifndef CONCATEDINTLISTS
#define CONCATEDINTLISTS
#include "IntList.h"

template <typename IntList1 ,typename... IntList2>
struct ConcatedIntLists;


template <int... t1>
struct ConcatedIntLists< IntList<t1...> > {
	typedef IntList<t1...> list;
};
template <int... t1,int...t2>
struct ConcatedIntLists< IntList<t1...>,IntList<t2...> > {
	typedef IntList<t1...,t2...> list;
};

template <int... t1 , typename... lists>
struct ConcatedIntLists< IntList<t1...>, lists... > {
	typedef typename ConcatedIntLists<IntList<t1...> , typename ConcatedIntLists<lists...>::list >::list list;
};




#endif // !CONCATEDINTLISTS
