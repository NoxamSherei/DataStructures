#pragma once
#include "FixedArray.h"
//Queue - Structure First In First Out (FIFO)
template<int maxSize>
class Queue {
private:
	FixArray<int, maxSize> queue;
	int acctualQueueMembers=0;
public:
	bool enqueue(int member) {
		if (acctualQueueMembers < maxSize) {
			queue[acctualQueueMembers] = member;
			acctualQueueMembers++;
			return true;
		}
		return false;
	}
	int dequeue() {
		if (acctualQueueMembers != 0) {
			int temp = queue[0];
			for (size_t i = 0; i < acctualQueueMembers-1; i++) {
				queue[i] = queue[i + 1];
			}
			acctualQueueMembers--;
			return temp;
		}
		return NULL;
	}
	int peek() {
		return queue[0];
	}
	void print(std::ostringstream& os) {
		os << "queue << ";
		queue.print(os,acctualQueueMembers);
	}
};