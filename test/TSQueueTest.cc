//
// File:    TSQueueTest.cc
// Project: TSQueue
// 
// Author:  Cameron Bergoon
// Email:   cbergoon@gmail.com
//
// Date:    2-20-15
//
// Purpose: Test driver for the thread safe queue class.
//

#include <iostream>
#include <thread>
#include <exception>

#include "TSQueue.h"

#define SUCCESS 0
#define FAILURE -1 
#define NUM_THREADS 4

void addToQueue(TS::TSQueue<int> &q, int i);

int main(void) { 

	//Create an instance of a thread safe queue

	TS::TSQueue<int> tsq;

	//Spool up testing threads

	std::vector<std::thread> threads;
	for(int i = 0; i < NUM_THREADS; i++){
		threads.push_back(std::thread(addToQueue, std::ref(tsq), i));
	}

	//Join all threads

	for(int i = 0; i < NUM_THREADS; i++){
		threads[i].join();
	}

	//Display what ended up in the queue

	while(!tsq.isEmpty()){
		std::cout << tsq.deQueue() << std::endl;
	}

	return SUCCESS;
}

void addToQueue(TS::TSQueue<int> &q, int i){
	q.enQueue(i);
	return;
}