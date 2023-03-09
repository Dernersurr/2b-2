# pragma once
#ifndef __INT_LIST_H__
#define __INT_LIST_H__



#include "IntListIterator.h"
friend class IntListIterator;
namespace df {
	
	const int MAX = 100;

	class IntList {
	private:
		int list[MAX];
		int count;

	public:
		IntList() {
			count = 0;
		}

		void clear() {
			count = 0;
	}

		bool insert(int x) {
			if (count == MAX)
				return false;
			list[count] = x;
			count++;
			return true;
	}
		bool remove(int x) {
			for (int i = 0; i < count; i++) {
				if (list[i] == x) {
					for (int j = i; j < count - 1; j++)
						list[j] = list[j + 1];
					count--;
					return true;
				}
			}
			return false;
		}

	};

}
#endif