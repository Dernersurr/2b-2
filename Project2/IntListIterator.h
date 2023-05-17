# pragma once
#ifndef __INT_LIST_ITERATOR_H__
#define __INT_LIST_ITERATOR_H__


#include "IntList.h"

namespace df {
	class IntListIterator {
	private:
		const IntList *p_list;
		int index;
	public:
		IntListIterator(const IntList *p_l) {
			p_list = p_l;
			first();
		}
		void first() {
			index = 0;
		}
		void next() {
			if (index < p_list->count)
				index++;
		}
		bool isDone() {
			return (index == p_list->count);
		}
		int currentItem() {
			return p_list->item[index];
		}
	};
}
#endif