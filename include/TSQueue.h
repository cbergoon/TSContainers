//
// File:    TSQueue.cc
// Project: TSQueue
// 
// Author:  Cameron Bergoon
// Email:   cbergoon@gmail.com
//
// Date:    2-20-15
//
// Purpose: Implementation of a thread safe std::queue.
// Multi-Producer/Multi-Consumer
//

#ifndef TSQUEUE_H
#define TSQUEUE_H

#include <mutex>
#include <queue>
#include <condition_variable>

namespace TS{

	template <class T>
	class TSQueue {
	public:
		TSQueue() : q(), m(), condVar(){ }
		~TSQueue(){ }
		void enQueue(T t){
			std::lock_guard<std::mutex> lock(m);
			q.push(t);
			condVar.notify_one();
		}
		
		T deQueue(){
			std::unique_lock<std::mutex> lock(m);
			condVar.wait(lock, [&]() { return !q.empty(); });
			T val = q.front();
			q.pop();
			return val;
		}

		bool isEmpty(){
			std::unique_lock<std::mutex> lock(m);
			return q.empty();
		}
	private: 
		std::queue<T> q;
		mutable std::mutex m;
		std::condition_variable condVar;
	};

}

#endif /* TSQUEUE_H */