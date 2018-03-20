/*
 * SmartMutex.h
 *
 *  Created on: Feb 19, 2018
 *      Author: subbu
 */

#ifndef SMARTMUTEX_H_
#define SMARTMUTEX_H_
#include "headers.h"

struct cMutex{
	std::unique_lock<std::mutex> get_lock(){
		std::unique_lock<std::mutex> ul(local_mutex);
		std::cout<<"\n Yes we got the mutex for ::"<<std::this_thread::get_id();
		return std::move(ul);
	}

private:
	   std::mutex local_mutex;

};

 //std::mutex cMutex::local_mutex;


#endif /* SMARTMUTEX_H_ */
