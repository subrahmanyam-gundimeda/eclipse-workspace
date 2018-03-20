#Specify the version being used as well as language
 cmake_minimum_required(VERSION 2.6)

#Name your project here
 project(ConcurrencyInAction)

#Add options to the compiler
add_definitions(-std=c++17 )

#Specify executable name and dependencies
add_executable(executable src/main.cpp)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

#link libraries
target_link_libraries(executable Threads::Threads)

#include search directory
include_directories(includes)
#include_libraries(pthread)

#Find all C++ main source files and execute them one by one
FILE(GLOB main_src src/*cc)
#build individual executables
FOREACH(main_exe ${main_src})
	get_filename_component(exe ${main_exe} NAME_WE) #Get full name without dir name
	MESSAGE(STATUS "New Executable is==>" ${exe})
	add_executable(${exe} ${main_exe})
	target_link_libraries(${exe} MyLib)
ENDFOREACH()


