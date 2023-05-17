#include <Windows.h>

#include "Clock.h"


namespace df {

	Clock::Clock() {
		SYSTEMTIME now;
		GetSystemTime(&now);
		previous_time = (now.wMinute * 60 * 1000000)
			+ (now.wSecond * 1000000)
			+ (now.wMilliseconds * 1000);
	}
	long int Clock::delta() {
		SYSTEMTIME before;
		GetSystemTime(&before);
		previous_time = (before.wMinute * 60 * 1000000)
			+ (before.wSecond * 1000000)
			+ (before.wMilliseconds * 1000);
		return previous_time;
	}
	long int Clock::split() const {
		SYSTEMTIME after;

		long int after_time;
		GetSystemTime(&after);
		after_time = (after.wMinute * 60 * 1000000)
			+ (after.wSecond * 1000000)
			+ (after.wMilliseconds * 1000);

		return after_time - previous_time;
	}
}