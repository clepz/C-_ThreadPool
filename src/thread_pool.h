/*
 * thread_pool.cpp
 *
 *  Created on: Nov 16, 2020
 *      Author: clepz
 */

#ifndef TEST_H_
#define TEST_H_


#include <stddef.h>
#include <boost/thread/thread.hpp>
#include <boost/function.hpp>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

/*
std::atomic<int> bos(0);
std::atomic<int> dolu(0);
std::atomic<int> empty(0);
std::atomic<int> fonk(0);
std::atomic<int> once(0);
std::atomic<int> sonra(0);*/

namespace clepz {


	class thread_pool {

	private:
		size_t num_thread = 4;
		std::queue<boost::function<void()>> que;
		std::mutex que_mtx;
		std::mutex job_mtx;
		bool terminate_pool = false;
		bool join = false;
		std::condition_variable thread_cv;
		std::condition_variable job_cv;
		std::vector<boost::thread> thread_v;
		std::atomic<int> job_count;


		void pool_thread(void);


	public:
		thread_pool();
		thread_pool(int);
		~thread_pool();
		void add_function(boost::function<void()> fun);
		void wait_all_jobs();
		void join_all();



	};
}

#endif /* TEST_H_ */
