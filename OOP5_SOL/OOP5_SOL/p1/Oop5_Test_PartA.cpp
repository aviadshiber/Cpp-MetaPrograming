#include <iostream>
#include "IntList.h"
#include "MergedIntLists.h"
#include "ConcatedIntLists.h"
#include "IntListUtils.h"
#include "IntListComparators.h"
using namespace std;

void testExample();
void testIntList();
void testMergedIntLists();
void testConcatedIntLists();
void testIntListUtils();
void testIntListComparators();

int main() {
	testExample();
	testIntList();
	testMergedIntLists();
	testConcatedIntLists();
	testIntListUtils();
	testIntListComparators();
	
	return 0;
}

void testExample(){
	IntList<1, 2, 3>::head; // = 1
	IntList<1, 2, 3>::next::next list_1; // = IntList<3>
	static_assert(IntListsEqual<IntList<1, 2, 3>::next::next, IntList<3> >::value, "Failed!");
	IntList<1, 2>::size; // = 2
	IntList<1, 2>::next::next::empty; // = true
	typedef ConcatedIntLists<IntList<1>, IntList<>, IntList<2, 3, 4>>::list Concated; // = IntList<1,2,3,4> 
	static_assert(IntListsEqual<Concated, IntList<1, 2, 3, 4>>::value, "Failed!");
	MergedIntLists<IntList<>, IntList<>>::list list_2; // = IntList<1,1,9,2,3,4> 
	MergedIntLists<IntList<1, 9>, IntList<1, 2, 3, 4>>::list list_3; // = IntList<1,1,9,2,3,4> 
	typedef IntListUtils<IntList<1, 2, 3>>::reversed MyList; // = IntList<3,2,1>
	static_assert(IntListsEqual<MyList, IntListUtils<IntListUtils<MyList>::reversed>::reversed>::value, "Failed!");
	IntListUtils<IntList<1, 2, 3>>::max; // = 3
	IntListUtils<IntList<1, 2, 3>>::min; // = 1
	IntListsEqual<IntList<2, 3>, IntList<2, 3>>::value; // = true
	IntListContains<IntList<2, 3>, 2, 3>::value; // = true
	IntListIndexEquals<IntList<1, 2>, 0, 1>::value; // = true (index 0 contains 1)
}

void testIntList(){
	typedef IntList<> list_empty;
	typedef IntList<42> list_one_element;
	typedef IntList<666,1000> list_two_elements;
	typedef IntList<3,5,7> list_three_elements;
	
	static_assert(list_empty::empty,"Failed! :(");
	static_assert(list_empty::size==0,"Failed! :(");
	
	static_assert(list_one_element::head==42,"Failed! :(");
	static_assert(list_one_element::empty==false,"Failed! :(");
	static_assert(list_one_element::size==1,"Failed! :(");
	static_assert(list_one_element::next::empty,"Failed! :(");
	static_assert(list_one_element::next::size==0,"Failed! :(");
	
	static_assert(list_two_elements::head==666,"Failed! :(");
	static_assert(list_two_elements::empty==false,"Failed! :(");
	static_assert(list_two_elements::size==2,"Failed! :(");
	static_assert(list_two_elements::next::head==1000,"Failed! :(");
	static_assert(list_two_elements::next::empty==false,"Failed! :(");
	static_assert(list_two_elements::next::size==1,"Failed! :(");
	static_assert(list_two_elements::next::next::empty,"Failed! :(");
	static_assert(list_two_elements::next::next::size==0,"Failed! :(");
	
	static_assert(list_three_elements::head==3,"Failed! :(");
	static_assert(list_three_elements::empty==false,"Failed! :(");
	static_assert(list_three_elements::size==3,"Failed! :(");
	static_assert(list_three_elements::next::head==5,"Failed! :(");
	static_assert(list_three_elements::next::empty==false,"Failed! :(");
	static_assert(list_three_elements::next::size==2,"Failed! :(");
	static_assert(list_three_elements::next::next::head==7,"Failed! :(");
	static_assert(list_three_elements::next::next::empty==false,"Failed! :(");
	static_assert(list_three_elements::next::next::size==1,"Failed! :(");
	static_assert(list_three_elements::next::next::next::empty,"Failed! :(");
	static_assert(list_three_elements::next::next::next::size==0,"Failed! :(");
	
}

