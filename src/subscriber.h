#pragma once
#include <list>


template<class EVENT_TYPE, class EVENT_CLASS>
class Subscriber {
public:
	virtual void processEvent(const EVENT_CLASS* e) = 0;
	virtual std::list<EVENT_TYPE> acceptTypes() const = 0;
};

