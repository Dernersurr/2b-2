# pragma once
#ifndef __EVENT_H__
#define __EVENT_H__

#include <string>

const std::string UNDEFINED_EVENT = "df::undefined";

namespace df {
	class Event {
	private:
		std::string event_type;

	public:
		Event();
		virtual ~Event();

		void setType(std::string new_type);

		std::string getType() const;
	};
}
#endif // __EVENT_H__