//
// File:    TSVector.cc
// Project: TSVector
// 
// Author:  Cameron Bergoon
// Email:   cbergoon@gmail.com
//
// Date:    2-20-15
//
// Purpose: Implementation of a thread safe std::vector.
//

#ifndef TSVECTOR_H
#define TSVECTOR_H

#include <mutex>
#include <queue>
#include <condition_variable>

namespace TS { 

	template <class T> 
	class TSVector { 
	public:
		TSVector() : v(), m(), condVar() { }
		~TSVector() { }
		void pushBack(T t){
			std::lock_guard<std::mutex> lock(m);
			v.push_back(t);
		}	
		T &operator[](size_t index){
			std::unique_lock<std::mutex> lock(m);
			return v[index];
		}
		size_t getSize(){
			std::unique_lock<std::mutex> lock(m);
			return v.size();
		}
		bool isEmpty(){
			std::unique_lock<std::mutex> lock(m);
			return v.empty();
		}
	private: 
		std::vector<T> v;
		mutable std::mutex m;
		std::condition_variable condVar;
	};

}

#endif /* TSVECTOR_H */