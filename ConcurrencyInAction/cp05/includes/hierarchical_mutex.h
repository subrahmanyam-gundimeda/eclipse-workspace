/*
 * hierarchical_mutex.h
 *
 *  Created on: Feb 21, 2018
 *      Author: subbu
 */

#ifndef HIERARCHICAL_MUTEX_H_
#define HIERARCHICAL_MUTEX_H_
#include "headers.h"

class cHierarchical_mutex{
	std::mutex local_mutex;
	long previous_mutex_value;
	long const initiated_mutex_value;
	static thread_local long current_Requested_mutex_value;
public:
	explicit cHierarchical_mutex(long const mutex_value):initiated_mutex_value(mutex_value),previous_mutex_value(0){
		std::cout<<"\n mutex triggered with :"<<mutex_value;
	}
	void check_for_violations(){
		if(current_Requested_mutex_value <= initiated_mutex_value){
			throw std::logic_error("order of lock on mutex is invalid.");
		}
	}
	void update_mutex_values(){
		previous_mutex_value = current_Requested_mutex_value;
		current_Requested_mutex_value = initiated_mutex_value;
		std::cout<<"\n current requested and value of mutex became:"<<current_Requested_mutex_value;
	}
	void lock(){
		check_for_violations();
		local_mutex.lock();
		update_mutex_values();
	}
	void unlock(){
		current_Requested_mutex_value = previous_mutex_value;
		local_mutex.unlock();
		std::cout<<"\n mutex value is been reset with:"<<current_Requested_mutex_value;
	}
	bool try_lock(){
		check_for_violations();
		if(!local_mutex.try_lock())
			return false;
		update_mutex_values();
	}
};
thread_local long cHierarchical_mutex::current_Requested_mutex_value(99999);
cHierarchical_mutex higher_layer_mutex(10000);
cHierarchical_mutex lower_layer_mutex(5000);
cHierarchical_mutex service_layer_mutex(8000);


void other_stuff(){
	std::lock_guard<cHierarchical_mutex> lk(lower_layer_mutex);
	std::cout<<"\n Reached the mutex call in proper order";

}
void do_something(){
	std::lock_guard<cHierarchical_mutex> lk(higher_layer_mutex);
	other_stuff();
}
void optional_call(){

	std::lock_guard<cHierarchical_mutex> lk(service_layer_mutex);
	std::cout<<"\n Not supposed to come here";
	std::cout<<"\n Ready get throw exception";
	std::lock_guard<cHierarchical_mutex> lkk(higher_layer_mutex);
	other_stuff();
}
void do_something2(){
	optional_call();

}
#endif /* HIERARCHICAL_MUTEX_H_ */
