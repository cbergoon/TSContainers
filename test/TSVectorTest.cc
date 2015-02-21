//
// File:    TSVectorTest.cc
// Project: TSVectorTest
// 
// Author:  Cameron Bergoon
// Email:   cbergoon@gmail.com
//
// Date:    2-20-15
//
// Purpose: Test driver for the thread safe vector class.
//

#include <iostream>
#include <thread>
#include <exception>

#include "TSVector.h"

#define SUCCESS 0
#define FAILURE -1 
#define NUM_THREADS 4

void addToVector(TS::TSVector<int> &v, int i);

int main(void) { 

	//Create an instance of a thread safe queue

	TS::TSVector<int> tsv;

	//Spool up testing threads

	std::vector<std::thread> threads;
	for(int i = 0; i < NUM_THREADS; i++){
		threads.push_back(std::thread(addToVector, std::ref(tsv), i));
	}

	//Join all threads

	for(int i = 0; i < NUM_THREADS; i++){
		threads[i].join();
	}

	//Display what ended up in the queue

	for(int i = 0; i < tsv.getSize(); i++){
		std::cout << tsv[i] << std::endl;
	}

	return SUCCESS;
}

void addToVector(TS::TSVector<int> &v, int i){
	v.pushBack(i);
	return;
}