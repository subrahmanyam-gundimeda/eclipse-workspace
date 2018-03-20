/*
 * call_once.h
 *
 *  Created on: Feb 20, 2018
 *      Author: subbu
 */

#ifndef CALL_ONCE_H_
#define CALL_ONCE_H_
#include "headers.h"

class cinstance{
public:
	void create_memory(){
		if(!sp){
			std::cout<<"\n creating the memory";
			sp = std::make_unique<int>(12);
		}
		std::cout<<"\n Value present in memory ::"<<*sp;
	}

private:
	std::shared_ptr<int> sp;
};



void call_once_flag(){
	 cinstance obj;
	static /*thread_local*/  std::once_flag called;
	std::cout<<"\n Calling method::"<<std::this_thread::get_id()<<std::endl;
	std::call_once(called,&cinstance::create_memory,obj);
}

void spawn_threads(){
	try{
	std::vector<std::thread> vThreads;
    for(std::size_t i =0;i<5;++i)
    	vThreads.emplace_back(std::thread(call_once_flag));

    std::for_each(vThreads.begin(),vThreads.end(),std::mem_fn(&std::thread::join));
	}
	catch(...){
		std::cout<<"\n caught unknown exception";
	}
}

#endif /* CALL_ONCE_H_ */
