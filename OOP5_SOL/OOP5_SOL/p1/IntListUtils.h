#ifndef INTLISTUTILS
#define INTLISTUTILS
#include "IntList.h"
#include "ConcatedIntLists.h"

template<typename... t>
struct IntListUtils;


template<int h,int...t>
struct IntListUtils< IntList<h,t...> > {
private:
	using restList = IntList<t...>;
	using recursiveCallToTail = IntListUtils<restList>;
	using concateHeadToTailRecorsivly =  ConcatedIntLists<typename recursiveCallToTail::reversed , IntList<h>>;
	constexpr static int maxOfRestList =  recursiveCallToTail::max;
	constexpr static int minOfRestList =  recursiveCallToTail::min;
public:
	constexpr static int max = h > maxOfRestList ? h : maxOfRestList;
	constexpr static int min = h < minOfRestList ? h : minOfRestList;
	using reversed = typename concateHeadToTailRecorsivly::list;
};

template<int t>
struct IntListUtils< IntList<t> > {
	constexpr static int max = t;
	constexpr static int min = t;
	using reversed = IntList<t>;
};




#endif // !INTLISTUTILS
