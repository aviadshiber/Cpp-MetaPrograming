#include <iostream>
#include "IntList.h"
#include "MergedIntLists.h"
#include "ConcatedIntLists.h"
#include "IntListUtils.h"
#include "IntListComparators.h"
using namespace std;

int main() {
	IntList<1, 2, 3>::head; // = 1
	IntList<1, 2, 3>::next::next; // = IntList<3>
	static_assert(IntListsEqual<IntList<1, 2, 3>::next::next, IntList<3> >::value, "Failed!");
	IntList<1, 2>::size; // = 2
	IntList<1, 2>::next::next::empty; // = true
	typedef ConcatedIntLists<IntList<1>, IntList<>, IntList<2, 3, 4>>::list Concated; // = IntList<1,2,3,4> 
	static_assert(IntListsEqual<Concated, IntList<1, 2, 3, 4>>::value, "Failed!");
	MergedIntLists<IntList<1, 9>, IntList<1, 2, 3, 4>>::list; // = IntList<1,1,9,2,3,4> 
	typedef IntListUtils<IntList<1, 2, 3>>::reversed MyList; // = IntList<3,2,1>
	static_assert(IntListsEqual<MyList, IntListUtils<IntListUtils<MyList>::reversed>::reversed>::value, "Failed!");
	IntListUtils<IntList<1, 2, 3>>::max; // = 3
	IntListUtils<IntList<1, 2, 3>>::min; // = 1
	IntListsEqual<IntList<2, 3>, IntList<2, 3>>::value; // = true
	IntListContains<IntList<2, 3>, 2, 3>::value; // = true
	IntListIndexEquals<IntList<1, 2>, 0, 1>::value; // = true (index 0 contains 1)
	return 0;
}