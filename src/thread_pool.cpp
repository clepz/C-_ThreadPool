/*
 * thread_pool.cpp
 *
 *  Created on: Nov 16, 2020
 *      Author: clepz
 */
#include "thread_pool.h"


clepz::thread_pool::thread_pool(){
	job_count = 0;
	for(size_t i = 0 ; i < num_thread ; i ++){
		thread_v.push_back(boost::thread(boost::bind(&clepz::thread_pool::pool_thread,this)));
	}
}

clepz::thread_pool::thread_pool(int num_thread){
	job_count = 0;
	this->num_thread = num_thread;
	for(size_t i = 0 ; i < num_thread ; i ++){
		thread_v.push_back(boost::thread(boost::bind(&clepz::thread_pool::pool_thread,this)));
	}
}

clepz::thread_pool::~thread_pool(){

}

void clepz::thread_pool::pool_thread(void){

	while(!terminate_pool) {
		boost::function<void()> job;
		{
			std::unique_lock<std::mutex> u_lock (que_mtx);
			thread_cv.wait(u_lock, [&]() { return !que.empty() || terminate_pool; });
			if (!que.empty()){
				job = que.front();
				que.pop();
			}
			else{
				std::cout<<"else"<<std::endl;
				continue;}
		}
		job();
		job_count--;
		job_cv.notify_one();

	}

}

void clepz::thread_pool::add_function(boost::function<void()> fun){
	{
		std::unique_lock<std::mutex>(que_mtx);
		que.push(fun);
		job_count++;
	}
	thread_cv.notify_one();
}


void clepz::thread_pool::wait_all_jobs(){
	std::unique_lock<std::mutex> job_lock(job_mtx);
	std::cout<<"girdi"<<std::endl;
	job_cv.wait(job_lock, [&]() {return job_count == 0;});
	std::cout<<"j_c: "<<job_count<<std::endl;

}

void clepz::thread_pool::join_all(){
	terminate_pool = true;
	thread_cv.notify_all();
	for (boost::thread &t : thread_v){
		t.join();
	}
	thread_v.clear();
}
