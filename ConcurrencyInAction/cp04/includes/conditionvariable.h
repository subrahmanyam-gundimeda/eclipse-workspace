/*
 * conditionvariable.h
 *
 *  Created on: Feb 22, 2018
 *      Author: subbu
 */

#ifndef CONDITIONVARIABLE_H_
#define CONDITIONVARIABLE_H_
#include "headers.h"
class cConditionVariable{
public:
	cConditionVariable():items_finished(false){}
	void prepare_data(){
		for(auto i:{1,2,3,4,5,6}){
			std::async([this,i](){std::launch::async,
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			std::lock_guard<std::mutex> lg(mtx);
			shared_data.push_back(i);
			cv.notify_one();
			});

		}
		items_finished = true;
	}

	void process_data(){
		while(true ){

			std::unique_lock<std::mutex> ul(mtx);
			cv.wait(ul,[this](){return !shared_data.empty();});
			int data = shared_data.at(0);;
			shared_data.pop_back();
			std::cout<<"\n got it:"<<data;
			ul.unlock();

			if(items_finished)
				break;
		}
	}

	void operator()(){
		std::vector<std::thread>  vThreads;

		vThreads.emplace_back(std::thread(&cConditionVariable::process_data,this));
		vThreads.emplace_back(std::thread(&cConditionVariable::prepare_data,this));
		std::for_each(vThreads.begin(),vThreads.end(),std::mem_fn(&std::thread::join));
		std::cout<<"\n Reached the end";
	}
private:
	std::vector<int> shared_data;
	std::mutex mtx;
	std::condition_variable cv;
	bool items_finished ;
};



#endif /* CONDITIONVARIABLE_H_ */
