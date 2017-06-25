#ifndef INTLIST
#define INTLIST

template<int...>
struct IntList;

template<int H,int...TT>
struct IntList<H,TT...> {
	constexpr static int head = H;
	typedef IntList<TT...> next; //unpacking to be T, TT...T
	constexpr static int size = next::size + 1;
	constexpr static bool empty = false;
};


template<>
struct IntList<> { //empty list
	constexpr static bool empty = true;
	constexpr static int size = 0;
};

#endif