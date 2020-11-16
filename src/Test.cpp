//============================================================================
// Name        : Test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <boost/chrono.hpp>
#include "thread_pool.h"


void sayi_ekle(int a){
	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	std::cout<<"eklendi"<<std::endl;;
}

int main() {


	clepz::thread_pool pool(4);
	//boost::this_thread::sleep_for(boost::chrono::milliseconds(2));

	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	pool.add_function(boost::bind(sayi_ekle,1));
	//boost::this_thread::sleep_for(boost::chrono::milliseconds(200));


	pool.wait_all_jobs();

	pool.join_all();

	std::cout<<"bitti..."<<std::endl;

	return 0;
}
