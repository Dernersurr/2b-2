#include "ObjectList.h"


namespace df {
	ObjectList::ObjectList() {
		m_count = 0;
	}
	int ObjectList::insert(Object* p_o) {
		if (isFull()) {
			return false;
		}
		m_p_obj[m_count] = p_o;
		m_count++;
		return true;
	}
	int ObjectList::remove(Object* p_o) {
		for (int i = 0; i < m_count; i++) {
			if (m_p_obj[i] == p_o) {
				for (int j = i; j < m_count - 1; j++) {
					m_p_obj[j] = m_p_obj[j + 1];
				}
				m_count--;
				return true;
			}
		}
		return false;
	}

	void ObjectList::clear() {
		m_count = 0;
	}
	int ObjectList::getCount() const {
		return m_count;
	}
	bool ObjectList::isEmpty() const {
		if (m_count == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool ObjectList::isFull() const {
		if (m_count == MAX_OBJECTS) {
			return true;
		}
		else {
			return false;
		}
	}

}