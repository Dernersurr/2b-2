# pragma once
#ifndef __SINGLETON_H__
#define __SINGLETON_H__


namespace df {

	class Singleton {

	private:
		Singleton();
		Singleton(Singleton const& copy);
		void operator=(Singleton const& assign);
	public:
		static Singleton& getInstance();
	};

	Singleton& Singleton::getInstance() {
		static Singleton single;
		return single;
	}
}
#endif 