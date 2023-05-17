# pragma once
#ifndef __OBJECT_LIST_H__
#define __OBJECT_LIST_H__

#include "Object.h"
#include "ObjectListIterator.h"
const int MAX_OBJECTS = 5000;

namespace df {
	class ObjectIterator;

	class ObjectList {
	private:
		int m_count;
		Object* m_p_obj[MAX_OBJECTS];

	public:
		friend class ObjectListIterator;

		ObjectList();

		int insert(Object* p_o);

		int remove(Object* p_o);

		void clear();

		int getCount() const;

		bool isEmpty() const;

		bool isFull() const;


	};


}
#endif