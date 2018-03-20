//============================================================================
// Name        : FirstTestProject.cpp
// Author      : Subrahmanyam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "mutexfile.h"
#include "SmartMutex.h"
#include "call_once.h"
#include "hierarchical_mutex.h"
#include "conditionvariable.h"
int main() {
	//-------------------------------------------------------------
	// The below code is for testing mutex race condition.
	//-------------------------------------------------------------
#ifdef RACECOND
	clist<int> obj;
	obj.addData(1);
	obj.addData(4);
	obj.addData(3);
	obj.addData(2);

	obj.caller(malicious_function<std::list<int>>);
	std::cout<<obj.Contains(1)<<std::endl;
	std::cout<<obj.Contains(2)<<std::endl;
#endif

	//-------------------------------------------------------------
	// This below code demonstrates mutex scope.
	//-------------------------------------------------------------
#ifdef SCOPE
	cMutex obj1,obj2,obj3;
	std::unique_lock<std::mutex> ul1(obj1.get_lock());
	std::unique_lock<std::mutex> ul2(obj1.get_lock());
	std::cout<<"\n does u1 "<<ul1.owns_lock();
	std::cout<<"\n does u2 "<<ul2.owns_lock();

	std::unique_lock<std::mutex> ul3{obj3.get_lock()};*/
#endif
	//-------------------------------------------------------------
	//This below code demonstrates call_once
	//-------------------------------------------------------------
#ifdef CALLONCE
	spawn_threads();
#endif

	//-------------------------------------------------------------
	//This below code demonstrates Hierarchical mutex call implementaion
	// eg:Can be used for multiple layers.
	//-------------------------------------------------------------
#ifdef HIERARCHICAL_MUTEX
	do_something();
	std::cout<<"\n End of proper call ";
	do_something2();
#endif


#ifndef CONDITION_VARIABLE
	cConditionVariable cv;
	cv();

#endif

	return 0;
}