void testMergedIntLists(){
	typedef IntList<> list_empty;
	typedef IntList<42> list_one_element;
	typedef IntList<666,1000> list_two_elements;
	typedef IntList<3,5,7> list_three_elements;
	typedef MergedIntLists<list_empty,list_empty> merged_list_empty;
	typedef MergedIntLists<list_empty,list_one_element> merged_list_empty_left;
	typedef MergedIntLists<list_three_elements,list_empty> merged_list_empty_right;
	typedef MergedIntLists<list_one_element,list_two_elements> merged_list_one_two;
	typedef MergedIntLists<list_two_elements,list_one_element> merged_list_two_one;
	typedef MergedIntLists<list_one_element,list_three_elements> merged_list_one_three;
	typedef MergedIntLists<list_three_elements,list_one_element> merged_list_three_one;
	typedef MergedIntLists<list_two_elements,list_three_elements> merged_list_two_three;
	typedef MergedIntLists<list_three_elements,list_two_elements> merged_list_three_two;
	typedef MergedIntLists<IntList<1,3,5,7,9,11,13>,IntList<2,4,6,8,10,12>> merged_list_sorted;
	
	static_assert(merged_list_empty::list::empty,"Failed! :(");
	static_assert(merged_list_empty::list::size==0,"Failed! :(");

	static_assert(merged_list_empty_left::list::empty==false,"Failed! :(");
	static_assert(merged_list_empty_left::list::size==1,"Failed! :(");
	static_assert(merged_list_empty_left::list::head==42,"Failed! :(");
	static_assert(merged_list_empty_left::list::next::empty,"Failed! :(");
	static_assert(merged_list_empty_left::list::next::size==0,"Failed! :(");
	
	static_assert(merged_list_empty_right::list::empty==false,"Failed! :(");
	static_assert(merged_list_empty_right::list::size==3,"Failed! :(");
	static_assert(merged_list_empty_right::list::head==3,"Failed! :(");
	static_assert(merged_list_empty_right::list::next::head==5,"Failed! :(");
	static_assert(merged_list_empty_right::list::next::next::head==7,"Failed! :(");
	static_assert(merged_list_empty_right::list::next::next::next::empty,"Failed! :(");
	
	static_assert(merged_list_one_two::list::empty==false,"Failed! :(");
	static_assert(merged_list_one_two::list::size==3,"Failed! :(");
	static_assert(merged_list_one_two::list::head==42,"Failed! :(");
	static_assert(merged_list_one_two::list::next::head==666,"Failed! :(");
	static_assert(merged_list_one_two::list::next::next::head==1000,"Failed! :(");
	static_assert(merged_list_one_two::list::next::next::next::empty,"Failed! :(");

	static_assert(merged_list_two_one::list::empty==false,"Failed! :(");
	static_assert(merged_list_two_one::list::size==3,"Failed! :(");
	static_assert(merged_list_two_one::list::head==666,"Failed! :(");
	static_assert(merged_list_two_one::list::next::head==42,"Failed! :(");
	static_assert(merged_list_two_one::list::next::next::head==1000,"Failed! :(");
	static_assert(merged_list_two_one::list::next::next::next::empty,"Failed! :(");
	
	static_assert(merged_list_one_three::list::empty==false,"Failed! :(");
	static_assert(merged_list_one_three::list::size==4,"Failed! :(");
	static_assert(merged_list_one_three::list::head==42,"Failed! :(");
	static_assert(merged_list_one_three::list::next::head==3,"Failed! :(");
	static_assert(merged_list_one_three::list::next::next::head==5,"Failed! :(");
	static_assert(merged_list_one_three::list::next::next::next::head==7,"Failed! :(");
	static_assert(merged_list_one_three::list::next::next::next::next::empty,"Failed! :(");

	
	static_assert(merged_list_three_one::list::empty==false,"Failed! :(");
	static_assert(merged_list_three_one::list::size==4,"Failed! :(");
	static_assert(merged_list_three_one::list::head==3,"Failed! :(");
	static_assert(merged_list_three_one::list::next::head==42,"Failed! :(");
	static_assert(merged_list_three_one::list::next::next::head==5,"Failed! :(");
	static_assert(merged_list_three_one::list::next::next::next::head==7,"Failed! :(");
	static_assert(merged_list_three_one::list::next::next::next::next::empty,"Failed! :(");
	
	static_assert(merged_list_two_three::list::empty==false,"Failed! :(");
	static_assert(merged_list_two_three::list::size==5,"Failed! :(");
	static_assert(merged_list_two_three::list::head==666,"Failed! :(");
	static_assert(merged_list_two_three::list::next::head==3,"Failed! :(");
	static_assert(merged_list_two_three::list::next::next::head==1000,"Failed! :(");
	static_assert(merged_list_two_three::list::next::next::next::head==5,"Failed! :(");
	static_assert(merged_list_two_three::list::next::next::next::next::head==7,"Failed! :(");
	static_assert(merged_list_two_three::list::next::next::next::next::next::empty,"Failed! :(");

	static_assert(merged_list_three_two::list::empty==false,"Failed! :(");
	static_assert(merged_list_three_two::list::size==5,"Failed! :(");
	static_assert(merged_list_three_two::list::head==3,"Failed! :(");
	static_assert(merged_list_three_two::list::next::head==666,"Failed! :(");
	static_assert(merged_list_three_two::list::next::next::head==5,"Failed! :(");
	static_assert(merged_list_three_two::list::next::next::next::head==1000,"Failed! :(");
	static_assert(merged_list_three_two::list::next::next::next::next::head==7,"Failed! :(");
	static_assert(merged_list_three_two::list::next::next::next::next::next::empty,"Failed! :(");
	
	static_assert(merged_list_sorted::list::empty==false,"Failed! :(");
	static_assert(merged_list_sorted::list::size==13,"Failed! :(");
	static_assert(merged_list_sorted::list::head==1,"Failed! :(");
	static_assert(merged_list_sorted::list::next::head==2,"Failed! :(");
	static_assert(merged_list_sorted::list::next::next::head==3,"Failed! :(");
	static_assert(merged_list_sorted::list::next::next::next::head==4,"Failed! :(");
	static_assert(merged_list_sorted::list::next::next::next::next::head==5,"Failed! :(");
	static_assert(merged_list_sorted::list::next::next::next::next::next::head==6,"Failed! :(");
	static_assert(merged_list_sorted::list::next::next::next::next::next::next::head==7,"Failed! :(");
	static_assert(merged_list_sorted::list::next::next::next::next::next::next::next::head==8,"Failed! :(");
	static_assert(merged_list_sorted::list::next::next::next::next::next::next::next::next::head==9,"Failed! :(");
	static_assert(merged_list_sorted::list::next::next::next::next::next::next::next::next::next::head==10,"Failed! :(");
	static_assert(merged_list_sorted::list::next::next::next::next::next::next::next::next::next::next::head==11,"Failed! :(");
	static_assert(merged_list_sorted::list::next::next::next::next::next::next::next::next::next::next::next::head==12,"Failed! :(");
	static_assert(merged_list_sorted::list::next::next::next::next::next::next::next::next::next::next::next::next::head==13,"Failed! :(");
	static_assert(merged_list_sorted::list::next::next::next::next::next::next::next::next::next::next::next::next::next::empty,"Failed! :(");

}
void testConcatedIntLists(){
	typedef IntList<> list_empty;
	typedef IntList<42> list_one_element;
	typedef IntList<666,1000> list_two_elements;
	typedef IntList<3,5,7> list_three_elements;
	typedef ConcatedIntLists<list_empty,list_empty> concated_list_empty;
	typedef ConcatedIntLists<list_empty,list_one_element> concated_list_empty_left;
	typedef ConcatedIntLists<list_three_elements,list_empty> concated_list_empty_right;
	typedef ConcatedIntLists<list_one_element,list_two_elements> concated_list_one_two;
	typedef ConcatedIntLists<list_two_elements,list_one_element> concated_list_two_one;
	typedef ConcatedIntLists<list_one_element,list_three_elements> concated_list_one_three;
	typedef ConcatedIntLists<list_three_elements,list_one_element> concated_list_three_one;
	typedef ConcatedIntLists<list_two_elements,list_three_elements> concated_list_two_three;
	typedef ConcatedIntLists<list_three_elements,list_two_elements> concated_list_three_two;
	typedef ConcatedIntLists<IntList<1,2,3,4,5,6,7>,IntList<8,9,10,11,12,13>> concated_list_sorted;
	
	static_assert(concated_list_empty::list::empty,"Failed! :(");
	static_assert(concated_list_empty::list::size==0,"Failed! :(");

	static_assert(concated_list_empty_left::list::empty==false,"Failed! :(");
	static_assert(concated_list_empty_left::list::size==1,"Failed! :(");
	static_assert(concated_list_empty_left::list::head==42,"Failed! :(");
	static_assert(concated_list_empty_left::list::next::empty,"Failed! :(");
	static_assert(concated_list_empty_left::list::next::size==0,"Failed! :(");
	
	static_assert(concated_list_empty_right::list::empty==false,"Failed! :(");
	static_assert(concated_list_empty_right::list::size==3,"Failed! :(");
	static_assert(concated_list_empty_right::list::head==3,"Failed! :(");
	static_assert(concated_list_empty_right::list::next::head==5,"Failed! :(");
	static_assert(concated_list_empty_right::list::next::next::head==7,"Failed! :(");
	static_assert(concated_list_empty_right::list::next::next::next::empty,"Failed! :(");
	
	static_assert(concated_list_one_two::list::empty==false,"Failed! :(");
	static_assert(concated_list_one_two::list::size==3,"Failed! :(");
	static_assert(concated_list_one_two::list::head==42,"Failed! :(");
	static_assert(concated_list_one_two::list::next::head==666,"Failed! :(");
	static_assert(concated_list_one_two::list::next::next::head==1000,"Failed! :(");
	static_assert(concated_list_one_two::list::next::next::next::empty,"Failed! :(");

	static_assert(concated_list_two_one::list::empty==false,"Failed! :(");
	static_assert(concated_list_two_one::list::size==3,"Failed! :(");
	static_assert(concated_list_two_one::list::head==666,"Failed! :(");
	static_assert(concated_list_two_one::list::next::head==1000,"Failed! :(");
	static_assert(concated_list_two_one::list::next::next::head==42,"Failed! :(");
	static_assert(concated_list_two_one::list::next::next::next::empty,"Failed! :(");
	
	static_assert(concated_list_one_three::list::empty==false,"Failed! :(");
	static_assert(concated_list_one_three::list::size==4,"Failed! :(");
	static_assert(concated_list_one_three::list::head==42,"Failed! :(");
	static_assert(concated_list_one_three::list::next::head==3,"Failed! :(");
	static_assert(concated_list_one_three::list::next::next::head==5,"Failed! :(");
	static_assert(concated_list_one_three::list::next::next::next::head==7,"Failed! :(");
	static_assert(concated_list_one_three::list::next::next::next::next::empty,"Failed! :(");

	
	static_assert(concated_list_three_one::list::empty==false,"Failed! :(");
	static_assert(concated_list_three_one::list::size==4,"Failed! :(");
	static_assert(concated_list_three_one::list::head==3,"Failed! :(");
	static_assert(concated_list_three_one::list::next::head==5,"Failed! :(");
	static_assert(concated_list_three_one::list::next::next::head==7,"Failed! :(");
	static_assert(concated_list_three_one::list::next::next::next::head==42,"Failed! :(");
	static_assert(concated_list_three_one::list::next::next::next::next::empty,"Failed! :(");
	
	static_assert(concated_list_two_three::list::empty==false,"Failed! :(");
	static_assert(concated_list_two_three::list::size==5,"Failed! :(");
	static_assert(concated_list_two_three::list::head==666,"Failed! :(");
	static_assert(concated_list_two_three::list::next::head==1000,"Failed! :(");
	static_assert(concated_list_two_three::list::next::next::head==3,"Failed! :(");
	static_assert(concated_list_two_three::list::next::next::next::head==5,"Failed! :(");
	static_assert(concated_list_two_three::list::next::next::next::next::head==7,"Failed! :(");
	static_assert(concated_list_two_three::list::next::next::next::next::next::empty,"Failed! :(");

	static_assert(concated_list_three_two::list::empty==false,"Failed! :(");
	static_assert(concated_list_three_two::list::size==5,"Failed! :(");
	static_assert(concated_list_three_two::list::head==3,"Failed! :(");
	static_assert(concated_list_three_two::list::next::head==5,"Failed! :(");
	static_assert(concated_list_three_two::list::next::next::head==7,"Failed! :(");
	static_assert(concated_list_three_two::list::next::next::next::head==666,"Failed! :(");
	static_assert(concated_list_three_two::list::next::next::next::next::head==1000,"Failed! :(");
	static_assert(concated_list_three_two::list::next::next::next::next::next::empty,"Failed! :(");
	
	static_assert(concated_list_sorted::list::empty==false,"Failed! :(");
	static_assert(concated_list_sorted::list::size==13,"Failed! :(");
	static_assert(concated_list_sorted::list::head==1,"Failed! :(");
	static_assert(concated_list_sorted::list::next::head==2,"Failed! :(");
	static_assert(concated_list_sorted::list::next::next::head==3,"Failed! :(");
	static_assert(concated_list_sorted::list::next::next::next::head==4,"Failed! :(");
	static_assert(concated_list_sorted::list::next::next::next::next::head==5,"Failed! :(");
	static_assert(concated_list_sorted::list::next::next::next::next::next::head==6,"Failed! :(");
	static_assert(concated_list_sorted::list::next::next::next::next::next::next::head==7,"Failed! :(");
	static_assert(concated_list_sorted::list::next::next::next::next::next::next::next::head==8,"Failed! :(");
	static_assert(concated_list_sorted::list::next::next::next::next::next::next::next::next::head==9,"Failed! :(");
	static_assert(concated_list_sorted::list::next::next::next::next::next::next::next::next::next::head==10,"Failed! :(");
	static_assert(concated_list_sorted::list::next::next::next::next::next::next::next::next::next::next::head==11,"Failed! :(");
	static_assert(concated_list_sorted::list::next::next::next::next::next::next::next::next::next::next::next::head==12,"Failed! :(");
	static_assert(concated_list_sorted::list::next::next::next::next::next::next::next::next::next::next::next::next::head==13,"Failed! :(");
	static_assert(concated_list_sorted::list::next::next::next::next::next::next::next::next::next::next::next::next::next::empty,"Failed! :(");
	
	// Concation of many! :)
	
	static_assert(ConcatedIntLists<IntList<>,IntList<>,IntList<>>::list::empty,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<>,IntList<>,IntList<>,IntList<>,IntList<>>::list::empty,"Failed! :(");
	
	static_assert(ConcatedIntLists<IntList<1>,IntList<2>,IntList<3>,IntList<4>,IntList<5>>::list::empty==false,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<1>,IntList<2>,IntList<3>,IntList<4>,IntList<5>>::list::head==1,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<1>,IntList<2>,IntList<3>,IntList<4>,IntList<5>>::list::next::head==2,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<1>,IntList<2>,IntList<3>,IntList<4>,IntList<5>>::list::next::next::head==3,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<1>,IntList<2>,IntList<3>,IntList<4>,IntList<5>>::list::next::next::next::head==4,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<1>,IntList<2>,IntList<3>,IntList<4>,IntList<5>>::list::next::next::next::next::head==5,"Failed! :(");

	static_assert(ConcatedIntLists<IntList<>,IntList<>,IntList<60>,IntList<>,IntList<>,IntList<>,IntList<>>::list::empty==false,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<>,IntList<>,IntList<60>,IntList<>,IntList<>,IntList<>,IntList<>>::list::size==1,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<>,IntList<>,IntList<60>,IntList<>,IntList<>,IntList<>,IntList<>>::list::head==60,"Failed! :(");
	
	static_assert(ConcatedIntLists<IntList<>,IntList<>,IntList<>,IntList<>,IntList<>,IntList<>,IntList<>>::list::empty,"Failed! :(");
	
	static_assert(ConcatedIntLists<IntList<4>,IntList<>,IntList<>,IntList<>,IntList<>,IntList<>,IntList<9>>::list::empty==false,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<4>,IntList<>,IntList<>,IntList<>,IntList<>,IntList<>,IntList<9>>::list::size==2,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<4>,IntList<>,IntList<>,IntList<>,IntList<>,IntList<>,IntList<9>>::list::head==4,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<4>,IntList<>,IntList<>,IntList<>,IntList<>,IntList<>,IntList<9>>::list::next::head==9,"Failed! :(");

	static_assert(ConcatedIntLists<IntList<>,IntList<>,IntList<60>,IntList<>,IntList<50,40,20>,IntList<>,IntList<>>::list::empty==false,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<>,IntList<>,IntList<60>,IntList<>,IntList<50,40,20>,IntList<>,IntList<>>::list::size==4,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<>,IntList<>,IntList<60>,IntList<>,IntList<50,40,20>,IntList<>,IntList<>>::list::head==60,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<>,IntList<>,IntList<60>,IntList<>,IntList<50,40,20>,IntList<>,IntList<>>::list::next::head==50,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<>,IntList<>,IntList<60>,IntList<>,IntList<50,40,20>,IntList<>,IntList<>>::list::next::next::head==40,"Failed! :(");
	static_assert(ConcatedIntLists<IntList<>,IntList<>,IntList<60>,IntList<>,IntList<50,40,20>,IntList<>,IntList<>>::list::next::next::next::head==20,"Failed! :(");

}
void testIntListUtils(){
	static_assert(IntListUtils<IntList<>>::reversed::empty,"Failed! :(");
	
	static_assert(IntListUtils<IntList<42>>::reversed::head==42,"Failed! :(");
	static_assert(IntListUtils<IntList<42>>::max==42,"Failed! :(");
	static_assert(IntListUtils<IntList<42>>::min==42,"Failed! :(");
	
	static_assert(IntListUtils<IntList<1024,512>>::reversed::size==2,"Failed! :(");
	static_assert(IntListUtils<IntList<1024,512>>::reversed::head==512,"Failed! :(");
	static_assert(IntListUtils<IntList<1024,512>>::reversed::next::head==1024,"Failed! :(");
	static_assert(IntListUtils<IntList<1024,512>>::max==1024,"Failed! :(");
	static_assert(IntListUtils<IntList<1024,512>>::min==512,"Failed! :(");
	
	static_assert(IntListUtils<IntList<80,60,70>>::reversed::size==3,"Failed! :(");
	static_assert(IntListUtils<IntList<80,60,70>>::reversed::head==70,"Failed! :(");
	static_assert(IntListUtils<IntList<80,60,70>>::reversed::next::head==60,"Failed! :(");
	static_assert(IntListUtils<IntList<80,60,70>>::reversed::next::next::head==80,"Failed! :(");
	static_assert(IntListUtils<IntList<80,60,70>>::max==80,"Failed! :(");
	static_assert(IntListUtils<IntList<80,60,70>>::min==60,"Failed! :(");
	
	static_assert(IntListUtils<IntList<1,2,3,4>>::reversed::size==4,"Failed! :(");
	static_assert(IntListUtils<IntList<1,2,3,4>>::reversed::head==4,"Failed! :(");
	static_assert(IntListUtils<IntList<1,2,3,4>>::reversed::next::head==3,"Failed! :(");
	static_assert(IntListUtils<IntList<1,2,3,4>>::reversed::next::next::head==2,"Failed! :(");
	static_assert(IntListUtils<IntList<1,2,3,4>>::reversed::next::next::next::head==1,"Failed! :(");
	static_assert(IntListUtils<IntList<1,2,3,4>>::max==4,"Failed! :(");
	static_assert(IntListUtils<IntList<1,2,3,4>>::min==1,"Failed! :(");
	
	static_assert(IntListUtils<IntList<50,30,80,20,40>>::reversed::size==5,"Failed! :(");
	static_assert(IntListUtils<IntList<50,30,80,20,40>>::reversed::head==40,"Failed! :(");
	static_assert(IntListUtils<IntList<50,30,80,20,40>>::reversed::next::head==20,"Failed! :(");
	static_assert(IntListUtils<IntList<50,30,80,20,40>>::reversed::next::next::head==80,"Failed! :(");
	static_assert(IntListUtils<IntList<50,30,80,20,40>>::reversed::next::next::next::head==30,"Failed! :(");
	static_assert(IntListUtils<IntList<50,30,80,20,40>>::reversed::next::next::next::next::head==50,"Failed! :(");
	static_assert(IntListUtils<IntList<50,30,80,20,40>>::max==80,"Failed! :(");
	static_assert(IntListUtils<IntList<50,30,80,20,40>>::min==20,"Failed! :(");
	
}
void testIntListComparators(){

	/****************************************************************IntListsEqual :)****************************************************************/
	
	// True assertion section :)
	
	static_assert(IntListsEqual<IntList<>,IntList<>>::value,"Failed! :(");
	static_assert(IntListsEqual<IntList<1>,IntList<1>>::value,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,2>,IntList<1,2>>::value,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,1>,IntList<2,1>>::value,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,2,3>,IntList<1,2,3>>::value,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,3,2>,IntList<1,3,2>>::value,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,1,3>,IntList<2,1,3>>::value,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,3,1>,IntList<2,3,1>>::value,"Failed! :(");
	static_assert(IntListsEqual<IntList<3,1,2>,IntList<3,1,2>>::value,"Failed! :(");
	static_assert(IntListsEqual<IntList<3,2,1>,IntList<3,2,1>>::value,"Failed! :(");

	// True assertion section :)
	
	// False assertion section :)
	
	static_assert(IntListsEqual<IntList<>,IntList<1>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<>,IntList<1,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<>,IntList<2,1>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<>,IntList<1,2,3>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<>,IntList<1,3,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<>,IntList<2,1,3>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<>,IntList<2,3,1>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<>,IntList<3,1,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<>,IntList<3,2,1>>::value==false,"Failed! :(");
	
	static_assert(IntListsEqual<IntList<1>,IntList<>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,2>,IntList<>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,1>,IntList<>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,2,3>,IntList<>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,3,2>,IntList<>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,1,3>,IntList<>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,3,1>,IntList<>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<3,1,2>,IntList<>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<3,2,1>,IntList<>>::value==false,"Failed! :(");

	static_assert(IntListsEqual<IntList<1,2>,IntList<2,1>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,2>,IntList<1,2,3>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,2>,IntList<1,3,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,2>,IntList<2,1,3>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,2>,IntList<2,3,1>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,2>,IntList<3,1,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,2>,IntList<3,2,1>>::value==false,"Failed! :(");
	
	static_assert(IntListsEqual<IntList<2,1>,IntList<1,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,2,3>,IntList<1,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,3,2>,IntList<1,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,1,3>,IntList<1,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,3,1>,IntList<1,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<3,1,2>,IntList<1,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<3,2,1>,IntList<1,2>>::value==false,"Failed! :(");
	
	static_assert(IntListsEqual<IntList<2,1>,IntList<1,2,3>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,1>,IntList<1,3,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,1>,IntList<2,1,3>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,1>,IntList<2,3,1>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,1>,IntList<3,1,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,1>,IntList<3,2,1>>::value==false,"Failed! :(");
	
	static_assert(IntListsEqual<IntList<1,2,3>,IntList<2,1>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,3,2>,IntList<2,1>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,1,3>,IntList<2,1>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,3,1>,IntList<2,1>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<3,1,2>,IntList<2,1>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<3,2,1>,IntList<2,1>>::value==false,"Failed! :(");

	static_assert(IntListsEqual<IntList<1,2,3>,IntList<1,3,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,2,3>,IntList<2,1,3>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,2,3>,IntList<2,3,1>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,2,3>,IntList<3,1,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,2,3>,IntList<3,2,1>>::value==false,"Failed! :(");

	static_assert(IntListsEqual<IntList<1,3,2>,IntList<1,2,3>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,1,3>,IntList<1,2,3>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,3,1>,IntList<1,2,3>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<3,1,2>,IntList<1,2,3>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<3,2,1>,IntList<1,2,3>>::value==false,"Failed! :(");
	
	static_assert(IntListsEqual<IntList<1,3,2>,IntList<2,1,3>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,3,2>,IntList<2,3,1>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,3,2>,IntList<3,1,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<1,3,2>,IntList<3,2,1>>::value==false,"Failed! :(");
	
	static_assert(IntListsEqual<IntList<2,1,3>,IntList<1,3,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,3,1>,IntList<1,3,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<3,1,2>,IntList<1,3,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<3,2,1>,IntList<1,3,2>>::value==false,"Failed! :(");
	
	static_assert(IntListsEqual<IntList<2,1,3>,IntList<2,3,1>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,1,3>,IntList<3,1,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,1,3>,IntList<3,2,1>>::value==false,"Failed! :(");
	
	static_assert(IntListsEqual<IntList<2,3,1>,IntList<2,1,3>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<3,1,2>,IntList<2,1,3>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<3,2,1>,IntList<2,1,3>>::value==false,"Failed! :(");
		
	static_assert(IntListsEqual<IntList<2,3,1>,IntList<3,1,2>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<2,3,1>,IntList<3,2,1>>::value==false,"Failed! :(");
	
	static_assert(IntListsEqual<IntList<3,1,2>,IntList<2,3,1>>::value==false,"Failed! :(");
	static_assert(IntListsEqual<IntList<3,2,1>,IntList<2,3,1>>::value==false,"Failed! :(");
	
	static_assert(IntListsEqual<IntList<3,1,2>,IntList<3,2,1>>::value==false,"Failed! :(");
	
	static_assert(IntListsEqual<IntList<3,2,1>,IntList<3,1,2>>::value==false,"Failed! :(");
	
	// False assertion section :)
	
	/****************************************************************IntListsEqual :)****************************************************************/
	
	/****************************************************************IntListContains :)****************************************************************/
	
	// True assertion section :)
	
	static_assert(IntListContains<IntList<>>::value,"Failed! :(");
	static_assert(IntListContains<IntList<1>,1>::value,"Failed! :(");
	static_assert(IntListContains<IntList<1,2>,1,2>::value,"Failed! :(");
	static_assert(IntListContains<IntList<2,1>,2,1>::value,"Failed! :(");
	static_assert(IntListContains<IntList<1,2,3>,1,2,3>::value,"Failed! :(");
	static_assert(IntListContains<IntList<1,3,2>,1,3,2>::value,"Failed! :(");
	static_assert(IntListContains<IntList<2,1,3>,2,1,3>::value,"Failed! :(");
	static_assert(IntListContains<IntList<2,3,1>,2,3,1>::value,"Failed! :(");
	static_assert(IntListContains<IntList<3,1,2>,3,1,2>::value,"Failed! :(");
	static_assert(IntListContains<IntList<3,2,1>,3,2,1>::value,"Failed! :(");

	// True assertion section :)
	
	// False assertion section :)
	
	static_assert(IntListContains<IntList<>,1>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<>,1,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<>,2,1>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<>,1,2,3>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<>,1,3,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<>,2,1,3>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<>,2,3,1>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<>,3,1,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<>,3,2,1>::value==false,"Failed! :(");
	
	static_assert(IntListContains<IntList<1>>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,2>>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,1>>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,2,3>>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,3,2>>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,1,3>>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,3,1>>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<3,1,2>>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<3,2,1>>::value==false,"Failed! :(");

	static_assert(IntListContains<IntList<1,2>,2,1>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,2>,1,2,3>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,2>,1,3,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,2>,2,1,3>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,2>,2,3,1>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,2>,3,1,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,2>,3,2,1>::value==false,"Failed! :(");
	
	static_assert(IntListContains<IntList<2,1>,1,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,2,3>,1,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,3,2>,1,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,1,3>,1,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,3,1>,1,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<3,1,2>,1,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<3,2,1>,1,2>::value==false,"Failed! :(");
	
	static_assert(IntListContains<IntList<2,1>,1,2,3>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,1>,1,3,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,1>,2,1,3>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,1>,2,3,1>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,1>,3,1,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,1>,3,2,1>::value==false,"Failed! :(");
	
	static_assert(IntListContains<IntList<1,2,3>,2,1>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,3,2>,2,1>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,1,3>,2,1>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,3,1>,2,1>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<3,1,2>,2,1>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<3,2,1>,2,1>::value==false,"Failed! :(");

	static_assert(IntListContains<IntList<1,2,3>,1,3,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,2,3>,2,1,3>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,2,3>,2,3,1>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,2,3>,3,1,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,2,3>,3,2,1>::value==false,"Failed! :(");

	static_assert(IntListContains<IntList<1,3,2>,1,2,3>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,1,3>,1,2,3>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,3,1>,1,2,3>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<3,1,2>,1,2,3>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<3,2,1>,1,2,3>::value==false,"Failed! :(");
	
	static_assert(IntListContains<IntList<1,3,2>,2,1,3>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,3,2>,2,3,1>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,3,2>,3,1,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<1,3,2>,3,2,1>::value==false,"Failed! :(");
	
	static_assert(IntListContains<IntList<2,1,3>,1,3,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,3,1>,1,3,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<3,1,2>,1,3,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<3,2,1>,1,3,2>::value==false,"Failed! :(");
	
	static_assert(IntListContains<IntList<2,1,3>,2,3,1>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,1,3>,3,1,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,1,3>,3,2,1>::value==false,"Failed! :(");
	
	static_assert(IntListContains<IntList<2,3,1>,2,1,3>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<3,1,2>,2,1,3>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<3,2,1>,2,1,3>::value==false,"Failed! :(");
		
	static_assert(IntListContains<IntList<2,3,1>,3,1,2>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<2,3,1>,3,2,1>::value==false,"Failed! :(");
	
	static_assert(IntListContains<IntList<3,1,2>,2,3,1>::value==false,"Failed! :(");
	static_assert(IntListContains<IntList<3,2,1>,2,3,1>::value==false,"Failed! :(");
	
	static_assert(IntListContains<IntList<3,1,2>,3,2,1>::value==false,"Failed! :(");
	
	static_assert(IntListContains<IntList<3,2,1>,3,1,2>::value==false,"Failed! :(");
	
	// False assertion section :)
	
	/****************************************************************IntListContains :)****************************************************************/
	
	/****************************************************************IntListIndexEquals :)****************************************************************/
		
	// True assertion section :)
	
	static_assert(IntListIndexEquals<IntList<1>,0,1>::value,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2>,0,1>::value,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2>,1,2>::value,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3>,0,1>::value,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3>,1,2>::value,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3>,2,3>::value,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4>,0,1>::value,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4>,1,2>::value,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4>,2,3>::value,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4>,3,4>::value,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4,5>,0,1>::value,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4,5>,1,2>::value,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4,5>,2,3>::value,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4,5>,3,4>::value,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4,5>,4,5>::value,"Failed! :(");
	
	// True assertion section :)

	// Empty List Automatic false assertion :)
	
	static_assert(IntListIndexEquals<IntList<>,0,1>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<>,0,2>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<>,0,3>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<>,1,1>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<>,1,5>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<>,100,7>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<>,200,42>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<>,1000,-7>::value==false,"Failed! :(");
	
	// Empty List Automatic false assertion :)
	
	// False assertion section :)

	static_assert(IntListIndexEquals<IntList<1>,0,2>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2>,0,3>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2>,1,42>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3>,0,77>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3>,1,666>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3>,2,5>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4>,0,-4>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4>,1,1000>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4>,2,333>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4>,3,45125>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4,5>,0,0>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4,5>,1,1>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4,5>,2,-3>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4,5>,3,-4>::value==false,"Failed! :(");
	static_assert(IntListIndexEquals<IntList<1,2,3,4,5>,4,105>::value==false,"Failed! :(");
	
	// False assertion section :)
	
	/****************************************************************IntListIndexEquals :)****************************************************************/


}
	