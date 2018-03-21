#include "headers.h"

template<typename Fun,typename... Args>
std::future<decltype(std::invoke_result<Fun,Args&&...>::type)> spawn_task ( Fun && f, Args && ...arg){
	using result_type = typedef std::invoke_result<Fun(Args&&...)::type;
	std::promise<result_type(arg&&...)> task(std::move(f));
	std::future<result_type> f(task.get_future());
	std::thread t(std::move(f),std::move(arg...));
	t.detach();
	return f;
}
