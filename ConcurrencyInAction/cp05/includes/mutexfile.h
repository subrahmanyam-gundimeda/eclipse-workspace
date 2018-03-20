/*
 * mutexfile.h
 *
 *  Created on: Feb 16, 2018
 *      Author: subbu
 */

#ifndef MUTEXFILE_H_
#define MUTEXFILE_H_
#include "headers.h"
template<typename T>
class clist{
public:
	//template<typename T>
	void addData(T ivalue){
		std::lock_guard<std::mutex> lck(DataMutex);
		wholeData.push_back(ivalue);
	}
	bool Contains(T ivalue){
		std::lock_guard<std::mutex> lck(DataMutex);
		return std::find(wholeData.begin(),wholeData.end(),ivalue) != wholeData.end();
	}
	template<typename FunctionCall>
	void caller(FunctionCall f){
		f(wholeData);
	}
private:
	std::list<T> wholeData;
	std::mutex DataMutex;
};

template<typename T>
void malicious_function(T & sharedData){
	T* ptr = &sharedData;
	ptr->pop_front();
	std::cout<<"\n Finally we got the reference so we can alter data\n";
}


#endif /* MUTEXFILE_H_ */
